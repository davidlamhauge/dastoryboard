/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Sun Jan 5 19:41:45 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      25,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      30,   11,   11,   11, 0x08,
      47,   11,   11,   11, 0x08,
      63,   11,   11,   11, 0x08,
      80,   11,   11,   11, 0x08,
      91,   11,   11,   11, 0x08,
     106,   11,   11,   11, 0x08,
     114,   11,   11,   11, 0x08,
     122,   11,   11,   11, 0x08,
     130,   11,   11,   11, 0x08,
     138,   11,   11,   11, 0x08,
     148,   11,   11,   11, 0x08,
     160,   11,   11,   11, 0x08,
     176,   11,   11,   11, 0x08,
     186,   11,   11,   11, 0x08,
     197,   11,   11,   11, 0x08,
     205,   11,   11,   11, 0x08,
     223,   11,   11,   11, 0x08,
     241,   11,   11,   11, 0x08,
     257,   11,   11,   11, 0x08,
     271,   11,   11,   11, 0x08,
     284,   11,   11,   11, 0x08,
     299,   11,   11,   11, 0x08,
     318,   11,   11,   11, 0x08,
     333,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0disableStoryPad()\0"
    "enableStoryPad()\0newStoryboard()\0"
    "openStoryboard()\0writeXML()\0saveSettings()\0"
    "penF5()\0penF6()\0penF7()\0penF8()\0"
    "penPick()\0okPenPick()\0cancelPenPick()\0"
    "eraseF5()\0eraseAll()\0about()\0"
    "appendSketchPad()\0insertSketchPad()\0"
    "updateComment()\0updateScene()\0"
    "updateShot()\0updateFrames()\0"
    "updateSaveImages()\0updateImages()\0"
    "changeImage()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->disableStoryPad(); break;
        case 1: _t->enableStoryPad(); break;
        case 2: _t->newStoryboard(); break;
        case 3: _t->openStoryboard(); break;
        case 4: _t->writeXML(); break;
        case 5: _t->saveSettings(); break;
        case 6: _t->penF5(); break;
        case 7: _t->penF6(); break;
        case 8: _t->penF7(); break;
        case 9: _t->penF8(); break;
        case 10: _t->penPick(); break;
        case 11: _t->okPenPick(); break;
        case 12: _t->cancelPenPick(); break;
        case 13: _t->eraseF5(); break;
        case 14: _t->eraseAll(); break;
        case 15: _t->about(); break;
        case 16: _t->appendSketchPad(); break;
        case 17: _t->insertSketchPad(); break;
        case 18: _t->updateComment(); break;
        case 19: _t->updateScene(); break;
        case 20: _t->updateShot(); break;
        case 21: _t->updateFrames(); break;
        case 22: _t->updateSaveImages(); break;
        case 23: _t->updateImages(); break;
        case 24: _t->changeImage(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 25)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 25;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
