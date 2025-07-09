#include "PowerCheckWindow.h"
#include <QRandomGenerator>

PowerCheckWindow::PowerCheckWindow(QWidget *parent)
    : QWidget(parent), progress(0)
{
    setWindowTitle("电脑开机状态检测工具");
    QVBoxLayout *layout = new QVBoxLayout(this);
    titleLabel = new QLabel("检测电脑是否开机", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(16);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    checkButton = new QPushButton("开始检测", this);
    checkButton->setFixedSize(120, 40);
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(checkButton);
    buttonLayout->addStretch();
    progressBar = new QProgressBar(this);
    progressBar->setRange(0, 100);
    progressBar->hide();
    layout->addStretch();
    layout->addWidget(titleLabel);
    layout->addSpacing(30);
    layout->addLayout(buttonLayout);
    layout->addStretch();
    layout->addWidget(progressBar);
    layout->addSpacing(10);
    resize(650, 450);
    checkTimer = new QTimer(this);
    checkTimer->setInterval(50);
    connect(checkButton, &QPushButton::clicked, this, &PowerCheckWindow::startCheck);
    connect(checkTimer, &QTimer::timeout, this, &PowerCheckWindow::updateProgress);
}

void PowerCheckWindow::startCheck()
{
    checkButton->setEnabled(false);
    progressBar->show();
    progressBar->setValue(0);
    progress = 0;
    checkTimer->start();
}

void PowerCheckWindow::updateProgress()
{
    int randomIncrement = QRandomGenerator::global()->bounded(1, 4);
    progress += randomIncrement;
    progressBar->setValue(progress);
    if (progress >= 100)
    {
        progressBar->setValue(100);
        checkTimer->stop();
        checkComplete();
    }
}

void PowerCheckWindow::checkComplete()
{
    QMessageBox::information(this, "检测完成", "您的电脑已开机！");
    resetWindow();
}

void PowerCheckWindow::resetWindow()
{
    progressBar->hide();
    checkButton->setEnabled(true);
    progress = 0;
} 
