/****************************************************************************
** Meta object code from reading C++ file 'getfiletotal.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "getfiletotal.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'getfiletotal.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_GetFileTotal_t {
    QByteArrayData data[8];
    char stringdata[69];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_GetFileTotal_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_GetFileTotal_t qt_meta_stringdata_GetFileTotal = {
    {
QT_MOC_LITERAL(0, 0, 12),
QT_MOC_LITERAL(1, 13, 8),
QT_MOC_LITERAL(2, 22, 0),
QT_MOC_LITERAL(3, 23, 5),
QT_MOC_LITERAL(4, 29, 11),
QT_MOC_LITERAL(5, 41, 9),
QT_MOC_LITERAL(6, 51, 3),
QT_MOC_LITERAL(7, 55, 12)
    },
    "GetFileTotal\0finished\0\0close\0disableScan\0"
    "selectDir\0dir\0getfileTotal\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GetFileTotal[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06,
       3,    0,   42,    2, 0x06,
       4,    0,   43,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       5,    1,   44,    2, 0x0a,
       7,    0,   47,    2, 0x0a,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void,

       0        // eod
};

void GetFileTotal::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GetFileTotal *_t = static_cast<GetFileTotal *>(_o);
        switch (_id) {
        case 0: _t->finished((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->close(); break;
        case 2: _t->disableScan(); break;
        case 3: _t->selectDir((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->getfileTotal(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (GetFileTotal::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GetFileTotal::finished)) {
                *result = 0;
            }
        }
        {
            typedef void (GetFileTotal::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GetFileTotal::close)) {
                *result = 1;
            }
        }
        {
            typedef void (GetFileTotal::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GetFileTotal::disableScan)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject GetFileTotal::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_GetFileTotal.data,
      qt_meta_data_GetFileTotal,  qt_static_metacall, 0, 0}
};


const QMetaObject *GetFileTotal::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GetFileTotal::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GetFileTotal.stringdata))
        return static_cast<void*>(const_cast< GetFileTotal*>(this));
    return QObject::qt_metacast(_clname);
}

int GetFileTotal::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void GetFileTotal::finished(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GetFileTotal::close()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void GetFileTotal::disableScan()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
