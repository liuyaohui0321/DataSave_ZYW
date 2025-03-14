// PlaybackMonitor.h - 独立的回放监控线程
#ifndef PLAYBACKMONITOR_H
#define PLAYBACKMONITOR_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QElapsedTimer>

class PlaybackMonitor: public QThread
{
    Q_OBJECT
public:
    explicit PlaybackMonitor(QObject *parent = nullptr) : QThread(parent), abortFlag(false) {}
    virtual ~PlaybackMonitor();

    void abort();
protected:
    void run() override
    {
        QMutexLocker locker(&mutex);

        // 初始化计数器，用于显示进度条动画
        int progress = 0;

        while (!abortFlag)
        {
            // 释放锁，允许其他线程修改状态
            mutex.unlock();

            // 发送进度更新信号
            progress = (progress + 1) % 101; // 0-100循环
            emit progressUpdated(progress);

            // 检查是否超时
            elapsedTimer.start();

            // 重新获取锁
            mutex.lock();

            // 等待条件变量或超时(100毫秒)
            condition.wait(&mutex, 100);
        }
    }

signals:
    void progressUpdated(int value);

private:
    QMutex mutex;
    QWaitCondition condition;
    bool abortFlag;
    QElapsedTimer elapsedTimer;
};

#endif // PLAYBACKMONITOR_H
