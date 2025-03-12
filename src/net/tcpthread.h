#ifndef TCPTHREAD_H
#define TCPTHREAD_H

#include <QObject>
#include <QThread>
#include <QTcpServer>
#include <QTcpSocket>
#include <QByteArray>
#include <QFile>

#include "../helper/dsv_define.h"
#include "datapacketparser.h"
#include "directoryparser.h"
#include "../helper/protocol_disk.h"

class TCPThread : public QThread
{
    Q_OBJECT
public:
    explicit TCPThread(QObject *parent = nullptr);

//    void setExportModule(bool b)
//    {
//        checkIfMvpp = b;
//        //qDebug()<<"接收线程中的mvpp标志位 = "<<checkIfMvpp;
//    }

    void setExportFileInfo(const ExportFileInfo &info)
    {
        tcp_exportFileInfo = info;
        //qDebug()<<" TCP线程中标志位，是否为数据导出"<<tcp_exportFileInfo.isReceivingFileInfo;
    }

    //解析收到的应答帧
    void processCompletePacket( QByteArray& data);
    Cmd_Disk_State_Info readDataDiskState(const QByteArray &data);
    Cmd_Response_Common_Info readDataCommon(const QByteArray &data);
    Cmd_File_Attribute_Answer_Info readDataFileInfo(const QByteArray &data);
    Cmd_Folder_Attribute_Answer_Info readDataFolderInfo(const QByteArray &data);
    Cmd_One_File_Info parseOneFileInfo(QByteArray &data, int &offset);
    Cmd_Catalog_Info parseCatalogInfo(QByteArray &data);

//    double p,hz;
    bool m_abortFlag = false; // 新增中止标志
    bool m_exportCompleted = false;  // 新增导出完成标志位

public slots:
    void slot_getCmd(const QByteArray &cmd);
    void slot_getLenCmd(const QByteArray &cmd,const int &len);
    void slot_getExportCap(const uint64_t &len);
//    void slot_addTcpHead(const QString &path,double p,double hz);

//public:
    void abortExport();

signals:
    //用于告诉主窗口的信号
    void sign_waitConnect();    //服务器等待连接
    void sign_getNewConnect(const QString &client); //获取到了新的连接
    void sign_tcpNotConnect();  //提示当前连接未建立
    void sign_tellMainDisconnect();     //提示当前连接已经断开

    //解析出来的内容
    void sign_diskData(const Cmd_Disk_State_Info &data);
    //void sign_commonData(const Cmd_Response_Common_Info *data);
    void sign_catalogData(const Cmd_Catalog_Info *data);
    void sign_fileData(const Cmd_File_Attribute_Answer_Info *data);
    void sign_folderData(const Cmd_Folder_Attribute_Answer_Info *data);

    void sign_newCommonData(const quint32 &type,const quint32 &id,const quint32 &result);

    //发送目录树信息
    void sign_sendDirectoryParser(QStandardItemModel *data);
    void sign_speed(uint data);     //获取存盘速度
    void sign_exportProgress(int percent);
    void sign_exportFinished();

private slots:
    void slot_newConnection();      //建立新的连接
    void onReadyRead(); //读取数据和返回真

private:

    //数据导出的两种方式
    void processFileData(const QByteArray& data);
    void processFileDataMVPP(const QByteArray &data);

    QTcpServer *m_tcpSever;
    QTcpSocket *m_tcpsocket;

    QByteArray m_dataBuffer;        //缓存区

//    bool checkIfMvpp = false;
    ExportFileInfo tcp_exportFileInfo;//导出文件信息

    QTimer *m_timer;
    quint64 m_receivedBytes = 0;
    quint64 m_totalBytes = 0;
};

#endif // TCPTHREAD_H
