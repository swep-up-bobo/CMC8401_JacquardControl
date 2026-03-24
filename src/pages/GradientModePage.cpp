#include "pages/GradientModePage.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
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

GradientModePage::GradientModePage(QWidget *parent) : QWidget(parent)
{
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(10, 6, 6, 6);

    auto *group = new QGroupBox();
    auto *g = new QGridLayout(group);
    g->setSpacing(10);
    g->setContentsMargins(14, 14, 14, 14);

    int r = 0;
    g->addWidget(new QLabel("针刺速度"), r, 0);
    m_needleSpeedEdit = makeEdit("800");
    g->addWidget(m_needleSpeedEdit, r, 1);
    g->addWidget(makeUnit("次/分"), r, 2);

    auto *modeTitleLabel = new QLabel("渐变模式");
    g->addWidget(modeTitleLabel, r, 3);

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
    btnCol->addStretch();
    g->addLayout(btnCol, 0, 4, 4, 1);

    r = 1;
    g->addWidget(new QLabel("渐变卷布速度"), r, 0);
    m_clothSpeedEdit = makeEdit("1.2");
    g->addWidget(m_clothSpeedEdit, r, 1);
    g->addWidget(makeUnit("cm/s"), r, 2);
    auto *modeLabel = new QLabel("浅-深-浅");
    modeLabel->setProperty("cssClass", "modeTag");
    g->addWidget(modeLabel, r, 3);

    r = 2;
    g->addWidget(new QLabel("间隔卷布速度"), r, 0);
    g->addWidget(makeEdit("12.0"), r, 1);
    g->addWidget(makeUnit("cm/s"), r, 2);

    r = 3;
    g->addWidget(new QLabel("针刺深度1"), r, 0);
    m_needleDepthEdit = makeEdit("0.70");
    g->addWidget(m_needleDepthEdit, r, 1);
    g->addWidget(makeUnit("cm"), r, 2);

    r = 4;
    g->addWidget(new QLabel("针刺深度2"), r, 0);
    g->addWidget(makeEdit("1.20"), r, 1);
    g->addWidget(makeUnit("cm"), r, 2);

    r = 5;
    g->addWidget(new QLabel("压板间隔"), r, 0);
    m_plateGapEdit = makeEdit("0.40");
    g->addWidget(m_plateGapEdit, r, 1);
    g->addWidget(makeUnit("cm"), r, 2);

    r = 6;
    g->addWidget(new QLabel("渐变长度"), r, 0);
    g->addWidget(makeEdit("22.0"), r, 1);
    g->addWidget(makeUnit("cm"), r, 2);

    r = 7;
    g->addWidget(new QLabel("间隔长度"), r, 0);
    g->addWidget(makeEdit("38.0"), r, 1);
    g->addWidget(makeUnit("cm"), r, 2);

    mainLayout->addWidget(group);
    mainLayout->addStretch();
}
