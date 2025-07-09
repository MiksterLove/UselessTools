#ifndef BUDGETCALCULATOR_H
#define BUDGETCALCULATOR_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDoubleValidator>
#include <QMessageBox>

class BudgetCalculator : public QWidget
{
    Q_OBJECT

public:
    explicit BudgetCalculator(QWidget *parent = nullptr);

private slots:
    void startCalculate();
    void resetInput();
    void onTextChanged();

private:
    QLabel *titleLabel;
    QLineEdit *itemInput;
    QLineEdit *budgetInput;
    QPushButton *calculateButton;
    QPushButton *resetButton;
};

#endif // BUDGETCALCULATOR_H 