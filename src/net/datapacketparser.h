#ifndef DATAPACKETPARSER_H
#define DATAPACKETPARSER_H

#include <QByteArray>
#include <QDebug>

class DataPacketParser
{
public:
    explicit DataPacketParser(const QByteArray& data);

    // 公共函数，用于获取每个字段
    uint32_t getHead() const;
    uint32_t getSourceID() const;
    uint32_t getDestID() const;
    uint32_t getOperType() const;
    uint32_t getOperID() const;
    uint32_t getPackageNum() const;
    uint32_t getEnd() const;
    bool isValid() const;

    // 公共函数，用于解析其他操作符或数据
    uint32_t parseField(int offset) const;

    // 获取整个数据包的长度
    int getDataLength() const;

private:
    void parse();

    // 解析指定位置的 32 位无符号整数
    uint32_t parseUInt32(int offset) const;

private:
    QByteArray m_data;
    uint32_t m_head;
    uint32_t m_sourceID;
    uint32_t m_destID;
    uint32_t m_operType;
    uint32_t m_operID;
    uint32_t m_packageNum;
    uint32_t m_end;
    bool m_isValid;
};

#endif // DATAPACKETPARSER_H
