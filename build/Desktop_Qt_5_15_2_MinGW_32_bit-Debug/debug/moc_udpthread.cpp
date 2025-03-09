/****************************************************************************
** Meta object code from reading C++ file 'udpthread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/net/udpthread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'udpthread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_UDPThread_t {
    QByteArrayData data[12];
    char stringdata0[119];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UDPThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UDPThread_t qt_meta_stringdata_UDPThread = {
    {
QT_MOC_LITERAL(0, 0, 9), // "UDPThread"
QT_MOC_LITERAL(1, 10, 16), // "sign_mainShowUDP"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 2), // "ip"
QT_MOC_LITERAL(4, 31, 4), // "port"
QT_MOC_LITERAL(5, 36, 26), // "sign_tellMainUdpDisconnect"
QT_MOC_LITERAL(6, 63, 19), // "slot_onDataReceived"
QT_MOC_LITERAL(7, 83, 12), // "slot_addHead"
QT_MOC_LITERAL(8, 96, 4), // "path"
QT_MOC_LITERAL(9, 101, 1), // "p"
QT_MOC_LITERAL(10, 103, 2), // "hz"
QT_MOC_LITERAL(11, 106, 12) // "slot_setPath"

    },
    "UDPThread\0sign_mainShowUDP\0\0ip\0port\0"
    "sign_tellMainUdpDisconnect\0"
    "slot_onDataReceived\0slot_addHead\0path\0"
    "p\0hz\0slot_setPath"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UDPThread[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   39,    2, 0x06 /* Public */,
       5,    0,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   45,    2, 0x0a /* Public */,
       7,    3,   46,    2, 0x0a /* Public */,
      11,    1,   53,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::UShort,    3,    4,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Double, QMetaType::Double,    8,    9,   10,
    QMetaType::Void, QMetaType::QString,    8,

       0        // eod
};

void UDPThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<UDPThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sign_mainShowUDP((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const quint16(*)>(_a[2]))); break;
        case 1: _t->sign_tellMainUdpDisconnect(); break;
        case 2: _t->slot_onDataReceived(); break;
        case 3: _t->slot_addHead((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 4: _t->slot_setPath((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (UDPThread::*)(const QString , const quint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UDPThread::sign_mainShowUDP)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (UDPThread::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UDPThread::sign_tellMainUdpDisconnect)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject UDPThread::staticMetaObject = { {
    QMetaObject::SuperData::link<QThread::staticMetaObject>(),
    qt_meta_stringdata_UDPThread.data,
    qt_meta_data_UDPThread,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *UDPThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UDPThread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_UDPThread.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int UDPThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void UDPThread::sign_mainShowUDP(const QString _t1, const quint16 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void UDPThread::sign_tellMainUdpDisconnect()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
