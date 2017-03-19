/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      25,   21,   11,   11, 0x0a,
      53,   21,   11,   11, 0x0a,
      84,   82,   11,   11, 0x0a,
     104,   82,   11,   11, 0x0a,
     123,   11,   11,   11, 0x0a,
     136,   11,   11,   11, 0x0a,
     149,   11,   11,   11, 0x0a,
     175,   11,   11,   11, 0x08,
     199,   11,   11,   11, 0x08,
     216,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0showMB()\0val\0"
    "linearSpinBoxChange(double)\0"
    "angularSpinBoxChange(double)\0p\0"
    "setAngularP(double)\0setLinearP(double)\0"
    "setNewGoal()\0cancelGoal()\0"
    "startTestButtonCallback()\0"
    "on_pushButton_clicked()\0showMessageBox()\0"
    "drawMap()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->showMB(); break;
        case 1: _t->linearSpinBoxChange((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: _t->angularSpinBoxChange((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->setAngularP((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: _t->setLinearP((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: _t->setNewGoal(); break;
        case 6: _t->cancelGoal(); break;
        case 7: _t->startTestButtonCallback(); break;
        case 8: _t->on_pushButton_clicked(); break;
        case 9: _t->showMessageBox(); break;
        case 10: _t->drawMap(); break;
        default: ;
        }
    }
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
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::showMB()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
