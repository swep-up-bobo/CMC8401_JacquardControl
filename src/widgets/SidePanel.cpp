#include "widgets/SidePanel.h"
#include <QVBoxLayout>
#include <QStyle>

SidePanel::SidePanel(QWidget *parent) : QWidget(parent)
{
    setFixedWidth(94);

    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(6, 8, 6, 8);
    layout->setSpacing(6);

    QStringList names = {"标准模式", "间歇模式", "渐变模式", "手动调试", "厂家设置", "报警复位"};

    for (int i = 0; i < names.size(); ++i) {
        auto *btn = new QPushButton(names[i]);
        btn->setFixedHeight(48);
        connect(btn, &QPushButton::clicked, this, [this, i]() { emit pageSelected(i); });
        layout->addWidget(btn);
        m_buttons.append(btn);
    }
    layout->addStretch();
}

void SidePanel::setCurrentIndex(int index)
{
    for (int i = 0; i < m_buttons.size(); ++i) {
        m_buttons[i]->setProperty("active", i == index);
        m_buttons[i]->style()->unpolish(m_buttons[i]);
        m_buttons[i]->style()->polish(m_buttons[i]);
    }
}
