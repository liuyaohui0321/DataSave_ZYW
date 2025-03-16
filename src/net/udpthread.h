#ifndef UDPTHREAD_H
#define UDPTHREAD_H

#include <QObject>
#include <QThread>
#include <QUdpSocket>
#include <QFile>
#include <QTimer>
#include "../helper/dsv_define.h"

class UDPThread : public QThread
{
    Q_OBJECT
public:
    explicit UDPThread(QObject *parent = nullptr);

//    void setUdpModule(bool b)
//    {
//        isMvppModule = b;
//    }

    QString m_path;
//    double p,hz;
    void setPath(QString path)
    {
        m_path = path;
    }

    void writeDataToFile(const QByteArray& data);
    void writeDataToFileMvpp(const QByteArray& data);

    void setUdpInfo(QString newip,quint16 newport)
    {
        ip = newip;
        port = newport;
    }

    void startConnect(QString ip,quint16 port);

public slots:
    void slot_onDataReceived();
    void slot_addHead(const QString &path,double p,double hz);
    void abortExport();
    //void slot_connect(QString ip,quint16 port);
    void slot_setPath(const QString &path);
    void slot_get10GExportCap(const quint64 &len);

signals:
    void sign_mainShowUDP(const QString ip,const quint16 port);
    void sign_tellMainUdpDisconnect();
    void sign_recvFinished();
    void sign_10GexportProgress(int percent);
    void sign_10GexportFinished();

private:
    QUdpSocket *udpSocket;

    QString ip;
    quint16 port;

//    bool isMvppModule;
    quint64 receivedBytes = 0;
    quint64 totalBytes = 0;
    bool abortFlag = false;    // 中止标志
    bool exportCompleted = false;  // 导出完成标志位
    int lastProgress = 0;
    QTimer *m_timer1;
    QTimer *m_stallTimer1;
};

#endif // UDPTHREAD_H
