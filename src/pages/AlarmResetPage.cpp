#include "pages/AlarmResetPage.h"
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

AlarmResetPage::AlarmResetPage(QWidget *parent) : QWidget(parent)
{
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(10, 6, 6, 6);
    mainLayout->setSpacing(8);

    auto *group = new QGroupBox();
    auto *g = new QGridLayout(group);
    g->setSpacing(12);
    g->setContentsMargins(14, 16, 14, 16);

    g->addWidget(new QLabel("针板坐标"), 0, 0);
    m_needleCoordEdit = makeEdit("68.254");
    g->addWidget(m_needleCoordEdit, 0, 1);
    m_zeroNeedleBtn = makeBtn("置 零");
    g->addWidget(m_zeroNeedleBtn, 0, 2);
    g->addWidget(new QLabel("针板回零速度"), 0, 3);
    g->addWidget(makeEdit("100"), 0, 4);
    g->addWidget(makeUnit("rpm"), 0, 5);

    g->addWidget(new QLabel("上压板坐标"), 1, 0);
    m_upperCoordEdit = makeEdit("0.00");
    g->addWidget(m_upperCoordEdit, 1, 1);
    m_zeroUpperBtn = makeBtn("置 零");
    g->addWidget(m_zeroUpperBtn, 1, 2);
    g->addWidget(new QLabel("上压板回零速度"), 1, 3);
    g->addWidget(makeEdit("1500"), 1, 4);
    g->addWidget(makeUnit("rpm"), 1, 5);

    g->addWidget(new QLabel("下压板坐标"), 2, 0);
    m_lowerCoordEdit = makeEdit("-0.00");
    g->addWidget(m_lowerCoordEdit, 2, 1);
    m_zeroLowerBtn = makeBtn("置 零");
    g->addWidget(m_zeroLowerBtn, 2, 2);
    g->addWidget(new QLabel("下压板回零速度"), 2, 3);
    g->addWidget(makeEdit("1500"), 2, 4);
    g->addWidget(makeUnit("rpm"), 2, 5);

    g->addWidget(new QLabel("零位时上下压板间距"), 3, 0, 1, 2);
    g->addWidget(makeEdit("2.0"), 3, 2);
    g->addWidget(makeUnit("cm"), 3, 3);
    auto *gearBtn = makeBtn("齿轮比设置", "write");
    gearBtn->setMinimumWidth(96);
    connect(gearBtn, &QPushButton::clicked, this, &AlarmResetPage::gearSettingsRequested);
    g->addWidget(gearBtn, 3, 4, 1, 2);

    mainLayout->addWidget(group);

    auto *infoLabel = new QLabel(
        "1. 将下压板移动到目标位置后，将当前坐标置零\n"
        "2. 设置上方压板间距参数，一般设为2或3即可\n"
        "3. 根据压板零位间距值，将上压板移动到目标位置后，将上压板位置置零"
    );
    infoLabel->setProperty("cssClass", "info");
    infoLabel->setWordWrap(true);
    mainLayout->addWidget(infoLabel);

    mainLayout->addStretch();
}
