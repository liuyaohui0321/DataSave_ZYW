#include "playbackdialog.h"

playbackDialog::playbackDialog(QWidget *parent) : QDialog(parent)
{
    // 设置对话框为模态
    setModal(true);
    setWindowTitle("回放进行中");

    // 创建界面元素
    statusLabel = new QLabel("回放数据中...", this);
    progressBar = new QProgressBar(this);
    progressBar->setRange(0, 100);
    progressBar->setTextVisible(false); // 不显示百分比数字

    stopButton = new QPushButton("停止回放", this);

    // 布局
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(statusLabel);
    layout->addWidget(progressBar);
    layout->addWidget(stopButton);
    setLayout(layout);
    // 移除关闭按钮（需保留其他标志，避免影响窗口行为）
    setWindowFlags(windowFlags() & ~Qt::WindowCloseButtonHint);
    // 连接停止按钮信号
    connect(stopButton, &QPushButton::clicked, this, &playbackDialog::onStopButtonClicked);

    // 创建并启动监控线程
    monitor = new PlaybackMonitor(this);
    connect(monitor, &PlaybackMonitor::progressUpdated,
            this, &playbackDialog::updateProgress, Qt::QueuedConnection);

    // 超时检测
    timeoutTimer = new QTimer(this);
    timeoutTimer->setSingleShot(false);
    connect(timeoutTimer, &QTimer::timeout, this, &playbackDialog::checkTimeout);
    timeoutSeconds = 0;

    // 固定大小
    setMinimumWidth(300);
    resize(300, 150);

    // 启动监控和计时
    monitor->start();
    timeoutTimer->start(1000); // 每秒更新一次
}

playbackDialog::~playbackDialog()
{
    if (monitor && monitor->isRunning())
    {
        monitor->abort();
        monitor->wait();
    }

    if (timeoutTimer && timeoutTimer->isActive())
    {
        timeoutTimer->stop();
    }
}

void playbackDialog::updateProgress(int value)
{
    progressBar->setValue(value);
    // 动态更新文本
    static const QStringList animations =
    {
        "回放数据中   ",
        "回放数据中.  ",
        "回放数据中.. ",
        "回放数据中..."
    };
    statusLabel->setText(animations[value % animations.size()]);
}

void playbackDialog::checkTimeout()
{
    timeoutSeconds++;
    // 如果回放时间超过60秒，显示提示
    if (timeoutSeconds >= 60 && timeoutSeconds % 60 == 0) {
        emit playbackMaybeHanging(timeoutSeconds);
        statusLabel->setText(QString("回放已持续 %1 秒...").arg(timeoutSeconds));
    }
}
