/****************************************************************************
** Meta object code from reading C++ file 'home_screen.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../Desktop/include/home_screen.h"
#include <QtNetwork/QSslError>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'home_screen.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN11home_screenE_t {};
} // unnamed namespace

template <> constexpr inline auto home_screen::qt_create_metaobjectdata<qt_meta_tag_ZN11home_screenE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "home_screen",
        "profile_requested",
        "",
        "username",
        "tb_modules_down",
        "tb_savings_down",
        "tb_loans_down",
        "on_pb_next_month_clicked",
        "on_pb_mod_loans_clicked",
        "on_pb_mod_savings_clicked",
        "show_game_result",
        "GameStatus",
        "status",
        "show_financial_profile",
        "balance",
        "monthly_minimum",
        "total_loans",
        "interest_due",
        "salary",
        "current_month",
        "update_financial_chart",
        "debt",
        "savings",
        "loan_information",
        "min_loan_amount",
        "max_loan_amount",
        "interest_rate",
        "update_financial_profile",
        "on_pb_make_loan_clicked",
        "on_pb_my_loans_clicked",
        "on_pb_make_deposit_clicked",
        "WIN",
        "LOSE"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'profile_requested'
        QtMocHelpers::SignalData<void(const QString &)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 3 },
        }}),
        // Slot 'tb_modules_down'
        QtMocHelpers::SlotData<void()>(4, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'tb_savings_down'
        QtMocHelpers::SlotData<void()>(5, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'tb_loans_down'
        QtMocHelpers::SlotData<void()>(6, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_pb_next_month_clicked'
        QtMocHelpers::SlotData<void()>(7, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_pb_mod_loans_clicked'
        QtMocHelpers::SlotData<void()>(8, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_pb_mod_savings_clicked'
        QtMocHelpers::SlotData<void()>(9, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'show_game_result'
        QtMocHelpers::SlotData<void(GameStatus)>(10, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 11, 12 },
        }}),
        // Slot 'show_financial_profile'
        QtMocHelpers::SlotData<void(int, int, int, int, int, int, const QString &)>(13, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 14 }, { QMetaType::Int, 15 }, { QMetaType::Int, 16 }, { QMetaType::Int, 17 },
            { QMetaType::Int, 18 }, { QMetaType::Int, 19 }, { QMetaType::QString, 12 },
        }}),
        // Slot 'update_financial_chart'
        QtMocHelpers::SlotData<void(int, int, int)>(20, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 14 }, { QMetaType::Int, 21 }, { QMetaType::Int, 22 },
        }}),
        // Slot 'loan_information'
        QtMocHelpers::SlotData<void(int, int, int)>(23, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 24 }, { QMetaType::Int, 25 }, { QMetaType::Int, 26 },
        }}),
        // Slot 'update_financial_profile'
        QtMocHelpers::SlotData<void()>(27, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_pb_make_loan_clicked'
        QtMocHelpers::SlotData<void()>(28, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_pb_my_loans_clicked'
        QtMocHelpers::SlotData<void()>(29, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_pb_make_deposit_clicked'
        QtMocHelpers::SlotData<void()>(30, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
        // enum 'GameStatus'
        QtMocHelpers::EnumData<GameStatus>(11, 11, QMC::EnumFlags{}).add({
            {   31, GameStatus::WIN },
            {   32, GameStatus::LOSE },
        }),
    };
    return QtMocHelpers::metaObjectData<home_screen, qt_meta_tag_ZN11home_screenE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject home_screen::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11home_screenE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11home_screenE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN11home_screenE_t>.metaTypes,
    nullptr
} };

void home_screen::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<home_screen *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->profile_requested((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->tb_modules_down(); break;
        case 2: _t->tb_savings_down(); break;
        case 3: _t->tb_loans_down(); break;
        case 4: _t->on_pb_next_month_clicked(); break;
        case 5: _t->on_pb_mod_loans_clicked(); break;
        case 6: _t->on_pb_mod_savings_clicked(); break;
        case 7: _t->show_game_result((*reinterpret_cast< std::add_pointer_t<GameStatus>>(_a[1]))); break;
        case 8: _t->show_financial_profile((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[5])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[6])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[7]))); break;
        case 9: _t->update_financial_chart((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
        case 10: _t->loan_information((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
        case 11: _t->update_financial_profile(); break;
        case 12: _t->on_pb_make_loan_clicked(); break;
        case 13: _t->on_pb_my_loans_clicked(); break;
        case 14: _t->on_pb_make_deposit_clicked(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (home_screen::*)(const QString & )>(_a, &home_screen::profile_requested, 0))
            return;
    }
}

const QMetaObject *home_screen::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *home_screen::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11home_screenE_t>.strings))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int home_screen::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void home_screen::profile_requested(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}
QT_WARNING_POP
