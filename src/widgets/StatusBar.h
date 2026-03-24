#pragma once
#include <QWidget>
#include <QLabel>

class StatusBar : public QWidget
{
    Q_OBJECT
public:
    explicit StatusBar(QWidget *parent = nullptr);
    void setUpperPosition(double val);
    void setLowerPosition(double val);
    void setGap(double val);

private:
    QLabel *m_upperVal;
    QLabel *m_lowerVal;
    QLabel *m_gapVal;
};
