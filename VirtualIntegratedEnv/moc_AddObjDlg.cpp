/****************************************************************************
** Meta object code from reading C++ file 'AddObjDlg.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "AddObjDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AddObjDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AddObjDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x0a,
      33,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_AddObjDlg[] = {
    "AddObjDlg\0\0on_ApplyBtn_clicked()\0"
    "on_browseBtn_clicked()\0"
};

void AddObjDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AddObjDlg *_t = static_cast<AddObjDlg *>(_o);
        switch (_id) {
        case 0: _t->on_ApplyBtn_clicked(); break;
        case 1: _t->on_browseBtn_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData AddObjDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject AddObjDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_AddObjDlg,
      qt_meta_data_AddObjDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AddObjDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AddObjDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AddObjDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AddObjDlg))
        return static_cast<void*>(const_cast< AddObjDlg*>(this));
    if (!strcmp(_clname, "Ui_AddObjDlg"))
        return static_cast< Ui_AddObjDlg*>(const_cast< AddObjDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int AddObjDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
