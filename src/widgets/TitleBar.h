#pragma once
#include <QWidget>
#include <QLabel>
#include <QTimer>

class TitleBar : public QWidget
{
    Q_OBJECT
public:
    explicit TitleBar(QWidget *parent = nullptr);
    void setStatus(const QString &status);

private:
    QLabel *m_statusLabel;
    QLabel *m_dateTimeLabel;
    QTimer *m_timer;
};
