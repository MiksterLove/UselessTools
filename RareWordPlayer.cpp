#include "RareWordPlayer.h"
#include <QDir>
#include <QCoreApplication>
#include <QTemporaryFile>
#include <QFile>
#include <QDebug>

RareWordPlayer::RareWordPlayer(QWidget *parent)
    : QWidget(parent), progress(0)
{
    setWindowTitle("生僻字发音器");
    resize(650, 450);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    titleLabel = new QLabel("生僻字发音器", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(16);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    QHBoxLayout *inputLayout = new QHBoxLayout();
    QLabel *wordLabel = new QLabel("请输入生僻字：", this);
    wordLabel->setFont(QFont("", 12));
    wordInput = new QLineEdit(this);
    wordInput->setFixedSize(300, 30);
    wordInput->setAlignment(Qt::AlignCenter);
    wordInput->setPlaceholderText("输入生僻字");
    inputLayout->addStretch();
    inputLayout->addWidget(wordLabel);
    inputLayout->addWidget(wordInput);
    inputLayout->addStretch();
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    playButton = new QPushButton("发音", this);
    resetButton = new QPushButton("重置", this);
    playButton->setFixedSize(120, 40);
    resetButton->setFixedSize(120, 40);
    playButton->setEnabled(false);
    buttonLayout->addStretch();
    buttonLayout->addWidget(playButton);
    buttonLayout->addSpacing(20);
    buttonLayout->addWidget(resetButton);
    buttonLayout->addStretch();
    statusLabel = new QLabel(this);
    statusLabel->setAlignment(Qt::AlignCenter);
    statusLabel->setFont(QFont("", 12));
    progressBar = new QProgressBar(this);
    progressBar->setRange(0, 100);
    progressBar->setValue(0);
    progressBar->setTextVisible(false);
    progressBar->setFixedHeight(20);
    progressTimer = new QTimer(this);
    progressTimer->setInterval(100);
    mainLayout->addStretch();
    mainLayout->addWidget(titleLabel);
    mainLayout->addSpacing(30);
    mainLayout->addLayout(inputLayout);
    mainLayout->addSpacing(20);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addSpacing(20);
    mainLayout->addWidget(statusLabel);
    mainLayout->addSpacing(10);
    mainLayout->addWidget(progressBar);
    mainLayout->addStretch();
    connect(playButton, &QPushButton::clicked, this, &RareWordPlayer::startPlay);
    connect(resetButton, &QPushButton::clicked, this, &RareWordPlayer::resetInput);
    connect(wordInput, &QLineEdit::textChanged, this, &RareWordPlayer::onTextChanged);
    connect(progressTimer, &QTimer::timeout, this, &RareWordPlayer::updateProgress);
    QFile resourceFile(":/spz.mp3");
    if (resourceFile.open(QIODevice::ReadOnly)) {
        QTemporaryFile tempFile;
        tempFile.setAutoRemove(false);
        if (tempFile.open()) {
            tempFile.write(resourceFile.readAll());
            tempFilePath = QDir::toNativeSeparators(tempFile.fileName());
            tempFile.close();
        }
        resourceFile.close();
    }
}

RareWordPlayer::~RareWordPlayer()
{
    closeAudio();
    if (!tempFilePath.isEmpty()) {
        QFile::remove(tempFilePath);
    }
}

void RareWordPlayer::startPlay()
{
    playButton->setEnabled(false);
    resetButton->setEnabled(false);
    wordInput->setEnabled(false);
    progress = 0;
    progressBar->setValue(0);
    statusLabel->setText("声音合成中...");
    progressTimer->start();
}

void RareWordPlayer::resetInput()
{
    wordInput->clear();
    progressBar->setValue(0);
    statusLabel->clear();
    playButton->setEnabled(false);
    progressTimer->stop();
    closeAudio();
    wordInput->setEnabled(true);
    resetButton->setEnabled(true);
}

void RareWordPlayer::updateProgress()
{
    progress += 5;
    progressBar->setValue(progress);
    
    if (progress >= 100)
    {
        progressTimer->stop();
        statusLabel->clear();
        playAudio();
    }
}

void RareWordPlayer::onTextChanged(const QString &text)
{
    playButton->setEnabled(!text.trimmed().isEmpty());
}

void RareWordPlayer::playAudio()
{
    if (tempFilePath.isEmpty()) {
        statusLabel->setText("音频文件未准备好");
        return;
    }
    closeAudio();
    QString openCmd = QString("open \"%1\" type mpegvideo alias mySound").arg(tempFilePath);
    MCIERROR error = mciSendStringW(openCmd.toStdWString().c_str(), NULL, 0, NULL);
    if (error) {
        statusLabel->setText("打开音频失败: " + getMciErrorString(error));
        return;
    }
    error = mciSendStringW(L"play mySound", NULL, 0, NULL);
    if (error) {
        statusLabel->setText("播放音频失败: " + getMciErrorString(error));
        closeAudio();
        return;
    }
    resetButton->setEnabled(true);
}

void RareWordPlayer::closeAudio()
{
    mciSendStringW(L"close mySound", NULL, 0, NULL);
}

QString RareWordPlayer::getMciErrorString(MCIERROR error)
{
    wchar_t errorText[256];
    if (mciGetErrorStringW(error, errorText, sizeof(errorText)/sizeof(wchar_t))) {
        return QString::fromWCharArray(errorText);
    }
    return QString("未知错误 (%1)").arg(error);
} 