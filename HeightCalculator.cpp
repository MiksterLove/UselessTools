#include "HeightCalculator.h"
#include <QRandomGenerator>

HeightCalculator::HeightCalculator(QWidget *parent)
    : QWidget(parent), progress(0), currentHeight(0)
{
    setWindowTitle("身高计算工具");
    QVBoxLayout *layout = new QVBoxLayout(this);
    titleLabel = new QLabel("身高计算器", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(16);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    QHBoxLayout *inputLayout = new QHBoxLayout();
    QLabel *heightLabel = new QLabel("身高：", this);
    heightLabel->setFont(QFont("", 12));
    heightInput = new QLineEdit(this);
    heightInput->setFixedSize(100, 30);
    heightInput->setAlignment(Qt::AlignCenter);
    heightInput->setValidator(new QIntValidator(0, 300, this));
    QLabel *unitLabel = new QLabel("cm", this);
    unitLabel->setFont(QFont("", 12));
    inputLayout->addStretch();
    inputLayout->addWidget(heightLabel);
    inputLayout->addWidget(heightInput);
    inputLayout->addWidget(unitLabel);
    inputLayout->addStretch();
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
    progressBar = new QProgressBar(this);
    progressBar->setRange(0, 100);
    progressBar->hide();
    layout->addStretch();
    layout->addWidget(titleLabel);
    layout->addSpacing(30);
    layout->addLayout(inputLayout);
    layout->addSpacing(20);
    layout->addLayout(buttonLayout);
    layout->addStretch();
    layout->addWidget(progressBar);
    layout->addSpacing(10);
    resize(650, 450);
    calculateTimer = new QTimer(this);
    calculateTimer->setInterval(50);
    connect(calculateButton, &QPushButton::clicked, this, &HeightCalculator::startCalculate);
    connect(resetButton, &QPushButton::clicked, this, &HeightCalculator::resetInput);
    connect(calculateTimer, &QTimer::timeout, this, &HeightCalculator::updateProgress);
    connect(heightInput, &QLineEdit::textChanged, this, &HeightCalculator::onTextChanged);
}

void HeightCalculator::startCalculate()
{
    currentHeight = heightInput->text().toInt();
    calculateButton->setEnabled(false);
    resetButton->setEnabled(false);
    heightInput->setEnabled(false);
    progressBar->show();
    progressBar->setValue(0);
    progress = 0;
    calculateTimer->start();
}

void HeightCalculator::resetInput()
{
    heightInput->clear();
    resetProgress();
}

void HeightCalculator::updateProgress()
{
    int randomIncrement = QRandomGenerator::global()->bounded(2, 5);
    progress += randomIncrement;
    progressBar->setValue(progress);
    
    if (progress >= 100)
    {
        progressBar->setValue(100);
        calculateTimer->stop();
        checkComplete();
    }
}

void HeightCalculator::checkComplete()
{
    int meters = currentHeight / 100;
    int centimeters = currentHeight % 100;
    QString message = QString("您的身高是%1米%2").arg(meters).arg(centimeters);
    
    QMessageBox::information(this, "计算完成", message);
    resetProgress();
}

void HeightCalculator::resetProgress()
{
    progressBar->hide();
    calculateButton->setEnabled(!heightInput->text().isEmpty());
    resetButton->setEnabled(true);
    heightInput->setEnabled(true);
    progress = 0;
}

void HeightCalculator::onTextChanged(const QString &text)
{
    calculateButton->setEnabled(!text.isEmpty());
} 
