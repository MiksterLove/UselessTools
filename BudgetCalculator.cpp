#include "BudgetCalculator.h"

BudgetCalculator::BudgetCalculator(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("预算计算器");
    resize(650, 450);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    titleLabel = new QLabel("预算计算器", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(16);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    QHBoxLayout *itemLayout = new QHBoxLayout();
    QLabel *itemLabel = new QLabel("物品：", this);
    itemLabel->setFont(QFont("", 12));
    itemInput = new QLineEdit(this);
    itemInput->setFixedSize(200, 30);
    itemInput->setAlignment(Qt::AlignCenter);
    itemInput->setPlaceholderText("输入物品名称");
    itemLayout->addStretch();
    itemLayout->addWidget(itemLabel);
    itemLayout->addWidget(itemInput);
    itemLayout->addStretch();
    QHBoxLayout *budgetLayout = new QHBoxLayout();
    QLabel *budgetLabel = new QLabel("预算：", this);
    budgetLabel->setFont(QFont("", 12));
    budgetInput = new QLineEdit(this);
    budgetInput->setFixedSize(100, 30);
    budgetInput->setAlignment(Qt::AlignCenter);
    budgetInput->setPlaceholderText("输入金额");
    QDoubleValidator *validator = new QDoubleValidator(0, 999999.99, 2, this);
    validator->setNotation(QDoubleValidator::StandardNotation);
    budgetInput->setValidator(validator);
    QLabel *unitLabel = new QLabel("元", this);
    unitLabel->setFont(QFont("", 12));
    budgetLayout->addStretch();
    budgetLayout->addWidget(budgetLabel);
    budgetLayout->addWidget(budgetInput);
    budgetLayout->addWidget(unitLabel);
    budgetLayout->addStretch();
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    calculateButton = new QPushButton("开始计算", this);
    resetButton = new QPushButton("重置", this);
    calculateButton->setFixedSize(120, 40);
    resetButton->setFixedSize(120, 40);
    calculateButton->setEnabled(false);
    buttonLayout->addStretch();
    buttonLayout->addWidget(calculateButton);
    buttonLayout->addSpacing(20);
    buttonLayout->addWidget(resetButton);
    buttonLayout->addStretch();
    mainLayout->addStretch();
    mainLayout->addWidget(titleLabel);
    mainLayout->addSpacing(30);
    mainLayout->addLayout(itemLayout);
    mainLayout->addSpacing(20);
    mainLayout->addLayout(budgetLayout);
    mainLayout->addSpacing(20);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addStretch();
    connect(calculateButton, &QPushButton::clicked, this, &BudgetCalculator::startCalculate);
    connect(resetButton, &QPushButton::clicked, this, &BudgetCalculator::resetInput);
    connect(itemInput, &QLineEdit::textChanged, this, &BudgetCalculator::onTextChanged);
    connect(budgetInput, &QLineEdit::textChanged, this, &BudgetCalculator::onTextChanged);
}

void BudgetCalculator::startCalculate()
{
    QString item = itemInput->text().trimmed();
    QString budget = budgetInput->text();
    
    if (!item.isEmpty() && !budget.isEmpty()) {
        double amount = budget.toDouble();
        QString message = QString("购买 %1 的预算为 %2 元")
                         .arg(item, QString::number(amount, 'f', 2));
        
        QMessageBox::information(this, "预算结果", message);
    }
}

void BudgetCalculator::resetInput()
{
    itemInput->clear();
    budgetInput->clear();
    calculateButton->setEnabled(false);
}

void BudgetCalculator::onTextChanged()
{
    bool enabled = !itemInput->text().trimmed().isEmpty() && !budgetInput->text().isEmpty();
    calculateButton->setEnabled(enabled);
} 