#include "Calculator.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QStandardPaths>

Calculator::Calculator(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("计算器");
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    display = new QLineEdit();
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setMinimumHeight(50);
    QFont displayFont = display->font();
    displayFont.setPointSize(16);
    display->setFont(displayFont);
    mainLayout->addWidget(display);
    QGridLayout *buttonLayout = new QGridLayout();
    buttonLayout->addWidget(createButton("C", &Calculator::clearClicked), 0, 0, 1, 2);
    buttonLayout->addWidget(createButton("⌫", &Calculator::backspaceClicked), 0, 2);
    buttonLayout->addWidget(createButton("÷", &Calculator::operatorClicked), 0, 3);
    buttonLayout->addWidget(createButton("7", &Calculator::numberClicked), 1, 0);
    buttonLayout->addWidget(createButton("8", &Calculator::numberClicked), 1, 1);
    buttonLayout->addWidget(createButton("9", &Calculator::numberClicked), 1, 2);
    buttonLayout->addWidget(createButton("×", &Calculator::operatorClicked), 1, 3);
    buttonLayout->addWidget(createButton("4", &Calculator::numberClicked), 2, 0);
    buttonLayout->addWidget(createButton("5", &Calculator::numberClicked), 2, 1);
    buttonLayout->addWidget(createButton("6", &Calculator::numberClicked), 2, 2);
    buttonLayout->addWidget(createButton("-", &Calculator::operatorClicked), 2, 3);
    buttonLayout->addWidget(createButton("1", &Calculator::numberClicked), 3, 0);
    buttonLayout->addWidget(createButton("2", &Calculator::numberClicked), 3, 1);
    buttonLayout->addWidget(createButton("3", &Calculator::numberClicked), 3, 2);
    buttonLayout->addWidget(createButton("+", &Calculator::operatorClicked), 3, 3);
    buttonLayout->addWidget(createButton("0", &Calculator::numberClicked), 4, 0, 1, 2);
    buttonLayout->addWidget(createButton(".", &Calculator::numberClicked), 4, 2);
    buttonLayout->addWidget(createButton("=", &Calculator::equalClicked), 4, 3);
    mainLayout->addLayout(buttonLayout);
    resize(300, 400);
}

QPushButton* Calculator::createButton(const QString &text, void (Calculator::*slot)())
{
    QPushButton *button = new QPushButton(text);
    button->setMinimumSize(60, 60);
    QFont buttonFont = button->font();
    buttonFont.setPointSize(14);
    button->setFont(buttonFont);
    
    connect(button, &QPushButton::clicked, this, slot);
    return button;
}

void Calculator::numberClicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    QString digit = button->text();
    display->setText(display->text() + digit);
}

void Calculator::operatorClicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    QString op = button->text();
    display->setText(display->text() + " " + op + " ");
}

void Calculator::clearClicked()
{
    display->clear();
}

void Calculator::backspaceClicked()
{
    QString text = display->text();
    if (!text.isEmpty()) {
        if (text.endsWith(" ")) {
            text.chop(3);
        } else {
            text.chop(1);
        }
        display->setText(text);
    }
}

void Calculator::equalClicked()
{
    QString expression = display->text();
    if (expression.isEmpty()) {
        return;
    }
    QString calcExpression = expression;
    calcExpression.replace(QChar(0x00D7), "*");
    calcExpression.replace(QChar(0x00F7), "/");
    
    // 将表达式转换为按键序列
    QString keySequence;
    for (const QChar &ch : calcExpression) {
        if (ch == ' ') continue;
        if (ch == '*') {
            keySequence += "{*}";
        } else if (ch == '/') {
            keySequence += "{/}";
        } else if (ch == '+') {
            keySequence += "{+}";
        } else if (ch == '-') {
            keySequence += "{-}";
        } else {
            keySequence += ch;
        }
    }
    keySequence += "{ENTER}";
    QString tempPath = QStandardPaths::writableLocation(QStandardPaths::TempLocation);
    QString batchPath = tempPath + "/calc_command.bat";
    QString vbsPath = tempPath + "/calc_input.vbs";
    QFile batchFile(batchPath);
    if (batchFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&batchFile);
        stream << "@echo off\n";
        stream << "start calc\n";
        stream << "timeout /t 1 /nobreak >nul\n\n";
        stream << "echo Option Explicit > " << vbsPath << "\n";
        stream << "echo Dim WshShell >> " << vbsPath << "\n";
        stream << "echo Set WshShell = CreateObject(\"WScript.Shell\") >> " << vbsPath << "\n";
        stream << "echo WScript.Sleep 500 >> " << vbsPath << "\n";
        stream << "echo WshShell.AppActivate \"计算器\" >> " << vbsPath << "\n";
        stream << "echo WScript.Sleep 100 >> " << vbsPath << "\n";
        stream << "echo WshShell.SendKeys \"{ESC}\" >> " << vbsPath << "\n";  // 清除可能的旧输入
        stream << "echo WScript.Sleep 100 >> " << vbsPath << "\n";
        stream << "echo WshShell.SendKeys \"" << keySequence << "\" >> " << vbsPath << "\n";
        stream << "echo Set WshShell = Nothing >> " << vbsPath << "\n\n";
        stream << "cscript //nologo " << vbsPath << "\n\n";
        stream << "del " << vbsPath << "\n";
        batchFile.close();
        QProcess *process = new QProcess(this);
        process->setProcessChannelMode(QProcess::MergedChannels);
        connect(process, &QProcess::readyReadStandardOutput, [process]() {
            qDebug() << "进程输出:" << process->readAllStandardOutput();
        });
        connect(process, &QProcess::errorOccurred, [](QProcess::ProcessError error) {
            qDebug() << "进程错误:" << error;
        });
        connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
                [](int exitCode, QProcess::ExitStatus exitStatus) {
            qDebug() << "进程完成:" << exitCode << exitStatus;
        });
        process->start(batchPath);
        QTimer::singleShot(3000, [batchPath]() {
            QFile::remove(batchPath);
        });
    } else {
        qDebug() << "无法创建批处理文件:" << batchPath;
    }
} 
