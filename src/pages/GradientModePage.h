#pragma once
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

class GradientModePage : public QWidget
{
    Q_OBJECT
public:
    explicit GradientModePage(QWidget *parent = nullptr);

    QLineEdit* needleSpeedEdit() const { return m_needleSpeedEdit; }
    QLineEdit* clothSpeedEdit() const { return m_clothSpeedEdit; }
    QLineEdit* needleDepthEdit() const { return m_needleDepthEdit; }
    QLineEdit* plateGapEdit() const { return m_plateGapEdit; }

    QPushButton* needleHighBtn() const { return m_needleHighBtn; }
    QPushButton* plateReturnBtn() const { return m_plateReturnBtn; }
    QPushButton* startBtn() const { return m_startBtn; }
    QPushButton* stopBtn() const { return m_stopBtn; }

private:
    QLineEdit *m_needleSpeedEdit;
    QLineEdit *m_clothSpeedEdit;
    QLineEdit *m_needleDepthEdit;
    QLineEdit *m_plateGapEdit;

    QPushButton *m_needleHighBtn;
    QPushButton *m_plateReturnBtn;
    QPushButton *m_startBtn;
    QPushButton *m_stopBtn;
};
