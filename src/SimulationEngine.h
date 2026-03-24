#pragma once
#include <QObject>
#include <QTimer>

class SimulationEngine : public QObject
{
    Q_OBJECT
public:
    enum MachineState { Idle, Running, NeedleHigh, PlateResetting, Alarm };
    Q_ENUM(MachineState)

    explicit SimulationEngine(QObject *parent = nullptr);

    MachineState state() const { return m_state; }
    double upperPlatePos() const { return m_upperPlatePos; }
    double lowerPlatePos() const { return m_lowerPlatePos; }
    double plateGap() const { return m_upperPlatePos - m_lowerPlatePos; }
    double clothLength() const { return m_clothLength; }
    double needleCoord() const { return m_needleCoord; }
    double upperCoord() const { return m_upperCoord; }
    double lowerCoord() const { return m_lowerCoord; }

public slots:
    // State control
    void start();
    void stop();
    void needleHighStop();
    void plateReturnZero();
    void clearAlarm();

    // Cloth
    void resetClothLength();
    void rollerForward();
    void rollerReverse();

    // Parameter setters
    void setNeedleSpeed(double v);
    void setClothSpeed(double v);
    void setNeedleDepth(double v);
    void setPlateGap(double v);

    // Motor control (0=needle, 1=cloth, 2=upperPlate, 3=lowerPlate)
    void motorAccel(int motorId);
    void motorDecel(int motorId);
    void motorWrite(int motorId, double speed);
    void motorForward(int motorId);
    void motorReverse(int motorId);

    // Coordinate zero (0=needle, 1=upper, 2=lower)
    void zeroCoord(int axis);

signals:
    void stateChanged(int state);
    void valuesUpdated(double upperPos, double lowerPos, double gap);
    void clothLengthChanged(double length);
    void coordsUpdated(double needle, double upper, double lower);
    void motorSpeedChanged(int motorId, double speed);

private slots:
    void tick();

private:
    void setState(MachineState s);

    MachineState m_state = Idle;
    QTimer *m_timer;

    // Physical quantities
    double m_upperPlatePos = 0.0;
    double m_lowerPlatePos = 0.0;
    double m_clothLength = 100.0;

    // Coordinates (alarm/reset page)
    double m_needleCoord = 68.254;
    double m_upperCoord = 0.0;
    double m_lowerCoord = 0.0;

    // Parameters
    double m_needleSpeed = 800.0;   // rpm
    double m_clothSpeed = 3.0;      // cm/s
    double m_needleDepth = 0.55;    // cm
    double m_plateGapParam = 0.50;  // cm

    // Motor speeds (manual debug)
    double m_motorSpeed[4] = {10.0, 8.0, 20.0, 6.0};
    int m_motorDir[4] = {0, 0, 0, 0}; // 0=stopped, 1=forward, -1=reverse

    bool m_rollerRunning = false;
    int m_rollerDir = 0; // 1=forward, -1=reverse
};
