#pragma once
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

class ManualDebugPage : public QWidget
{
    Q_OBJECT
public:
    explicit ManualDebugPage(QWidget *parent = nullptr);

    QLineEdit* motorSpeedEdit(int id) const { return m_motorSpeedEdit[id]; }
    QPushButton* accelBtn(int id) const { return m_accelBtn[id]; }
    QPushButton* decelBtn(int id) const { return m_decelBtn[id]; }
    QPushButton* writeBtn(int id) const { return m_writeBtn[id]; }
    QPushButton* forwardBtn(int id) const { return m_forwardBtn[id]; }
    QPushButton* reverseBtn(int id) const { return m_reverseBtn[id]; }

private:
    QLineEdit *m_motorSpeedEdit[4];
    QPushButton *m_accelBtn[4];
    QPushButton *m_decelBtn[4];
    QPushButton *m_writeBtn[4];
    QPushButton *m_forwardBtn[4];
    QPushButton *m_reverseBtn[4];
};
