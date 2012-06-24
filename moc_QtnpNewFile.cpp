/****************************************************************************
** Meta object code from reading C++ file 'QtnpNewFile.h'
**
** Created: Sun Feb 26 00:56:13 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "QtnpNewFile.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QtnpNewFile.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QtnpNewFile[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   13,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
      33,   12,   12,   12, 0x08,
      45,   12,   12,   12, 0x08,
      56,   12,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QtnpNewFile[] = {
    "QtnpNewFile\0\0,\0newImage(int,int)\0"
    "clickOkay()\0xChanged()\0yChanged()\0"
};

const QMetaObject QtnpNewFile::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QtnpNewFile,
      qt_meta_data_QtnpNewFile, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QtnpNewFile::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QtnpNewFile::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QtnpNewFile::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QtnpNewFile))
        return static_cast<void*>(const_cast< QtnpNewFile*>(this));
    return QDialog::qt_metacast(_clname);
}

int QtnpNewFile::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: newImage((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: clickOkay(); break;
        case 2: xChanged(); break;
        case 3: yChanged(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void QtnpNewFile::newImage(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
