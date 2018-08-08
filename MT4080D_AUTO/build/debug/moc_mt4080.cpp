/****************************************************************************
** Meta object code from reading C++ file 'mt4080.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../MT4080/mt4080.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mt4080.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MT4080_t {
    QByteArrayData data[7];
    char stringdata0[45];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MT4080_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MT4080_t qt_meta_stringdata_MT4080 = {
    {
QT_MOC_LITERAL(0, 0, 6), // "MT4080"
QT_MOC_LITERAL(1, 7, 7), // "Primary"
QT_MOC_LITERAL(2, 15, 0), // ""
QT_MOC_LITERAL(3, 16, 3), // "val"
QT_MOC_LITERAL(4, 20, 6), // "Second"
QT_MOC_LITERAL(5, 27, 7), // "Display"
QT_MOC_LITERAL(6, 35, 9) // "Display_t"

    },
    "MT4080\0Primary\0\0val\0Second\0Display\0"
    "Display_t"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MT4080[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       4,    1,   32,    2, 0x06 /* Public */,
       5,    1,   35,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, 0x80000000 | 6,    3,

       0        // eod
};

void MT4080::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MT4080 *_t = static_cast<MT4080 *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Primary((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->Second((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: _t->Display((*reinterpret_cast< const Display_t(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (MT4080::*_t)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MT4080::Primary)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MT4080::*_t)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MT4080::Second)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (MT4080::*_t)(const Display_t & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MT4080::Display)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject MT4080::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MT4080.data,
      qt_meta_data_MT4080,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MT4080::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MT4080::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MT4080.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int MT4080::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void MT4080::Primary(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MT4080::Second(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MT4080::Display(const Display_t & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
