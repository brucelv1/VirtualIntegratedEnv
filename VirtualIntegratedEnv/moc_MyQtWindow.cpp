/****************************************************************************
** Meta object code from reading C++ file 'MyQtWindow.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "MyQtWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MyQtWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MyQtWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      23,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: signature, parameters, type, tag, flags
      16,   12,   11,   11, 0x05,
      42,   11,   11,   11, 0x05,
      59,   11,   11,   11, 0x05,
     177,   75,   11,   11, 0x05,
     224,  219,   11,   11, 0x05,
     246,  219,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
     268,   11,   11,   11, 0x0a,
     294,   11,   11,   11, 0x0a,
     321,   11,   11,   11, 0x0a,
     347,   11,   11,   11, 0x0a,
     377,   11,   11,   11, 0x0a,
     403,   11,   11,   11, 0x0a,
     429,   11,   11,   11, 0x0a,
     456,   11,   11,   11, 0x0a,
     483,   11,   11,   11, 0x0a,
     512,   11,   11,   11, 0x0a,
     543,   11,   11,   11, 0x0a,
     575,   11,   11,   11, 0x0a,
     602,   11,   11,   11, 0x0a,
     637,   11,   11,   11, 0x0a,
     667,   11,   11,   11, 0x0a,
     696,   11,   11,   11, 0x0a,
     728,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MyQtWindow[] = {
    "MyQtWindow\0\0uAI\0userAddData(userAddInfo*)\0"
    "StartTriggered()\0StopTriggered()\0"
    "isUsingKeyboard,isUsingDataGlove,isUsingPlatform,isUsingCollision,plat"
    "formSerialNum,hardwareSerialNum\0"
    "SettingsInfo(bool,bool,bool,bool,int,int)\0"
    "path\0fileSave(std::string)\0"
    "fileOpen(std::string)\0on_action_Add_triggered()\0"
    "on_actionStart_triggered()\0"
    "on_actionStop_triggered()\0"
    "on_actionSettings_triggered()\0"
    "on_actionOpen_triggered()\0"
    "on_actionSave_triggered()\0"
    "on_actionSJT_6_triggered()\0"
    "on_actionSJT_3_triggered()\0"
    "on_actionBarrett_triggered()\0"
    "on_actionHumanHand_triggered()\0"
    "on_actionAddObjects_triggered()\0"
    "on_actionReset_triggered()\0"
    "on_actionAddCustomHand_triggered()\0"
    "on_actionTraining_triggered()\0"
    "on_actionTesting_triggered()\0"
    "on_actionExercising_triggered()\0"
    "_qTimer_timeout()\0"
};

void MyQtWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MyQtWindow *_t = static_cast<MyQtWindow *>(_o);
        switch (_id) {
        case 0: _t->userAddData((*reinterpret_cast< userAddInfo*(*)>(_a[1]))); break;
        case 1: _t->StartTriggered(); break;
        case 2: _t->StopTriggered(); break;
        case 3: _t->SettingsInfo((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6]))); break;
        case 4: _t->fileSave((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 5: _t->fileOpen((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 6: _t->on_action_Add_triggered(); break;
        case 7: _t->on_actionStart_triggered(); break;
        case 8: _t->on_actionStop_triggered(); break;
        case 9: _t->on_actionSettings_triggered(); break;
        case 10: _t->on_actionOpen_triggered(); break;
        case 11: _t->on_actionSave_triggered(); break;
        case 12: _t->on_actionSJT_6_triggered(); break;
        case 13: _t->on_actionSJT_3_triggered(); break;
        case 14: _t->on_actionBarrett_triggered(); break;
        case 15: _t->on_actionHumanHand_triggered(); break;
        case 16: _t->on_actionAddObjects_triggered(); break;
        case 17: _t->on_actionReset_triggered(); break;
        case 18: _t->on_actionAddCustomHand_triggered(); break;
        case 19: _t->on_actionTraining_triggered(); break;
        case 20: _t->on_actionTesting_triggered(); break;
        case 21: _t->on_actionExercising_triggered(); break;
        case 22: _t->_qTimer_timeout(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MyQtWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MyQtWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MyQtWindow,
      qt_meta_data_MyQtWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MyQtWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MyQtWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MyQtWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MyQtWindow))
        return static_cast<void*>(const_cast< MyQtWindow*>(this));
    if (!strcmp(_clname, "Ui_MainWindow"))
        return static_cast< Ui_MainWindow*>(const_cast< MyQtWindow*>(this));
    if (!strcmp(_clname, "dtCore::Base"))
        return static_cast< dtCore::Base*>(const_cast< MyQtWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MyQtWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 23)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    }
    return _id;
}

// SIGNAL 0
void MyQtWindow::userAddData(userAddInfo * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MyQtWindow::StartTriggered()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void MyQtWindow::StopTriggered()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void MyQtWindow::SettingsInfo(bool _t1, bool _t2, bool _t3, bool _t4, int _t5, int _t6)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MyQtWindow::fileSave(std::string _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void MyQtWindow::fileOpen(std::string _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_END_MOC_NAMESPACE
