/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Thu Jan 16 23:07:33 2014
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
      32,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      28,   11,   11,   11, 0x08,
      45,   11,   11,   11, 0x08,
      56,   11,   11,   11, 0x08,
      68,   11,   11,   11, 0x08,
      83,   11,   11,   11, 0x08,
     104,   11,   11,   11, 0x08,
     119,   11,   11,   11, 0x08,
     130,   11,   11,   11, 0x08,
     140,   11,   11,   11, 0x08,
     154,   11,   11,   11, 0x08,
     163,   11,   11,   11, 0x08,
     171,   11,   11,   11, 0x08,
     179,   11,   11,   11, 0x08,
     187,   11,   11,   11, 0x08,
     195,   11,   11,   11, 0x08,
     205,   11,   11,   11, 0x08,
     217,   11,   11,   11, 0x08,
     233,   11,   11,   11, 0x08,
     243,   11,   11,   11, 0x08,
     254,   11,   11,   11, 0x08,
     262,   11,   11,   11, 0x08,
     280,   11,   11,   11, 0x08,
     298,   11,   11,   11, 0x08,
     314,   11,   11,   11, 0x08,
     328,   11,   11,   11, 0x08,
     341,   11,   11,   11, 0x08,
     356,   11,   11,   11, 0x08,
     374,   11,   11,   11, 0x08,
     387,   11,   11,   11, 0x08,
     402,   11,   11,   11, 0x08,
     421,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0newStoryboard()\0"
    "openStoryboard()\0newScene()\0openScene()\0"
    "writeProjXML()\0writeStoryboardXML()\0"
    "saveSettings()\0setPrefs()\0okPrefs()\0"
    "cancelPrefs()\0penStd()\0penF5()\0penF6()\0"
    "penF7()\0penF8()\0penPick()\0okPenPick()\0"
    "cancelPenPick()\0eraseF5()\0eraseAll()\0"
    "about()\0appendSketchPad()\0insertSketchPad()\0"
    "updateComment()\0updateScene()\0"
    "updateShot()\0updateFrames()\0"
    "updateScenelist()\0saveImages()\0"
    "updateImages()\0centerStoryboard()\0"
    "changeImage()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->newStoryboard(); break;
        case 1: _t->openStoryboard(); break;
        case 2: _t->newScene(); break;
        case 3: _t->openScene(); break;
        case 4: _t->writeProjXML(); break;
        case 5: _t->writeStoryboardXML(); break;
        case 6: _t->saveSettings(); break;
        case 7: _t->setPrefs(); break;
        case 8: _t->okPrefs(); break;
        case 9: _t->cancelPrefs(); break;
        case 10: _t->penStd(); break;
        case 11: _t->penF5(); break;
        case 12: _t->penF6(); break;
        case 13: _t->penF7(); break;
        case 14: _t->penF8(); break;
        case 15: _t->penPick(); break;
        case 16: _t->okPenPick(); break;
        case 17: _t->cancelPenPick(); break;
        case 18: _t->eraseF5(); break;
        case 19: _t->eraseAll(); break;
        case 20: _t->about(); break;
        case 21: _t->appendSketchPad(); break;
        case 22: _t->insertSketchPad(); break;
        case 23: _t->updateComment(); break;
        case 24: _t->updateScene(); break;
        case 25: _t->updateShot(); break;
        case 26: _t->updateFrames(); break;
        case 27: _t->updateScenelist(); break;
        case 28: _t->saveImages(); break;
        case 29: _t->updateImages(); break;
        case 30: _t->centerStoryboard(); break;
        case 31: _t->changeImage(); break;
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
        if (_id < 32)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 32;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
