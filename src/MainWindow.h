#pragma once
#include <QWidget>
#include <QStackedWidget>
#include "widgets/TitleBar.h"
#include "widgets/StatusBar.h"
#include "widgets/SidePanel.h"
#include "SimulationEngine.h"
#include "pages/StandardModePage.h"
#include "pages/IntermittentModePage.h"
#include "pages/GradientModePage.h"
#include "pages/ManualDebugPage.h"
#include "pages/FactorySettingsPage.h"
#include "pages/AlarmResetPage.h"

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    void switchPage(int index);
    void connectEngine();
    static QString globalStyleSheet();

    TitleBar *m_titleBar;
    StatusBar *m_statusBar;
    SidePanel *m_sidePanel;
    QStackedWidget *m_stack;

    SimulationEngine *m_engine;

    StandardModePage *m_standardPage;
    IntermittentModePage *m_intermittentPage;
    GradientModePage *m_gradientPage;
    ManualDebugPage *m_manualDebugPage;
    FactorySettingsPage *m_factoryPage;
    AlarmResetPage *m_alarmPage;
};
