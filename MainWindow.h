#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include "PowerCheckWindow.h"
#include "HeightCalculator.h"
#include "Calculator.h"
#include "TimeConverter.h"
#include "BudgetCalculator.h"
#include "RareWordPlayer.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openPowerCheck();
    void openHeightCalculator();
    void openCalculator();
    void openTimeConverter();
    void openBudgetCalculator();
    void openRareWordPlayer();

private:
    PowerCheckWindow *powerCheckWindow;
    HeightCalculator *heightCalculator;
    Calculator *calculator;
    TimeConverter *timeConverter;
    BudgetCalculator *budgetCalculator;
    RareWordPlayer *rareWordPlayer;
    QPushButton *powerCheckButton;
    QPushButton *heightCalculatorButton;
    QPushButton *calculatorButton;
    QPushButton *timeConverterButton;
    QPushButton *budgetCalculatorButton;
    QPushButton *rareWordPlayerButton;
};

#endif // MAINWINDOW_H
