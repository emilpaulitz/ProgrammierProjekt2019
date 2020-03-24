/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../UglyVCF/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[22];
    char stringdata0[475];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 27), // "on_actionVCF_file_triggered"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 31), // "on_actionset_pipeline_triggered"
QT_MOC_LITERAL(4, 72, 29), // "on_actionFastQ_file_triggered"
QT_MOC_LITERAL(5, 102, 22), // "handlePipelineFinished"
QT_MOC_LITERAL(6, 125, 20), // "QProcess::ExitStatus"
QT_MOC_LITERAL(7, 146, 6), // "status"
QT_MOC_LITERAL(8, 153, 39), // "on_actionset_reference_genome..."
QT_MOC_LITERAL(9, 193, 36), // "on_actionSpace_for_Testing_tr..."
QT_MOC_LITERAL(10, 230, 39), // "on_actionpull_all_annotations..."
QT_MOC_LITERAL(11, 270, 26), // "on_tableWidget_cellClicked"
QT_MOC_LITERAL(12, 297, 3), // "row"
QT_MOC_LITERAL(13, 301, 35), // "on_actionhide_annotations_tri..."
QT_MOC_LITERAL(14, 337, 38), // "on_actionFilter_by_Frequency_..."
QT_MOC_LITERAL(15, 376, 17), // "pop_no_connection"
QT_MOC_LITERAL(16, 394, 16), // "updateAnnoWidget"
QT_MOC_LITERAL(17, 411, 10), // "rowUpdated"
QT_MOC_LITERAL(18, 422, 16), // "showAnnoProgress"
QT_MOC_LITERAL(19, 439, 18), // "updateAnnoProgress"
QT_MOC_LITERAL(20, 458, 10), // "update_row"
QT_MOC_LITERAL(21, 469, 5) // "index"

    },
    "MainWindow\0on_actionVCF_file_triggered\0"
    "\0on_actionset_pipeline_triggered\0"
    "on_actionFastQ_file_triggered\0"
    "handlePipelineFinished\0QProcess::ExitStatus\0"
    "status\0on_actionset_reference_genome_triggered\0"
    "on_actionSpace_for_Testing_triggered\0"
    "on_actionpull_all_annotations_triggered\0"
    "on_tableWidget_cellClicked\0row\0"
    "on_actionhide_annotations_triggered\0"
    "on_actionFilter_by_Frequency_triggered\0"
    "pop_no_connection\0updateAnnoWidget\0"
    "rowUpdated\0showAnnoProgress\0"
    "updateAnnoProgress\0update_row\0index"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   89,    2, 0x08 /* Private */,
       3,    0,   90,    2, 0x08 /* Private */,
       4,    0,   91,    2, 0x08 /* Private */,
       5,    2,   92,    2, 0x08 /* Private */,
       8,    0,   97,    2, 0x08 /* Private */,
       9,    0,   98,    2, 0x08 /* Private */,
      10,    0,   99,    2, 0x08 /* Private */,
      11,    2,  100,    2, 0x08 /* Private */,
      13,    0,  105,    2, 0x08 /* Private */,
      14,    0,  106,    2, 0x08 /* Private */,
      15,    0,  107,    2, 0x08 /* Private */,
      16,    1,  108,    2, 0x08 /* Private */,
      18,    0,  111,    2, 0x08 /* Private */,
      19,    0,  112,    2, 0x08 /* Private */,
      20,    1,  113,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 6,    2,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   12,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   17,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   21,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_actionVCF_file_triggered(); break;
        case 1: _t->on_actionset_pipeline_triggered(); break;
        case 2: _t->on_actionFastQ_file_triggered(); break;
        case 3: _t->handlePipelineFinished((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QProcess::ExitStatus(*)>(_a[2]))); break;
        case 4: _t->on_actionset_reference_genome_triggered(); break;
        case 5: _t->on_actionSpace_for_Testing_triggered(); break;
        case 6: _t->on_actionpull_all_annotations_triggered(); break;
        case 7: _t->on_tableWidget_cellClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: _t->on_actionhide_annotations_triggered(); break;
        case 9: _t->on_actionFilter_by_Frequency_triggered(); break;
        case 10: _t->pop_no_connection(); break;
        case 11: _t->updateAnnoWidget((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->showAnnoProgress(); break;
        case 13: _t->updateAnnoProgress(); break;
        case 14: _t->update_row((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
