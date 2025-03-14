#ifndef PLAYBACKDIALOG_H
#define PLAYBACKDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QProgressBar>
#include <QTimer>
#include "PlaybackMonitor.h"

class playbackDialog : public QDialog
{
    Q_OBJECT
public:
    explicit playbackDialog(QWidget *parent = nullptr);
    ~playbackDialog();
public slots:
    // 接收到停止回放信号时调用
    void onPlaybackStopped()
    {
        if (monitor && monitor->isRunning()) {
            monitor->abort();
        }
        if (timeoutTimer && timeoutTimer->isActive()) {
            timeoutTimer->stop();
        }
        accept(); // 关闭对话框并返回 Accepted
    }

signals:
    // 停止按钮被点击时发出
    void stopRequested();
    // 提示可能超时
    void playbackMaybeHanging(int seconds);

private slots:
    void onStopButtonClicked()
    {
        stopButton->setEnabled(false); // 防止重复点击
        stopButton->setText("正在停止...");
        emit stopRequested();// 注意：不在这里关闭对话框，等待实际停止信号
    }

    void updateProgress(int value);

    void checkTimeout();

private:
    QLabel *statusLabel;
    QProgressBar *progressBar;
    QPushButton *stopButton;
    PlaybackMonitor *monitor;
    QTimer *timeoutTimer;
    int timeoutSeconds;
};

#endif // PLAYBACKDIALOG_H
