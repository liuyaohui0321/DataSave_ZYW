#include "datapacketparser.h"

// 构造函数，传入需要解析的数据
DataPacketParser::DataPacketParser(const QByteArray& data)
    : m_data(data), m_isValid(false)
{
    parse();
}

// 公共函数，用于获取每个字段
uint32_t DataPacketParser::getHead() const { return m_head; }
uint32_t DataPacketParser::getSourceID() const { return m_sourceID; }
uint32_t DataPacketParser::getDestID() const { return m_destID; }
uint32_t DataPacketParser::getOperType() const { return m_operType; }
uint32_t DataPacketParser::getOperID() const { return m_operID; }
uint32_t DataPacketParser::getPackageNum() const { return m_packageNum; }
uint32_t DataPacketParser::getEnd() const { return m_end; }
bool DataPacketParser::isValid() const { return m_isValid; }

// 获取整个数据包的长度
int DataPacketParser::getDataLength() const {
    return m_data.size();
}

// 解析函数，解析数据包的各个字段
void DataPacketParser::parse()
{
    // 确保数据长度足够
    if (m_data.size() < 28) {
        //        qDebug() << "数据长度不足，无法解析";
        return;
    }

    // 解析各个字段
    m_head = parseUInt32(0);
    m_sourceID = parseUInt32(4);
    m_destID = parseUInt32(8);
    m_operType = parseUInt32(12);
    m_operID = parseUInt32(16);
    m_packageNum = parseUInt32(20);
    m_end = parseUInt32(m_data.size() - 4);  // 解析最后四个字节

    m_isValid = true;
}

// 公共函数，用于解析指定位置的 32 位无符号整数
uint32_t DataPacketParser::parseField(int offset) const {
    return parseUInt32(offset);
}

// 私有函数，用于从指定偏移量解析 32 位无符号整数
uint32_t DataPacketParser::parseUInt32(int offset) const {
    if (offset + 4 > m_data.size()) {
        //        qDebug() << "数据偏移量超出范围";
        return 0;
    }
    const char* dataPtr = m_data.constData() + offset;
    return *reinterpret_cast<const uint32_t*>(dataPtr);
}

