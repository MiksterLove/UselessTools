#include "TimeConverter.h"

TimeConverter::TimeConverter(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("分秒转换器");
    resize(650, 450);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    titleLabel = new QLabel("分秒转换器", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(16);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    QHBoxLayout *inputLayout = new QHBoxLayout();
    QLabel *minutesLabel = new QLabel("时间：", this);
    minutesLabel->setFont(QFont("", 12));
    minutesInput = new QLineEdit(this);
    minutesInput->setFixedSize(100, 30);
    minutesInput->setAlignment(Qt::AlignCenter);
    minutesInput->setValidator(new QIntValidator(0, 999999, this));
    minutesInput->setPlaceholderText("输入分钟");
    QLabel *unitLabel = new QLabel("分钟 = ", this);
    unitLabel->setFont(QFont("", 12));
    resultLabel = new QLabel(this);
    resultLabel->setFont(QFont("", 12));
    inputLayout->addStretch();
    inputLayout->addWidget(minutesLabel);
    inputLayout->addWidget(minutesInput);
    inputLayout->addWidget(unitLabel);
    inputLayout->addWidget(resultLabel);
    inputLayout->addStretch();
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    convertButton = new QPushButton("开始转换", this);
    resetButton = new QPushButton("重置", this);
    convertButton->setFixedSize(120, 40);
    resetButton->setFixedSize(120, 40);
    convertButton->setEnabled(false);
    buttonLayout->addStretch();
    buttonLayout->addWidget(convertButton);
    buttonLayout->addSpacing(20);
    buttonLayout->addWidget(resetButton);
    buttonLayout->addStretch();
    mainLayout->addStretch();
    mainLayout->addWidget(titleLabel);
    mainLayout->addSpacing(30);
    mainLayout->addLayout(inputLayout);
    mainLayout->addSpacing(20);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addStretch();
    connect(convertButton, &QPushButton::clicked, this, &TimeConverter::startConvert);
    connect(resetButton, &QPushButton::clicked, this, &TimeConverter::resetInput);
    connect(minutesInput, &QLineEdit::textChanged, this, &TimeConverter::onTextChanged);
}

void TimeConverter::startConvert()
{
    bool ok;
    int minutes = minutesInput->text().toInt(&ok);
    if (ok) {
        QString result = convertToCustomTime(minutes);
        resultLabel->setText(result);
    }
}

void TimeConverter::resetInput()
{
    minutesInput->clear();
    resultLabel->clear();
}

void TimeConverter::onTextChanged(const QString &text)
{
    convertButton->setEnabled(!text.isEmpty());
}

QString TimeConverter::convertToCustomTime(int minutes)
{
    if (minutes == 0) {
        return "0秒";
    }
    int totalSeconds = minutes * 60;
    int customMinutes = totalSeconds / 100;
    int remainingSeconds = totalSeconds % 100;
    if (customMinutes == 0) {
        return QString("%1秒").arg(remainingSeconds);
    } else {
        if (remainingSeconds == 0) {
            return QString("%1分钟").arg(customMinutes);
        } else {
            return QString("%1分%2秒").arg(customMinutes).arg(remainingSeconds);
        }
    }
} 