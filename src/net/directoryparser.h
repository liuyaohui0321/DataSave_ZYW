#ifndef DIRECTORYPARSER_H
#define DIRECTORYPARSER_H

#include "../helper/protocol_disk.h"
#include <QStandardItem>
#include <QByteArray>
#include <QString>


class DirectoryParser
{
public:
    DirectoryParser();

    // 包头和包尾常量定义
    static const uint32_t HEADER_MAGIC;
    static const uint32_t FOOTER_MAGIC;
    static const int PACKAGE_HEADER_SIZE;
    static const int PACKAGE_FOOTER_SIZE;

    // 用于解析数据包
    void parsePackage(QByteArray& data, FileOrFolderInfo& parentInfo);

    //解析结构，返回model
    QStandardItemModel* createModelFromFileOrFolderInfo(const FileOrFolderInfo& rootInfo);

    //重建树
    void rebuildFileOrFolderTree(FileOrFolderInfo& root) ;

private:
    // 读取 UINT64 类型数据
    uint32_t readUInt32(QByteArray& data, int& offset);

    //读取 UINT64 类型数据
    uint64_t readUInt64(QByteArray& data, int& offset);

    // 私有方法：读取 UTF-16 LE 字符串
    QString readUtf16String(QByteArray& data, int& offset, int length);

    // 私有方法：计算 32 位校验和
    uint32_t calculateChecksum(QByteArray& data);

    // 包头、包体和包尾解析
    void parseHeader(QByteArray& data, int& offset);
    void parseBody(QByteArray& data, int& offset, FileOrFolderInfo& parentInfo);
    void parseFooter(QByteArray& data, int& offset);

    // 单个文件或文件夹信息解析
    void parseFileOrFolderInfo(QByteArray& data, int& offset,FileOrFolderInfo& parentInfo);

    //添加文件信息到model
    void addFileOrFolderToModel(const FileOrFolderInfo& info, QStandardItem* parentItem);

    //解析路径
    QStringList parsePath(const QString& path);

    //重新构建树
    void rebuildTreeFromFileOrFolderInfo(FileOrFolderInfo& root, FileOrFolderInfo& currentItem) ;

    //添加项到树形结构
    void addPathToTree(FileOrFolderInfo& root, const QStringList& pathComponents, uint64_t type, uint64_t size, const QString& modifyTime) ;


    //字节转换成GB
    uint64_t bytesToGB(unsigned long long bytes) {
        return bytes / (1024.0 * 1024.0 * 1024.0);
    }

    //字节转换成MB
    uint64_t bytesToMB(unsigned long long bytes) {
        return bytes / (1024.0 * 1024.0);
    }

    //字节转换成kB
    uint64_t bytesToKB(unsigned long long bytes) {
        return bytes / (1024.0);
    }

    //根据字节大小判断显示
    QString formatSize(uint64_t size);

};

#endif // DIRECTORYPARSER_H
