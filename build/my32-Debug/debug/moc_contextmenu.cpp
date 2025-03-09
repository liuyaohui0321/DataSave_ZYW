/****************************************************************************
** Meta object code from reading C++ file 'contextmenu.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/contextmenu.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'contextmenu.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ContextMenu_t {
    QByteArrayData data[15];
    char stringdata0[183];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ContextMenu_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ContextMenu_t qt_meta_stringdata_ContextMenu = {
    {
QT_MOC_LITERAL(0, 0, 11), // "ContextMenu"
QT_MOC_LITERAL(1, 12, 10), // "sigRefresh"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 10), // "signalOpen"
QT_MOC_LITERAL(4, 35, 11), // "signalClose"
QT_MOC_LITERAL(5, 47, 15), // "signalNewFolder"
QT_MOC_LITERAL(6, 63, 13), // "signalNewFile"
QT_MOC_LITERAL(7, 77, 12), // "signalDelete"
QT_MOC_LITERAL(8, 90, 10), // "signalMove"
QT_MOC_LITERAL(9, 101, 10), // "signalCopy"
QT_MOC_LITERAL(10, 112, 12), // "signalRename"
QT_MOC_LITERAL(11, 125, 11), // "signalWrite"
QT_MOC_LITERAL(12, 137, 14), // "signalPlayback"
QT_MOC_LITERAL(13, 152, 12), // "signalExport"
QT_MOC_LITERAL(14, 165, 17) // "signalAcquisition"

    },
    "ContextMenu\0sigRefresh\0\0signalOpen\0"
    "signalClose\0signalNewFolder\0signalNewFile\0"
    "signalDelete\0signalMove\0signalCopy\0"
    "signalRename\0signalWrite\0signalPlayback\0"
    "signalExport\0signalAcquisition"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ContextMenu[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      13,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x06 /* Public */,
       3,    0,   80,    2, 0x06 /* Public */,
       4,    0,   81,    2, 0x06 /* Public */,
       5,    0,   82,    2, 0x06 /* Public */,
       6,    0,   83,    2, 0x06 /* Public */,
       7,    0,   84,    2, 0x06 /* Public */,
       8,    0,   85,    2, 0x06 /* Public */,
       9,    0,   86,    2, 0x06 /* Public */,
      10,    0,   87,    2, 0x06 /* Public */,
      11,    0,   88,    2, 0x06 /* Public */,
      12,    0,   89,    2, 0x06 /* Public */,
      13,    0,   90,    2, 0x06 /* Public */,
      14,    0,   91,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ContextMenu::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ContextMenu *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sigRefresh(); break;
        case 1: _t->signalOpen(); break;
        case 2: _t->signalClose(); break;
        case 3: _t->signalNewFolder(); break;
        case 4: _t->signalNewFile(); break;
        case 5: _t->signalDelete(); break;
        case 6: _t->signalMove(); break;
        case 7: _t->signalCopy(); break;
        case 8: _t->signalRename(); break;
        case 9: _t->signalWrite(); break;
        case 10: _t->signalPlayback(); break;
        case 11: _t->signalExport(); break;
        case 12: _t->signalAcquisition(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ContextMenu::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ContextMenu::sigRefresh)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ContextMenu::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ContextMenu::signalOpen)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ContextMenu::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ContextMenu::signalClose)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ContextMenu::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ContextMenu::signalNewFolder)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ContextMenu::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ContextMenu::signalNewFile)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (ContextMenu::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ContextMenu::signalDelete)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (ContextMenu::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ContextMenu::signalMove)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (ContextMenu::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ContextMenu::signalCopy)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (ContextMenu::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ContextMenu::signalRename)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (ContextMenu::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ContextMenu::signalWrite)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (ContextMenu::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ContextMenu::signalPlayback)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (ContextMenu::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ContextMenu::signalExport)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (ContextMenu::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ContextMenu::signalAcquisition)) {
                *result = 12;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject ContextMenu::staticMetaObject = { {
    QMetaObject::SuperData::link<QMenu::staticMetaObject>(),
    qt_meta_stringdata_ContextMenu.data,
    qt_meta_data_ContextMenu,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ContextMenu::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ContextMenu::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ContextMenu.stringdata0))
        return static_cast<void*>(this);
    return QMenu::qt_metacast(_clname);
}

int ContextMenu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMenu::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void ContextMenu::sigRefresh()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ContextMenu::signalOpen()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ContextMenu::signalClose()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void ContextMenu::signalNewFolder()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void ContextMenu::signalNewFile()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void ContextMenu::signalDelete()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void ContextMenu::signalMove()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void ContextMenu::signalCopy()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void ContextMenu::signalRename()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void ContextMenu::signalWrite()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}

// SIGNAL 10
void ContextMenu::signalPlayback()
{
    QMetaObject::activate(this, &staticMetaObject, 10, nullptr);
}

// SIGNAL 11
void ContextMenu::signalExport()
{
    QMetaObject::activate(this, &staticMetaObject, 11, nullptr);
}

// SIGNAL 12
void ContextMenu::signalAcquisition()
{
    QMetaObject::activate(this, &staticMetaObject, 12, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
