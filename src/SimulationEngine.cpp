#include "SimulationEngine.h"

SimulationEngine::SimulationEngine(QObject *parent) : QObject(parent)
{
    m_timer = new QTimer(this);
    m_timer->setInterval(50);
    connect(m_timer, &QTimer::timeout, this, &SimulationEngine::tick);
    m_timer->start();
}

void SimulationEngine::setState(MachineState s)
{
    if (m_state == s) return;
    m_state = s;
    emit stateChanged(static_cast<int>(s));
}

void SimulationEngine::start()
{
    if (m_state == Idle)
        setState(Running);
}

void SimulationEngine::stop()
{
    if (m_state == Running) {
        m_rollerRunning = false;
        m_rollerDir = 0;
        for (int i = 0; i < 4; ++i) m_motorDir[i] = 0;
        setState(Idle);
    }
}

void SimulationEngine::needleHighStop()
{
    if (m_state == Running)
        setState(NeedleHigh);
}

void SimulationEngine::plateReturnZero()
{
    if (m_state == Running || m_state == Idle)
        setState(PlateResetting);
}

void SimulationEngine::clearAlarm()
{
    if (m_state == Alarm)
        setState(Idle);
}

void SimulationEngine::resetClothLength()
{
    m_clothLength = 0.0;
    emit clothLengthChanged(m_clothLength);
}

void SimulationEngine::rollerForward()
{
    m_rollerRunning = true;
    m_rollerDir = 1;
}

void SimulationEngine::rollerReverse()
{
    m_rollerRunning = true;
    m_rollerDir = -1;
}

void SimulationEngine::setNeedleSpeed(double v) { m_needleSpeed = v; }
void SimulationEngine::setClothSpeed(double v) { m_clothSpeed = v; }
void SimulationEngine::setNeedleDepth(double v) { m_needleDepth = v; }
void SimulationEngine::setPlateGap(double v) { m_plateGapParam = v; }

void SimulationEngine::motorAccel(int id)
{
    if (id < 0 || id > 3) return;
    m_motorSpeed[id] += (id >= 2) ? 1.0 : 2.0;
    emit motorSpeedChanged(id, m_motorSpeed[id]);
}

void SimulationEngine::motorDecel(int id)
{
    if (id < 0 || id > 3) return;
    m_motorSpeed[id] = qMax(0.0, m_motorSpeed[id] - ((id >= 2) ? 1.0 : 2.0));
    emit motorSpeedChanged(id, m_motorSpeed[id]);
}

void SimulationEngine::motorWrite(int id, double speed)
{
    if (id < 0 || id > 3) return;
    m_motorSpeed[id] = speed;
    emit motorSpeedChanged(id, m_motorSpeed[id]);
}

void SimulationEngine::motorForward(int id)
{
    if (id < 0 || id > 3) return;
    m_motorDir[id] = 1;
}

void SimulationEngine::motorReverse(int id)
{
    if (id < 0 || id > 3) return;
    m_motorDir[id] = -1;
}

void SimulationEngine::zeroCoord(int axis)
{
    switch (axis) {
    case 0: m_needleCoord = 0.0; break;
    case 1: m_upperCoord = 0.0; break;
    case 2: m_lowerCoord = 0.0; break;
    }
    emit coordsUpdated(m_needleCoord, m_upperCoord, m_lowerCoord);
}

void SimulationEngine::tick()
{
    const double dt = 0.05; // 50ms in seconds

    if (m_state == Running) {
        // Cloth length accumulates
        m_clothLength += m_clothSpeed * dt / 100.0; // cm/s -> m
        emit clothLengthChanged(m_clothLength);

        // Plate positions drift slightly to simulate motion
        m_upperPlatePos += 0.002 * dt;
        m_lowerPlatePos -= 0.001 * dt;

        // Needle coord accumulates based on needle speed
        m_needleCoord += m_needleSpeed * dt / 60.0 * 0.01;
    }

    if (m_state == NeedleHigh) {
        // Simulate needle moving to high position, then return to idle
        m_needleCoord += 0.5;
        setState(Idle);
    }

    if (m_state == PlateResetting) {
        // Simulate plates returning to zero
        m_upperPlatePos *= 0.5;
        m_lowerPlatePos *= 0.5;
        if (qAbs(m_upperPlatePos) < 0.01 && qAbs(m_lowerPlatePos) < 0.01) {
            m_upperPlatePos = 0.0;
            m_lowerPlatePos = 0.0;
            setState(Idle);
        }
    }

    // Manual motor simulation
    for (int i = 0; i < 4; ++i) {
        if (m_motorDir[i] != 0) {
            double delta = m_motorSpeed[i] * dt * m_motorDir[i];
            switch (i) {
            case 0: m_needleCoord += delta / 60.0; break;
            case 1: m_clothLength += delta * 0.01; break; // cm/s -> m
            case 2: m_upperPlatePos += delta / 60.0; break; // cm/min -> cm
            case 3: m_lowerPlatePos += delta / 60.0; break;
            }
        }
    }

    // Roller simulation
    if (m_rollerRunning && m_rollerDir != 0) {
        m_clothLength += 8.33 * dt * m_rollerDir / 100.0;
    }

    emit valuesUpdated(m_upperPlatePos, m_lowerPlatePos, m_upperPlatePos - m_lowerPlatePos);
    emit coordsUpdated(m_needleCoord, m_upperCoord, m_lowerCoord);
}
