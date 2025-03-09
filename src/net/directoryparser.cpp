#include "directoryparser.h"

#include "../helper/dsv_define.h"
#include <iostream>
#include <QDebug>
#include <cstring>
#include <QFileInfo>

// 初始化常量
const int DirectoryParser::PACKAGE_HEADER_SIZE = 24;
const int DirectoryParser::PACKAGE_FOOTER_SIZE = 8;

DirectoryParser::DirectoryParser() {}

uint32_t DirectoryParser::readUInt32(QByteArray& data, int& offset) {
    uint32_t value = 0;
    memcpy(&value, data.data() + offset, sizeof(uint32_t));
    offset += sizeof(uint32_t);
    return value;
}

uint64_t DirectoryParser::readUInt64(QByteArray& data, int& offset) {
    uint64_t value = 0;
    memcpy(&value, data.data() + offset, sizeof(uint64_t));
    offset += sizeof(uint64_t);
    return value;
}

QString DirectoryParser::readUtf16String(QByteArray& data, int& offset, int length) {
    QString str = QString::fromUtf16(reinterpret_cast<const ushort*>(data.data() + offset), length / 2);
    offset += length;

    //    QFileInfo fileInfo(str);
    //    QString fileName = fileInfo.fileName();  // 提取最后的文件名或文件夹名
    str.remove(QChar('\u0000'));
    str.remove("0:/");


    return str;
}

uint32_t DirectoryParser::calculateChecksum(QByteArray& data) {
    uint32_t checksum = 0;
    for (int i = 0; i < data.size(); i += 2) {
        checksum += (data[i] | (data[i + 1] << 8));
    }
    return checksum;
}

void DirectoryParser::parseHeader(QByteArray& data, int& offset) {
    uint32_t headerMagic = readUInt32(data, offset);
    if (headerMagic != DSV_PACKET_HEADER) {
        std::cerr << "Invalid header magic!" << std::endl;
        return;
    }

    uint32_t srcID = readUInt32(data, offset);
    uint32_t destID = readUInt32(data, offset);
    uint32_t opType = readUInt32(data, offset);
    uint32_t opID = readUInt32(data, offset);
    uint32_t seqNum = readUInt32(data, offset);

}

void DirectoryParser::parseBody(QByteArray& data, int& offset,FileOrFolderInfo& parentInfo)
{
    uint32_t responseType = readUInt32(data, offset);
    uint32_t responseOpID = readUInt32(data, offset);
    uint32_t fileCount = readUInt32(data, offset);
    uint32_t folderCount = readUInt32(data, offset);

    // std::cout << "Response Type: " << responseType << std::endl;
    // std::cout << "Response Operation ID: " << responseOpID << std::endl;
    // std::cout << "File Count: " << fileCount << std::endl;
    // std::cout << "Folder Count: " << folderCount << std::endl;

    // qDebug()<<"Response Type: "<<responseType;
    // qDebug()<<"Response Operation ID: "<<responseOpID;
    // qDebug()<<"File Count:  "<<fileCount;
    // qDebug()<<"Folder Count: "<<folderCount;

    uint32_t totalCount = fileCount + folderCount;
    for (uint32_t i = 0; i < totalCount; ++i)
    {
        parseFileOrFolderInfo(data, offset, parentInfo);
    }
}

void DirectoryParser::parseFileOrFolderInfo(QByteArray& data, int& offset, FileOrFolderInfo& parentInfo)
{
    //qDebug()<<"递归解析文件夹-------";
    uint64_t type = readUInt64(data, offset);
    uint64_t size = (type == 0) ? readUInt64(data, offset) : 0; // 读取文件大小，如果是文件夹则忽略
    QString name = readUtf16String(data, offset, 1024);
    QString modifyTime1 = readUtf16String(data, offset, 48);

    QFileInfo fileInfo(name);
    QString fileName = fileInfo.fileName();  // 提取最后的文件名或文件夹名
    fileName.remove(QChar('\u0000'));

    //qDebug()<< "正在解析___"<<type<<"___类型的文件："<<" 文件大小："<<size<<" 文件名字："<<name.trimmed() ;

    // 创建新的文件或文件夹信息
    FileOrFolderInfo itemInfo;
    //itemInfo.name = name.trimmed();
    itemInfo.name = name;
    itemInfo.size = size;
    itemInfo.modifyTime = modifyTime1;
    itemInfo.type = (type == 0) ? "File" : "Folder";

    // 将此项添加到父级结构体的 children 中
    parentInfo.children.append(itemInfo);

    // 文件夹递归解析子项 // 如果是文件夹
    if (type == 1)
    {
        // 读取子文件夹和文件数量
        uint32_t subFolderCount = readUInt32(data, offset);
        uint32_t fileCount = readUInt32(data, offset);

        // 引用当前文件夹信息
        FileOrFolderInfo& currentFolderInfo = parentInfo.children.last();

        // 解析子文件夹
        for (uint32_t i = 0; i < subFolderCount; ++i) {
            parseFileOrFolderInfo(data, offset, currentFolderInfo);
            //qDebug()<< "正在解析子文件夹";
        }

        // 解析文件
        for (uint32_t i = 0; i < fileCount; ++i) {
            parseFileOrFolderInfo(data, offset, currentFolderInfo);
            //qDebug()<< "正在解析文件";
        }
    }
}

void DirectoryParser::addFileOrFolderToModel(const FileOrFolderInfo& info, QStandardItem* parentItem)
{
    //    // 创建一个新的 QStandardItem，代表文件或文件夹
    //    QStandardItem* item = new QStandardItem(info.name);
    //    // 设置项的其他数据
    //    item->setData(info.type, Qt::UserRole + 1); // 文件或文件夹类型
    //    item->setData(info.size, Qt::UserRole + 2); // 文件大小
    //    item->setData(info.modifyTime, Qt::UserRole + 3); // 修改时间
    // 将该项添加到父项
    //    parentItem->appendRow(item);
    if(info.name.contains("/"))
    {
        return;
    }

    QStandardItem* nameItem = new QStandardItem(info.name);  // 第1列：名称
    QStandardItem* typeItem = new QStandardItem(info.type);  // 第2列：类型


    QString formattedSize = formatSize(info.size);

    QStandardItem* sizeItem = new QStandardItem(formattedSize);  // 第3列：大小
    QStandardItem* timeItem = new QStandardItem(info.modifyTime);  // 第4列：修改时间


    // 判断是否是文件，根据文件类型设置图标
    if (info.type == "File") {
        nameItem->setIcon(QIcon(":/my/images/file.png"));  // 设置文件图标
        nameItem->setData(1, Qt::UserRole+ 1);
        nameItem->setData(QVariant::fromValue(info.size), Qt::UserRole+ 2);      //zyw
    } else if (info.type == "Folder") {
        nameItem->setIcon(QIcon(":/my/images/folder.png"));  // 设置文件夹图标
        nameItem->setData(2, Qt::UserRole+ 1);
    }


    // 创建一行，并将四个 QStandardItem 添加到同一行中
    QList<QStandardItem*> rowItems;
    rowItems << nameItem << typeItem << sizeItem << timeItem;

    // 将这一行添加到父项
    parentItem->appendRow(rowItems);

    // 如果有子项，递归添加
    for (const FileOrFolderInfo& child : info.children) {
        addFileOrFolderToModel(child, nameItem);
    }
}

QStringList DirectoryParser::parsePath(const QString& path) {
    // 移除 "0:/" 前缀并根据 '/' 进行拆解
    QString cleanedPath = path;
    if (cleanedPath.startsWith("0:/")) {
        cleanedPath = cleanedPath.mid(3);  // 移除 "0:/"
    }

    return cleanedPath.split('/', QString::SkipEmptyParts); // 拆解路径
}

void DirectoryParser::rebuildTreeFromFileOrFolderInfo(FileOrFolderInfo& root, FileOrFolderInfo& currentItem)
{
    // 解析当前节点的路径
    QStringList pathComponents = parsePath(currentItem.name);

    // 将当前节点路径插入到树形结构
    addPathToTree(root, pathComponents, currentItem.type == "File" ? 0 : 1, currentItem.size, currentItem.modifyTime);

    // 递归处理子节点
    for (FileOrFolderInfo& child : currentItem.children)
    {
        rebuildTreeFromFileOrFolderInfo(root, child);
    }
}

void DirectoryParser::addPathToTree(FileOrFolderInfo& root, const QStringList& pathComponents, uint64_t type, uint64_t size, const QString& modifyTime)
{
    //    size =size/1000000;

    // 如果路径组件为空，返回
    if (pathComponents.isEmpty()) return;

    // 获取当前层的文件或文件夹名称
    QString currentName = pathComponents.first();

    // 查找当前节点是否已经存在
    FileOrFolderInfo* existingChild = nullptr;
    for (FileOrFolderInfo& child : root.children) {
        if (child.name == currentName) {
            existingChild = &child;
            break;
        }
    }

    // 如果当前节点不存在，创建新的
    if (!existingChild)
    {
        FileOrFolderInfo newItem;
        newItem.name = currentName;
        newItem.type = (pathComponents.size() == 1) ? (type == 0 ? "File" : "Folder") : "Folder"; // 判断是文件夹还是文件
        newItem.size = (newItem.type == "File") ? size : 0;
        newItem.modifyTime = (newItem.type == "File") ? modifyTime : "";
        root.children.append(newItem);
        existingChild = &root.children.last();
    }

    // 递归处理剩余路径
    if (pathComponents.size() > 1) {
        addPathToTree(*existingChild, pathComponents.mid(1), type, size, modifyTime);
    }
}

QStandardItemModel*  DirectoryParser::createModelFromFileOrFolderInfo(const FileOrFolderInfo& rootInfo) {

    // 创建模型
    QStandardItemModel* model = new QStandardItemModel();

    // 设置模型的标题行
    model->setHorizontalHeaderLabels({"名称", "类型", "文件大小", "修改时间"});

    // 创建根项
    QStandardItem* rootItem = model->invisibleRootItem();
    rootItem->setIcon(QIcon(":/my/images/disk.png"));  // 设置文件夹图标
    rootItem->setData(2, Qt::UserRole+ 1);

    // 将根目录项添加到模型中
    addFileOrFolderToModel(rootInfo, rootItem);

    return model;
}

void DirectoryParser::rebuildFileOrFolderTree(FileOrFolderInfo& root)
{
    // 递归处理根节点的所有子节点
    for (FileOrFolderInfo& child : root.children)
    {
        rebuildTreeFromFileOrFolderInfo(root, child);
    }
}

void DirectoryParser::parseFooter(QByteArray& data, int& offset) {
    uint32_t checksum = readUInt32(data, offset);
    uint32_t footerMagic = readUInt32(data, offset);

    if (footerMagic != DSV_PACKET_TAIL) {
        std::cerr << "Invalid footer magic! 没有找到包尾" << std::endl;
        return;
    }

    QByteArray body = data.mid(PACKAGE_HEADER_SIZE, data.size() - PACKAGE_HEADER_SIZE - PACKAGE_FOOTER_SIZE);
    // uint32_t calculatedChecksum = calculateChecksum(body);
    // if (checksum != calculatedChecksum) {
    //     std::cerr << "Checksum verification failed!" << std::endl;
    // } else {
    //     std::cout << "Checksum verified successfully." << std::endl;
    // }
}

void DirectoryParser::parsePackage(QByteArray& data, FileOrFolderInfo& parentInfo) {
    int offset = 0;
    parseHeader(data, offset);
    parseBody(data, offset, parentInfo);
    parseFooter(data, offset);
}

QString DirectoryParser::formatSize(uint64_t size){
    uint64_t convertedSize;
    QString unit;

    if (size >= 1024ULL * 1024ULL * 1024ULL) {
        // 大于等于1GB
        convertedSize = size / (1024ULL * 1024ULL);
        unit = "MB";
    } else if (size >= 1024ULL * 1024ULL) {
        // 大于等于1MB
        convertedSize = size / (1024ULL * 1024ULL);
        unit = "MB";
    } else if (size >= 1024ULL) {
        // 大于等于1KB
        convertedSize = size / 1024ULL;
        unit = "KB";
    } else {
        // 小于1KB，单位为Bytes
        convertedSize = size;
        unit = "Bytes";
    }

    return QString::number(convertedSize) + " " + unit;
}

