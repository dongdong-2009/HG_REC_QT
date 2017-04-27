/****************************************************************************
** Meta object code from reading C++ file 'handgesture.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/handgesture.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'handgesture.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_handGesture[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      23,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x08,
      48,   12,   12,   12, 0x08,
      60,   12,   12,   12, 0x08,
      90,   81,   12,   12, 0x08,
     127,  120,   12,   12, 0x08,
     189,  175,   12,   12, 0x08,
     273,  247,   12,   12, 0x08,
     335,   12,   12,   12, 0x08,
     365,  361,  356,   12, 0x08,
     384,   12,   12,   12, 0x08,
     406,   12,   12,   12, 0x08,
     470,  443,   12,   12, 0x08,
     545,   12,   12,   12, 0x08,
     566,   12,   12,   12, 0x08,
     599,  592,  588,   12, 0x08,
     638,  634,   12,   12, 0x08,
     664,   12,   12,   12, 0x08,
     703,   12,   12,   12, 0x08,
     746,   12,   12,   12, 0x08,
     777,  768,   12,   12, 0x08,
     818,  809,   12,   12, 0x08,
     844,   12,   12,   12, 0x08,
     861,   12,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_handGesture[] = {
    "handGesture\0\0on_pushButton_openCamera_clicked()\0"
    "readFrame()\0handGestureDrawing()\0"
    "original\0sourceImagePreprocessing(Mat)\0"
    "center\0ComputeHandGestureCenterPoint(vector<Point2f>&)\0"
    "center,radius\0"
    "ComputeHandGestureMaxCenterRadius(vector<Point2f>,float&)\0"
    "ptArr,width,height,result\0"
    "RecogniseHandGestureSeq(vector<Point2f>&,float,float,string&)\0"
    "getCurrentFilePath()\0QDir\0num\0"
    "SetFolderPath(int)\0saveImageWithDialog()\0"
    "on_pushButton_captureImage_clicked()\0"
    "contour,hull,convexDefects\0"
    "findConvexityDefects(vector<Point>&,vector<int>&,vector<ConvexityDefec"
    "t>&)\0"
    "init_hand_template()\0hand_template_match()\0"
    "int\0iArray\0filterRecogniseResult(vector<int>)\0"
    "src\0binary_image_process(Mat)\0"
    "on_pushButton_startRecognize_clicked()\0"
    "on_pushButton_DirectionRecognize_clicked()\0"
    "handRecogniseResult()\0curPoint\0"
    "judgeCurrentDrawingColor(Point)\0"
    "minPoint\0saveFingerTopPoint(Point)\0"
    "control_images()\0resetFuntion()\0"
};

void handGesture::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        handGesture *_t = static_cast<handGesture *>(_o);
        switch (_id) {
        case 0: _t->on_pushButton_openCamera_clicked(); break;
        case 1: _t->readFrame(); break;
        case 2: _t->handGestureDrawing(); break;
        case 3: _t->sourceImagePreprocessing((*reinterpret_cast< Mat(*)>(_a[1]))); break;
        case 4: _t->ComputeHandGestureCenterPoint((*reinterpret_cast< vector<Point2f>(*)>(_a[1]))); break;
        case 5: _t->ComputeHandGestureMaxCenterRadius((*reinterpret_cast< vector<Point2f>(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 6: _t->RecogniseHandGestureSeq((*reinterpret_cast< vector<Point2f>(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< string(*)>(_a[4]))); break;
        case 7: _t->getCurrentFilePath(); break;
        case 8: { QDir _r = _t->SetFolderPath((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QDir*>(_a[0]) = _r; }  break;
        case 9: _t->saveImageWithDialog(); break;
        case 10: _t->on_pushButton_captureImage_clicked(); break;
        case 11: _t->findConvexityDefects((*reinterpret_cast< vector<Point>(*)>(_a[1])),(*reinterpret_cast< vector<int>(*)>(_a[2])),(*reinterpret_cast< vector<ConvexityDefect>(*)>(_a[3]))); break;
        case 12: _t->init_hand_template(); break;
        case 13: _t->hand_template_match(); break;
        case 14: { int _r = _t->filterRecogniseResult((*reinterpret_cast< vector<int>(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 15: _t->binary_image_process((*reinterpret_cast< Mat(*)>(_a[1]))); break;
        case 16: _t->on_pushButton_startRecognize_clicked(); break;
        case 17: _t->on_pushButton_DirectionRecognize_clicked(); break;
        case 18: _t->handRecogniseResult(); break;
        case 19: _t->judgeCurrentDrawingColor((*reinterpret_cast< Point(*)>(_a[1]))); break;
        case 20: _t->saveFingerTopPoint((*reinterpret_cast< Point(*)>(_a[1]))); break;
        case 21: _t->control_images(); break;
        case 22: _t->resetFuntion(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData handGesture::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject handGesture::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_handGesture,
      qt_meta_data_handGesture, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &handGesture::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *handGesture::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *handGesture::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_handGesture))
        return static_cast<void*>(const_cast< handGesture*>(this));
    return QWidget::qt_metacast(_clname);
}

int handGesture::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 23)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
