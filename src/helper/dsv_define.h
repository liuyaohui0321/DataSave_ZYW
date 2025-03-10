#ifndef DSV_DEFINE_H
#define DSV_DEFINE_H

#include <QString>
#include <QDateTime>

#define DSV_PACKET_HEADER      0x55555555 // 包头
#define DSV_PACKET_TAIL      0xAAAAAAAA// 包尾
#define DSV_PORT  8511        //端口号

#define  DSV_WRITE_PACKAGE_SIZE  100*1024*1024

#define TEMPMARK 0xBBBBBBBBCCCCCCCC
#define ORDERHEAD 0xBCBCAAAA
#define ORDEREND 0xBCBCCCCC
#define TIMER 1500
#define NEWFOLDERTIMER 18000
#define BUFFERSIZE 1446*1024

#define XISHU 0.009613
#define NOXISHU 1

#define HEAD 0x55555555
#define END 0xAAAAAAAA

#define dbug 0


//用于解析包头包尾
struct CmdOperationInfo {
    uint32_t srcID;
    uint32_t destID;
    uint32_t opType;
    uint32_t opID;
    uint32_t seqNum;
};

enum ItemType {
    Error, File, Folder     //1是文件，2是文件夹
};

//回放类型
enum ReadMode {
    ReadOnce,      // 一次性读完
    LoopRead       // 循环回读
};

//导出类型
enum class NetworkPortType {
    GigabitEthernet = 0, // 千兆网口
    TenGigabitEthernet = 1 // 万兆网口
};

//回放类型
enum BackGTH {
    GTH_NETWORK,      // 网口
    GTH_1X,      // 回放通道1x
    GTH_8X       // 回放通道8x
};

//对话框类型
enum DlgType {
    DlgFile = 1, //文件
    DlgFolder,    //文件夹
    DlgRename,    //重命名
    DlgMove,    //移动
    DlgCopy,    //拷贝
};

// 单个文件,hy20240818
struct TreeItemInfo {
    QString name;                // 文件或文件夹的名称
    QString path;          // 完整路径
    ItemType type;//类型
    QString prefixPath;          // 路径前缀
};

enum class ButtonType {
    Refresh = 0,   // 刷新
    Close,       // 关闭
    Open,   // 打开
    AddFolder,        // 新增文件夹
    AddFile,      // 新增文件
    Delete,    // 删除
    Move,        // 移动
    Copy,          // 复制
    Rename,       // 重命名
    Write,// 写入
    PlayBack,//回放
    Export,//导出
    Acquisition//采集
};


// 下载文件信息
struct ExportFileInfo {
    QString name;         // dsv中文件或文件夹的名称
    QString path;         // dsv中文件路径

    //QString localPath="F:/DSV/111.txt";    //本地下载文件位置
    QString localPath;

    uint64_t size;        // 文件大小
    bool  isReceivingFileInfo;//是否执行写入操作
};





#endif // DSV_DEFINE_H
