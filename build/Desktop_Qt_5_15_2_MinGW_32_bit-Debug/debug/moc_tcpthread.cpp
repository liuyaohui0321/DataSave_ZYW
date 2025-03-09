/****************************************************************************
** Meta object code from reading C++ file 'tcpthread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/net/tcpthread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tcpthread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TCPThread_t {
    QByteArrayData data[32];
    char stringdata0[464];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TCPThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TCPThread_t qt_meta_stringdata_TCPThread = {
    {
QT_MOC_LITERAL(0, 0, 9), // "TCPThread"
QT_MOC_LITERAL(1, 10, 16), // "sign_waitConnect"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 18), // "sign_getNewConnect"
QT_MOC_LITERAL(4, 47, 6), // "client"
QT_MOC_LITERAL(5, 54, 18), // "sign_tcpNotConnect"
QT_MOC_LITERAL(6, 73, 23), // "sign_tellMainDisconnect"
QT_MOC_LITERAL(7, 97, 13), // "sign_diskData"
QT_MOC_LITERAL(8, 111, 26), // "const Cmd_Disk_State_Info*"
QT_MOC_LITERAL(9, 138, 4), // "data"
QT_MOC_LITERAL(10, 143, 16), // "sign_catalogData"
QT_MOC_LITERAL(11, 160, 23), // "const Cmd_Catalog_Info*"
QT_MOC_LITERAL(12, 184, 13), // "sign_fileData"
QT_MOC_LITERAL(13, 198, 37), // "const Cmd_File_Attribute_Answ..."
QT_MOC_LITERAL(14, 236, 15), // "sign_folderData"
QT_MOC_LITERAL(15, 252, 39), // "const Cmd_Folder_Attribute_An..."
QT_MOC_LITERAL(16, 292, 18), // "sign_newCommonData"
QT_MOC_LITERAL(17, 311, 8), // "uint32_t"
QT_MOC_LITERAL(18, 320, 4), // "type"
QT_MOC_LITERAL(19, 325, 2), // "id"
QT_MOC_LITERAL(20, 328, 6), // "result"
QT_MOC_LITERAL(21, 335, 24), // "sign_sendDirectoryParser"
QT_MOC_LITERAL(22, 360, 19), // "QStandardItemModel*"
QT_MOC_LITERAL(23, 380, 10), // "sign_speed"
QT_MOC_LITERAL(24, 391, 11), // "slot_getCmd"
QT_MOC_LITERAL(25, 403, 3), // "cmd"
QT_MOC_LITERAL(26, 407, 15), // "slot_addTcpHead"
QT_MOC_LITERAL(27, 423, 4), // "path"
QT_MOC_LITERAL(28, 428, 1), // "p"
QT_MOC_LITERAL(29, 430, 2), // "hz"
QT_MOC_LITERAL(30, 433, 18), // "slot_newConnection"
QT_MOC_LITERAL(31, 452, 11) // "onReadyRead"

    },
    "TCPThread\0sign_waitConnect\0\0"
    "sign_getNewConnect\0client\0sign_tcpNotConnect\0"
    "sign_tellMainDisconnect\0sign_diskData\0"
    "const Cmd_Disk_State_Info*\0data\0"
    "sign_catalogData\0const Cmd_Catalog_Info*\0"
    "sign_fileData\0const Cmd_File_Attribute_Answer_Info*\0"
    "sign_folderData\0const Cmd_Folder_Attribute_Answer_Info*\0"
    "sign_newCommonData\0uint32_t\0type\0id\0"
    "result\0sign_sendDirectoryParser\0"
    "QStandardItemModel*\0sign_speed\0"
    "slot_getCmd\0cmd\0slot_addTcpHead\0path\0"
    "p\0hz\0slot_newConnection\0onReadyRead"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TCPThread[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      11,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   89,    2, 0x06 /* Public */,
       3,    1,   90,    2, 0x06 /* Public */,
       5,    0,   93,    2, 0x06 /* Public */,
       6,    0,   94,    2, 0x06 /* Public */,
       7,    1,   95,    2, 0x06 /* Public */,
      10,    1,   98,    2, 0x06 /* Public */,
      12,    1,  101,    2, 0x06 /* Public */,
      14,    1,  104,    2, 0x06 /* Public */,
      16,    3,  107,    2, 0x06 /* Public */,
      21,    1,  114,    2, 0x06 /* Public */,
      23,    1,  117,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      24,    1,  120,    2, 0x0a /* Public */,
      26,    3,  123,    2, 0x0a /* Public */,
      30,    0,  130,    2, 0x08 /* Private */,
      31,    0,  131,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, 0x80000000 | 11,    9,
    QMetaType::Void, 0x80000000 | 13,    9,
    QMetaType::Void, 0x80000000 | 15,    9,
    QMetaType::Void, 0x80000000 | 17, 0x80000000 | 17, 0x80000000 | 17,   18,   19,   20,
    QMetaType::Void, 0x80000000 | 22,    9,
    QMetaType::Void, QMetaType::UInt,    9,

 // slots: parameters
    QMetaType::Void, QMetaType::QByteArray,   25,
    QMetaType::Void, QMetaType::QString, QMetaType::Double, QMetaType::Double,   27,   28,   29,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void TCPThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TCPThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sign_waitConnect(); break;
        case 1: _t->sign_getNewConnect((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->sign_tcpNotConnect(); break;
        case 3: _t->sign_tellMainDisconnect(); break;
        case 4: _t->sign_diskData((*reinterpret_cast< const Cmd_Disk_State_Info*(*)>(_a[1]))); break;
        case 5: _t->sign_catalogData((*reinterpret_cast< const Cmd_Catalog_Info*(*)>(_a[1]))); break;
        case 6: _t->sign_fileData((*reinterpret_cast< const Cmd_File_Attribute_Answer_Info*(*)>(_a[1]))); break;
        case 7: _t->sign_folderData((*reinterpret_cast< const Cmd_Folder_Attribute_Answer_Info*(*)>(_a[1]))); break;
        case 8: _t->sign_newCommonData((*reinterpret_cast< uint32_t(*)>(_a[1])),(*reinterpret_cast< uint32_t(*)>(_a[2])),(*reinterpret_cast< uint32_t(*)>(_a[3]))); break;
        case 9: _t->sign_sendDirectoryParser((*reinterpret_cast< QStandardItemModel*(*)>(_a[1]))); break;
        case 10: _t->sign_speed((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 11: _t->slot_getCmd((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 12: _t->slot_addTcpHead((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 13: _t->slot_newConnection(); break;
        case 14: _t->onReadyRead(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QStandardItemModel* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TCPThread::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TCPThread::sign_waitConnect)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (TCPThread::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TCPThread::sign_getNewConnect)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (TCPThread::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TCPThread::sign_tcpNotConnect)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (TCPThread::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TCPThread::sign_tellMainDisconnect)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (TCPThread::*)(const Cmd_Disk_State_Info * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TCPThread::sign_diskData)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (TCPThread::*)(const Cmd_Catalog_Info * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TCPThread::sign_catalogData)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (TCPThread::*)(const Cmd_File_Attribute_Answer_Info * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TCPThread::sign_fileData)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (TCPThread::*)(const Cmd_Folder_Attribute_Answer_Info * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TCPThread::sign_folderData)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (TCPThread::*)(uint32_t , uint32_t , uint32_t );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TCPThread::sign_newCommonData)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (TCPThread::*)(QStandardItemModel * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TCPThread::sign_sendDirectoryParser)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (TCPThread::*)(uint );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TCPThread::sign_speed)) {
                *result = 10;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject TCPThread::staticMetaObject = { {
    QMetaObject::SuperData::link<QThread::staticMetaObject>(),
    qt_meta_stringdata_TCPThread.data,
    qt_meta_data_TCPThread,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TCPThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TCPThread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TCPThread.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int TCPThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void TCPThread::sign_waitConnect()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void TCPThread::sign_getNewConnect(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void TCPThread::sign_tcpNotConnect()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void TCPThread::sign_tellMainDisconnect()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void TCPThread::sign_diskData(const Cmd_Disk_State_Info * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void TCPThread::sign_catalogData(const Cmd_Catalog_Info * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void TCPThread::sign_fileData(const Cmd_File_Attribute_Answer_Info * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void TCPThread::sign_folderData(const Cmd_Folder_Attribute_Answer_Info * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void TCPThread::sign_newCommonData(uint32_t _t1, uint32_t _t2, uint32_t _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void TCPThread::sign_sendDirectoryParser(QStandardItemModel * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void TCPThread::sign_speed(uint _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
