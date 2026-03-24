#pragma once
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

class StandardModePage : public QWidget
{
    Q_OBJECT
public:
    explicit StandardModePage(QWidget *parent = nullptr);

    QLineEdit* needleSpeedEdit() const { return m_needleSpeedEdit; }
    QLineEdit* clothSpeedEdit() const { return m_clothSpeedEdit; }
    QLineEdit* needleDepthEdit() const { return m_needleDepthEdit; }
    QLineEdit* plateGapEdit() const { return m_plateGapEdit; }
    QLineEdit* clothLengthEdit() const { return m_clothLengthEdit; }
    QLineEdit* manualClothSpeedEdit() const { return m_manualClothSpeedEdit; }

    QPushButton* needleHighBtn() const { return m_needleHighBtn; }
    QPushButton* plateReturnBtn() const { return m_plateReturnBtn; }
    QPushButton* startBtn() const { return m_startBtn; }
    QPushButton* stopBtn() const { return m_stopBtn; }
    QPushButton* resetLengthBtn() const { return m_resetLengthBtn; }
    QPushButton* rollerForwardBtn() const { return m_rollerForwardBtn; }
    QPushButton* speedWriteBtn() const { return m_speedWriteBtn; }
    QPushButton* rollerReverseBtn() const { return m_rollerReverseBtn; }

private:
    QLineEdit *m_needleSpeedEdit;
    QLineEdit *m_clothSpeedEdit;
    QLineEdit *m_needleDepthEdit;
    QLineEdit *m_plateGapEdit;
    QLineEdit *m_clothLengthEdit;
    QLineEdit *m_manualClothSpeedEdit;

    QPushButton *m_needleHighBtn;
    QPushButton *m_plateReturnBtn;
    QPushButton *m_startBtn;
    QPushButton *m_stopBtn;
    QPushButton *m_resetLengthBtn;
    QPushButton *m_rollerForwardBtn;
    QPushButton *m_speedWriteBtn;
    QPushButton *m_rollerReverseBtn;
};
