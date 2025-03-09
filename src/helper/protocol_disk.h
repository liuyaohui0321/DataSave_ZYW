#ifndef PROTOCOL_DISK_H
#define PROTOCOL_DISK_H

#pragma pack(push, 1)  // 设置1字节对齐
#include <stdint.h>
#include <QString>
#include <string>
#include <memory>
#include <QVector>


/*5.2.1	文件及文件夹一般维护报文结构*/
typedef struct
{
    uint32_t order_head;    //指令的头

    //原协议内容
    uint32_t head ;         //包头
    uint32_t source_ID ;    //源组件ID，0
    uint32_t dest_ID ;      //目的组件ID，0
    uint32_t oper_type ;    //操作类型
    uint32_t oper_ID ;      //操作ID
    uint32_t package_num;   //包序列号，0
    uint32_t fun_type ;     //指令类型：1->新建文件 2->新建文件夹
    char16_t fun_para1[1024];
    char16_t fun_para2[1024];
    uint32_t check;         //校验码
    uint32_t end ;          //包尾

} Cmd_Folder_And_File_Info;


/*5.2.2	文件、文件夹及磁盘管理操作结果通用问询报文结构*/
typedef struct
{
    uint32_t order_head;    //指令的头

    //原协议内容
    uint32_t head ;         //包头
    uint32_t source_ID ;    //源组件ID，0
    uint32_t dest_ID ;      //目的组件ID，0
    uint32_t oper_type ;    //操作类型
    uint32_t oper_ID ;      //操作ID
    uint32_t package_num;   //包序列号，0
    uint32_t ask_type ;     //所询问操作类型
    uint32_t ask_ID;        //所询问操作ID
    uint32_t ask_package_num;   //所询问包序列号
    uint32_t check;         //校验码，0
    uint32_t end ;          //包尾

} Cmd_Ask_Common_Info;


//5.2.3	文件、文件夹及磁盘管理操作结果通用应答报文结构
typedef struct
{
    uint32_t head ;         //包头
    uint32_t source_ID ;    //源组件ID，0
    uint32_t dest_ID ;      //目的组件ID，0
    uint32_t oper_type ;    //操作类型
    uint32_t oper_ID ;      //操作ID
    uint32_t package_num;   //包序列号，0

    uint32_t res_package_num;   //应答的操作包序列号
    uint32_t res_type;          //所应答的操作类型
    uint32_t res_ID;            //所应答的操作操作ID
    uint32_t res_result;        //所应答的操作结果
    uint32_t res_byte[4];          //字节备份

    uint32_t check;         //校验码
    uint32_t end ;          //包尾

}Cmd_Response_Common_Info;

/*5.2.4	文件及文件夹属性维护报文结构*/
typedef struct
{
    uint32_t order_head;    //指令的头

    //原协议内容
    uint32_t head ;         //包头
    uint32_t source_ID ;    //源组件ID，0
    uint32_t dest_ID ;      //目的组件ID，0
    uint32_t oper_type ;    //操作类型
    uint32_t oper_ID ;      //操作ID
    uint32_t package_num;   //包序列号，0

    uint32_t change;            //属性修改使能
    char16_t file_path[2048];   //文件目录及名称
    uint32_t new_file_readWrite;     //文件读写控制值
    uint32_t new_file_show;          //文件显示控制值

    char16_t folder_path[2048];   //文件夹目录及名称
    uint32_t new_folder_readWrite;     //文件夹读写控制值
    uint32_t new_folder_show;          //文件夹显示控制值

    uint32_t check;         //校验码，0
    uint32_t end ;          //包尾

} Cmd_Attribute_Set_Info;


/*5.2.5	文件及文件夹属性获取报文结构*/
typedef struct
{
    uint32_t order_head;    //指令的头

    //原协议内容
    uint32_t head ;         //包头
    uint32_t source_ID ;    //源组件ID，0
    uint32_t dest_ID ;      //目的组件ID，0
    uint32_t oper_type ;    //操作类型
    uint32_t oper_ID ;      //操作ID
    uint32_t package_num;   //包序列号，0
    uint32_t set_type;        //类别使能,选择文件或者文件夹

    char16_t file_address[1024];   //文件目录
    char16_t folder_address[1024];   //文件夹目录
    uint32_t check;         //校验码，0
    uint32_t end ;          //包尾

} Cmd_Attribute_Get_Info;

/*	5.2.6	文件属性获取应答报文结构*/
typedef struct
{
    uint32_t head ;         //包头
    uint32_t source_ID ;    //源组件ID，0
    uint32_t dest_ID ;      //目的组件ID，0
    uint32_t oper_type ;    //操作类型
    uint32_t oper_ID ;      //操作ID
    uint32_t package_num;   //包序列号，0

    char16_t file_name[1024];   //文件名称
    char16_t file_address[1024];   //文件所在目录
    uint64_t file_size;     //文件大小

    //这里本应该还有时间相关的内容，但是fpga无法获取
    //通过上位机存储到数据库的方式来填充，协议中并不解析

    uint32_t file_readWrite_control;     //读写控制
    uint32_t file_show_control;          //显示控制
    uint32_t byte_backups[12];       //字节备份
    uint32_t check;         //校验码，0
    uint32_t end ;          //包尾

} Cmd_File_Attribute_Answer_Info;

/*	5.2.7	文件夹属性获取应答报文结构*/
typedef struct
{
    uint32_t head ;         //包头
    uint32_t source_ID ;    //源组件ID，0
    uint32_t dest_ID ;      //目的组件ID，0
    uint32_t oper_type ;    //操作类型
    uint32_t oper_ID ;      //操作ID
    uint32_t package_num;   //包序列号，0

    char16_t folder_name[1024];   //文件夹名称
    char16_t folder_address[1024];   //文件夹所在目录
    uint64_t folder_size;     //文件夹大小
    uint32_t have_child_folder_num;     //包含子文件夹的数量，取值范围：[0~16384]
    uint32_t have_file_num;     //包含子文件的数量，取值范围：[0~16384]

    //这里本应该还有时间相关的内容，但是fpga无法获取
    //通过上位机存储到数据库的方式来填充，协议中并不解析

    uint32_t folder_readWrite_control;    //读写控制
    uint32_t folder_show_control;         //显示控制
    uint32_t byte_backups[12];          //字节备份
    uint32_t check;         //校验码，0
    uint32_t end ;          //包尾

} Cmd_Folder_Attribute_Answer_Info;

/*5.2.8	返回目录中的文件和子目录列表报文结构 */

typedef struct
{
    uint64_t type;          //类型
    uint64_t file_size;     //文件大小
    char16_t file_name[512];    //文件或文件夹名
    char16_t modTime[24];       //修改时间1（上位机时间）

}Cmd_One_File_Info;

typedef struct
{
    uint32_t head ;         //包头
    uint32_t source_ID ;    //源组件ID，0
    uint32_t dest_ID ;      //目的组件ID，0
    uint32_t oper_type ;    //操作类型
    uint32_t oper_ID ;      //操作ID
    uint32_t answer_package_num;    //应答的操作包序列号，0

    uint32_t answer_type;   //所应答的类型
    uint32_t answer_ID;     //所应答的操作ID
    uint32_t file_num;      //文件总个数
    uint32_t folder_num;    //文件夹总个数

    Cmd_One_File_Info* file_obj;     //N个单个文件或文件夹目录信息
    //std::unique_ptr<Cmd_One_File_Info[]> file_obj;

    uint32_t check;         //校验码，0
    uint32_t end;          //包尾

    // 析构函数释放数组
    //    ~Cmd_Catalog_Info() {
    //        delete file_obj;
    //    }

} Cmd_Catalog_Info;


// 单个文件,hy20240818
struct FileOrFolderInfo {
    QString name;                // 文件或文件夹的名称
    QString modifyTime;          // 修改时间
    uint64_t size;               // 文件大小（如果是文件夹，则为0）
    QString type;                // "File" 或 "Folder"
    QVector<FileOrFolderInfo> children;  // 子文件夹和文件
};


/*5.3磁盘管理维护报文结构*/
typedef struct
{
    uint32_t order_head;    //指令的头

    //原协议内容
    uint32_t head ;         //包头
    uint32_t source_ID ;    //源组件ID，0
    uint32_t dest_ID ;      //目的组件ID，0
    uint32_t oper_type ;    //操作类型
    uint32_t oper_ID ;      //操作ID
    uint32_t package_num;   //包序列号，0
    uint32_t fun_type ;     //指令类型：1->磁盘格式化 2->增加重新挂载 3->增加解挂载
    uint32_t check;         //校验码
    uint32_t end ;          //包尾

} Cmd_Disk_Info;


//5.4	文件读写操作
//5.4.2	分包写入文件报文结构 第一包数据
typedef struct
{
    uint32_t order_head;    //指令的头

    //原协议内容
    uint32_t head ;         //包头
    uint32_t source_ID ;    //源组件ID，0
    uint32_t dest_ID ;      //目的组件ID，0
    uint32_t oper_type ;    //操作类型
    uint32_t oper_ID ;      //操作ID
    uint32_t package_num;   //包序列号，0

    char16_t file_address[1024];    //文件路径
    //uint32_t zibao_num;             //子包序号
    //uint32_t last_package;          //最后一包标识
    //uint32_t data_len;              //有效数据长度

    //QByteArray data;

    uint32_t check;         //校验码
    uint32_t end ;          //包尾

}Cmd_Write_One_Package_To_Disk_Info;

//新的数据发送方式
typedef struct
{
    uint32_t head_data;

    QByteArray head;
    QByteArray data;
    QByteArray end_data;

    uint32_t end;

}Cmd_Data_To_Disk_Info;

//7.6修改，第一包和最后一包的结构体需要单独定义
typedef struct
{
    uint32_t head;
    QByteArray head_array;
    QByteArray data;

}Cmd_Data_To_Disk_One_Package_Info;

typedef struct
{
    QByteArray data;
    QByteArray end_array;
    uint32_t end;

}Cmd_Data_To_Disk_Last_Package_Info;



//新得分包写入的报文,给出了最后一包的分片信息，并没有
typedef struct
{
    uint32_t order_head;    //指令的头
    //原协议内容
    uint32_t head ;         //包头
    uint32_t source_ID ;    //源组件ID，0
    uint32_t dest_ID ;      //目的组件ID，0
    uint32_t oper_type ;    //操作类型
    uint32_t oper_ID ;      //操作ID
    uint32_t package_num;   //包序列号，0

    char16_t file_address[1024];    //文件路径
    uint32_t package_cnt;
    uint32_t last_package_pian_num;
    uint32_t last_pian_len;

    uint32_t check;         //校验码
    uint32_t end ;          //包尾

}Cmd_New_Package_To_Disk_Info;


//5.4.4	读文件命令报文结构
typedef struct
{
    uint32_t order_head;    //指令的头

    //原协议内容
    uint32_t head ;         //包头
    uint32_t source_ID ;    //源组件ID，0
    uint32_t dest_ID ;      //目的组件ID，0
    uint32_t oper_type ;    //操作类型
    uint32_t oper_ID ;      //操作ID
    uint32_t package_num;   //包序列号，0

    char16_t file_address[1024];    //文件路径
    uint32_t read_func;             //读取方式
    uint32_t read_xunhuan_cnt;      //循环读取次数

    uint32_t check;         //校验码
    uint32_t end ;          //包尾

}Cmd_Read_File_Func_Info;

//5.4.4	读文件命令报文结构
typedef struct
{
    uint8_t reserved[60];          // 60 字节，初始化为 0

    uint32_t check;         //校验码
    uint32_t end ;          //包尾

}Cmd_Stop_Read_File_Func_Info;

//5.4.6	导出文件命令报文结构
typedef struct
{
    uint32_t order_head;    //指令的头

    //原协议内容
    uint32_t head ;         //包头
    uint32_t source_ID ;    //源组件ID，0
    uint32_t dest_ID ;      //目的组件ID，0
    uint32_t oper_type ;    //操作类型
    uint32_t oper_ID ;      //操作ID
    uint32_t package_num;   //包序列号，0

    char16_t file_address[1024];    //文件路径
    uint32_t export_type;             //导出方式


    uint32_t check;         //校验码
    uint32_t end ;          //包尾

}Cmd_Export_File_Func_Info;

//读文件报文，老的协议内容
//typedef struct
//{
//    uint32_t order_head;    //指令的头

//    //原协议内容
//    uint32_t head ;         //包头
//    uint32_t source_ID ;    //源组件ID，0
//    uint32_t dest_ID ;      //目的组件ID，0
//    uint32_t oper_type ;    //操作类型
//    uint32_t oper_ID ;      //操作ID
//    uint32_t package_num;   //包序列号，0

//    char16_t file_address[1024];   //文件路径

//    uint32_t check;         //校验码
//    uint32_t end ;          //包尾


//}Cmd_Read_One_Package_From_Disk_Info;

//5.4.9	写文件停止命令报文结构
typedef struct
{
    uint32_t order_head;    //指令的头

    //原协议内容
    uint32_t head ;         //包头
    uint32_t source_ID ;    //源组件ID，0
    uint32_t dest_ID ;      //目的组件ID，0
    uint32_t oper_type ;    //操作类型
    uint32_t oper_ID ;      //操作ID
    uint32_t package_num;   //包序列号，0

    char16_t file_address[1024];   //文件路径
    uint32_t stop_type;             //停止方式 ,0 立即停止

    uint32_t check;         //校验码
    uint32_t end ;          //包尾

}Cmd_Write_Stop_Info;


//5.5	健康状态报文结构,应答报文，需要我解析
typedef struct
{
    uint32_t head ;         //包头
    uint32_t source_ID ;    //源组件ID，0
    uint32_t dest_ID ;      //目的组件ID，0
    uint32_t oper_type ;    //操作类型
    uint32_t oper_ID ;      //操作ID
    uint32_t package_num;   //包序列号，0

    uint64_t disk_total;
    uint64_t disk_used;
    uint64_t disk_rest;

    uint32_t file_num;
    uint32_t disk_state;
    int32_t disk_t;
    uint32_t disk_power;
    uint32_t disk_open_num;

    uint32_t check;         //校验码
    uint32_t end ;          //包尾

}Cmd_Disk_State_Info;





typedef struct
{
    uint32_t order_head;    //指令的头

    //原协议内容
    uint32_t head ;         //包头
    uint32_t source_ID ;    //源组件ID，0
    uint32_t dest_ID ;      //目的组件ID，0
    uint32_t oper_type ;    //操作类型
    uint32_t oper_ID ;      //操作ID
    uint32_t package_num;   //包序列号，0

    uint32_t check;         //校验码
    uint32_t end ;          //包尾

}Cmd_Ask_Disk_State_Info;

/* 文件数据采集命令报文结构 */
typedef struct
{
    uint32_t order_head;    //指令的头

    // 操作数据包头部
    uint32_t package_head;   // 包头，固定值为 0x55555555

    // 基本信息
    uint32_t source_ID;      // 源组件ID，操作指令发送方的ID
    uint32_t dest_ID;        // 目的组件ID，操作指令接收方的ID

    uint32_t oper_type;      // 操作类型，0xD2
    // 文件相关信息
    uint32_t oper_ID;        // 操作ID，0x03为操作类型ID
    uint32_t package_num;    // 包序列号
    char16_t file_address[1024];  // 文件路径，UTF-16 LE编码，支持1024字节

    // 校验与尾部
    uint32_t check_code;     // 校验码，32位校验和
    uint32_t package_tail;   // 包尾，固定值为 0xAAAAAAAA

    uint32_t order_end;    //指令的尾部

} Cmd_File_Acquisition_Info;









#endif // PROTOCOL_DISK_H
