#pragma once
#include <QWidget>

class FactorySettingsPage : public QWidget
{
    Q_OBJECT
public:
    explicit FactorySettingsPage(QWidget *parent = nullptr);

signals:
    void returnRequested();
};
