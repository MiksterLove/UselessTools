#ifndef POWERCHECKWINDOW_H
#define POWERCHECKWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QProgressBar>
#include <QVBoxLayout>
#include <QTimer>
#include <QMessageBox>

class PowerCheckWindow : public QWidget
{
    Q_OBJECT

public:
    explicit PowerCheckWindow(QWidget *parent = nullptr);

private slots:
    void startCheck();
    void updateProgress();
    void checkComplete();
    void resetWindow();

private:
    QLabel *titleLabel;
    QPushButton *checkButton;
    QProgressBar *progressBar;
    QTimer *checkTimer;
    int progress;
};

#endif // POWERCHECKWINDOW_H 