#pragma once
#include <QWidget>
#include <QPushButton>
#include <QVector>

class SidePanel : public QWidget
{
    Q_OBJECT
public:
    explicit SidePanel(QWidget *parent = nullptr);
    void setCurrentIndex(int index);

signals:
    void pageSelected(int index);

private:
    QVector<QPushButton*> m_buttons;
};
