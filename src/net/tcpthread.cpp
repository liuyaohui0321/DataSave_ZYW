#include "tcpthread.h"
#include <QDebug>
#include "../helper/dsv_define.h"
#include <cstring>
#include <iostream>
#include <QTimer>
using namespace std;

TCPThread::TCPThread(QObject *parent)
    : QThread{parent}
{
    m_tcpSever = new QTcpServer(this);
    if (m_tcpSever->listen(QHostAddress::Any, DSV_PORT))
    {
        emit sign_waitConnect();
    }
    connect(m_tcpSever, &QTcpServer::newConnection, this, &TCPThread::slot_newConnection);

    m_timer = new QTimer(this);
    connect(m_timer,&QTimer::timeout,this,[=](){
        tcp_exportFileInfo.isReceivingFileInfo = false;
        m_timer->stop();
    });

    m_stallTimer = new QTimer(this);
    connect(m_stallTimer, &QTimer::timeout, this, [this]()
    {
        if (!m_exportCompleted)
        {
//            qWarning() << "检测到进度停滞，强制完成导出";
            m_receivedBytes = 0;
            m_exportCompleted = true;
//            emit sign_SetexportProgress(100);  // 立即更新进度
            emit sign_exportFinished();
            m_stallTimer->stop();
        }
    });
}

void TCPThread::slot_getCmd(const QByteArray &cmd)
{
    if(m_tcpsocket!=nullptr)
    {
        QAbstractSocket::SocketState state = m_tcpsocket->state();
        //qDebug()<<"TCP的连接状态 = "<<state;
        if(state == QAbstractSocket::ConnectedState )
        {
            quint64 bytesWritten = m_tcpsocket->write(cmd);
            if(bytesWritten<0){
                //qDebug()<<"指令发送失败";
            }
            else{
                qDebug()<<"指令发送成功";
            }
        }
        else
        {
            //qDebug()<<"#########################";
            emit sign_tcpNotConnect();
        }
    }
}

void TCPThread::slot_getLenCmd(const QByteArray &cmd,const int &len)
{
    if(m_tcpsocket!=nullptr)
    {
        QAbstractSocket::SocketState state = m_tcpsocket->state();
        //qDebug()<<"TCP的连接状态 = "<<state;
        if(state == QAbstractSocket::ConnectedState )
        {
            quint64 bytesWritten = m_tcpsocket->write(cmd);
            if(bytesWritten<0){
                //qDebug()<<"指令发送失败";
            }
            else{
                //qDebug()<<"指令发送成功";
            }
        }
        else
        {
            //qDebug()<<"#########################";
            emit sign_tcpNotConnect();
        }
    }

}

void TCPThread::slot_getExportCap(const quint64 &len)
{
    m_totalBytes=len;
    m_receivedBytes=0;
    m_abortFlag = false;
    m_exportCompleted = false;
    m_lastProgress=0;//3.17
    qDebug() << "m_totalBytes:" << m_totalBytes;
}

//void TCPThread::slot_addTcpHead(const QString &path,double p, double hz)
//{
//    QFile file(path);
//    if (!file.open(QIODevice::WriteOnly | QIODevice::Append)) {
//        qWarning() << "add head Failed to open file for writing:" <<file.fileName();
//        return;
//    }
//    file.write(reinterpret_cast<const char*>(&p),sizeof(double));
//    file.write(reinterpret_cast<const char*>(&hz),sizeof(double));
//    file.close();
//}


void TCPThread::slot_newConnection()
{
    //qDebug() << "进入到了连接的槽函数中.";
    QTcpSocket *clientSocket = m_tcpSever->nextPendingConnection();

    m_tcpsocket = clientSocket;
    QString client = clientSocket->peerAddress().toString();
    client.replace("::ffff:", "");
    //qDebug() << "连接的客户端:" << client;
    emit sign_getNewConnect(client);

    connect(m_tcpsocket, &QTcpSocket::readyRead, this, &TCPThread::onReadyRead);
    connect(m_tcpsocket,&QTcpSocket::disconnected,this,[=](){
        emit sign_tellMainDisconnect();
    });
}

void TCPThread::onReadyRead()
{
    m_timer->start(1000);
    QByteArray data = m_tcpsocket->readAll();
    if(data.size()==0)
    {
        //qDebug()<<"TCP收到的数据大小是0";
        return;
    }

    //应答帧
//    if(tcp_exportFileInfo.isReceivingFileInfo==false && checkIfMvpp==false)
    if(tcp_exportFileInfo.isReceivingFileInfo==false)
    {
        m_dataBuffer.append(data);
        if (m_dataBuffer.isEmpty()) {
            return; // 没有接收到数据
        }

        // 获取包头和包尾
        uint32_t header = *reinterpret_cast<uint32_t*>(m_dataBuffer.data());
        uint32_t footer = *reinterpret_cast<uint32_t*>(m_dataBuffer.data() + m_dataBuffer.size() - sizeof(uint32_t));
        if (header == HEAD && footer == END) {
            // 找到完整的数据包，处理数据
            //qDebug() <<"收到了完整的目录数据包，长度为"<< m_dataBuffer.size()<<"开始准备解析目录";
            //解析树目录
            processCompletePacket(m_dataBuffer);
            // 清空缓冲区
            m_dataBuffer.clear();
        }
        else {
            //qDebug() << "没有找到完整的数据包，退出当前检查";
        }
    }
//    else if(tcp_exportFileInfo.isReceivingFileInfo==true  && checkIfMvpp==false)
    else if(tcp_exportFileInfo.isReceivingFileInfo==true)
    {
        //qDebug()<<"收到了要导出的数据,正常模式导出";
        processFileData(data);  //接收要导出的数据
    }
//    else if(tcp_exportFileInfo.isReceivingFileInfo==true  && checkIfMvpp==true)
//    {
//        //qDebug()<<"收到了要导出的数据，使用mvpp模式导出";
//        processFileDataMVPP(data);  //接收要导出的数据
//    }
    else
    {
        //qDebug()<<"TCP收到的数据判断错误";
    }
}

//解析收到的应答真
void TCPThread::processCompletePacket(QByteArray &data)
{
    //qDebug() << "————————————正在解析应答帧——————————————";

    DataPacketParser dataParser(data);
    if (!dataParser.isValid()) {
        //qDebug() << "输入的报文格式错误";
        return;
    }

    uint32_t head = dataParser.getHead();         //包头
    uint32_t source_ID = dataParser.getSourceID();    //源组件ID，0
    uint32_t dest_ID = dataParser.getDestID();      //目的组件ID，0
    uint32_t oper_type = dataParser.getOperType();    //操作类型
    uint32_t oper_ID = dataParser.getOperID();      //操作ID
    uint32_t package_num = dataParser.getPackageNum();   //包序列号，0
    uint32_t end = dataParser.getEnd();


    //qDebug() << "包头：" << hex << head;
    //qDebug() << "源组件：" << hex << source_ID;
    //qDebug() << "目的组件：" << hex << dest_ID;
    //qDebug() << "操作类型：" << hex << oper_type;
    //qDebug() << "操作ID：" << hex << oper_ID;
    //qDebug() << "包尾：" << hex << end;

    if (head == HEAD && end == END && oper_type == 0xF2 && oper_ID == 0x01) {
        qDebug() << "收到磁盘状态回复消息";
        Cmd_Disk_State_Info diskInfo = readDataDiskState(data);
        emit sign_diskData(diskInfo);
    }
    if (head == HEAD && end == END && oper_type == 0xA2 && oper_ID == 0x03) {
        qDebug() << "文件、文件夹及磁盘管理操作结果通用应答";
        Cmd_Response_Common_Info commonInfo = readDataCommon(data);
        qDebug()<<"tcp线程中，收到的通用应答包操作类型："<<hex<<commonInfo.res_type;
        qDebug()<<"tcp线程中，收到的通用应答包操作ID："<<hex<<commonInfo.res_ID;
        qDebug()<<"tcp线程中，收到的通用应答包jieguo："<<hex<<commonInfo.res_result;
        //emit sign_commonData(&commonInfo);
        emit sign_newCommonData(commonInfo.res_type,commonInfo.res_ID,commonInfo.res_result);
    }
    //刷新目录树操作
    if (head == HEAD && end == END && oper_type == 0xA2 && oper_ID == 0x08) {

        // 创建根目录信息，表示文件系统的根节点
        FileOrFolderInfo rootInfo;
        rootInfo.name = "0:";     // 根文件夹的名称
        rootInfo.type = "Folder";   // 根项为文件夹

        // 调用解析函数，解析整个文件系统并存储到rootInfo结构体中
        DirectoryParser parser;
        parser.parsePackage(data, rootInfo);        //解析出包头包体和包尾
        parser.rebuildFileOrFolderTree(rootInfo);

        // 创建模型并将 FileOrFolderInfo 转换为模型数据
        QStandardItemModel *model = parser.createModelFromFileOrFolderInfo(rootInfo);
        emit sign_sendDirectoryParser(model);
    }
    if(head == HEAD && end == END && oper_type == 0xA5 && oper_ID == 0x11)
    {
        //qDebug() << "获取速度的应答包."<<data.toHex();
        uint32_t speed;
        std::memcpy(&speed, data.constData() + 20, sizeof(4));
        //qDebug()<<"获取到的速度为 = "<<speed;
        emit sign_speed(speed);
    }
    if(head == HEAD && end == END && oper_type == 0xB5 && oper_ID == 0x11)
    {
//        qDebug() << "获取回放结束的应答包."<<data.toHex();
        emit stopplayback();
    }
    if(head == HEAD && end == END && oper_type == 0xC5 && oper_ID == 0x11)
    {
        qDebug() << "收到导出完成应答包";
        emit sign_exportFinished1();
    }
}


void TCPThread::processFileData(const QByteArray& data)
{
    // 如果已经完成导出，忽略后续数据
    if (m_exportCompleted)
    {
        return;
    }
    QByteArray dataTemp=data;
    //qDebug() << "TCP 正常模式导出文件中······"<<" 当前收到的数据大小为 = "<<dataTemp.size();
    QFile receivedFile(tcp_exportFileInfo.localPath);
    if (!receivedFile.open(QIODevice::WriteOnly | QIODevice::Append)) {
        qWarning() << "common module Failed to open file for writing:" << receivedFile.fileName();
        return;
    }

    // 写入文件
    qint64 bytesWritten = receivedFile.write(data.constData(), data.size());
    if (bytesWritten == -1) {
        qWarning() << "Failed to write data to file:" << receivedFile.fileName();
        return;
    }
    if (m_abortFlag) // 中止标志检查
    {
        qDebug() << "导出已中止";
        return;
    }
//    // 新增进度计算
//     m_receivedBytes += data.size();
//     int progress = static_cast<int>((m_receivedBytes * 100) / m_totalBytes);
//     // 进度未到100时发送进度信号
//     if (progress < 100) {
//         emit sign_exportProgress(progress);
//     }
//     // 当进度达到或超过100时，重置计数并发送完成信号
//     else {
//         m_receivedBytes = 0;
//         m_exportCompleted = true;
//         emit sign_exportFinished();
//     }
    m_receivedBytes += data.size();
    int progress = static_cast<int>((m_receivedBytes * 100) / m_totalBytes);
    // 检测进度停滞
    if (progress >= 97 && progress <= 99)
    {
        if (progress != m_lastProgress)
        {
            m_lastProgress = progress;
//            m_stallTimer->start(8000); // 8秒超时检测
            int mSec=0;
            if((m_totalBytes>0)&&(m_totalBytes<=0x40000000*8))  mSec=8;
            else if ((m_totalBytes>0x40000000*8)&&(m_totalBytes<=0x40000000*16)) mSec=16;
            else if ((m_totalBytes>0x40000000*16)&&(m_totalBytes<=0x40000000*32)) mSec=32;
            else if (m_totalBytes>0x40000000*32)   mSec=60;
            m_stallTimer->start(mSec); // 超时检测
        }
    }
    else
    {
        m_stallTimer->stop();
    }

    // 进度未到100时发送进度信号
     if (progress < 100)
     {
         emit sign_exportProgress(progress);
     }
     // 当进度达到或超过100时，重置计数并发送完成信号
     else
     {
        m_stallTimer->stop();
        m_receivedBytes = 0;
        m_exportCompleted = true;
        m_lastProgress=0;
        emit sign_exportFinished();
     }

     receivedFile.close();
}

//void TCPThread::processFileDataMVPP(const QByteArray &data)
//{
//    //qDebug()<<"TCP正在使用MVPP模式导出数据·······"<<"数据的大小为 = "<<data.size();
//    static QByteArray tempData;
//    tempData.append(data);

//    if(tempData.size()%2!=0)    //奇数
//    {
//        return;
//    }
//    else
//    {
//        QVector<float> mvppVector;
//        static float factor = NOXISHU;
//        for (int i = 0; i < tempData.size(); i+=2)
//        {
//            float tmp = static_cast<float>(static_cast<int16_t>((tempData.at(i) & 0xff) | (tempData.at(i+1) << 8))*factor);
//            mvppVector.append(tmp);
//        }

//        QByteArray writeArray;
//        int datasize = mvppVector.size() * sizeof(float);
//        writeArray.resize(datasize);
//        memcpy(writeArray.data(), mvppVector.constData(), datasize);

//        // 写入文件
//        QFile receivedFile(tcp_exportFileInfo.localPath);
//        if (!receivedFile.open(QIODevice::WriteOnly | QIODevice::Append)) {
//            qWarning() << "mvpp module Failed to open file for writing:" << receivedFile.fileName();
//            return;
//        }
//        qint64 bytesWritten = receivedFile.write(writeArray.constData(), writeArray.size());
//        if (bytesWritten == -1)
//        {
//            qWarning() << "Failed to write TCP commom module data to file:" << receivedFile.fileName();
//            return;
//        }
//        mvppVector.clear();     //每次填充完后清空一下数组
//        receivedFile.close();
//        tempData.clear();
//    }
//}

void TCPThread::abortExport()
{
    // 只有在实际导出过程中才执行中止操作
    if (!m_exportCompleted && m_receivedBytes > 0 && m_receivedBytes < m_totalBytes)
    {
        m_abortFlag = true;
        m_exportCompleted = true;  // 设置完成标志，防止后续数据处理
//        if (m_tcpsocket)
//        {
//            m_tcpsocket->abort(); // 中止当前连接
//        }
        m_receivedBytes = 0;
        tcp_exportFileInfo.isReceivingFileInfo = false;
        m_stallTimer->stop(); // 中止时需要停止计时器
    }
}


//但是只能返回磁盘的状态
Cmd_Disk_State_Info TCPThread::readDataDiskState(const QByteArray &data) {
    Cmd_Disk_State_Info diskData;
    int offset = 0;
    // 解析各字段
    std::memcpy(&diskData.head, data.constData() + offset, sizeof(diskData.head));
    offset += sizeof(diskData.head);

    std::memcpy(&diskData.source_ID, data.constData() + offset, sizeof(diskData.source_ID));
    offset += sizeof(diskData.source_ID);

    std::memcpy(&diskData.dest_ID, data.constData() + offset, sizeof(diskData.dest_ID));
    offset += sizeof(diskData.dest_ID);

    std::memcpy(&diskData.oper_type, data.constData() + offset, sizeof(diskData.oper_type));
    offset += sizeof(diskData.oper_type);

    std::memcpy(&diskData.oper_ID, data.constData() + offset, sizeof(diskData.oper_ID));
    offset += sizeof(diskData.oper_ID);

    std::memcpy(&diskData.package_num, data.constData() + offset, sizeof(diskData.package_num));
    offset += sizeof(diskData.package_num);

    std::memcpy(&diskData.disk_total, data.constData() + offset, sizeof(diskData.disk_total));
    offset += sizeof(diskData.disk_total);

    std::memcpy(&diskData.disk_used, data.constData() + offset, sizeof(diskData.disk_used));
    offset += sizeof(diskData.disk_used);

    std::memcpy(&diskData.disk_rest, data.constData() + offset, sizeof(diskData.disk_rest));
    offset += sizeof(diskData.disk_rest);

    std::memcpy(&diskData.file_num, data.constData() + offset, sizeof(diskData.file_num));
    offset += sizeof(diskData.file_num);

    std::memcpy(&diskData.disk_state, data.constData() + offset, sizeof(diskData.disk_state));
    offset += sizeof(diskData.disk_state);

    std::memcpy(&diskData.disk_t, data.constData() + offset, sizeof(diskData.disk_t));
    offset += sizeof(diskData.disk_t);

    std::memcpy(&diskData.disk_power, data.constData() + offset, sizeof(diskData.disk_power));
    offset += sizeof(diskData.disk_power);

    std::memcpy(&diskData.disk_open_num, data.constData() + offset, sizeof(diskData.disk_open_num));
    offset += sizeof(diskData.disk_open_num);

    std::memcpy(&diskData.check, data.constData() + offset, sizeof(diskData.check));
    offset += sizeof(diskData.check);

    std::memcpy(&diskData.end, data.constData() + offset, sizeof(diskData.end));
    offset += sizeof(diskData.end);

    return diskData;

}

Cmd_Response_Common_Info TCPThread::readDataCommon(const QByteArray &data)
{
    Cmd_Response_Common_Info commonData;

    int offset = 0;

    // 解析各字段

    std::memcpy(&commonData.head, data.constData() + offset, sizeof(commonData.head));
    offset += sizeof(commonData.head);

    std::memcpy(&commonData.source_ID, data.constData() + offset, sizeof(commonData.source_ID));
    offset += sizeof(commonData.source_ID);

    std::memcpy(&commonData.dest_ID, data.constData() + offset, sizeof(commonData.dest_ID));
    offset += sizeof(commonData.dest_ID);

    std::memcpy(&commonData.oper_type, data.constData() + offset, sizeof(commonData.oper_type));
    offset += sizeof(commonData.oper_type);

    std::memcpy(&commonData.oper_ID, data.constData() + offset, sizeof(commonData.oper_ID));
    offset += sizeof(commonData.oper_ID);

    std::memcpy(&commonData.package_num, data.constData() + offset, sizeof(commonData.package_num));
    offset += sizeof(commonData.package_num);

    std::memcpy(&commonData.res_package_num, data.constData() + offset, sizeof(commonData.package_num));
    offset += sizeof(commonData.res_package_num);

    std::memcpy(&commonData.res_type, data.constData() + offset, sizeof(commonData.res_type));
    offset += sizeof(commonData.res_type);

    std::memcpy(&commonData.res_ID, data.constData() + offset, sizeof(commonData.res_ID));
    offset += sizeof(commonData.res_ID);

    std::memcpy(&commonData.res_result, data.constData() + offset, sizeof(commonData.res_result));
    offset += sizeof(commonData.res_result);

    std::memcpy(commonData.res_byte, data.constData() + offset, sizeof(commonData.res_byte));
    offset += sizeof(commonData.res_byte);

    std::memcpy(&commonData.check, data.constData() + offset, sizeof(commonData.check));
    offset += sizeof(commonData.check);

    std::memcpy(&commonData.end, data.constData() + offset, sizeof(commonData.end));
    offset += sizeof(commonData.end);

    return commonData;

}

//解析出文件属性应答的报文
Cmd_File_Attribute_Answer_Info TCPThread::readDataFileInfo(const QByteArray &data) {
    Cmd_File_Attribute_Answer_Info fileInfo;

    // 检查 data 的大小是否符合预期
    if (data.size() < sizeof(Cmd_File_Attribute_Answer_Info)) {
        // 处理错误，例如抛出异常或返回一个无效的结构体
        //qDebug() << "Data size is too small!";
    }

    int offset = 0;

    // 解析各字段
    std::memcpy(&fileInfo.head, data.constData() + offset, sizeof(fileInfo.head));
    offset += sizeof(fileInfo.head);

    std::memcpy(&fileInfo.source_ID, data.constData() + offset, sizeof(fileInfo.source_ID));
    offset += sizeof(fileInfo.source_ID);

    std::memcpy(&fileInfo.dest_ID, data.constData() + offset, sizeof(fileInfo.dest_ID));
    offset += sizeof(fileInfo.dest_ID);

    std::memcpy(&fileInfo.oper_type, data.constData() + offset, sizeof(fileInfo.oper_type));
    offset += sizeof(fileInfo.oper_type);

    std::memcpy(&fileInfo.oper_ID, data.constData() + offset, sizeof(fileInfo.oper_ID));
    offset += sizeof(fileInfo.oper_ID);

    std::memcpy(&fileInfo.package_num, data.constData() + offset, sizeof(fileInfo.package_num));
    offset += sizeof(fileInfo.package_num);

    std::memcpy(fileInfo.file_name, data.constData() + offset, sizeof(fileInfo.file_name));
    offset += sizeof(fileInfo.file_name);

    std::memcpy(fileInfo.file_address, data.constData() + offset, sizeof(fileInfo.file_address));
    offset += sizeof(fileInfo.file_address);

    std::memcpy(&fileInfo.file_size, data.constData() + offset, sizeof(fileInfo.file_size));
    offset += sizeof(fileInfo.file_size);

    std::memcpy(&fileInfo.file_readWrite_control, data.constData() + offset, sizeof(fileInfo.file_readWrite_control));
    offset += sizeof(fileInfo.file_readWrite_control);

    std::memcpy(&fileInfo.file_show_control, data.constData() + offset, sizeof(fileInfo.file_show_control));
    offset += sizeof(fileInfo.file_show_control);

    std::memcpy(fileInfo.byte_backups, data.constData() + offset, sizeof(fileInfo.byte_backups));
    offset += sizeof(fileInfo.byte_backups);

    std::memcpy(&fileInfo.check, data.constData() + offset, sizeof(fileInfo.check));
    offset += sizeof(fileInfo.check);

    std::memcpy(&fileInfo.end, data.constData() + offset, sizeof(fileInfo.end));
    offset += sizeof(fileInfo.end);

    return fileInfo;
}

Cmd_Folder_Attribute_Answer_Info TCPThread::readDataFolderInfo(const QByteArray &data) {
    Cmd_Folder_Attribute_Answer_Info folderInfo;

    // 检查 data 的大小是否符合预期
    if (data.size() < sizeof(Cmd_Folder_Attribute_Answer_Info)) {
        // 处理错误，例如抛出异常或返回一个无效的结构体
        //qDebug() << "Data size is too small!";
    }

    int offset = 0;

    // 解析各字段

    std::memcpy(&folderInfo.head, data.constData() + offset, sizeof(folderInfo.head));
    offset += sizeof(folderInfo.head);

    std::memcpy(&folderInfo.source_ID, data.constData() + offset, sizeof(folderInfo.source_ID));
    offset += sizeof(folderInfo.source_ID);

    std::memcpy(&folderInfo.dest_ID, data.constData() + offset, sizeof(folderInfo.dest_ID));
    offset += sizeof(folderInfo.dest_ID);

    std::memcpy(&folderInfo.oper_type, data.constData() + offset, sizeof(folderInfo.oper_type));
    offset += sizeof(folderInfo.oper_type);

    std::memcpy(&folderInfo.oper_ID, data.constData() + offset, sizeof(folderInfo.oper_ID));
    offset += sizeof(folderInfo.oper_ID);

    std::memcpy(&folderInfo.package_num, data.constData() + offset, sizeof(folderInfo.package_num));
    offset += sizeof(folderInfo.package_num);

    std::memcpy(folderInfo.folder_name, data.constData() + offset, sizeof(folderInfo.folder_name));
    offset += sizeof(folderInfo.folder_name);

    std::memcpy(folderInfo.folder_address, data.constData() + offset, sizeof(folderInfo.folder_address));
    offset += sizeof(folderInfo.folder_address);

    std::memcpy(&folderInfo.folder_size, data.constData() + offset, sizeof(folderInfo.folder_size));
    offset += sizeof(folderInfo.folder_size);

    std::memcpy(&folderInfo.have_child_folder_num, data.constData() + offset, sizeof(folderInfo.have_child_folder_num));
    offset += sizeof(folderInfo.have_child_folder_num);

    std::memcpy(&folderInfo.have_file_num, data.constData() + offset, sizeof(folderInfo.have_file_num));
    offset += sizeof(folderInfo.have_file_num);

    std::memcpy(&folderInfo.folder_readWrite_control, data.constData() + offset,
                sizeof(folderInfo.folder_readWrite_control));
    offset += sizeof(folderInfo.folder_readWrite_control);

    std::memcpy(&folderInfo.folder_show_control, data.constData() + offset, sizeof(folderInfo.folder_show_control));
    offset += sizeof(folderInfo.folder_show_control);

    std::memcpy(folderInfo.byte_backups, data.constData() + offset, sizeof(folderInfo.byte_backups));
    offset += sizeof(folderInfo.byte_backups);

    std::memcpy(&folderInfo.check, data.constData() + offset, sizeof(folderInfo.check));
    offset += sizeof(folderInfo.check);

    std::memcpy(&folderInfo.end, data.constData() + offset, sizeof(folderInfo.end));
    offset += sizeof(folderInfo.end);

    return folderInfo;
}

// 从字节流解析出 Cmd_Catalog_Info 结构体
Cmd_Catalog_Info TCPThread::parseCatalogInfo(QByteArray &data) {
    Cmd_Catalog_Info catalog;
    int offset = 0;
    //qDebug() << "此时0的offset = " << offset;

    std::memcpy(&catalog.head, data.constData() + offset, sizeof(catalog.head));
    offset += sizeof(catalog.head);
    //qDebug() << "此时1的offset = " << offset;

    std::memcpy(&catalog.source_ID, data.constData() + offset, sizeof(catalog.source_ID));
    offset += sizeof(catalog.source_ID);
    //qDebug() << "此时2的offset = " << offset;

    std::memcpy(&catalog.dest_ID, data.constData() + offset, sizeof(catalog.dest_ID));
    offset += sizeof(catalog.dest_ID);
    //qDebug() << "此时3的offset = " << offset;

    std::memcpy(&catalog.oper_type, data.constData() + offset, sizeof(catalog.oper_type));
    offset += sizeof(catalog.oper_type);
    //qDebug() << "此时4的offset = " << offset;

    std::memcpy(&catalog.oper_ID, data.constData() + offset, sizeof(catalog.oper_ID));
    offset += sizeof(catalog.oper_ID);
    //qDebug() << "此时5的offset = " << offset;

    std::memcpy(&catalog.answer_package_num, data.constData() + offset, sizeof(catalog.answer_package_num));
    offset += sizeof(catalog.answer_package_num);
    //qDebug() << "此时6的offset = " << offset;

    std::memcpy(&catalog.answer_type, data.constData() + offset, sizeof(catalog.answer_type));
    offset += sizeof(catalog.answer_type);
    //qDebug() << "此时7的offset = " << offset;

    std::memcpy(&catalog.answer_ID, data.constData() + offset, sizeof(catalog.answer_ID));
    offset += sizeof(catalog.answer_ID);
    //qDebug() << "此时8的offset = " << offset;

    std::memcpy(&catalog.file_num, data.constData() + offset, sizeof(catalog.file_num));
    offset += sizeof(catalog.file_num);
    //qDebug() << "此时9的offset = " << offset;

    std::memcpy(&catalog.folder_num, data.constData() + offset, sizeof(catalog.folder_num));
    offset += sizeof(catalog.folder_num);
    //qDebug() << "此时10的offset = " << offset;

    uint32_t totalCount = catalog.file_num + catalog.folder_num;
    //qDebug() << "查看是不是结构体数组越界：" << totalCount;
    catalog.file_obj = new Cmd_One_File_Info[totalCount];   //用来存放单个文件的数组
    //catalog.file_obj = std::make_unique<Cmd_One_File_Info[]>(totalCount);

    //int offsettemp = offset-40;
    QByteArray modifiedByteArray = data.mid(40);
    for (uint32_t i = 0; i < totalCount; ++i) {
        catalog.file_obj[i] = parseOneFileInfo(data, offset);
        data.mid(1088 * (i + 1));
        //qDebug() << "第i个文件：" << QString::fromUtf16(catalog.file_obj[i].file_name);
        //qDebug() << "此时，第" << i << "个offest = " << offset;
    }

    std::memcpy(&catalog.check, data.constData() + offset, sizeof(catalog.check));
    offset += sizeof(catalog.check);
    //qDebug() << "此时11的offset = " << offset;

    std::memcpy(&catalog.end, data.constData() + offset, sizeof(catalog.end));
    offset += sizeof(catalog.end);
    //qDebug() << "此时12的offset = " << offset;

    return catalog;
    //delete[] catalog.file_obj;
    //catalog.file_obj = nullptr;

}

// 从字节流解析出 Cmd_One_File_Info 结构体
Cmd_One_File_Info TCPThread::parseOneFileInfo(QByteArray &data, int &offset)
{
    Cmd_One_File_Info fileInfo;

    std::memcpy(&fileInfo.type, data.constData() + offset, sizeof(fileInfo.type));
    offset = sizeof(fileInfo.type) + offset;

    std::memcpy(&fileInfo.file_size, data.constData() + offset, sizeof(fileInfo.file_size));
    offset += sizeof(fileInfo.file_size);

    std::memcpy(fileInfo.file_name, data.constData() + offset, sizeof(fileInfo.file_name));
    offset += sizeof(fileInfo.file_name);

    std::memcpy(fileInfo.modTime, data.constData() + offset, sizeof(fileInfo.modTime));
    offset += sizeof(fileInfo.modTime);

    return fileInfo;
}
