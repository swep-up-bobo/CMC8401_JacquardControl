#pragma once
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

class AlarmResetPage : public QWidget
{
    Q_OBJECT
public:
    explicit AlarmResetPage(QWidget *parent = nullptr);

    QLineEdit* needleCoordEdit() const { return m_needleCoordEdit; }
    QLineEdit* upperCoordEdit() const { return m_upperCoordEdit; }
    QLineEdit* lowerCoordEdit() const { return m_lowerCoordEdit; }
    QPushButton* zeroNeedleBtn() const { return m_zeroNeedleBtn; }
    QPushButton* zeroUpperBtn() const { return m_zeroUpperBtn; }
    QPushButton* zeroLowerBtn() const { return m_zeroLowerBtn; }

signals:
    void gearSettingsRequested();

private:
    QLineEdit *m_needleCoordEdit;
    QLineEdit *m_upperCoordEdit;
    QLineEdit *m_lowerCoordEdit;
    QPushButton *m_zeroNeedleBtn;
    QPushButton *m_zeroUpperBtn;
    QPushButton *m_zeroLowerBtn;
};
