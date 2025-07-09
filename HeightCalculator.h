#ifndef HEIGHTCALCULATOR_H
#define HEIGHTCALCULATOR_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QProgressBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTimer>
#include <QMessageBox>
#include <QIntValidator>

class HeightCalculator : public QWidget
{
    Q_OBJECT

public:
    explicit HeightCalculator(QWidget *parent = nullptr);

private slots:
    void startCalculate();
    void resetInput();
    void updateProgress();
    void checkComplete();
    void resetProgress();
    void onTextChanged(const QString &text);

private:
    QLabel *titleLabel;
    QLineEdit *heightInput;
    QPushButton *calculateButton;
    QPushButton *resetButton;
    QProgressBar *progressBar;
    QTimer *calculateTimer;
    int progress;
    int currentHeight;
};

#endif // HEIGHTCALCULATOR_H 