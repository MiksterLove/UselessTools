#ifndef TIMECONVERTER_H
#define TIMECONVERTER_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QIntValidator>

class TimeConverter : public QWidget
{
    Q_OBJECT

public:
    explicit TimeConverter(QWidget *parent = nullptr);

private slots:
    void startConvert();
    void resetInput();
    void onTextChanged(const QString &text);

private:
    QLabel *titleLabel;
    QLineEdit *minutesInput;
    QLabel *resultLabel;
    QPushButton *convertButton;
    QPushButton *resetButton;
    
    QString convertToCustomTime(int minutes);
};

#endif // TIMECONVERTER_H 