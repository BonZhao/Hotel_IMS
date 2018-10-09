/****************************************************************************
** Meta object code from reading C++ file 'resignin.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../3.3.4.1/resignin.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'resignin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_resignIn_t {
    QByteArrayData data[11];
    char stringdata[186];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_resignIn_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_resignIn_t qt_meta_stringdata_resignIn = {
    {
QT_MOC_LITERAL(0, 0, 8), // "resignIn"
QT_MOC_LITERAL(1, 9, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 23), // "on_pushButton_2_clicked"
QT_MOC_LITERAL(4, 56, 11), // "closeWidget"
QT_MOC_LITERAL(5, 68, 10), // "closeEvent"
QT_MOC_LITERAL(6, 79, 12), // "QCloseEvent*"
QT_MOC_LITERAL(7, 92, 21), // "on_pushButton_pressed"
QT_MOC_LITERAL(8, 114, 22), // "on_pushButton_released"
QT_MOC_LITERAL(9, 137, 23), // "on_pushButton_2_pressed"
QT_MOC_LITERAL(10, 161, 24) // "on_pushButton_2_released"

    },
    "resignIn\0on_pushButton_clicked\0\0"
    "on_pushButton_2_clicked\0closeWidget\0"
    "closeEvent\0QCloseEvent*\0on_pushButton_pressed\0"
    "on_pushButton_released\0on_pushButton_2_pressed\0"
    "on_pushButton_2_released"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_resignIn[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x08 /* Private */,
       3,    0,   55,    2, 0x08 /* Private */,
       4,    0,   56,    2, 0x08 /* Private */,
       5,    1,   57,    2, 0x08 /* Private */,
       7,    0,   60,    2, 0x08 /* Private */,
       8,    0,   61,    2, 0x08 /* Private */,
       9,    0,   62,    2, 0x08 /* Private */,
      10,    0,   63,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void, 0x80000000 | 6,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void resignIn::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        resignIn *_t = static_cast<resignIn *>(_o);
        switch (_id) {
        case 0: _t->on_pushButton_clicked(); break;
        case 1: _t->on_pushButton_2_clicked(); break;
        case 2: { bool _r = _t->closeWidget();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 3: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        case 4: _t->on_pushButton_pressed(); break;
        case 5: _t->on_pushButton_released(); break;
        case 6: _t->on_pushButton_2_pressed(); break;
        case 7: _t->on_pushButton_2_released(); break;
        default: ;
        }
    }
}

const QMetaObject resignIn::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_resignIn.data,
      qt_meta_data_resignIn,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *resignIn::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *resignIn::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_resignIn.stringdata))
        return static_cast<void*>(const_cast< resignIn*>(this));
    return QDialog::qt_metacast(_clname);
}

int resignIn::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
