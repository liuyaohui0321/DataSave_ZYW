#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileInfo>
#include <QMessageBox>
#include <QContextMenuEvent>
#include <QLabel>
#include <QPushButton>
#include <QTcpServer>
#include <qlineedit.h>
#include <QProgressDialog>
#include <QRegularExpression>
#include <QComboBox>

#include "src/contextmenu.h"
#include "src/helper/protocol_disk.h"
#include "src/mymenu.h"
#include "src/net/tcpthread.h"
#include "src/dialog/diskconfirm.h"
//#include "src/dialog/dlgexportdata.h"
#include "src/dialog/dlgfileorfolder.h"
#include "src/dialog/dlg_play_back_data.h"
#include "src/dialog/dlgwritedata.h"
#include "src/dialog/dlg_acquisition.h"
#include "src/dialog/login.h"
#include "src/net/udpthread.h"
#include "src/dialog/udpwidget.h"
#include "src/dialog/dlg_delete.h"
#include "src/dialog/dlg_multifile_play_back.h"
#include "src/dialog/dlg_export_data.h"
#include "src/dialog/dlg_percent_export_data.h"
#include "src/dialog/dlg_export_morefile_data.h"
#include "src/playbackdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
struct IPData {
    int ipValue;
    QString ipAddress;
};
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void init();    //初始化指针和界面设置
    QString buildPath(QModelIndex index); //构建树的路径

    //菜单栏样式配置
    void menubarInit();
    //状态栏设置
    void statebarInit();

    QString extractNumbers(const QString &input);
    quint64 calculateSize(const QString &input);
    quint64 countSize(QModelIndexList &indexlist);

    inline QString getNowTime()
    {
        return QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    }

    //对应的文件操作
    void addNewFolder(const QString &name, const QString &path);    //新增文件夹
    void addNewFile(const QString &name, const QString &path);     //新建文件
    void reName(const QString &newname);    //重命名的具体操作
    void moveFileOrFolder(const QString &newpath);    //移动的具体操作
    void copyFileOrFolder(const QString &newpath);    //复制的具体操作
    //void writeFile(const QString &localPath, const QString &dsvPath);   //点击开始写入
    //void stopWriteFile();  //点击停止写入
    void playBack(ReadMode mode,BackGTH gth,const int &count);    //回放
    void stopPlayBack();    //停止回放
    void exportFile(const NetworkPortType &type,uint32_t percent=100,uint32_t cap=0);
    void PercentExport();           //百分比导出指令
    void MoreFileExport();          //批量导出指令
    void exportMoreFile(const NetworkPortType &type,QStringList *strlist,int Num);   //发送批量导出指令
    void acquisition(const QString &path);    //采集
    void stopAcquisition(const QString &path);    //停止采集

    void DeleteOne();  //单个删除
    void DeleteMore(int &num,QStringList &data);  //批量删除
    void MultiFilePlayBack(); //批量回放

signals:
    void sign_sendCmd(const QByteArray &command);
    void sign_sendLenCmd(const QByteArray &command,const int &len);
    void sign_sendExportCap(const quint64 &len);
    void sign_send10GExportCap(const quint64 &len);

//    void sign_addTcpFileHead(const QString &path,double p,double hz);  //给文件添加功率和采样hz
    void sign_addUdpFileHead(const QString &path,double p,double hz);

      //tcp导出数据时，单独使用，创建名字
    void sign_setUdpFilePath(const QString &path);

public slots:
    void slot_CustomContextMenuRequested(const QPoint &pos); // 显示右键菜单
    void slot_haveNewConnection(const QString &client);   //获取到了新的tcp连接，只有显示作用
    void slot_haveNewUdpConnect(const QString ip,const quint16 port);

    void slot_recvDiskData(const Cmd_Disk_State_Info &data);
    void slot_StandardItemModel(QStandardItemModel *data);
    //void slot_recvCommonRespon(const Cmd_Response_Common_Info *data);
    void slot_newrecvCommonRespon(const quint32 &type,const quint32 &id,const quint32 &result);
    void onExportProgress(int percent);
//    void SetExportProgress(int percent);
    void onExportFinished();
    void onStopExport();
    void PlayBackWaitfinished();

private slots:
    void slot_onItemSelected();     //点击任意节点获取信息
    void slot_showSpeed(uint data);     //速度的应答
    void slot_udpInfo();        //udp连接配置
    void onTreeViewClicked(const QModelIndex& index);//LYH 2.14

    //右键菜单相关
    void slotRefresh();//刷新
    void slotFolder(); //新增文件夹
    void slotFile(); //新增文件
    void slotOpen();    //打开    unuse --
    void slotDelete();  //删除
    void slotClose();   //关闭文件  --
    void slotRename(); //重命名
    void slotMove(); //移动
    void slotCopy(); //复制
    void slotWrite(); //写入      --
    void slotStopWrite(); //停止写入    --
    void slotPlayBack(); //回放   --
    void slotExport(); //导出
    void stopExport(); //停止导出
    void slotAcquisition(); //采集    --

    void showMenu();

    //磁盘管理相关
    void slot_diskFormat();     //磁盘格式化
    void slot_diskAgainMount(); //磁盘重新挂载
    void slot_diskUnmount();    //磁盘解挂载
    void slot_stateBarRefresh(); //磁盘刷新状态
    void updateStatusLabel(const QColor &color);
    void setFiberStatus(FiberStatus status);
    void showIPDialog();
    void updateIPData(int index,const QString &ipAddress);

private:
    Ui::MainWindow *ui;

    TCPThread *m_tcp;
    QThread *m_tcpWorkThread;
    UDPThread *m_udp;
    QThread *m_udpWorkThread;
    udpWidget *m_udpInfoWidget;


    //底部状态栏显示
    QLabel *totalShow;
    QLabel *usedShow;
    QLabel *restShow;
    QLabel *fileNumShow;
    QLabel *stateShow;
    QLabel *tShow;
    QLabel *powerShow;
    QLabel *SpeedShow;
    QLabel *fiberStateShow;
    QPushButton *pbtn_stateBarRefresh;  //底部的状态刷新按钮
    //顶部菜单栏空间

    QLabel *m_pSocklLabel;  //用于显示tcp连接状态
    QLabel *m_udpLabel;

    ContextMenu *m_pContextMenu{nullptr};  //右键菜单
    TreeItemInfo m_TreeItemInfo; //选中项信息
    ExportFileInfo m_ExportFileInfo;//导出文件信息


    enum TYPE{
        UNUSE,REFRESH,ADDFOLDER,ADDFILE,DELETE,RENAME,MOVE,COPY,EXPORT,STOP_EXPORT,DISK_FORMAT,DISK_AGAINMOUNT,DISK_UNMOUNT,STOPAcquisition,Acquisition,PLAYBACK,stopPLAYBACK
    };
    int lastOrderType = 0;
    quint64 export_cap=0;
    IPData ipData;
private:
    DlgPlayBackData* dlg;               // 添加指向回放对话框的指针   LYH 2.14
    dlg_acquisition* dlg1;              // 添加指向采集对话框的指针   LYH 2.14
    dlg_delete* dlg2;                   // 添加指向删除对话框的指针   LYH 2.19
    dlg_multifile_play_back* dlg3;      // 添加指向多文件回放对话框的指针      LYH 2.19
    DlgExportData* dlg4;                // 添加指向导出数据对话框的指针        LYH 2.24
    dlg_percent_export_data *dlg5;      // 添加指向百分比导出数据对话框的指针   LYH 2.24
    dlg_export_moreFile_data *dlg6;     // 添加指向批量导出数据对话框的指针   LYH 2.24
    QStandardItemModel *Model;
    QProgressDialog* progressDialog = nullptr; // 导出进度对话框
    playbackDialog *playbackdialog = nullptr;
};

class IPDialog : public QDialog
{
    Q_OBJECT

public:
        IPDialog(QWidget *parent = nullptr);

signals:
    void ipSelected(int ip,const QString &ipAddress);

private slots:
    void onOKClicked();

private:
    QComboBox *ipComboBox;
    QLineEdit *ipLineEdit;
    QString getIPAddressForType(int type) const
    {
        switch(type)
        {
            case 1: return "192.168.0.33";
            case 2: return "192.168.0.34";
            case 3: return "192.168.0.35";
            case 4: return "192.168.0.36";
            default: return "192.168.0.32";
        }
    }
    bool validateIPAddress(const QString &ip);
};



#endif // MAINWINDOW_H
