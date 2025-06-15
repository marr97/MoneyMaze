/********************************************************************************
** Form generated from reading UI file 'loan_info.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOAN_INFO_H
#define UI_LOAN_INFO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_loan_info
{
public:
    QWidget *verticalLayoutWidget_5;
    QVBoxLayout *verticalLayout_8;
    QLabel *ql_loans;
    QWidget *widget_amount;
    QWidget *verticalLayoutWidget_4;
    QVBoxLayout *verticalLayout_6;
    QLabel *ql_amount;
    QLabel *amount_value;
    QWidget *widget_payment;
    QWidget *verticalLayoutWidget_6;
    QVBoxLayout *verticalLayout_9;
    QLabel *ql_next_payment;
    QLabel *next_payment_value;
    QWidget *horizontalLayoutWidget_5;
    QHBoxLayout *horizontalLayout_8;
    QLabel *rate;
    QWidget *horizontalLayoutWidget_7;
    QHBoxLayout *horizontalLayout_16;
    QLabel *rate_value;
    QWidget *horizontalLayoutWidget_8;
    QHBoxLayout *horizontalLayout_17;
    QLabel *period_value;
    QWidget *horizontalLayoutWidget_6;
    QHBoxLayout *horizontalLayout_15;
    QLabel *period;
    QWidget *horizontalLayoutWidget_9;
    QHBoxLayout *horizontalLayout_18;
    QLabel *payed_months_value;
    QWidget *horizontalLayoutWidget_10;
    QHBoxLayout *horizontalLayout_19;
    QLabel *payed_months;
    QToolButton *tb_prev;
    QLabel *ql_loan_id;
    QToolButton *tb_next;

    void setupUi(QWidget *loan_info)
    {
        if (loan_info->objectName().isEmpty())
            loan_info->setObjectName("loan_info");
        loan_info->resize(424, 340);
        verticalLayoutWidget_5 = new QWidget(loan_info);
        verticalLayoutWidget_5->setObjectName("verticalLayoutWidget_5");
        verticalLayoutWidget_5->setGeometry(QRect(20, 10, 381, 31));
        verticalLayout_8 = new QVBoxLayout(verticalLayoutWidget_5);
        verticalLayout_8->setObjectName("verticalLayout_8");
        verticalLayout_8->setContentsMargins(0, 0, 0, 0);
        ql_loans = new QLabel(verticalLayoutWidget_5);
        ql_loans->setObjectName("ql_loans");
        QPalette palette;
        QBrush brush(QColor(79, 192, 83, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::WindowText, brush);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Text, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::WindowText, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Text, brush);
        ql_loans->setPalette(palette);
        QFont font;
        font.setFamilies({QString::fromUtf8("Gill Sans")});
        font.setPointSize(22);
        ql_loans->setFont(font);

        verticalLayout_8->addWidget(ql_loans);

        widget_amount = new QWidget(loan_info);
        widget_amount->setObjectName("widget_amount");
        widget_amount->setGeometry(QRect(20, 60, 171, 71));
        verticalLayoutWidget_4 = new QWidget(widget_amount);
        verticalLayoutWidget_4->setObjectName("verticalLayoutWidget_4");
        verticalLayoutWidget_4->setGeometry(QRect(0, 0, 171, 71));
        verticalLayout_6 = new QVBoxLayout(verticalLayoutWidget_4);
        verticalLayout_6->setObjectName("verticalLayout_6");
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        ql_amount = new QLabel(verticalLayoutWidget_4);
        ql_amount->setObjectName("ql_amount");
        ql_amount->setMinimumSize(QSize(0, 0));
        ql_amount->setSizeIncrement(QSize(0, 0));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Gill Sans")});
        font1.setPointSize(16);
        ql_amount->setFont(font1);
        ql_amount->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_6->addWidget(ql_amount);

        amount_value = new QLabel(verticalLayoutWidget_4);
        amount_value->setObjectName("amount_value");
        amount_value->setFont(font1);
        amount_value->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_6->addWidget(amount_value);

        widget_payment = new QWidget(loan_info);
        widget_payment->setObjectName("widget_payment");
        widget_payment->setGeometry(QRect(230, 60, 171, 71));
        verticalLayoutWidget_6 = new QWidget(widget_payment);
        verticalLayoutWidget_6->setObjectName("verticalLayoutWidget_6");
        verticalLayoutWidget_6->setGeometry(QRect(0, 0, 171, 71));
        verticalLayout_9 = new QVBoxLayout(verticalLayoutWidget_6);
        verticalLayout_9->setObjectName("verticalLayout_9");
        verticalLayout_9->setContentsMargins(0, 0, 0, 0);
        ql_next_payment = new QLabel(verticalLayoutWidget_6);
        ql_next_payment->setObjectName("ql_next_payment");
        ql_next_payment->setFont(font1);
        ql_next_payment->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_9->addWidget(ql_next_payment);

        next_payment_value = new QLabel(verticalLayoutWidget_6);
        next_payment_value->setObjectName("next_payment_value");
        next_payment_value->setFont(font1);
        next_payment_value->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_9->addWidget(next_payment_value);

        horizontalLayoutWidget_5 = new QWidget(loan_info);
        horizontalLayoutWidget_5->setObjectName("horizontalLayoutWidget_5");
        horizontalLayoutWidget_5->setGeometry(QRect(20, 150, 172, 42));
        horizontalLayout_8 = new QHBoxLayout(horizontalLayoutWidget_5);
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        rate = new QLabel(horizontalLayoutWidget_5);
        rate->setObjectName("rate");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(rate->sizePolicy().hasHeightForWidth());
        rate->setSizePolicy(sizePolicy);
        rate->setMinimumSize(QSize(170, 30));
        rate->setMaximumSize(QSize(200, 16777215));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Gill Sans")});
        font2.setPointSize(14);
        rate->setFont(font2);

        horizontalLayout_8->addWidget(rate, 0, Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignVCenter);

        horizontalLayoutWidget_7 = new QWidget(loan_info);
        horizontalLayoutWidget_7->setObjectName("horizontalLayoutWidget_7");
        horizontalLayoutWidget_7->setGeometry(QRect(270, 150, 92, 42));
        horizontalLayout_16 = new QHBoxLayout(horizontalLayoutWidget_7);
        horizontalLayout_16->setObjectName("horizontalLayout_16");
        horizontalLayout_16->setContentsMargins(0, 0, 0, 0);
        rate_value = new QLabel(horizontalLayoutWidget_7);
        rate_value->setObjectName("rate_value");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(rate_value->sizePolicy().hasHeightForWidth());
        rate_value->setSizePolicy(sizePolicy1);
        rate_value->setMinimumSize(QSize(90, 30));
        rate_value->setFont(font2);
        rate_value->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_16->addWidget(rate_value, 0, Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignVCenter);

        horizontalLayoutWidget_8 = new QWidget(loan_info);
        horizontalLayoutWidget_8->setObjectName("horizontalLayoutWidget_8");
        horizontalLayoutWidget_8->setGeometry(QRect(270, 200, 92, 42));
        horizontalLayout_17 = new QHBoxLayout(horizontalLayoutWidget_8);
        horizontalLayout_17->setObjectName("horizontalLayout_17");
        horizontalLayout_17->setContentsMargins(0, 0, 0, 0);
        period_value = new QLabel(horizontalLayoutWidget_8);
        period_value->setObjectName("period_value");
        sizePolicy1.setHeightForWidth(period_value->sizePolicy().hasHeightForWidth());
        period_value->setSizePolicy(sizePolicy1);
        period_value->setMinimumSize(QSize(90, 30));
        period_value->setFont(font2);
        period_value->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_17->addWidget(period_value, 0, Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignVCenter);

        horizontalLayoutWidget_6 = new QWidget(loan_info);
        horizontalLayoutWidget_6->setObjectName("horizontalLayoutWidget_6");
        horizontalLayoutWidget_6->setGeometry(QRect(20, 200, 172, 42));
        horizontalLayout_15 = new QHBoxLayout(horizontalLayoutWidget_6);
        horizontalLayout_15->setObjectName("horizontalLayout_15");
        horizontalLayout_15->setContentsMargins(0, 0, 0, 0);
        period = new QLabel(horizontalLayoutWidget_6);
        period->setObjectName("period");
        sizePolicy.setHeightForWidth(period->sizePolicy().hasHeightForWidth());
        period->setSizePolicy(sizePolicy);
        period->setMinimumSize(QSize(170, 30));
        period->setMaximumSize(QSize(200, 16777215));
        period->setFont(font2);

        horizontalLayout_15->addWidget(period, 0, Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignVCenter);

        horizontalLayoutWidget_9 = new QWidget(loan_info);
        horizontalLayoutWidget_9->setObjectName("horizontalLayoutWidget_9");
        horizontalLayoutWidget_9->setGeometry(QRect(270, 250, 92, 42));
        horizontalLayout_18 = new QHBoxLayout(horizontalLayoutWidget_9);
        horizontalLayout_18->setObjectName("horizontalLayout_18");
        horizontalLayout_18->setContentsMargins(0, 0, 0, 0);
        payed_months_value = new QLabel(horizontalLayoutWidget_9);
        payed_months_value->setObjectName("payed_months_value");
        sizePolicy1.setHeightForWidth(payed_months_value->sizePolicy().hasHeightForWidth());
        payed_months_value->setSizePolicy(sizePolicy1);
        payed_months_value->setMinimumSize(QSize(90, 30));
        payed_months_value->setFont(font2);
        payed_months_value->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_18->addWidget(payed_months_value, 0, Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignVCenter);

        horizontalLayoutWidget_10 = new QWidget(loan_info);
        horizontalLayoutWidget_10->setObjectName("horizontalLayoutWidget_10");
        horizontalLayoutWidget_10->setGeometry(QRect(20, 250, 172, 42));
        horizontalLayout_19 = new QHBoxLayout(horizontalLayoutWidget_10);
        horizontalLayout_19->setObjectName("horizontalLayout_19");
        horizontalLayout_19->setContentsMargins(0, 0, 0, 0);
        payed_months = new QLabel(horizontalLayoutWidget_10);
        payed_months->setObjectName("payed_months");
        sizePolicy.setHeightForWidth(payed_months->sizePolicy().hasHeightForWidth());
        payed_months->setSizePolicy(sizePolicy);
        payed_months->setMinimumSize(QSize(170, 30));
        payed_months->setMaximumSize(QSize(200, 16777215));
        payed_months->setFont(font2);

        horizontalLayout_19->addWidget(payed_months, 0, Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignVCenter);

        tb_prev = new QToolButton(loan_info);
        tb_prev->setObjectName("tb_prev");
        tb_prev->setGeometry(QRect(20, 310, 25, 25));
        ql_loan_id = new QLabel(loan_info);
        ql_loan_id->setObjectName("ql_loan_id");
        ql_loan_id->setGeometry(QRect(160, 310, 111, 20));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Gill Sans")});
        font3.setPointSize(13);
        ql_loan_id->setFont(font3);
        ql_loan_id->setAlignment(Qt::AlignmentFlag::AlignCenter);
        tb_next = new QToolButton(loan_info);
        tb_next->setObjectName("tb_next");
        tb_next->setGeometry(QRect(370, 310, 25, 25));

        retranslateUi(loan_info);

        QMetaObject::connectSlotsByName(loan_info);
    } // setupUi

    void retranslateUi(QWidget *loan_info)
    {
        loan_info->setWindowTitle(QCoreApplication::translate("loan_info", "Form", nullptr));
        ql_loans->setText(QCoreApplication::translate("loan_info", "\320\222\320\260\321\210\320\270 \320\272\321\200\320\265\320\264\320\270\321\202\321\213", nullptr));
        ql_amount->setText(QCoreApplication::translate("loan_info", "\320\241\321\203\320\274\320\274\320\260 \320\264\320\276\320\273\320\263\320\260", nullptr));
        amount_value->setText(QCoreApplication::translate("loan_info", "0", nullptr));
        ql_next_payment->setText(QCoreApplication::translate("loan_info", "\320\241\320\273\320\265\320\264\321\203\321\216\321\211\320\270\320\271 \320\277\320\273\320\260\321\202\320\265\320\266", nullptr));
        next_payment_value->setText(QCoreApplication::translate("loan_info", "0", nullptr));
        rate->setText(QCoreApplication::translate("loan_info", " \320\237\321\200\320\276\321\206\320\265\320\275\321\202\320\275\320\260\321\217 \321\201\321\202\320\260\320\262\320\272\320\260", nullptr));
        rate_value->setText(QCoreApplication::translate("loan_info", "0", nullptr));
        period_value->setText(QCoreApplication::translate("loan_info", "0", nullptr));
        period->setText(QCoreApplication::translate("loan_info", " \320\237\320\265\321\200\320\270\320\276\320\264", nullptr));
        payed_months_value->setText(QCoreApplication::translate("loan_info", "0", nullptr));
        payed_months->setText(QCoreApplication::translate("loan_info", " \320\222\321\213\320\277\320\273\320\260\321\207\320\265\320\275\320\275\321\213\320\265 \320\274\320\265\321\201\321\217\321\206\321\213", nullptr));
        tb_prev->setText(QString());
        ql_loan_id->setText(QCoreApplication::translate("loan_info", "\320\235\320\276\320\274\320\265\321\200 \320\272\321\200\320\265\320\264\320\270\321\202\320\260: 1 ", nullptr));
        tb_next->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class loan_info: public Ui_loan_info {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOAN_INFO_H
