#include "pages/ManualDebugPage.h"
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

ManualDebugPage::ManualDebugPage(QWidget *parent) : QWidget(parent)
{
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(10, 6, 6, 6);

    auto *group = new QGroupBox();
    auto *g = new QGridLayout(group);
    g->setSpacing(14);
    g->setContentsMargins(14, 16, 14, 16);

    struct MotorDef { QString name; QString val; QString unit; QString fwd; QString rev; };
    MotorDef motors[4] = {
        {"针刺电机", "10",   "转/分",   "正 转", "反 转"},
        {"卷布电机", "8",    "cm/s",    "正 转", "反 转"},
        {"上压板电机", "20.0", "cm/min", "上 升", "下 降"},
        {"下压板电机", "6.0",  "cm/min", "上 升", "下 降"}
    };

    for (int i = 0; i < 4; ++i) {
        g->addWidget(new QLabel(motors[i].name), i, 0);
        m_motorSpeedEdit[i] = makeEdit(motors[i].val);
        g->addWidget(m_motorSpeedEdit[i], i, 1);
        g->addWidget(makeUnit(motors[i].unit), i, 2);
        m_accelBtn[i] = makeBtn("加 速");
        g->addWidget(m_accelBtn[i], i, 3);
        m_decelBtn[i] = makeBtn("减 速");
        g->addWidget(m_decelBtn[i], i, 4);
        m_writeBtn[i] = makeBtn("写 入", "write");
        g->addWidget(m_writeBtn[i], i, 5);

        auto *dirCol = new QVBoxLayout();
        dirCol->setSpacing(4);
        m_forwardBtn[i] = makeBtn(motors[i].fwd);
        m_reverseBtn[i] = makeBtn(motors[i].rev);
        dirCol->addWidget(m_forwardBtn[i]);
        dirCol->addWidget(m_reverseBtn[i]);
        g->addLayout(dirCol, i, 6);
    }

    mainLayout->addWidget(group);
    mainLayout->addStretch();
}
