/****************************************************************************
** Meta object code from reading C++ file 'worker.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "worker.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'worker.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_GUIUpdater_t {
    QByteArrayData data[18];
    char stringdata[156];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_GUIUpdater_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_GUIUpdater_t qt_meta_stringdata_GUIUpdater = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 3),
QT_MOC_LITERAL(2, 15, 0),
QT_MOC_LITERAL(3, 16, 8),
QT_MOC_LITERAL(4, 25, 14),
QT_MOC_LITERAL(5, 40, 12),
QT_MOC_LITERAL(6, 53, 16),
QT_MOC_LITERAL(7, 70, 5),
QT_MOC_LITERAL(8, 76, 5),
QT_MOC_LITERAL(9, 82, 6),
QT_MOC_LITERAL(10, 89, 6),
QT_MOC_LITERAL(11, 96, 9),
QT_MOC_LITERAL(12, 106, 3),
QT_MOC_LITERAL(13, 110, 8),
QT_MOC_LITERAL(14, 119, 9),
QT_MOC_LITERAL(15, 129, 8),
QT_MOC_LITERAL(16, 138, 8),
QT_MOC_LITERAL(17, 147, 7)
    },
    "GUIUpdater\0req\0\0Finished\0percentChanged\0"
    "getfileTotal\0displayFileTotal\0close\0"
    "total\0action\0method\0selectDir\0dir\0"
    "scanFile\0checkFile\0saveFile\0oldCheck\0"
    "oldSave\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GUIUpdater[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x06,
       3,    1,   85,    2, 0x06,
       4,    1,   88,    2, 0x06,
       5,    0,   91,    2, 0x06,
       6,    1,   92,    2, 0x06,
       7,    0,   95,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       5,    1,   96,    2, 0x0a,
       9,    1,   99,    2, 0x0a,
      11,    1,  102,    2, 0x0a,
      13,    0,  105,    2, 0x0a,
      14,    0,  106,    2, 0x0a,
      15,    0,  107,    2, 0x0a,
      16,    0,  108,    2, 0x0a,
      17,    0,  109,    2, 0x0a,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void GUIUpdater::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GUIUpdater *_t = static_cast<GUIUpdater *>(_o);
        switch (_id) {
        case 0: _t->req(); break;
        case 1: _t->Finished((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->percentChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->getfileTotal(); break;
        case 4: _t->displayFileTotal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->close(); break;
        case 6: _t->getfileTotal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->action((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->selectDir((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->scanFile(); break;
        case 10: _t->checkFile(); break;
        case 11: _t->saveFile(); break;
        case 12: _t->oldCheck(); break;
        case 13: _t->oldSave(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (GUIUpdater::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GUIUpdater::req)) {
                *result = 0;
            }
        }
        {
            typedef void (GUIUpdater::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GUIUpdater::Finished)) {
                *result = 1;
            }
        }
        {
            typedef void (GUIUpdater::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GUIUpdater::percentChanged)) {
                *result = 2;
            }
        }
        {
            typedef void (GUIUpdater::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GUIUpdater::getfileTotal)) {
                *result = 3;
            }
        }
        {
            typedef void (GUIUpdater::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GUIUpdater::displayFileTotal)) {
                *result = 4;
            }
        }
        {
            typedef void (GUIUpdater::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GUIUpdater::close)) {
                *result = 5;
            }
        }
    }
}

const QMetaObject GUIUpdater::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_GUIUpdater.data,
      qt_meta_data_GUIUpdater,  qt_static_metacall, 0, 0}
};


const QMetaObject *GUIUpdater::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GUIUpdater::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GUIUpdater.stringdata))
        return static_cast<void*>(const_cast< GUIUpdater*>(this));
    return QObject::qt_metacast(_clname);
}

int GUIUpdater::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void GUIUpdater::req()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void GUIUpdater::Finished(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void GUIUpdater::percentChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void GUIUpdater::getfileTotal()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void GUIUpdater::displayFileTotal(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void GUIUpdater::close()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}
QT_END_MOC_NAMESPACE
