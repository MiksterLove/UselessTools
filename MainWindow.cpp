#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent), powerCheckWindow(nullptr), heightCalculator(nullptr), 
      calculator(nullptr), timeConverter(nullptr), budgetCalculator(nullptr),
      rareWordPlayer(nullptr)
{
    setWindowTitle("Windows实用工具大全");
    QVBoxLayout *layout = new QVBoxLayout(this);
    powerCheckButton = new QPushButton("检测电脑是否开机", this);
    heightCalculatorButton = new QPushButton("身高计算器", this);
    calculatorButton = new QPushButton("计算器", this);
    timeConverterButton = new QPushButton("分秒转换器", this);
    budgetCalculatorButton = new QPushButton("预算计算器", this);
    rareWordPlayerButton = new QPushButton("生僻字发音器", this);
    layout->addWidget(powerCheckButton);
    layout->addWidget(heightCalculatorButton);
    layout->addWidget(calculatorButton);
    layout->addWidget(timeConverterButton);
    layout->addWidget(budgetCalculatorButton);
    layout->addWidget(rareWordPlayerButton);
    layout->addStretch();
    resize(400, 300);
    connect(powerCheckButton, &QPushButton::clicked, this, &MainWindow::openPowerCheck);
    connect(heightCalculatorButton, &QPushButton::clicked, this, &MainWindow::openHeightCalculator);
    connect(calculatorButton, &QPushButton::clicked, this, &MainWindow::openCalculator);
    connect(timeConverterButton, &QPushButton::clicked, this, &MainWindow::openTimeConverter);
    connect(budgetCalculatorButton, &QPushButton::clicked, this, &MainWindow::openBudgetCalculator);
    connect(rareWordPlayerButton, &QPushButton::clicked, this, &MainWindow::openRareWordPlayer);
}

MainWindow::~MainWindow()
{
    if (powerCheckWindow)
    {
        delete powerCheckWindow;
    }
    if (heightCalculator)
    {
        delete heightCalculator;
    }
    if (calculator)
    {
        delete calculator;
    }
    if (timeConverter)
    {
        delete timeConverter;
    }
    if (budgetCalculator)
    {
        delete budgetCalculator;
    }
    if (rareWordPlayer)
    {
        delete rareWordPlayer;
    }
}

void MainWindow::openPowerCheck()
{
    if (!powerCheckWindow)
    {
        powerCheckWindow = new PowerCheckWindow();
    }
    powerCheckWindow->show();
    powerCheckWindow->activateWindow();
}

void MainWindow::openHeightCalculator()
{
    if (!heightCalculator)
    {
        heightCalculator = new HeightCalculator();
    }
    heightCalculator->show();
    heightCalculator->activateWindow();
}

void MainWindow::openCalculator()
{
    if (!calculator)
    {
        calculator = new Calculator();
    }
    calculator->show();
    calculator->activateWindow();
}

void MainWindow::openTimeConverter()
{
    if (!timeConverter)
    {
        timeConverter = new TimeConverter();
    }
    timeConverter->show();
    timeConverter->activateWindow();
}

void MainWindow::openBudgetCalculator()
{
    if (!budgetCalculator)
    {
        budgetCalculator = new BudgetCalculator();
    }
    budgetCalculator->show();
    budgetCalculator->activateWindow();
}

void MainWindow::openRareWordPlayer()
{
    if (!rareWordPlayer)
    {
        rareWordPlayer = new RareWordPlayer();
    }
    rareWordPlayer->show();
    rareWordPlayer->activateWindow();
}

