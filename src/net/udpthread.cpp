#include "udpthread.h"
#include <QDebug>

UDPThread::UDPThread(QObject *parent)
    : QThread{parent}
{
    udpSocket = new QUdpSocket(this);
    //qDebug()<<"UDP threa create successed.";
    connect(udpSocket, &QUdpSocket::readyRead, this, &UDPThread::slot_onDataReceived);
    connect(udpSocket,&QUdpSocket::disconnected,this,[=](){
        emit sign_tellMainUdpDisconnect();
    });

    m_timer = new QTimer(this);
    connect(m_timer,&QTimer::timeout,this,[=](){
        emit sign_recvFinished();
        m_timer->stop();
    });
}

void UDPThread::slot_onDataReceived()
{
    QByteArray datagram;
    QHostAddress sender;
    quint16 senderPort;
    while (udpSocket->hasPendingDatagrams())
    {
        m_timer->start(1000);
        datagram.resize(udpSocket->pendingDatagramSize());
        qint64 readByte= udpSocket->readDatagram(datagram.data(), datagram.size(),&sender,&senderPort);
        //qDebug() << "Received from" << sender.toString() << ":" << senderPort<< "Data:" << readByte;

        static  QByteArray tempbuf;
        tempbuf.append(datagram);
        //qDebug()<<"buffer append data size = "<<tempbuf.size();
        if(tempbuf.size()>=1024*1024)
        {
            if(isMvppModule==false)
            {
                //qDebug() << "UDP common module get data size = "<<tempbuf.size();
                writeDataToFile(tempbuf);
                tempbuf.clear();
            }
            else
            {
                //qDebug() << "UDP mvpp module get data size = "<<tempbuf.size();
                writeDataToFileMvpp(tempbuf);
                tempbuf.clear();
            }
        }
        else
        {
            continue;
        }

    } 
}

void UDPThread::slot_addHead(const QString &path,double p,double hz)
{
    QFile m_file(path);
    if (!m_file.open(QIODevice::WriteOnly | QIODevice::Append)) {
        //qWarning() << "add head Failed to open file for writing:" << m_file.fileName();
        return;
    }
    m_file.write(reinterpret_cast<const char*>(&p),sizeof(double));
    m_file.write(reinterpret_cast<const char*>(&hz),sizeof(double));
    m_file.close();
}

void UDPThread::slot_setPath(const QString &path)
{
    m_path = path;
}


void UDPThread::writeDataToFile(const QByteArray& data)
{
    QFile file(m_path);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Append)) {
        //qWarning() << "common module Failed to open file for writing:" << file.fileName();
        return;
    }

    qint64 bytesWritten =file.write(data.constData(),data.size());
    if (bytesWritten == -1)
    {
        //qWarning() << "Failed to write data to file:" << file->fileName();
        return;
    }

    file.close();
}

void UDPThread::writeDataToFileMvpp(const QByteArray &data)
{
    qDebug()<<"DUP正在使用MVPP模式导出数据·······"<<"数据的大小为 = "<<data.size();
    static QByteArray tempData;
    tempData.append(data);

    if(tempData.size()%2!=0)    //奇数
    {
        return;
    }
    else
    {
        QFile file(m_path);
        QVector<float> mvppVector;
        static float factor = NOXISHU;

        int buffersize = tempData.size();
        if(buffersize%2!=0)
        {
            buffersize-=1;
        }
        for (int i = 0; i < buffersize; i+=2)
        {
            float tmp = static_cast<float>(static_cast<int16_t>((tempData.at(i) & 0xff) | (tempData.at(i+1) << 8))*factor);
            mvppVector.append(tmp);
        }

        QByteArray writeArray;
        int datasize = mvppVector.size() * sizeof(float);
        writeArray.resize(datasize);
        memcpy(writeArray.data(), mvppVector.constData(), datasize);

        if (!file.open(QIODevice::WriteOnly | QIODevice::Append)) {
            qWarning() << "mvpp module Failed to open file for writing:" << file.fileName();
            return;
        }

        qint64 bytesWritten = file.write(writeArray.constData(),writeArray.size());
        if (bytesWritten == -1)
        {
            qWarning() << "Failed to write data to file:" << file.fileName();
            return;
        }
        // else
        // {
        //     file.flush();
        // }
        file.close();
    }

}

void UDPThread::startConnect(QString ip, quint16 port)
{

    //如果有绑定则断开重新绑定
    if(udpSocket->state() == QAbstractSocket::BoundState)
    {
        udpSocket->disconnect();
        //udpSocket->abort();
    }

    if (udpSocket->bind(QHostAddress(ip), port))
    {
        qDebug() << "UDP socket successfully bound to" << QHostAddress(ip).toString() << "port" << port;
        emit sign_mainShowUDP(ip,port);
    } else {
        qWarning() << "Failed to bind UDP socket:" << udpSocket->errorString();
    }
}

