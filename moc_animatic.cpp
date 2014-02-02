/****************************************************************************
** Meta object code from reading C++ file 'animatic.h'
**
** Created: Sun Feb 2 07:31:22 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "animatic.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'animatic.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_animatic[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x0a,
      27,    9,    9,    9, 0x0a,
      44,    9,    9,    9, 0x0a,
      61,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_animatic[] = {
    "animatic\0\0btnPlayClicked()\0btnStopClicked()\0"
    "btnQuitClicked()\0clearTimer()\0"
};

void animatic::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        animatic *_t = static_cast<animatic *>(_o);
        switch (_id) {
        case 0: _t->btnPlayClicked(); break;
        case 1: _t->btnStopClicked(); break;
        case 2: _t->btnQuitClicked(); break;
        case 3: _t->clearTimer(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData animatic::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject animatic::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_animatic,
      qt_meta_data_animatic, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &animatic::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *animatic::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *animatic::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_animatic))
        return static_cast<void*>(const_cast< animatic*>(this));
    return QDialog::qt_metacast(_clname);
}

int animatic::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
