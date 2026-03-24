#include "MainWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    setStyleSheet(globalStyleSheet());

    m_engine = new SimulationEngine(this);

    m_titleBar = new TitleBar();
    m_titleBar->setObjectName("titleBar");

    m_statusBar = new StatusBar();
    m_statusBar->setObjectName("statusBar");

    m_sidePanel = new SidePanel();
    m_sidePanel->setObjectName("sidePanel");

    m_stack = new QStackedWidget();
    m_stack->setObjectName("pageStack");

    m_standardPage = new StandardModePage();
    m_intermittentPage = new IntermittentModePage();
    m_gradientPage = new GradientModePage();
    m_manualDebugPage = new ManualDebugPage();
    m_factoryPage = new FactorySettingsPage();
    m_alarmPage = new AlarmResetPage();

    m_stack->addWidget(m_standardPage);
    m_stack->addWidget(m_intermittentPage);
    m_stack->addWidget(m_gradientPage);
    m_stack->addWidget(m_manualDebugPage);
    m_stack->addWidget(m_factoryPage);
    m_stack->addWidget(m_alarmPage);

    connect(m_factoryPage, &FactorySettingsPage::returnRequested, this, [this]() { switchPage(5); });
    connect(m_alarmPage, &AlarmResetPage::gearSettingsRequested, this, [this]() { switchPage(4); });

    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    mainLayout->addWidget(m_titleBar);

    auto *middleLayout = new QHBoxLayout();
    middleLayout->setContentsMargins(0, 0, 0, 0);
    middleLayout->setSpacing(0);
    middleLayout->addWidget(m_stack, 1);
    middleLayout->addWidget(m_sidePanel);

    mainLayout->addLayout(middleLayout, 1);
    mainLayout->addWidget(m_statusBar);

    connect(m_sidePanel, &SidePanel::pageSelected, this, &MainWindow::switchPage);
    switchPage(0);

    connectEngine();
}

void MainWindow::switchPage(int index)
{
    m_stack->setCurrentIndex(index);
    m_sidePanel->setCurrentIndex(index);
}

void MainWindow::connectEngine()
{
    // --- Engine state -> TitleBar ---
    connect(m_engine, &SimulationEngine::stateChanged, this, [this](int s) {
        switch (static_cast<SimulationEngine::MachineState>(s)) {
        case SimulationEngine::Idle:           m_titleBar->setStatus("待机中||"); break;
        case SimulationEngine::Running:        m_titleBar->setStatus("运行中▶"); break;
        case SimulationEngine::NeedleHigh:     m_titleBar->setStatus("针停高位⏸"); break;
        case SimulationEngine::PlateResetting: m_titleBar->setStatus("压板回零↺"); break;
        case SimulationEngine::Alarm:          m_titleBar->setStatus("报警⚠"); break;
        }
    });

    // --- Engine values -> StatusBar ---
    connect(m_engine, &SimulationEngine::valuesUpdated, this,
        [this](double upper, double lower, double gap) {
        m_statusBar->setUpperPosition(upper);
        m_statusBar->setLowerPosition(lower);
        m_statusBar->setGap(gap);
    });

    // --- Engine cloth length -> StandardModePage ---
    connect(m_engine, &SimulationEngine::clothLengthChanged, this, [this](double len) {
        m_standardPage->clothLengthEdit()->setText(QString::number(len, 'f', 2));
    });

    // --- Engine coords -> AlarmResetPage ---
    connect(m_engine, &SimulationEngine::coordsUpdated, this,
        [this](double needle, double upper, double lower) {
        m_alarmPage->needleCoordEdit()->setText(QString::number(needle, 'f', 3));
        m_alarmPage->upperCoordEdit()->setText(QString::number(upper, 'f', 2));
        m_alarmPage->lowerCoordEdit()->setText(QString::number(lower, 'f', 2));
    });

    // === StandardModePage buttons ===
    connect(m_standardPage->startBtn(), &QPushButton::clicked, m_engine, &SimulationEngine::start);
    connect(m_standardPage->stopBtn(), &QPushButton::clicked, m_engine, &SimulationEngine::stop);
    connect(m_standardPage->needleHighBtn(), &QPushButton::clicked, m_engine, &SimulationEngine::needleHighStop);
    connect(m_standardPage->plateReturnBtn(), &QPushButton::clicked, m_engine, &SimulationEngine::plateReturnZero);
    connect(m_standardPage->resetLengthBtn(), &QPushButton::clicked, m_engine, &SimulationEngine::resetClothLength);
    connect(m_standardPage->rollerForwardBtn(), &QPushButton::clicked, m_engine, &SimulationEngine::rollerForward);
    connect(m_standardPage->rollerReverseBtn(), &QPushButton::clicked, m_engine, &SimulationEngine::rollerReverse);

    // Parameter edits -> engine
    connect(m_standardPage->needleSpeedEdit(), &QLineEdit::editingFinished, this, [this]() {
        m_engine->setNeedleSpeed(m_standardPage->needleSpeedEdit()->text().toDouble());
    });
    connect(m_standardPage->clothSpeedEdit(), &QLineEdit::editingFinished, this, [this]() {
        m_engine->setClothSpeed(m_standardPage->clothSpeedEdit()->text().toDouble());
    });
    connect(m_standardPage->needleDepthEdit(), &QLineEdit::editingFinished, this, [this]() {
        m_engine->setNeedleDepth(m_standardPage->needleDepthEdit()->text().toDouble());
    });
    connect(m_standardPage->plateGapEdit(), &QLineEdit::editingFinished, this, [this]() {
        m_engine->setPlateGap(m_standardPage->plateGapEdit()->text().toDouble());
    });
    connect(m_standardPage->speedWriteBtn(), &QPushButton::clicked, this, [this]() {
        m_engine->motorWrite(1, m_standardPage->manualClothSpeedEdit()->text().toDouble());
    });

    // === IntermittentModePage buttons ===
    connect(m_intermittentPage->startBtn(), &QPushButton::clicked, m_engine, &SimulationEngine::start);
    connect(m_intermittentPage->stopBtn(), &QPushButton::clicked, m_engine, &SimulationEngine::stop);
    connect(m_intermittentPage->needleHighBtn(), &QPushButton::clicked, m_engine, &SimulationEngine::needleHighStop);
    connect(m_intermittentPage->plateReturnBtn(), &QPushButton::clicked, m_engine, &SimulationEngine::plateReturnZero);

    connect(m_intermittentPage->needleSpeedEdit(), &QLineEdit::editingFinished, this, [this]() {
        m_engine->setNeedleSpeed(m_intermittentPage->needleSpeedEdit()->text().toDouble());
    });
    connect(m_intermittentPage->clothSpeedEdit(), &QLineEdit::editingFinished, this, [this]() {
        m_engine->setClothSpeed(m_intermittentPage->clothSpeedEdit()->text().toDouble());
    });
    connect(m_intermittentPage->needleDepthEdit(), &QLineEdit::editingFinished, this, [this]() {
        m_engine->setNeedleDepth(m_intermittentPage->needleDepthEdit()->text().toDouble());
    });
    connect(m_intermittentPage->plateGapEdit(), &QLineEdit::editingFinished, this, [this]() {
        m_engine->setPlateGap(m_intermittentPage->plateGapEdit()->text().toDouble());
    });

    // === GradientModePage buttons ===
    connect(m_gradientPage->startBtn(), &QPushButton::clicked, m_engine, &SimulationEngine::start);
    connect(m_gradientPage->stopBtn(), &QPushButton::clicked, m_engine, &SimulationEngine::stop);
    connect(m_gradientPage->needleHighBtn(), &QPushButton::clicked, m_engine, &SimulationEngine::needleHighStop);
    connect(m_gradientPage->plateReturnBtn(), &QPushButton::clicked, m_engine, &SimulationEngine::plateReturnZero);

    connect(m_gradientPage->needleSpeedEdit(), &QLineEdit::editingFinished, this, [this]() {
        m_engine->setNeedleSpeed(m_gradientPage->needleSpeedEdit()->text().toDouble());
    });
    connect(m_gradientPage->clothSpeedEdit(), &QLineEdit::editingFinished, this, [this]() {
        m_engine->setClothSpeed(m_gradientPage->clothSpeedEdit()->text().toDouble());
    });
    connect(m_gradientPage->needleDepthEdit(), &QLineEdit::editingFinished, this, [this]() {
        m_engine->setNeedleDepth(m_gradientPage->needleDepthEdit()->text().toDouble());
    });
    connect(m_gradientPage->plateGapEdit(), &QLineEdit::editingFinished, this, [this]() {
        m_engine->setPlateGap(m_gradientPage->plateGapEdit()->text().toDouble());
    });

    // === ManualDebugPage - 4 motors ===
    for (int i = 0; i < 4; ++i) {
        connect(m_manualDebugPage->accelBtn(i), &QPushButton::clicked, this, [this, i]() {
            m_engine->motorAccel(i);
        });
        connect(m_manualDebugPage->decelBtn(i), &QPushButton::clicked, this, [this, i]() {
            m_engine->motorDecel(i);
        });
        connect(m_manualDebugPage->writeBtn(i), &QPushButton::clicked, this, [this, i]() {
            m_engine->motorWrite(i, m_manualDebugPage->motorSpeedEdit(i)->text().toDouble());
        });
        connect(m_manualDebugPage->forwardBtn(i), &QPushButton::clicked, this, [this, i]() {
            m_engine->motorForward(i);
        });
        connect(m_manualDebugPage->reverseBtn(i), &QPushButton::clicked, this, [this, i]() {
            m_engine->motorReverse(i);
        });
    }

    // Motor speed feedback -> ManualDebugPage edits
    connect(m_engine, &SimulationEngine::motorSpeedChanged, this, [this](int id, double speed) {
        if (id >= 0 && id < 4)
            m_manualDebugPage->motorSpeedEdit(id)->setText(QString::number(speed, 'f', 1));
    });

    // === AlarmResetPage - zero buttons ===
    connect(m_alarmPage->zeroNeedleBtn(), &QPushButton::clicked, this, [this]() {
        m_engine->zeroCoord(0);
    });
    connect(m_alarmPage->zeroUpperBtn(), &QPushButton::clicked, this, [this]() {
        m_engine->zeroCoord(1);
    });
    connect(m_alarmPage->zeroLowerBtn(), &QPushButton::clicked, this, [this]() {
        m_engine->zeroCoord(2);
    });
}

QString MainWindow::globalStyleSheet()
{
    return R"QSS(

    /* ═══════════════════════════════════════════════════════
       GLOBAL - Industrial Light Blue-Gray Theme
       ═══════════════════════════════════════════════════════ */

    * {
        font-family: "PingFang SC", "Hiragino Sans GB", "Noto Sans CJK SC",
                     "Source Han Sans SC", "Helvetica Neue", sans-serif;
    }

    MainWindow {
        background: qlineargradient(x1:0, y1:0, x2:0.3, y2:1,
            stop:0 #d0dde8, stop:0.4 #c4d4e4, stop:1 #b8cce0);
    }

    /* ─── Title Bar ──────────────────────────────────────── */

    #titleBar {
        background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
            stop:0 #c8d8e8, stop:1 #b8c8dc);
        border-bottom: 1px solid #9aabbf;
        min-height: 44px;
        max-height: 44px;
    }

    #titleBar QLabel#statusLabel {
        font-size: 19px;
        font-weight: 700;
        color: #1a2a40;
        letter-spacing: 2px;
        padding-left: 6px;
    }

    #titleBar QLabel#dateTimeLabel {
        font-size: 15px;
        font-weight: 400;
        color: #4a6078;
        letter-spacing: 1px;
        padding-right: 6px;
    }

    /* ─── Status Bar ─────────────────────────────────────── */

    #statusBar {
        background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
            stop:0 #c8d8e8, stop:1 #bccee2);
        border-top: 1px solid #9aabbf;
        min-height: 34px;
        max-height: 34px;
    }

    #statusBar QLabel {
        font-size: 12px;
        color: #3a5068;
    }

    #statusBar QLabel[objectName^="val"] {
        font-size: 13px;
        font-weight: 600;
        color: #1a2a40;
        background: #ffffff;
        border: 1px solid #8899aa;
        border-radius: 3px;
        padding: 1px 8px;
        min-width: 52px;
    }

    /* ─── Side Panel ─────────────────────────────────────── */

    #sidePanel {
        background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
            stop:0 #bccee2, stop:1 #c4d4e8);
        border-left: 1px solid #9aabbf;
    }

    #sidePanel QPushButton {
        font-size: 13px;
        font-weight: 600;
        color: #3a5068;
        background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
            stop:0 #dce6f0, stop:0.5 #d0dce8, stop:1 #c4d2e0);
        border: 1px solid #99aabb;
        border-radius: 5px;
        padding: 6px 4px;
        min-height: 44px;
    }

    #sidePanel QPushButton:hover {
        color: #1a3050;
        background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
            stop:0 #e4eef8, stop:0.5 #d8e4f0, stop:1 #ccdae8);
        border: 1px solid #7090b0;
    }

    #sidePanel QPushButton[active="true"] {
        color: #ffffff;
        background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
            stop:0 #5090c0, stop:0.45 #4080b8, stop:1 #3070a8);
        border: 1px solid #3088c0;
        border-left: 3px solid #50a8e0;
    }

    /* ─── Page Stack ─────────────────────────────────────── */

    #pageStack {
        background: transparent;
    }

    /* ─── QGroupBox ──────────────────────────────────────── */

    QGroupBox {
        background: rgba(255, 255, 255, 160);
        border: 1px solid #5577aa;
        border-radius: 6px;
        margin-top: 4px;
        padding: 10px 8px 8px 8px;
    }

    QGroupBox::title {
        subcontrol-origin: margin;
        left: 12px;
        padding: 0 6px;
        color: #3a6090;
        font-size: 12px;
    }

    /* ─── QLabel ─────────────────────────────────────────── */

    QLabel {
        font-size: 13px;
        font-weight: 500;
        color: #2a3a50;
        background: transparent;
        border: none;
    }

    /* ─── QLineEdit ──────────────────────────────────────── */

    QLineEdit {
        font-size: 14px;
        font-weight: 600;
        color: #1a1a2e;
        background: #ffffff;
        border: 1px solid #8899aa;
        border-bottom: 2px solid #5577aa;
        border-radius: 4px;
        padding: 3px 8px;
        min-width: 58px;
        selection-background-color: #80b0e0;
    }

    QLineEdit:focus {
        border: 1px solid #4080c0;
        border-bottom: 2px solid #3070b0;
        background: #f8fbff;
    }

    QLineEdit:read-only {
        color: #5a6a7a;
        background: #eef2f6;
        border-bottom: 2px solid #99aabb;
    }

    /* ─── QPushButton (content area) ─────────────────────── */

    QGroupBox QPushButton,
    #pageStack QPushButton {
        font-size: 13px;
        font-weight: 600;
        color: #2a3a50;
        background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
            stop:0 #e8eef5, stop:0.48 #dce4ee, stop:0.52 #d0dae6, stop:1 #c0ccd8);
        border: 1px solid #8899aa;
        border-radius: 5px;
        padding: 5px 12px;
        min-width: 62px;
        min-height: 28px;
    }

    QGroupBox QPushButton:hover,
    #pageStack QPushButton:hover {
        color: #1a2a40;
        background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
            stop:0 #f0f4fa, stop:0.48 #e4ecf4, stop:0.52 #d8e2ee, stop:1 #ccd8e4);
        border: 1px solid #6080a0;
    }

    QGroupBox QPushButton:pressed,
    #pageStack QPushButton:pressed {
        color: #1a2a40;
        background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
            stop:0 #c8d4e0, stop:0.5 #bcc8d8, stop:1 #b0c0d0);
        border: 1px solid #4080c0;
        padding-top: 7px;
        padding-bottom: 3px;
    }

    /* Special accent for "开始" / "Start" type buttons */
    QPushButton[cssClass="start"] {
        background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
            stop:0 #b8e8c8, stop:0.5 #90d8a8, stop:1 #78c898);
        border: 1px solid #50a070;
        color: #1a4030;
    }
    QPushButton[cssClass="start"]:hover {
        background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
            stop:0 #c8f0d8, stop:0.5 #a0e0b8, stop:1 #88d8a8);
        border: 1px solid #40b068;
        color: #103828;
    }

    /* Special accent for "停止" / "Stop" type buttons */
    QPushButton[cssClass="stop"] {
        background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
            stop:0 #f0c0c0, stop:0.5 #e0a0a0, stop:1 #d08888);
        border: 1px solid #b06060;
        color: #4a1818;
    }
    QPushButton[cssClass="stop"]:hover {
        background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
            stop:0 #f8d0d0, stop:0.5 #e8b0b0, stop:1 #d89898);
        border: 1px solid #c05050;
        color: #3a1010;
    }

    /* Special accent for "写入" / "Write" type buttons */
    QPushButton[cssClass="write"] {
        background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
            stop:0 #b8d8f0, stop:0.5 #98c8e8, stop:1 #80b8d8);
        border: 1px solid #5090b8;
        color: #1a3a50;
    }
    QPushButton[cssClass="write"]:hover {
        background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
            stop:0 #c8e4f8, stop:0.5 #a8d4f0, stop:1 #90c8e8);
        border: 1px solid #40a0d0;
        color: #102840;
    }

    /* ─── Mode Label (渐变模式 浅-深-浅) ─────────────────── */

    QLabel[cssClass="modeTag"] {
        font-size: 13px;
        font-weight: 700;
        color: #2070a0;
        background: rgba(80, 160, 220, 60);
        border: 1px solid #5090c0;
        border-radius: 4px;
        padding: 2px 10px;
    }

    /* ─── Info / Instruction text ────────────────────────── */

    QLabel[cssClass="info"] {
        font-size: 12px;
        font-weight: 400;
        color: #3a5068;
        background: rgba(255, 255, 255, 120);
        border: 1px solid rgba(85, 119, 170, 80);
        border-radius: 4px;
        padding: 8px 12px;
        line-height: 1.6;
    }

    /* ─── Unit labels (次/分, cm/s, etc.) ─────────────────── */

    QLabel[cssClass="unit"] {
        font-size: 12px;
        font-weight: 400;
        color: #5a7a90;
    }

    /* ─── Colon separator in gear ratio ──────────────────── */

    QLabel[cssClass="colon"] {
        font-size: 16px;
        font-weight: 700;
        color: #4a6a88;
    }

    )QSS";
}
