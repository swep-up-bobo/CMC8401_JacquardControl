#include "pages/StandardModePage.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>

static QLineEdit* makeEdit(const QString &val) {
    auto *e = new QLineEdit(val);
    e->setAlignment(Qt::AlignCenter);
    return e;
}

static QLabel* makeUnit(const QString &text) {
    auto *l = new QLabel(text);
    l->setProperty("cssClass", "unit");
    return l;
}

static QPushButton* makeBtn(const QString &text, const char *cls = nullptr) {
    auto *b = new QPushButton(text);
    if (cls) b->setProperty("cssClass", cls);
    return b;
}

StandardModePage::StandardModePage(QWidget *parent) : QWidget(parent)
{
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(10, 6, 6, 6);
    mainLayout->setSpacing(8);

    // Upper group - parameters
    auto *upperGroup = new QGroupBox();
    auto *upperGrid = new QGridLayout(upperGroup);
    upperGrid->setSpacing(10);
    upperGrid->setContentsMargins(14, 14, 14, 14);

    upperGrid->addWidget(new QLabel("针刺速度"), 0, 0);
    m_needleSpeedEdit = makeEdit("800");
    upperGrid->addWidget(m_needleSpeedEdit, 0, 1);
    upperGrid->addWidget(makeUnit("次/分"), 0, 2);

    auto *btnCol = new QVBoxLayout();
    btnCol->setSpacing(6);
    m_needleHighBtn = makeBtn("针停高位");
    m_plateReturnBtn = makeBtn("压板回零");
    m_startBtn = makeBtn("开  始", "start");
    m_stopBtn = makeBtn("停  止", "stop");
    btnCol->addWidget(m_needleHighBtn);
    btnCol->addWidget(m_plateReturnBtn);
    btnCol->addWidget(m_startBtn);
    btnCol->addWidget(m_stopBtn);
    upperGrid->addLayout(btnCol, 0, 3, 4, 1);

    upperGrid->addWidget(new QLabel("卷布速度"), 1, 0);
    m_clothSpeedEdit = makeEdit("3.0");
    upperGrid->addWidget(m_clothSpeedEdit, 1, 1);
    upperGrid->addWidget(makeUnit("cm/s"), 1, 2);

    upperGrid->addWidget(new QLabel("针刺深度"), 2, 0);
    m_needleDepthEdit = makeEdit("0.55");
    upperGrid->addWidget(m_needleDepthEdit, 2, 1);
    upperGrid->addWidget(makeUnit("cm"), 2, 2);

    upperGrid->addWidget(new QLabel("压板间隔"), 3, 0);
    m_plateGapEdit = makeEdit("0.50");
    upperGrid->addWidget(m_plateGapEdit, 3, 1);
    upperGrid->addWidget(makeUnit("cm"), 3, 2);

    mainLayout->addWidget(upperGroup);

    // Lower group
    auto *lowerGroup = new QGroupBox();
    auto *lowerGrid = new QGridLayout(lowerGroup);
    lowerGrid->setSpacing(10);
    lowerGrid->setContentsMargins(14, 14, 14, 14);

    lowerGrid->addWidget(new QLabel("卷布长度"), 0, 0);
    m_clothLengthEdit = makeEdit("100.00");
    lowerGrid->addWidget(m_clothLengthEdit, 0, 1);
    lowerGrid->addWidget(makeUnit("m"), 0, 2);
    m_resetLengthBtn = makeBtn("长度清零");
    lowerGrid->addWidget(m_resetLengthBtn, 0, 3);
    m_rollerForwardBtn = makeBtn("滚筒正转");
    lowerGrid->addWidget(m_rollerForwardBtn, 0, 4);

    lowerGrid->addWidget(new QLabel("手动卷布速度"), 1, 0);
    m_manualClothSpeedEdit = makeEdit("8.33");
    lowerGrid->addWidget(m_manualClothSpeedEdit, 1, 1);
    lowerGrid->addWidget(makeUnit("cm/s"), 1, 2);
    m_speedWriteBtn = makeBtn("速度写入", "write");
    lowerGrid->addWidget(m_speedWriteBtn, 1, 3);
    m_rollerReverseBtn = makeBtn("滚筒反转");
    lowerGrid->addWidget(m_rollerReverseBtn, 1, 4);

    mainLayout->addWidget(lowerGroup);
    mainLayout->addStretch();
}
