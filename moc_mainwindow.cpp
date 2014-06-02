/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[25];
    char stringdata[375];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_MainWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 7),
QT_MOC_LITERAL(2, 19, 0),
QT_MOC_LITERAL(3, 20, 8),
QT_MOC_LITERAL(4, 29, 4),
QT_MOC_LITERAL(5, 34, 8),
QT_MOC_LITERAL(6, 43, 9),
QT_MOC_LITERAL(7, 53, 10),
QT_MOC_LITERAL(8, 64, 9),
QT_MOC_LITERAL(9, 74, 7),
QT_MOC_LITERAL(10, 82, 12),
QT_MOC_LITERAL(11, 95, 6),
QT_MOC_LITERAL(12, 102, 14),
QT_MOC_LITERAL(13, 117, 13),
QT_MOC_LITERAL(14, 131, 13),
QT_MOC_LITERAL(15, 145, 21),
QT_MOC_LITERAL(16, 167, 22),
QT_MOC_LITERAL(17, 190, 21),
QT_MOC_LITERAL(18, 212, 24),
QT_MOC_LITERAL(19, 237, 32),
QT_MOC_LITERAL(20, 270, 16),
QT_MOC_LITERAL(21, 287, 12),
QT_MOC_LITERAL(22, 300, 23),
QT_MOC_LITERAL(23, 324, 25),
QT_MOC_LITERAL(24, 350, 23)
    },
    "MainWindow\0getHash\0\0getCheck\0save\0"
    "sendTest\0checkTest\0userSelect\0selectDir\0"
    "hidebar\0getfileTotal\0action\0checkCompleted\0"
    "saveCompleted\0scanCompleted\0"
    "on_saveButton_clicked\0on_checkButton_clicked\0"
    "on_pushButton_clicked\0on_actionAbout_triggered\0"
    "on_actionSet_Directory_triggered\0"
    "displayFileTotal\0enableButton\0"
    "on_actionText_triggered\0"
    "on_actionBinary_triggered\0"
    "on_actionCopy_triggered\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      23,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  129,    2, 0x06,
       3,    0,  130,    2, 0x06,
       4,    0,  131,    2, 0x06,
       5,    0,  132,    2, 0x06,
       6,    0,  133,    2, 0x06,
       7,    1,  134,    2, 0x06,
       8,    1,  137,    2, 0x06,
       9,    0,  140,    2, 0x06,
      10,    0,  141,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
      11,    1,  142,    2, 0x0a,
      12,    0,  145,    2, 0x0a,
      13,    0,  146,    2, 0x0a,
      14,    0,  147,    2, 0x0a,
      15,    0,  148,    2, 0x08,
      16,    0,  149,    2, 0x08,
      17,    0,  150,    2, 0x08,
      18,    0,  151,    2, 0x08,
      19,    0,  152,    2, 0x08,
      20,    1,  153,    2, 0x08,
      21,    0,  156,    2, 0x08,
      22,    0,  157,    2, 0x08,
      23,    0,  158,    2, 0x08,
      24,    0,  159,    2, 0x08,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->getHash(); break;
        case 1: _t->getCheck(); break;
        case 2: _t->save(); break;
        case 3: _t->sendTest(); break;
        case 4: _t->checkTest(); break;
        case 5: _t->userSelect((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->selectDir((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->hidebar(); break;
        case 8: _t->getfileTotal(); break;
        case 9: _t->action((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->checkCompleted(); break;
        case 11: _t->saveCompleted(); break;
        case 12: _t->scanCompleted(); break;
        case 13: _t->on_saveButton_clicked(); break;
        case 14: _t->on_checkButton_clicked(); break;
        case 15: _t->on_pushButton_clicked(); break;
        case 16: _t->on_actionAbout_triggered(); break;
        case 17: _t->on_actionSet_Directory_triggered(); break;
        case 18: _t->displayFileTotal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 19: _t->enableButton(); break;
        case 20: _t->on_actionText_triggered(); break;
        case 21: _t->on_actionBinary_triggered(); break;
        case 22: _t->on_actionCopy_triggered(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::getHash)) {
                *result = 0;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::getCheck)) {
                *result = 1;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::save)) {
                *result = 2;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::sendTest)) {
                *result = 3;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::checkTest)) {
                *result = 4;
            }
        }
        {
            typedef void (MainWindow::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::userSelect)) {
                *result = 5;
            }
        }
        {
            typedef void (MainWindow::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::selectDir)) {
                *result = 6;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::hidebar)) {
                *result = 7;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::getfileTotal)) {
                *result = 8;
            }
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, 0, 0}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 23)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 23)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 23;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::getHash()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void MainWindow::getCheck()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void MainWindow::save()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void MainWindow::sendTest()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void MainWindow::checkTest()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void MainWindow::userSelect(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void MainWindow::selectDir(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void MainWindow::hidebar()
{
    QMetaObject::activate(this, &staticMetaObject, 7, 0);
}

// SIGNAL 8
void MainWindow::getfileTotal()
{
    QMetaObject::activate(this, &staticMetaObject, 8, 0);
}
QT_END_MOC_NAMESPACE
