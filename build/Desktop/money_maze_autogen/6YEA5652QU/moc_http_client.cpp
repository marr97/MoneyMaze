/****************************************************************************
** Meta object code from reading C++ file 'http_client.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../Desktop/include/http_client.h"
#include <QtNetwork/QSslError>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'http_client.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN10httpClientE_t {};
} // unnamed namespace

template <> constexpr inline auto httpClient::qt_create_metaobjectdata<qt_meta_tag_ZN10httpClientE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "httpClient",
        "registration_finished",
        "",
        "status_code",
        "error_msg",
        "authorization_finished",
        "error_occurred",
        "error",
        "financial_profile_received",
        "balance",
        "monthly_minimum",
        "total_loans",
        "interest_due",
        "salary",
        "current_month",
        "status",
        "loan_info_received",
        "min_loan_amount",
        "max_loan_amount",
        "interest_rate",
        "loans_received",
        "QList<QJsonObject>",
        "loans_list",
        "loan_taken",
        "Status",
        "OK",
        "ERROR",
        "NETWORK_ERROR"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'registration_finished'
        QtMocHelpers::SignalData<void(int, const QString &)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 3 }, { QMetaType::QString, 4 },
        }}),
        // Signal 'authorization_finished'
        QtMocHelpers::SignalData<void(int, const QString &)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 3 }, { QMetaType::QString, 4 },
        }}),
        // Signal 'error_occurred'
        QtMocHelpers::SignalData<void(const QString &)>(6, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 7 },
        }}),
        // Signal 'financial_profile_received'
        QtMocHelpers::SignalData<void(int, int, int, int, int, int, const QString &)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 9 }, { QMetaType::Int, 10 }, { QMetaType::Int, 11 }, { QMetaType::Int, 12 },
            { QMetaType::Int, 13 }, { QMetaType::Int, 14 }, { QMetaType::QString, 15 },
        }}),
        // Signal 'loan_info_received'
        QtMocHelpers::SignalData<void(int, int, int)>(16, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 17 }, { QMetaType::Int, 18 }, { QMetaType::Int, 19 },
        }}),
        // Signal 'loans_received'
        QtMocHelpers::SignalData<void(const QVector<QJsonObject> &)>(20, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 21, 22 },
        }}),
        // Signal 'loan_taken'
        QtMocHelpers::SignalData<void()>(23, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
        // enum 'Status'
        QtMocHelpers::EnumData<Status>(24, 24, QMC::EnumFlags{}).add({
            {   25, Status::OK },
            {   26, Status::ERROR },
            {   27, Status::NETWORK_ERROR },
        }),
    };
    return QtMocHelpers::metaObjectData<httpClient, qt_meta_tag_ZN10httpClientE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject httpClient::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10httpClientE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10httpClientE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN10httpClientE_t>.metaTypes,
    nullptr
} };

void httpClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<httpClient *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->registration_finished((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 1: _t->authorization_finished((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 2: _t->error_occurred((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->financial_profile_received((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[5])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[6])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[7]))); break;
        case 4: _t->loan_info_received((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
        case 5: _t->loans_received((*reinterpret_cast< std::add_pointer_t<QList<QJsonObject>>>(_a[1]))); break;
        case 6: _t->loan_taken(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QList<QJsonObject> >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (httpClient::*)(int , const QString & )>(_a, &httpClient::registration_finished, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (httpClient::*)(int , const QString & )>(_a, &httpClient::authorization_finished, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (httpClient::*)(const QString & )>(_a, &httpClient::error_occurred, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (httpClient::*)(int , int , int , int , int , int , const QString & )>(_a, &httpClient::financial_profile_received, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (httpClient::*)(int , int , int )>(_a, &httpClient::loan_info_received, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (httpClient::*)(const QVector<QJsonObject> & )>(_a, &httpClient::loans_received, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (httpClient::*)()>(_a, &httpClient::loan_taken, 6))
            return;
    }
}

const QMetaObject *httpClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *httpClient::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10httpClientE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int httpClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void httpClient::registration_finished(int _t1, const QString & _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1, _t2);
}

// SIGNAL 1
void httpClient::authorization_finished(int _t1, const QString & _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1, _t2);
}

// SIGNAL 2
void httpClient::error_occurred(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}

// SIGNAL 3
void httpClient::financial_profile_received(int _t1, int _t2, int _t3, int _t4, int _t5, int _t6, const QString & _t7)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1, _t2, _t3, _t4, _t5, _t6, _t7);
}

// SIGNAL 4
void httpClient::loan_info_received(int _t1, int _t2, int _t3)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1, _t2, _t3);
}

// SIGNAL 5
void httpClient::loans_received(const QVector<QJsonObject> & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 5, nullptr, _t1);
}

// SIGNAL 6
void httpClient::loan_taken()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}
QT_WARNING_POP
