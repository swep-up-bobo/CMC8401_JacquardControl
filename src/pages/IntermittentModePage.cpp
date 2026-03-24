#include "pages/IntermittentModePage.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>

static QLineEdit* makeEdit(const QString &v) {
    auto *e = new QLineEdit(v); e->setAlignment(Qt::AlignCenter); return e;
}
static QLabel* makeUnit(const QString &t) {
    auto *l = new QLabel(t); l->setProperty("cssClass", "unit"); return l;
}
static QPushButton* makeBtn(const QString &t, const char *cls = nullptr) {
    auto *b = new QPushButton(t); if (cls) b->setProperty("cssClass", cls); return b;
}

IntermittentModePage::IntermittentModePage(QWidget *parent) : QWidget(parent)
{
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(10, 6, 6, 6);
    mainLayout->setSpacing(8);

    // Upper group
    auto *upperGroup = new QGroupBox();
    auto *g = new QGridLayout(upperGroup);
    g->setSpacing(10);
    g->setContentsMargins(14, 14, 14, 14);

    g->addWidget(new QLabel("针刺速度"), 0, 0);
    m_needleSpeedEdit = makeEdit("800");
    g->addWidget(m_needleSpeedEdit, 0, 1);
    g->addWidget(makeUnit("次/分"), 0, 2);
    g->addWidget(new QLabel("程序号"), 0, 3);
    m_programNoEdit = makeEdit("2");
    g->addWidget(m_programNoEdit, 0, 4);

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
    g->addLayout(btnCol, 0, 5, 4, 1);

    g->addWidget(new QLabel("间歇卷布速度"), 1, 0);
    m_clothSpeedEdit = makeEdit("5.0");
    g->addWidget(m_clothSpeedEdit, 1, 1);
    g->addWidget(makeUnit("cm/s"), 1, 2);

    g->addWidget(new QLabel("针刺深度"), 2, 0);
    m_needleDepthEdit = makeEdit("0.80");
    g->addWidget(m_needleDepthEdit, 2, 1);
    g->addWidget(makeUnit("cm"), 2, 2);

    g->addWidget(new QLabel("压板间隔"), 3, 0);
    m_plateGapEdit = makeEdit("0.60");
    g->addWidget(m_plateGapEdit, 3, 1);
    g->addWidget(makeUnit("cm"), 3, 2);

    mainLayout->addWidget(upperGroup);

    // Lower group - parameter table
    auto *lowerGroup = new QGroupBox();
    auto *lg = new QGridLayout(lowerGroup);
    lg->setSpacing(8);
    lg->setContentsMargins(14, 14, 14, 14);

    lg->addWidget(new QLabel("针刺长度1"), 0, 0);
    lg->addWidget(makeEdit("0.0"), 0, 1);
    lg->addWidget(makeUnit("cm"), 0, 2);
    lg->addWidget(new QLabel("针刺长度2"), 0, 3);
    lg->addWidget(makeEdit("0.2"), 0, 4);
    lg->addWidget(makeUnit("cm"), 0, 5);

    lg->addWidget(new QLabel("针刺速度1"), 1, 0);
    lg->addWidget(makeEdit("0.1"), 1, 1);
    lg->addWidget(makeUnit("cm"), 1, 2);
    lg->addWidget(new QLabel("针刺速度2"), 1, 3);
    lg->addWidget(makeEdit("0.1"), 1, 4);
    lg->addWidget(makeUnit("cm"), 1, 5);

    lg->addWidget(new QLabel("间歇长度1"), 2, 0);
    lg->addWidget(makeEdit("37.5"), 2, 1);
    lg->addWidget(makeUnit("cm"), 2, 2);
    lg->addWidget(new QLabel("间歇长度2"), 2, 3);
    lg->addWidget(makeEdit("8.0"), 2, 4);
    lg->addWidget(makeUnit("cm"), 2, 5);

    mainLayout->addWidget(lowerGroup);
    mainLayout->addStretch();
}
