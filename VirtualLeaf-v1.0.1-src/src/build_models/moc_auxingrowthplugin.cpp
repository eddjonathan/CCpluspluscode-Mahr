/****************************************************************************
** Meta object code from reading C++ file 'auxingrowthplugin.h'
**
** Created: Thu Jun 8 22:21:21 2017
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "auxingrowthplugin.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'auxingrowthplugin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AuxinGrowthPlugin[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_AuxinGrowthPlugin[] = {
    "AuxinGrowthPlugin\0"
};

void AuxinGrowthPlugin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData AuxinGrowthPlugin::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject AuxinGrowthPlugin::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_AuxinGrowthPlugin,
      qt_meta_data_AuxinGrowthPlugin, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AuxinGrowthPlugin::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AuxinGrowthPlugin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AuxinGrowthPlugin::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AuxinGrowthPlugin))
        return static_cast<void*>(const_cast< AuxinGrowthPlugin*>(this));
    if (!strcmp(_clname, "SimPluginInterface"))
        return static_cast< SimPluginInterface*>(const_cast< AuxinGrowthPlugin*>(this));
    if (!strcmp(_clname, "nl.cwi.VirtualLeaf.SimPluginInterface/1.3"))
        return static_cast< SimPluginInterface*>(const_cast< AuxinGrowthPlugin*>(this));
    return QObject::qt_metacast(_clname);
}

int AuxinGrowthPlugin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
