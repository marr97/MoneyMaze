/********************************************************************************
** Form generated from reading UI file 'loan.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOAN_H
#define UI_LOAN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_loan
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *ql_loan_amount_text;
    QLineEdit *loan_amount;
    QWidget *verticalLayoutWidget_5;
    QVBoxLayout *verticalLayout_7;
    QLabel *ql_conditions;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_3;
    QLabel *ql_period;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *verticalSpacer_5;
    QRadioButton *rb_6months;
    QSpacerItem *verticalSpacer_2;
    QRadioButton *rb_9months;
    QSpacerItem *verticalSpacer;
    QRadioButton *rb_12months;
    QSpacerItem *verticalSpacer_6;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *ql_rate;
    QSpacerItem *verticalSpacer_3;
    QLabel *ql_rate_value;
    QPushButton *pb_take;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *ql_payment;
    QSpacerItem *verticalSpacer_4;
    QLabel *ql_payment_value;

    void setupUi(QWidget *loan)
    {
        if (loan->objectName().isEmpty())
            loan->setObjectName("loan");
        loan->resize(421, 350);
        verticalLayoutWidget = new QWidget(loan);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(20, 60, 382, 71));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        ql_loan_amount_text = new QLabel(verticalLayoutWidget);
        ql_loan_amount_text->setObjectName("ql_loan_amount_text");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(120);
        sizePolicy.setVerticalStretch(40);
        sizePolicy.setHeightForWidth(ql_loan_amount_text->sizePolicy().hasHeightForWidth());
        ql_loan_amount_text->setSizePolicy(sizePolicy);
        ql_loan_amount_text->setMinimumSize(QSize(200, 0));
        ql_loan_amount_text->setMaximumSize(QSize(120, 40));
        QFont font;
        font.setFamilies({QString::fromUtf8("Gill Sans")});
        font.setPointSize(16);
        ql_loan_amount_text->setFont(font);
        ql_loan_amount_text->setAlignment(Qt::AlignmentFlag::AlignBottom|Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft);

        verticalLayout->addWidget(ql_loan_amount_text, 0, Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);

        loan_amount = new QLineEdit(verticalLayoutWidget);
        loan_amount->setObjectName("loan_amount");
        loan_amount->setMinimumSize(QSize(0, 40));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Gill Sans")});
        font1.setPointSize(18);
        loan_amount->setFont(font1);

        verticalLayout->addWidget(loan_amount);

        verticalLayoutWidget_5 = new QWidget(loan);
        verticalLayoutWidget_5->setObjectName("verticalLayoutWidget_5");
        verticalLayoutWidget_5->setGeometry(QRect(20, 10, 381, 31));
        verticalLayout_7 = new QVBoxLayout(verticalLayoutWidget_5);
        verticalLayout_7->setObjectName("verticalLayout_7");
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        ql_conditions = new QLabel(verticalLayoutWidget_5);
        ql_conditions->setObjectName("ql_conditions");
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Gill Sans")});
        font2.setPointSize(22);
        ql_conditions->setFont(font2);

        verticalLayout_7->addWidget(ql_conditions);

        verticalLayoutWidget_2 = new QWidget(loan);
        verticalLayoutWidget_2->setObjectName("verticalLayoutWidget_2");
        verticalLayoutWidget_2->setGeometry(QRect(20, 140, 381, 61));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        ql_period = new QLabel(verticalLayoutWidget_2);
        ql_period->setObjectName("ql_period");
        sizePolicy.setHeightForWidth(ql_period->sizePolicy().hasHeightForWidth());
        ql_period->setSizePolicy(sizePolicy);
        ql_period->setMinimumSize(QSize(200, 0));
        ql_period->setMaximumSize(QSize(120, 40));
        ql_period->setFont(font);
        ql_period->setAlignment(Qt::AlignmentFlag::AlignBottom|Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft);

        verticalLayout_3->addWidget(ql_period, 0, Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        horizontalLayout->addItem(verticalSpacer_5);

        rb_6months = new QRadioButton(verticalLayoutWidget_2);
        rb_6months->setObjectName("rb_6months");
        QPalette palette;
        QBrush brush(QColor(97, 197, 84, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Link, brush);
#if QT_VERSION >= QT_VERSION_CHECK(6, 6, 0)
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Accent, brush);
#endif
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Link, brush);
#if QT_VERSION >= QT_VERSION_CHECK(6, 6, 0)
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Accent, brush);
#endif
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Link, brush);
#if QT_VERSION >= QT_VERSION_CHECK(6, 6, 0)
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Accent, brush);
#endif
        rb_6months->setPalette(palette);
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Gill Sans")});
        font3.setPointSize(14);
        rb_6months->setFont(font3);

        horizontalLayout->addWidget(rb_6months);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        horizontalLayout->addItem(verticalSpacer_2);

        rb_9months = new QRadioButton(verticalLayoutWidget_2);
        rb_9months->setObjectName("rb_9months");
        QPalette palette1;
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Link, brush);
#if QT_VERSION >= QT_VERSION_CHECK(6, 6, 0)
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Accent, brush);
#endif
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Link, brush);
#if QT_VERSION >= QT_VERSION_CHECK(6, 6, 0)
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Accent, brush);
#endif
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Link, brush);
#if QT_VERSION >= QT_VERSION_CHECK(6, 6, 0)
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Accent, brush);
#endif
        rb_9months->setPalette(palette1);
        rb_9months->setFont(font3);

        horizontalLayout->addWidget(rb_9months);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        horizontalLayout->addItem(verticalSpacer);

        rb_12months = new QRadioButton(verticalLayoutWidget_2);
        rb_12months->setObjectName("rb_12months");
        QPalette palette2;
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Link, brush);
#if QT_VERSION >= QT_VERSION_CHECK(6, 6, 0)
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Accent, brush);
#endif
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Link, brush);
#if QT_VERSION >= QT_VERSION_CHECK(6, 6, 0)
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Accent, brush);
#endif
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Link, brush);
#if QT_VERSION >= QT_VERSION_CHECK(6, 6, 0)
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Accent, brush);
#endif
        rb_12months->setPalette(palette2);
        rb_12months->setFont(font3);

        horizontalLayout->addWidget(rb_12months);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        horizontalLayout->addItem(verticalSpacer_6);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayoutWidget_2 = new QWidget(loan);
        horizontalLayoutWidget_2->setObjectName("horizontalLayoutWidget_2");
        horizontalLayoutWidget_2->setGeometry(QRect(20, 210, 381, 32));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        ql_rate = new QLabel(horizontalLayoutWidget_2);
        ql_rate->setObjectName("ql_rate");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(ql_rate->sizePolicy().hasHeightForWidth());
        ql_rate->setSizePolicy(sizePolicy1);
        ql_rate->setMinimumSize(QSize(225, 0));
        ql_rate->setMaximumSize(QSize(200, 16777215));
        ql_rate->setFont(font3);

        horizontalLayout_2->addWidget(ql_rate, 0, Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        horizontalLayout_2->addItem(verticalSpacer_3);

        ql_rate_value = new QLabel(horizontalLayoutWidget_2);
        ql_rate_value->setObjectName("ql_rate_value");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(ql_rate_value->sizePolicy().hasHeightForWidth());
        ql_rate_value->setSizePolicy(sizePolicy2);
        ql_rate_value->setMinimumSize(QSize(80, 30));
        ql_rate_value->setFont(font3);
        ql_rate_value->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_2->addWidget(ql_rate_value, 0, Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignVCenter);

        pb_take = new QPushButton(loan);
        pb_take->setObjectName("pb_take");
        pb_take->setGeometry(QRect(60, 300, 301, 40));
        sizePolicy2.setHeightForWidth(pb_take->sizePolicy().hasHeightForWidth());
        pb_take->setSizePolicy(sizePolicy2);
        pb_take->setMinimumSize(QSize(0, 40));
        pb_take->setMaximumSize(QSize(16777215, 40));
        pb_take->setFont(font);
        horizontalLayoutWidget_3 = new QWidget(loan);
        horizontalLayoutWidget_3->setObjectName("horizontalLayoutWidget_3");
        horizontalLayoutWidget_3->setGeometry(QRect(20, 250, 381, 42));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        ql_payment = new QLabel(horizontalLayoutWidget_3);
        ql_payment->setObjectName("ql_payment");
        sizePolicy1.setHeightForWidth(ql_payment->sizePolicy().hasHeightForWidth());
        ql_payment->setSizePolicy(sizePolicy1);
        ql_payment->setMinimumSize(QSize(225, 40));
        ql_payment->setMaximumSize(QSize(200, 16777215));
        ql_payment->setFont(font3);

        horizontalLayout_3->addWidget(ql_payment, 0, Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        horizontalLayout_3->addItem(verticalSpacer_4);

        ql_payment_value = new QLabel(horizontalLayoutWidget_3);
        ql_payment_value->setObjectName("ql_payment_value");
        sizePolicy2.setHeightForWidth(ql_payment_value->sizePolicy().hasHeightForWidth());
        ql_payment_value->setSizePolicy(sizePolicy2);
        ql_payment_value->setMinimumSize(QSize(80, 30));
        ql_payment_value->setFont(font3);
        ql_payment_value->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_3->addWidget(ql_payment_value, 0, Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignVCenter);


        retranslateUi(loan);

        QMetaObject::connectSlotsByName(loan);
    } // setupUi

    void retranslateUi(QWidget *loan)
    {
        loan->setWindowTitle(QCoreApplication::translate("loan", "Form", nullptr));
        ql_loan_amount_text->setText(QCoreApplication::translate("loan", "\320\241\321\203\320\274\320\274\320\260 \320\272\321\200\320\265\320\264\320\270\321\202\320\260", nullptr));
        ql_conditions->setText(QCoreApplication::translate("loan", "\320\222\321\213\320\261\320\265\321\200\320\270\321\202\320\265 \321\203\321\201\320\273\320\276\320\262\320\270\321\217", nullptr));
        ql_period->setText(QCoreApplication::translate("loan", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \320\274\320\265\321\201\321\217\321\206\320\265\320\262", nullptr));
        rb_6months->setText(QCoreApplication::translate("loan", "6 \320\274\320\265\321\201", nullptr));
        rb_9months->setText(QCoreApplication::translate("loan", "9 \320\274\320\265\321\201", nullptr));
        rb_12months->setText(QCoreApplication::translate("loan", "12 \320\274\320\265\321\201", nullptr));
        ql_rate->setText(QCoreApplication::translate("loan", "\320\237\321\200\320\276\321\206\320\265\320\275\321\202\320\275\320\260\321\217 \321\201\321\202\320\260\320\262\320\272\320\260", nullptr));
        ql_rate_value->setText(QCoreApplication::translate("loan", "0", nullptr));
        pb_take->setText(QCoreApplication::translate("loan", "\320\222\320\267\321\217\321\202\321\214 \320\272\321\200\320\265\320\264\320\270\321\202", nullptr));
        ql_payment->setText(QCoreApplication::translate("loan", "\320\241\321\203\320\274\320\274\320\260 \320\277\320\273\320\260\321\202\320\265\320\266\320\260 \320\262 \320\277\320\265\321\200\320\262\321\213\320\271 \320\274\320\265\321\201\321\217\321\206", nullptr));
        ql_payment_value->setText(QCoreApplication::translate("loan", "0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class loan: public Ui_loan {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOAN_H
