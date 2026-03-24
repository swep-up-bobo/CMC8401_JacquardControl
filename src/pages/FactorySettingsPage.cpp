#include "pages/FactorySettingsPage.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

static QLineEdit* makeEdit(const QString &v) {
    auto *e = new QLineEdit(v); e->setAlignment(Qt::AlignCenter); return e;
}
static QLabel* makeUnit(const QString &t) {
    auto *l = new QLabel(t); l->setProperty("cssClass", "unit"); return l;
}
static QPushButton* makeBtn(const QString &t, const char *cls = nullptr) {
    auto *b = new QPushButton(t); if (cls) b->setProperty("cssClass", cls); return b;
}

FactorySettingsPage::FactorySettingsPage(QWidget *parent) : QWidget(parent)
{
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(10, 6, 6, 6);

    auto *group = new QGroupBox();
    auto *g = new QGridLayout(group);
    g->setSpacing(12);
    g->setContentsMargins(14, 16, 14, 16);

    struct RatioRow { QString name; QString a; QString b; };
    QVector<RatioRow> rows = {
        {"针板速比", "41", "50"},
        {"滚筒速比", "1", "10"},
        {"上压板速比", "1", "5"},
        {"下压板速比", "1", "5"}
    };

    for (int i = 0; i < rows.size(); ++i) {
        g->addWidget(new QLabel(rows[i].name), i, 0);
        g->addWidget(makeEdit(rows[i].a), i, 1);
        auto *colon = new QLabel(":");
        colon->setProperty("cssClass", "colon");
        colon->setAlignment(Qt::AlignCenter);
        colon->setFixedWidth(18);
        g->addWidget(colon, i, 2);
        g->addWidget(makeEdit(rows[i].b), i, 3);
    }

    g->addWidget(new QLabel("滚筒直径"), 0, 4);
    g->addWidget(makeEdit("82.00"), 0, 5);
    g->addWidget(makeUnit("mm"), 0, 6);
    g->addWidget(makeBtn("修改", "write"), 0, 7);

    g->addWidget(new QLabel("涡轮导程"), 1, 4);
    g->addWidget(makeEdit("0.4"), 1, 5);
    g->addWidget(makeUnit("mm"), 1, 6);
    g->addWidget(makeBtn("修改", "write"), 1, 7);

    g->addWidget(new QLabel("涡轮导程"), 2, 4);
    g->addWidget(makeEdit("0.3"), 2, 5);
    g->addWidget(makeUnit("mm"), 2, 6);
    g->addWidget(makeBtn("修改", "write"), 2, 7);

    g->addWidget(makeBtn("修改", "write"), 3, 7);

    auto *returnBtn = makeBtn("返  回");
    returnBtn->setMinimumWidth(86);
    connect(returnBtn, &QPushButton::clicked, this, &FactorySettingsPage::returnRequested);

    auto *bottomLayout = new QHBoxLayout();
    bottomLayout->addStretch();
    bottomLayout->addWidget(returnBtn);
    bottomLayout->addSpacing(10);
    g->addLayout(bottomLayout, 4, 4, 1, 4);

    mainLayout->addWidget(group);
    mainLayout->addStretch();
}
