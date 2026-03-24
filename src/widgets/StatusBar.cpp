#include "widgets/StatusBar.h"
#include <QHBoxLayout>

static QLabel* makeLabel(const QString &text) {
    auto *l = new QLabel(text);
    return l;
}

static QLabel* makeValueLabel(const QString &text) {
    auto *l = new QLabel(text);
    l->setObjectName("valLabel");
    l->setFixedWidth(58);
    l->setAlignment(Qt::AlignCenter);
    return l;
}

// Small vertical line separator
static QWidget* makeSeparator() {
    auto *sep = new QWidget();
    sep->setFixedSize(1, 18);
    sep->setStyleSheet("background: #8899aa;");
    return sep;
}

StatusBar::StatusBar(QWidget *parent) : QWidget(parent)
{
    setFixedHeight(34);

    auto *layout = new QHBoxLayout(this);
    layout->setContentsMargins(14, 0, 14, 0);
    layout->setSpacing(8);

    layout->addWidget(makeLabel("上压板位置(cm)"));
    m_upperVal = makeValueLabel("0.00");
    layout->addWidget(m_upperVal);

    layout->addSpacing(6);
    layout->addWidget(makeSeparator());
    layout->addSpacing(6);

    layout->addWidget(makeLabel("下压板位置(cm)"));
    m_lowerVal = makeValueLabel("-0.00");
    layout->addWidget(m_lowerVal);

    layout->addSpacing(6);
    layout->addWidget(makeSeparator());
    layout->addSpacing(6);

    layout->addWidget(makeLabel("压板间隔(cm)"));
    m_gapVal = makeValueLabel("2.00");
    layout->addWidget(m_gapVal);

    layout->addStretch();
}

void StatusBar::setUpperPosition(double val) { m_upperVal->setText(QString::number(val, 'f', 2)); }
void StatusBar::setLowerPosition(double val) { m_lowerVal->setText(QString::number(val, 'f', 2)); }
void StatusBar::setGap(double val) { m_gapVal->setText(QString::number(val, 'f', 2)); }
