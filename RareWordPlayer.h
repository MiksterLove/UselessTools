#ifndef RAREWORDPLAYER_H
#define RAREWORDPLAYER_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QProgressBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTimer>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

class RareWordPlayer : public QWidget
{
    Q_OBJECT

public:
    explicit RareWordPlayer(QWidget *parent = nullptr);
    ~RareWordPlayer();

private slots:
    void startPlay();
    void resetInput();
    void updateProgress();
    void onTextChanged(const QString &text);
    void playAudio();

private:
    QString getMciErrorString(MCIERROR error);
    void closeAudio();

private:
    QLabel *titleLabel;
    QLineEdit *wordInput;
    QPushButton *playButton;
    QPushButton *resetButton;
    QProgressBar *progressBar;
    QTimer *progressTimer;
    QLabel *statusLabel;
    int progress;
    QString tempFilePath;
};

#endif // RAREWORDPLAYER_H 