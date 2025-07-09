#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QProcess>
#include <QTimer>
#include <QClipboard>
#include <QApplication>

class Calculator : public QWidget
{
    Q_OBJECT
    
public:
    explicit Calculator(QWidget *parent = nullptr);
    
private slots:
    void numberClicked();
    void operatorClicked();
    void equalClicked();
    void clearClicked();
    void backspaceClicked();
    
private:
    QLineEdit *display;
    QPushButton* createButton(const QString &text, void (Calculator::*slot)());
};

#endif // CALCULATOR_H 