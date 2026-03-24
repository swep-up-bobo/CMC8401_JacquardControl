#include "widgets/TitleBar.h"
#include <QHBoxLayout>
#include <QDateTime>

TitleBar::TitleBar(QWidget *parent) : QWidget(parent)
{
    setFixedHeight(44);

    m_statusLabel = new QLabel("待机中||");
    m_statusLabel->setObjectName("statusLabel");

    m_dateTimeLabel = new QLabel();
    m_dateTimeLabel->setObjectName("dateTimeLabel");
    m_dateTimeLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    auto *layout = new QHBoxLayout(this);
    layout->setContentsMargins(14, 0, 14, 0);
    layout->addWidget(m_statusLabel);
    layout->addStretch();
    layout->addWidget(m_dateTimeLabel);

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, [this]() {
        m_dateTimeLabel->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd  HH:mm:ss"));
    });
    m_timer->start(1000);
    m_dateTimeLabel->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd  HH:mm:ss"));
}

void TitleBar::setStatus(const QString &status)
{
    m_statusLabel->setText(status);
}
