/****************************************************************************
** Meta object code from reading C++ file 'canvas.h'
**
** Created: Thu Jun 8 22:21:10 2017
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "canvas.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'canvas.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FigureEditor[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x05,
      30,   13,   13,   13, 0x05,
      45,   13,   13,   13, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_FigureEditor[] = {
    "FigureEditor\0\0status(QString)\0"
    "MousePressed()\0MouseReleased()\0"
};

void FigureEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        FigureEditor *_t = static_cast<FigureEditor *>(_o);
        switch (_id) {
        case 0: _t->status((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->MousePressed(); break;
        case 2: _t->MouseReleased(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData FigureEditor::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject FigureEditor::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_FigureEditor,
      qt_meta_data_FigureEditor, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FigureEditor::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FigureEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FigureEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FigureEditor))
        return static_cast<void*>(const_cast< FigureEditor*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int FigureEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void FigureEditor::status(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void FigureEditor::MousePressed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void FigureEditor::MouseReleased()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
static const uint qt_meta_data_Main[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      66,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
       6,    5,    5,    5, 0x05,
      23,    5,    5,    5, 0x05,

 // slots: signature, parameters, type, tag, flags
      37,    5,    5,    5, 0x0a,
      45,    5,    5,    5, 0x0a,
      51,    5,    5,    5, 0x0a,
      66,    5,    5,    5, 0x0a,
      86,   81,    5,    5, 0x0a,
     108,    5,    5,    5, 0x0a,
     121,    5,    5,    5, 0x0a,
     145,    5,    5,    5, 0x0a,
     163,    5,    5,    5, 0x0a,
     187,    5,    5,    5, 0x0a,
     206,    5,    5,    5, 0x0a,
     226,    5,    5,    5, 0x0a,
     246,    5,    5,    5, 0x0a,
     263,    5,    5,    5, 0x0a,
     282,    5,    5,    5, 0x0a,
     300,    5,    5,    5, 0x0a,
     322,    5,    5,    5, 0x0a,
     339,    5,    5,    5, 0x0a,
     359,    5,    5,    5, 0x0a,
     380,    5,    5,    5, 0x0a,
     398,    5,    5,    5, 0x0a,
     406,    5,    5,    5, 0x0a,
     424,    5,    5,    5, 0x0a,
     441,    5,    5,    5, 0x0a,
     493,  462,  458,    5, 0x0a,
     557,  534,  458,    5, 0x2a,
     611,  593,  458,    5, 0x2a,
     651,  642,  458,    5, 0x2a,
     677,    5,    5,    5, 0x0a,
     697,    5,    5,    5, 0x0a,
     732,  716,    5,    5, 0x0a,
     765,  757,    5,    5, 0x2a,
     786,    5,    5,    5, 0x0a,
     796,    5,    5,    5, 0x0a,
     813,    5,    5,    5, 0x0a,
     838,  829,    5,    5, 0x0a,
     864,    5,    5,    5, 0x08,
     874,    5,    5,    5, 0x08,
     884,    5,    5,    5, 0x08,
     906,    5,  901,    5, 0x08,
     919,    5,    5,    5, 0x08,
     934,    5,    5,    5, 0x08,
     953,    5,    5,    5, 0x08,
     972,    5,    5,    5, 0x08,
     992,    5,    5,    5, 0x08,
    1011,    5,    5,    5, 0x08,
    1028,    5,    5,    5, 0x08,
    1052,    5,    5,    5, 0x08,
    1081,    5,    5,    5, 0x08,
    1103,    5,    5,    5, 0x08,
    1118,    5,    5,    5, 0x08,
    1129,    5,    5,    5, 0x08,
    1140,    5,    5,    5, 0x08,
    1151,    5,    5,    5, 0x08,
    1159,    5,    5,    5, 0x08,
    1166,    5,    5,    5, 0x08,
    1175,    5,    5,    5, 0x08,
    1185,    5,    5,    5, 0x08,
    1194,    5,    5,    5, 0x08,
    1203,    5,    5,    5, 0x08,
    1213,    5,    5,    5, 0x08,
    1225,    5,    5,    5, 0x08,
    1246,    5,    5,    5, 0x08,
    1270,    5,    5,    5, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Main[] = {
    "Main\0\0SimulationDone()\0ParsChanged()\0"
    "about()\0gpl()\0TimeStepWrap()\0"
    "togglePaused()\0size\0setFluxArrowSize(int)\0"
    "RestartSim()\0toggleShowCellCenters()\0"
    "toggleShowNodes()\0toggleShowBorderCells()\0"
    "toggleShowFluxes()\0toggleNodeNumbers()\0"
    "toggleCellNumbers()\0toggleCellAxes()\0"
    "toggleCellStrain()\0toggleShowWalls()\0"
    "toggleShowApoplasts()\0toggleDynCells()\0"
    "toggleMovieFrames()\0toggleLeafBoundary()\0"
    "toggleHideCells()\0print()\0startSimulation()\0"
    "stopSimulation()\0RefreshInfoBar()\0int\0"
    "filename,geometry,pars,simtime\0"
    "readStateXML(const char*,bool,bool,bool)\0"
    "filename,geometry,pars\0"
    "readStateXML(const char*,bool,bool)\0"
    "filename,geometry\0readStateXML(const char*,bool)\0"
    "filename\0readStateXML(const char*)\0"
    "EnterRotationMode()\0ExitRotationMode()\0"
    "message,timeout\0UserMessage(QString,int)\0"
    "message\0UserMessage(QString)\0Refresh()\0"
    "PauseIfRunning()\0ContIfRunning()\0"
    "settings\0XMLReadSettings(xmlNode*)\0"
    "aboutQt()\0newView()\0EditParameters()\0"
    "QDir\0GetLeafDir()\0readStateXML()\0"
    "readNextStateXML()\0readPrevStateXML()\0"
    "readFirstStateXML()\0readLastStateXML()\0"
    "exportCellData()\0exportCellData(QString)\0"
    "exportCellDatanodes(QString)\0"
    "exportCellDatanodes()\0saveStateXML()\0"
    "snapshot()\0savePars()\0readPars()\0"
    "clear()\0init()\0CutSAM()\0enlarge()\0"
    "shrink()\0zoomIn()\0zoomOut()\0CleanMesh()\0"
    "CleanMeshChemicals()\0CleanMeshTransporters()\0"
    "RandomizeMesh()\0"
};

void Main::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Main *_t = static_cast<Main *>(_o);
        switch (_id) {
        case 0: _t->SimulationDone(); break;
        case 1: _t->ParsChanged(); break;
        case 2: _t->about(); break;
        case 3: _t->gpl(); break;
        case 4: _t->TimeStepWrap(); break;
        case 5: _t->togglePaused(); break;
        case 6: _t->setFluxArrowSize((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->RestartSim(); break;
        case 8: _t->toggleShowCellCenters(); break;
        case 9: _t->toggleShowNodes(); break;
        case 10: _t->toggleShowBorderCells(); break;
        case 11: _t->toggleShowFluxes(); break;
        case 12: _t->toggleNodeNumbers(); break;
        case 13: _t->toggleCellNumbers(); break;
        case 14: _t->toggleCellAxes(); break;
        case 15: _t->toggleCellStrain(); break;
        case 16: _t->toggleShowWalls(); break;
        case 17: _t->toggleShowApoplasts(); break;
        case 18: _t->toggleDynCells(); break;
        case 19: _t->toggleMovieFrames(); break;
        case 20: _t->toggleLeafBoundary(); break;
        case 21: _t->toggleHideCells(); break;
        case 22: _t->print(); break;
        case 23: _t->startSimulation(); break;
        case 24: _t->stopSimulation(); break;
        case 25: _t->RefreshInfoBar(); break;
        case 26: { int _r = _t->readStateXML((*reinterpret_cast< const char*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 27: { int _r = _t->readStateXML((*reinterpret_cast< const char*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 28: { int _r = _t->readStateXML((*reinterpret_cast< const char*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 29: { int _r = _t->readStateXML((*reinterpret_cast< const char*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 30: _t->EnterRotationMode(); break;
        case 31: _t->ExitRotationMode(); break;
        case 32: _t->UserMessage((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 33: _t->UserMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 34: _t->Refresh(); break;
        case 35: _t->PauseIfRunning(); break;
        case 36: _t->ContIfRunning(); break;
        case 37: _t->XMLReadSettings((*reinterpret_cast< xmlNode*(*)>(_a[1]))); break;
        case 38: _t->aboutQt(); break;
        case 39: _t->newView(); break;
        case 40: _t->EditParameters(); break;
        case 41: { QDir _r = _t->GetLeafDir();
            if (_a[0]) *reinterpret_cast< QDir*>(_a[0]) = _r; }  break;
        case 42: _t->readStateXML(); break;
        case 43: _t->readNextStateXML(); break;
        case 44: _t->readPrevStateXML(); break;
        case 45: _t->readFirstStateXML(); break;
        case 46: _t->readLastStateXML(); break;
        case 47: _t->exportCellData(); break;
        case 48: _t->exportCellData((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 49: _t->exportCellDatanodes((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 50: _t->exportCellDatanodes(); break;
        case 51: _t->saveStateXML(); break;
        case 52: _t->snapshot(); break;
        case 53: _t->savePars(); break;
        case 54: _t->readPars(); break;
        case 55: _t->clear(); break;
        case 56: _t->init(); break;
        case 57: _t->CutSAM(); break;
        case 58: _t->enlarge(); break;
        case 59: _t->shrink(); break;
        case 60: _t->zoomIn(); break;
        case 61: _t->zoomOut(); break;
        case 62: _t->CleanMesh(); break;
        case 63: _t->CleanMeshChemicals(); break;
        case 64: _t->CleanMeshTransporters(); break;
        case 65: _t->RandomizeMesh(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Main::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Main::staticMetaObject = {
    { &Q3MainWindow::staticMetaObject, qt_meta_stringdata_Main,
      qt_meta_data_Main, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Main::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Main::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Main::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Main))
        return static_cast<void*>(const_cast< Main*>(this));
    if (!strcmp(_clname, "MainBase"))
        return static_cast< MainBase*>(const_cast< Main*>(this));
    return Q3MainWindow::qt_metacast(_clname);
}

int Main::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Q3MainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 66)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 66;
    }
    return _id;
}

// SIGNAL 0
void Main::SimulationDone()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void Main::ParsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
