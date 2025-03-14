#include "playbackmonitor.h"


PlaybackMonitor::~PlaybackMonitor()
{
    abort();
    wait();
}

void PlaybackMonitor::abort()
{
    QMutexLocker locker(&mutex);
    abortFlag = true;
    condition.wakeOne();
}
