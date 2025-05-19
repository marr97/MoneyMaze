/********************************************************************************
** Form generated from reading UI file 'home_screen.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOME_SCREEN_H
#define UI_HOME_SCREEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_home_screen
{
public:
    QWidget *centralwidget;
    QWidget *horizontalLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *ql_daily_min;
    QLabel *ql_balance;
    QLabel *ql_debt;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *ql_username;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout_3;
    QWidget *widget_savings;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *pb_make_deposit;
    QLabel *ql_savings;
    QToolButton *tb_savings;
    QSpacerItem *verticalSpacer_4;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_4;
    QLabel *ql_loans;
    QWidget *widget_loans;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pb_make_loan;
    QToolButton *tb_loans;
    QSpacerItem *verticalSpacer_5;
    QWidget *gridLayoutWidget_3;
    QGridLayout *gridLayout_5;
    QLabel *ql_modules;
    QWidget *widget_modules;
    QWidget *gridLayoutWidget_4;
    QGridLayout *gridLayout_2;
    QPushButton *pb_mod_savings;
    QPushButton *pb_mod_loans;
    QToolButton *tb_modules;
    QSpacerItem *verticalSpacer_3;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *home_screen)
    {
        if (home_screen->objectName().isEmpty())
            home_screen->setObjectName("home_screen");
        home_screen->resize(800, 600);
        centralwidget = new QWidget(home_screen);
        centralwidget->setObjectName("centralwidget");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(260, 110, 511, 91));
        gridLayout = new QGridLayout(horizontalLayoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        ql_daily_min = new QLabel(horizontalLayoutWidget);
        ql_daily_min->setObjectName("ql_daily_min");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(ql_daily_min->sizePolicy().hasHeightForWidth());
        ql_daily_min->setSizePolicy(sizePolicy1);
        ql_daily_min->setMinimumSize(QSize(135, 0));
        QFont font;
        font.setFamilies({QString::fromUtf8("Gill Sans")});
        font.setPointSize(14);
        ql_daily_min->setFont(font);
        ql_daily_min->setAlignment(Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignTop);

        gridLayout->addWidget(ql_daily_min, 0, 2, 1, 1);

        ql_balance = new QLabel(horizontalLayoutWidget);
        ql_balance->setObjectName("ql_balance");
        sizePolicy1.setHeightForWidth(ql_balance->sizePolicy().hasHeightForWidth());
        ql_balance->setSizePolicy(sizePolicy1);
        ql_balance->setMinimumSize(QSize(135, 0));
        ql_balance->setFont(font);
        ql_balance->setAlignment(Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignTop);

        gridLayout->addWidget(ql_balance, 0, 0, 1, 1);

        ql_debt = new QLabel(horizontalLayoutWidget);
        ql_debt->setObjectName("ql_debt");
        sizePolicy1.setHeightForWidth(ql_debt->sizePolicy().hasHeightForWidth());
        ql_debt->setSizePolicy(sizePolicy1);
        ql_debt->setMinimumSize(QSize(135, 0));
        ql_debt->setFont(font);
        ql_debt->setAlignment(Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignTop);

        gridLayout->addWidget(ql_debt, 0, 4, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 0, 3, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout->addItem(verticalSpacer, 0, 1, 1, 1);

        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(530, 30, 251, 31));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        ql_username = new QLabel(verticalLayoutWidget);
        ql_username->setObjectName("ql_username");
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Gill Sans")});
        font1.setPointSize(15);
        font1.setKerning(true);
        ql_username->setFont(font1);
        ql_username->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(ql_username);

        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(450, 270, 162, 183));
        gridLayout_3 = new QGridLayout(gridLayoutWidget);
        gridLayout_3->setObjectName("gridLayout_3");
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        widget_savings = new QWidget(gridLayoutWidget);
        widget_savings->setObjectName("widget_savings");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(widget_savings->sizePolicy().hasHeightForWidth());
        widget_savings->setSizePolicy(sizePolicy2);
        widget_savings->setMinimumSize(QSize(130, 120));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Window, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush);
        widget_savings->setPalette(palette);
        widget_savings->setAutoFillBackground(true);
        horizontalLayoutWidget_2 = new QWidget(widget_savings);
        horizontalLayoutWidget_2->setObjectName("horizontalLayoutWidget_2");
        horizontalLayoutWidget_2->setGeometry(QRect(0, 0, 131, 121));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pb_make_deposit = new QPushButton(horizontalLayoutWidget_2);
        pb_make_deposit->setObjectName("pb_make_deposit");
        sizePolicy2.setHeightForWidth(pb_make_deposit->sizePolicy().hasHeightForWidth());
        pb_make_deposit->setSizePolicy(sizePolicy2);
        pb_make_deposit->setMinimumSize(QSize(120, 75));
        QPalette palette1;
        QBrush brush1(QColor(0, 0, 0, 216));
        brush1.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush1);
        pb_make_deposit->setPalette(palette1);
        pb_make_deposit->setFont(font);
        pb_make_deposit->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
        pb_make_deposit->setAutoFillBackground(true);

        horizontalLayout->addWidget(pb_make_deposit);


        gridLayout_3->addWidget(widget_savings, 1, 0, 1, 1);

        ql_savings = new QLabel(gridLayoutWidget);
        ql_savings->setObjectName("ql_savings");
        sizePolicy2.setHeightForWidth(ql_savings->sizePolicy().hasHeightForWidth());
        ql_savings->setSizePolicy(sizePolicy2);
        ql_savings->setMinimumSize(QSize(120, 0));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Gill Sans")});
        font2.setPointSize(18);
        ql_savings->setFont(font2);
        ql_savings->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_3->addWidget(ql_savings, 0, 0, 1, 1);

        tb_savings = new QToolButton(gridLayoutWidget);
        tb_savings->setObjectName("tb_savings");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy3.setHorizontalStretch(3);
        sizePolicy3.setVerticalStretch(3);
        sizePolicy3.setHeightForWidth(tb_savings->sizePolicy().hasHeightForWidth());
        tb_savings->setSizePolicy(sizePolicy3);
        tb_savings->setMinimumSize(QSize(3, 3));

        gridLayout_3->addWidget(tb_savings, 0, 1, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_3->addItem(verticalSpacer_4, 1, 1, 1, 1);

        gridLayoutWidget_2 = new QWidget(centralwidget);
        gridLayoutWidget_2->setObjectName("gridLayoutWidget_2");
        gridLayoutWidget_2->setGeometry(QRect(630, 270, 162, 183));
        gridLayout_4 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_4->setObjectName("gridLayout_4");
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        ql_loans = new QLabel(gridLayoutWidget_2);
        ql_loans->setObjectName("ql_loans");
        sizePolicy2.setHeightForWidth(ql_loans->sizePolicy().hasHeightForWidth());
        ql_loans->setSizePolicy(sizePolicy2);
        ql_loans->setMinimumSize(QSize(120, 0));
        ql_loans->setFont(font2);
        ql_loans->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_4->addWidget(ql_loans, 0, 0, 1, 1);

        widget_loans = new QWidget(gridLayoutWidget_2);
        widget_loans->setObjectName("widget_loans");
        sizePolicy2.setHeightForWidth(widget_loans->sizePolicy().hasHeightForWidth());
        widget_loans->setSizePolicy(sizePolicy2);
        widget_loans->setMinimumSize(QSize(130, 120));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::Window, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::Window, brush);
        widget_loans->setPalette(palette2);
        widget_loans->setAutoFillBackground(true);
        horizontalLayoutWidget_3 = new QWidget(widget_loans);
        horizontalLayoutWidget_3->setObjectName("horizontalLayoutWidget_3");
        horizontalLayoutWidget_3->setGeometry(QRect(0, 0, 131, 121));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        pb_make_loan = new QPushButton(horizontalLayoutWidget_3);
        pb_make_loan->setObjectName("pb_make_loan");
        sizePolicy2.setHeightForWidth(pb_make_loan->sizePolicy().hasHeightForWidth());
        pb_make_loan->setSizePolicy(sizePolicy2);
        pb_make_loan->setMinimumSize(QSize(120, 75));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::ButtonText, brush1);
        palette3.setBrush(QPalette::Inactive, QPalette::ButtonText, brush1);
        pb_make_loan->setPalette(palette3);
        pb_make_loan->setFont(font);
        pb_make_loan->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
        pb_make_loan->setAutoFillBackground(true);

        horizontalLayout_2->addWidget(pb_make_loan);


        gridLayout_4->addWidget(widget_loans, 1, 0, 1, 1);

        tb_loans = new QToolButton(gridLayoutWidget_2);
        tb_loans->setObjectName("tb_loans");
        sizePolicy3.setHeightForWidth(tb_loans->sizePolicy().hasHeightForWidth());
        tb_loans->setSizePolicy(sizePolicy3);
        tb_loans->setMinimumSize(QSize(3, 3));

        gridLayout_4->addWidget(tb_loans, 0, 1, 1, 1);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_4->addItem(verticalSpacer_5, 1, 1, 1, 1);

        gridLayoutWidget_3 = new QWidget(centralwidget);
        gridLayoutWidget_3->setObjectName("gridLayoutWidget_3");
        gridLayoutWidget_3->setGeometry(QRect(270, 270, 162, 183));
        gridLayout_5 = new QGridLayout(gridLayoutWidget_3);
        gridLayout_5->setObjectName("gridLayout_5");
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        ql_modules = new QLabel(gridLayoutWidget_3);
        ql_modules->setObjectName("ql_modules");
        sizePolicy2.setHeightForWidth(ql_modules->sizePolicy().hasHeightForWidth());
        ql_modules->setSizePolicy(sizePolicy2);
        ql_modules->setMinimumSize(QSize(120, 0));
        ql_modules->setFont(font2);
        ql_modules->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_5->addWidget(ql_modules, 0, 0, 1, 1);

        widget_modules = new QWidget(gridLayoutWidget_3);
        widget_modules->setObjectName("widget_modules");
        sizePolicy2.setHeightForWidth(widget_modules->sizePolicy().hasHeightForWidth());
        widget_modules->setSizePolicy(sizePolicy2);
        widget_modules->setMinimumSize(QSize(130, 120));
        QPalette palette4;
        QBrush brush2(QColor(237, 237, 237, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette4.setBrush(QPalette::Active, QPalette::Window, brush2);
        palette4.setBrush(QPalette::Inactive, QPalette::Window, brush2);
        palette4.setBrush(QPalette::Disabled, QPalette::Base, brush2);
        palette4.setBrush(QPalette::Disabled, QPalette::Window, brush2);
        widget_modules->setPalette(palette4);
        widget_modules->setAutoFillBackground(true);
        gridLayoutWidget_4 = new QWidget(widget_modules);
        gridLayoutWidget_4->setObjectName("gridLayoutWidget_4");
        gridLayoutWidget_4->setGeometry(QRect(0, 0, 131, 121));
        gridLayout_2 = new QGridLayout(gridLayoutWidget_4);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        pb_mod_savings = new QPushButton(gridLayoutWidget_4);
        pb_mod_savings->setObjectName("pb_mod_savings");
        sizePolicy2.setHeightForWidth(pb_mod_savings->sizePolicy().hasHeightForWidth());
        pb_mod_savings->setSizePolicy(sizePolicy2);
        pb_mod_savings->setMinimumSize(QSize(120, 40));
        QPalette palette5;
        QBrush brush3(QColor(46, 47, 48, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette5.setBrush(QPalette::Active, QPalette::WindowText, brush3);
        palette5.setBrush(QPalette::Active, QPalette::Text, brush1);
        palette5.setBrush(QPalette::Active, QPalette::ButtonText, brush1);
        palette5.setBrush(QPalette::Inactive, QPalette::WindowText, brush3);
        palette5.setBrush(QPalette::Inactive, QPalette::Text, brush1);
        palette5.setBrush(QPalette::Inactive, QPalette::ButtonText, brush1);
        pb_mod_savings->setPalette(palette5);
        pb_mod_savings->setFont(font);
        pb_mod_savings->setAutoFillBackground(true);

        gridLayout_2->addWidget(pb_mod_savings, 0, 0, 1, 1);

        pb_mod_loans = new QPushButton(gridLayoutWidget_4);
        pb_mod_loans->setObjectName("pb_mod_loans");
        sizePolicy2.setHeightForWidth(pb_mod_loans->sizePolicy().hasHeightForWidth());
        pb_mod_loans->setSizePolicy(sizePolicy2);
        pb_mod_loans->setMinimumSize(QSize(120, 40));
        QPalette palette6;
        palette6.setBrush(QPalette::Active, QPalette::ButtonText, brush1);
        palette6.setBrush(QPalette::Inactive, QPalette::ButtonText, brush1);
        pb_mod_loans->setPalette(palette6);
        pb_mod_loans->setFont(font);
        pb_mod_loans->setAutoFillBackground(true);

        gridLayout_2->addWidget(pb_mod_loans, 1, 0, 1, 1);


        gridLayout_5->addWidget(widget_modules, 1, 0, 1, 1);

        tb_modules = new QToolButton(gridLayoutWidget_3);
        tb_modules->setObjectName("tb_modules");
        sizePolicy3.setHeightForWidth(tb_modules->sizePolicy().hasHeightForWidth());
        tb_modules->setSizePolicy(sizePolicy3);
        tb_modules->setMinimumSize(QSize(3, 3));

        gridLayout_5->addWidget(tb_modules, 0, 1, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_5->addItem(verticalSpacer_3, 1, 1, 1, 1);

        home_screen->setCentralWidget(centralwidget);
        menubar = new QMenuBar(home_screen);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 36));
        home_screen->setMenuBar(menubar);
        statusbar = new QStatusBar(home_screen);
        statusbar->setObjectName("statusbar");
        home_screen->setStatusBar(statusbar);

        retranslateUi(home_screen);

        QMetaObject::connectSlotsByName(home_screen);
    } // setupUi

    void retranslateUi(QMainWindow *home_screen)
    {
        home_screen->setWindowTitle(QCoreApplication::translate("home_screen", "MainWindow", nullptr));
        ql_daily_min->setText(QCoreApplication::translate("home_screen", "\320\225\320\266\320\265\320\264\320\275\320\265\320\262\320\275\321\213\320\271 \320\274\320\270\320\275\320\270\320\274\321\203\320\274", nullptr));
        ql_balance->setText(QCoreApplication::translate("home_screen", "\320\221\320\260\320\273\320\260\320\275\321\201", nullptr));
        ql_debt->setText(QCoreApplication::translate("home_screen", "\320\224\320\276\320\273\320\263", nullptr));
        ql_username->setText(QCoreApplication::translate("home_screen", "\320\230\320\274\321\217 \320\277\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\321\217", nullptr));
        pb_make_deposit->setText(QCoreApplication::translate("home_screen", "\320\236\321\204\320\276\321\200\320\274\320\270\321\202\321\214", nullptr));
        ql_savings->setText(QCoreApplication::translate("home_screen", "\320\222\320\272\320\273\320\260\320\264\321\213", nullptr));
        tb_savings->setText(QString());
        ql_loans->setText(QCoreApplication::translate("home_screen", "\320\232\321\200\320\265\320\264\320\270\321\202\321\213", nullptr));
        pb_make_loan->setText(QCoreApplication::translate("home_screen", "\320\236\321\204\320\276\321\200\320\274\320\270\321\202\321\214", nullptr));
        tb_loans->setText(QString());
        ql_modules->setText(QCoreApplication::translate("home_screen", "\320\234\320\276\320\264\321\203\320\273\320\270", nullptr));
        pb_mod_savings->setText(QCoreApplication::translate("home_screen", "\320\222\320\272\320\273\320\260\320\264\321\213", nullptr));
        pb_mod_loans->setText(QCoreApplication::translate("home_screen", "\320\232\321\200\320\265\320\264\320\270\321\202\321\213", nullptr));
        tb_modules->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class home_screen: public Ui_home_screen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOME_SCREEN_H
