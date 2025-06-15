/********************************************************************************
** Form generated from reading UI file 'home_screen.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
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
    QLabel *ql_monthly_min;
    QSpacerItem *verticalSpacer_2;
    QLabel *ql_debt;
    QSpacerItem *verticalSpacer;
    QLabel *ql_balance;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *ql_username;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout_3;
    QToolButton *tb_savings;
    QLabel *ql_savings;
    QSpacerItem *verticalSpacer_4;
    QWidget *widget_savings;
    QWidget *horizontalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pb_make_deposit;
    QPushButton *pb_my_savings;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_4;
    QLabel *ql_loans;
    QToolButton *tb_loans;
    QSpacerItem *verticalSpacer_5;
    QWidget *widget_loans;
    QWidget *horizontalLayoutWidget_5;
    QVBoxLayout *verticalLayout_4;
    QPushButton *pb_make_loan;
    QPushButton *pb_my_loans;
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
    QWidget *horizontalLayoutWidget_4;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pb_next_month;
    QSpacerItem *verticalSpacer_6;
    QLabel *ql_month;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *chart_layout;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_3;
    QLabel *ql_chart_balance;
    QLabel *ql_chart_debt;
    QLabel *ql_chart_savings;
    QWidget *verticalLayoutWidget_4;
    QVBoxLayout *verticalLayout_5;
    QLabel *ql_chart_balance_value;
    QLabel *ql_chart_debt_value;
    QLabel *ql_chart_savings_value;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *home_screen)
    {
        if (home_screen->objectName().isEmpty())
            home_screen->setObjectName("home_screen");
        home_screen->resize(881, 603);
        centralwidget = new QWidget(home_screen);
        centralwidget->setObjectName("centralwidget");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(330, 110, 511, 91));
        gridLayout = new QGridLayout(horizontalLayoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        ql_monthly_min = new QLabel(horizontalLayoutWidget);
        ql_monthly_min->setObjectName("ql_monthly_min");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(ql_monthly_min->sizePolicy().hasHeightForWidth());
        ql_monthly_min->setSizePolicy(sizePolicy1);
        ql_monthly_min->setMinimumSize(QSize(135, 0));
        QFont font;
        font.setFamilies({QString::fromUtf8("Gill Sans")});
        font.setPointSize(14);
        ql_monthly_min->setFont(font);
        ql_monthly_min->setAlignment(Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignTop);

        gridLayout->addWidget(ql_monthly_min, 0, 2, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 0, 3, 1, 1);

        ql_debt = new QLabel(horizontalLayoutWidget);
        ql_debt->setObjectName("ql_debt");
        sizePolicy1.setHeightForWidth(ql_debt->sizePolicy().hasHeightForWidth());
        ql_debt->setSizePolicy(sizePolicy1);
        ql_debt->setMinimumSize(QSize(135, 0));
        ql_debt->setFont(font);
        ql_debt->setAlignment(Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignTop);

        gridLayout->addWidget(ql_debt, 0, 4, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout->addItem(verticalSpacer, 0, 1, 1, 1);

        ql_balance = new QLabel(horizontalLayoutWidget);
        ql_balance->setObjectName("ql_balance");
        sizePolicy1.setHeightForWidth(ql_balance->sizePolicy().hasHeightForWidth());
        ql_balance->setSizePolicy(sizePolicy1);
        ql_balance->setMinimumSize(QSize(135, 0));
        ql_balance->setFont(font);
        ql_balance->setAlignment(Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignTop);

        gridLayout->addWidget(ql_balance, 0, 0, 1, 1);

        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(650, 30, 181, 31));
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
        gridLayoutWidget->setGeometry(QRect(520, 270, 162, 183));
        gridLayout_3 = new QGridLayout(gridLayoutWidget);
        gridLayout_3->setObjectName("gridLayout_3");
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        tb_savings = new QToolButton(gridLayoutWidget);
        tb_savings->setObjectName("tb_savings");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(3);
        sizePolicy2.setVerticalStretch(3);
        sizePolicy2.setHeightForWidth(tb_savings->sizePolicy().hasHeightForWidth());
        tb_savings->setSizePolicy(sizePolicy2);
        tb_savings->setMinimumSize(QSize(3, 3));

        gridLayout_3->addWidget(tb_savings, 0, 1, 1, 1);

        ql_savings = new QLabel(gridLayoutWidget);
        ql_savings->setObjectName("ql_savings");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(ql_savings->sizePolicy().hasHeightForWidth());
        ql_savings->setSizePolicy(sizePolicy3);
        ql_savings->setMinimumSize(QSize(120, 0));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Gill Sans")});
        font2.setPointSize(18);
        ql_savings->setFont(font2);
        ql_savings->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_3->addWidget(ql_savings, 0, 0, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_3->addItem(verticalSpacer_4, 1, 1, 1, 1);

        widget_savings = new QWidget(gridLayoutWidget);
        widget_savings->setObjectName("widget_savings");
        sizePolicy3.setHeightForWidth(widget_savings->sizePolicy().hasHeightForWidth());
        widget_savings->setSizePolicy(sizePolicy3);
        widget_savings->setMinimumSize(QSize(130, 120));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush);
        widget_savings->setPalette(palette);
        widget_savings->setAutoFillBackground(true);
        horizontalLayoutWidget_2 = new QWidget(widget_savings);
        horizontalLayoutWidget_2->setObjectName("horizontalLayoutWidget_2");
        horizontalLayoutWidget_2->setGeometry(QRect(0, 0, 131, 121));
        verticalLayout_2 = new QVBoxLayout(horizontalLayoutWidget_2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        pb_make_deposit = new QPushButton(horizontalLayoutWidget_2);
        pb_make_deposit->setObjectName("pb_make_deposit");
        QSizePolicy sizePolicy4(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(20);
        sizePolicy4.setHeightForWidth(pb_make_deposit->sizePolicy().hasHeightForWidth());
        pb_make_deposit->setSizePolicy(sizePolicy4);
        pb_make_deposit->setMinimumSize(QSize(120, 60));
        pb_make_deposit->setMaximumSize(QSize(120, 20));
        pb_make_deposit->setSizeIncrement(QSize(0, 15));
        pb_make_deposit->setBaseSize(QSize(0, 10));
        QPalette palette1;
        QBrush brush1(QColor(0, 0, 0, 216));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::ButtonText, brush1);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::ButtonText, brush1);
        pb_make_deposit->setPalette(palette1);
        pb_make_deposit->setFont(font);
        pb_make_deposit->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
        pb_make_deposit->setAutoFillBackground(true);

        verticalLayout_2->addWidget(pb_make_deposit, 0, Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignVCenter);

        pb_my_savings = new QPushButton(horizontalLayoutWidget_2);
        pb_my_savings->setObjectName("pb_my_savings");
        QSizePolicy sizePolicy5(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(12);
        sizePolicy5.setHeightForWidth(pb_my_savings->sizePolicy().hasHeightForWidth());
        pb_my_savings->setSizePolicy(sizePolicy5);
        pb_my_savings->setMinimumSize(QSize(120, 30));
        pb_my_savings->setMaximumSize(QSize(120, 20));
        pb_my_savings->setSizeIncrement(QSize(0, 0));
        pb_my_savings->setBaseSize(QSize(0, 0));
        QPalette palette2;
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::ButtonText, brush1);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::ButtonText, brush1);
        pb_my_savings->setPalette(palette2);
        pb_my_savings->setFont(font);
        pb_my_savings->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
        pb_my_savings->setAutoFillBackground(true);

        verticalLayout_2->addWidget(pb_my_savings, 0, Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignVCenter);


        gridLayout_3->addWidget(widget_savings, 1, 0, 1, 1);

        gridLayoutWidget_2 = new QWidget(centralwidget);
        gridLayoutWidget_2->setObjectName("gridLayoutWidget_2");
        gridLayoutWidget_2->setGeometry(QRect(700, 270, 162, 183));
        gridLayout_4 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_4->setObjectName("gridLayout_4");
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        ql_loans = new QLabel(gridLayoutWidget_2);
        ql_loans->setObjectName("ql_loans");
        sizePolicy3.setHeightForWidth(ql_loans->sizePolicy().hasHeightForWidth());
        ql_loans->setSizePolicy(sizePolicy3);
        ql_loans->setMinimumSize(QSize(120, 0));
        ql_loans->setFont(font2);
        ql_loans->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_4->addWidget(ql_loans, 0, 0, 1, 1);

        tb_loans = new QToolButton(gridLayoutWidget_2);
        tb_loans->setObjectName("tb_loans");
        sizePolicy2.setHeightForWidth(tb_loans->sizePolicy().hasHeightForWidth());
        tb_loans->setSizePolicy(sizePolicy2);
        tb_loans->setMinimumSize(QSize(3, 3));

        gridLayout_4->addWidget(tb_loans, 0, 1, 1, 1);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_4->addItem(verticalSpacer_5, 1, 1, 1, 1);

        widget_loans = new QWidget(gridLayoutWidget_2);
        widget_loans->setObjectName("widget_loans");
        sizePolicy3.setHeightForWidth(widget_loans->sizePolicy().hasHeightForWidth());
        widget_loans->setSizePolicy(sizePolicy3);
        widget_loans->setMinimumSize(QSize(130, 120));
        QPalette palette3;
        palette3.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush);
        palette3.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush);
        palette3.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush);
        palette3.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush);
        widget_loans->setPalette(palette3);
        widget_loans->setAutoFillBackground(true);
        horizontalLayoutWidget_5 = new QWidget(widget_loans);
        horizontalLayoutWidget_5->setObjectName("horizontalLayoutWidget_5");
        horizontalLayoutWidget_5->setGeometry(QRect(0, 0, 131, 121));
        verticalLayout_4 = new QVBoxLayout(horizontalLayoutWidget_5);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        pb_make_loan = new QPushButton(horizontalLayoutWidget_5);
        pb_make_loan->setObjectName("pb_make_loan");
        sizePolicy4.setHeightForWidth(pb_make_loan->sizePolicy().hasHeightForWidth());
        pb_make_loan->setSizePolicy(sizePolicy4);
        pb_make_loan->setMinimumSize(QSize(120, 60));
        pb_make_loan->setMaximumSize(QSize(120, 20));
        pb_make_loan->setSizeIncrement(QSize(0, 15));
        pb_make_loan->setBaseSize(QSize(0, 10));
        QPalette palette4;
        palette4.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::ButtonText, brush1);
        palette4.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::ButtonText, brush1);
        pb_make_loan->setPalette(palette4);
        pb_make_loan->setFont(font);
        pb_make_loan->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
        pb_make_loan->setAutoFillBackground(true);

        verticalLayout_4->addWidget(pb_make_loan, 0, Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignVCenter);

        pb_my_loans = new QPushButton(horizontalLayoutWidget_5);
        pb_my_loans->setObjectName("pb_my_loans");
        sizePolicy5.setHeightForWidth(pb_my_loans->sizePolicy().hasHeightForWidth());
        pb_my_loans->setSizePolicy(sizePolicy5);
        pb_my_loans->setMinimumSize(QSize(120, 30));
        pb_my_loans->setMaximumSize(QSize(120, 10));
        pb_my_loans->setSizeIncrement(QSize(0, 0));
        pb_my_loans->setBaseSize(QSize(0, 0));
        QPalette palette5;
        palette5.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::ButtonText, brush1);
        palette5.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::ButtonText, brush1);
        pb_my_loans->setPalette(palette5);
        pb_my_loans->setFont(font);
        pb_my_loans->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
        pb_my_loans->setAutoFillBackground(true);

        verticalLayout_4->addWidget(pb_my_loans, 0, Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignVCenter);


        gridLayout_4->addWidget(widget_loans, 1, 0, 1, 1);

        gridLayoutWidget_3 = new QWidget(centralwidget);
        gridLayoutWidget_3->setObjectName("gridLayoutWidget_3");
        gridLayoutWidget_3->setGeometry(QRect(340, 270, 162, 183));
        gridLayout_5 = new QGridLayout(gridLayoutWidget_3);
        gridLayout_5->setObjectName("gridLayout_5");
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        ql_modules = new QLabel(gridLayoutWidget_3);
        ql_modules->setObjectName("ql_modules");
        sizePolicy3.setHeightForWidth(ql_modules->sizePolicy().hasHeightForWidth());
        ql_modules->setSizePolicy(sizePolicy3);
        ql_modules->setMinimumSize(QSize(120, 0));
        ql_modules->setFont(font2);
        ql_modules->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_5->addWidget(ql_modules, 0, 0, 1, 1);

        widget_modules = new QWidget(gridLayoutWidget_3);
        widget_modules->setObjectName("widget_modules");
        sizePolicy3.setHeightForWidth(widget_modules->sizePolicy().hasHeightForWidth());
        widget_modules->setSizePolicy(sizePolicy3);
        widget_modules->setMinimumSize(QSize(130, 120));
        QPalette palette6;
        QBrush brush2(QColor(237, 237, 237, 255));
        brush2.setStyle(Qt::BrushStyle::SolidPattern);
        palette6.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush2);
        palette6.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush2);
        palette6.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush2);
        palette6.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush2);
        widget_modules->setPalette(palette6);
        widget_modules->setAutoFillBackground(true);
        gridLayoutWidget_4 = new QWidget(widget_modules);
        gridLayoutWidget_4->setObjectName("gridLayoutWidget_4");
        gridLayoutWidget_4->setGeometry(QRect(0, 0, 131, 121));
        gridLayout_2 = new QGridLayout(gridLayoutWidget_4);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        pb_mod_savings = new QPushButton(gridLayoutWidget_4);
        pb_mod_savings->setObjectName("pb_mod_savings");
        sizePolicy3.setHeightForWidth(pb_mod_savings->sizePolicy().hasHeightForWidth());
        pb_mod_savings->setSizePolicy(sizePolicy3);
        pb_mod_savings->setMinimumSize(QSize(120, 40));
        QPalette palette7;
        QBrush brush3(QColor(46, 47, 48, 255));
        brush3.setStyle(Qt::BrushStyle::SolidPattern);
        palette7.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::WindowText, brush3);
        palette7.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Text, brush1);
        palette7.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::ButtonText, brush1);
        palette7.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::WindowText, brush3);
        palette7.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Text, brush1);
        palette7.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::ButtonText, brush1);
        pb_mod_savings->setPalette(palette7);
        pb_mod_savings->setFont(font);
        pb_mod_savings->setAutoFillBackground(true);

        gridLayout_2->addWidget(pb_mod_savings, 0, 0, 1, 1);

        pb_mod_loans = new QPushButton(gridLayoutWidget_4);
        pb_mod_loans->setObjectName("pb_mod_loans");
        sizePolicy3.setHeightForWidth(pb_mod_loans->sizePolicy().hasHeightForWidth());
        pb_mod_loans->setSizePolicy(sizePolicy3);
        pb_mod_loans->setMinimumSize(QSize(120, 40));
        QPalette palette8;
        palette8.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::ButtonText, brush1);
        palette8.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::ButtonText, brush1);
        pb_mod_loans->setPalette(palette8);
        pb_mod_loans->setFont(font);
        pb_mod_loans->setAutoFillBackground(true);

        gridLayout_2->addWidget(pb_mod_loans, 1, 0, 1, 1);


        gridLayout_5->addWidget(widget_modules, 1, 0, 1, 1);

        tb_modules = new QToolButton(gridLayoutWidget_3);
        tb_modules->setObjectName("tb_modules");
        sizePolicy2.setHeightForWidth(tb_modules->sizePolicy().hasHeightForWidth());
        tb_modules->setSizePolicy(sizePolicy2);
        tb_modules->setMinimumSize(QSize(3, 3));

        gridLayout_5->addWidget(tb_modules, 0, 1, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_5->addItem(verticalSpacer_3, 1, 1, 1, 1);

        horizontalLayoutWidget_4 = new QWidget(centralwidget);
        horizontalLayoutWidget_4->setObjectName("horizontalLayoutWidget_4");
        horizontalLayoutWidget_4->setGeometry(QRect(340, 490, 521, 35));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget_4);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        pb_next_month = new QPushButton(horizontalLayoutWidget_4);
        pb_next_month->setObjectName("pb_next_month");
        sizePolicy3.setHeightForWidth(pb_next_month->sizePolicy().hasHeightForWidth());
        pb_next_month->setSizePolicy(sizePolicy3);
        pb_next_month->setMinimumSize(QSize(0, 0));
        pb_next_month->setMaximumSize(QSize(250, 16777215));
        pb_next_month->setFont(font);

        horizontalLayout_3->addWidget(pb_next_month);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        horizontalLayout_3->addItem(verticalSpacer_6);

        ql_month = new QLabel(horizontalLayoutWidget_4);
        ql_month->setObjectName("ql_month");
        sizePolicy1.setHeightForWidth(ql_month->sizePolicy().hasHeightForWidth());
        ql_month->setSizePolicy(sizePolicy1);
        ql_month->setMaximumSize(QSize(130, 16777215));
        ql_month->setFont(font);

        horizontalLayout_3->addWidget(ql_month);

        verticalLayoutWidget_2 = new QWidget(centralwidget);
        verticalLayoutWidget_2->setObjectName("verticalLayoutWidget_2");
        verticalLayoutWidget_2->setGeometry(QRect(20, 80, 291, 231));
        chart_layout = new QVBoxLayout(verticalLayoutWidget_2);
        chart_layout->setObjectName("chart_layout");
        chart_layout->setContentsMargins(0, 0, 0, 0);
        verticalLayoutWidget_3 = new QWidget(centralwidget);
        verticalLayoutWidget_3->setObjectName("verticalLayoutWidget_3");
        verticalLayoutWidget_3->setGeometry(QRect(150, 320, 111, 87));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        ql_chart_balance = new QLabel(verticalLayoutWidget_3);
        ql_chart_balance->setObjectName("ql_chart_balance");
        sizePolicy.setHeightForWidth(ql_chart_balance->sizePolicy().hasHeightForWidth());
        ql_chart_balance->setSizePolicy(sizePolicy);
        ql_chart_balance->setMinimumSize(QSize(0, 20));
        ql_chart_balance->setFont(font);
        ql_chart_balance->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_3->addWidget(ql_chart_balance, 0, Qt::AlignmentFlag::AlignVCenter);

        ql_chart_debt = new QLabel(verticalLayoutWidget_3);
        ql_chart_debt->setObjectName("ql_chart_debt");
        sizePolicy.setHeightForWidth(ql_chart_debt->sizePolicy().hasHeightForWidth());
        ql_chart_debt->setSizePolicy(sizePolicy);
        ql_chart_debt->setMinimumSize(QSize(0, 20));
        ql_chart_debt->setFont(font);
        ql_chart_debt->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_3->addWidget(ql_chart_debt, 0, Qt::AlignmentFlag::AlignVCenter);

        ql_chart_savings = new QLabel(verticalLayoutWidget_3);
        ql_chart_savings->setObjectName("ql_chart_savings");
        sizePolicy.setHeightForWidth(ql_chart_savings->sizePolicy().hasHeightForWidth());
        ql_chart_savings->setSizePolicy(sizePolicy);
        ql_chart_savings->setMinimumSize(QSize(0, 20));
        ql_chart_savings->setFont(font);
        ql_chart_savings->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_3->addWidget(ql_chart_savings, 0, Qt::AlignmentFlag::AlignVCenter);

        verticalLayoutWidget_4 = new QWidget(centralwidget);
        verticalLayoutWidget_4->setObjectName("verticalLayoutWidget_4");
        verticalLayoutWidget_4->setGeometry(QRect(60, 320, 81, 87));
        verticalLayout_5 = new QVBoxLayout(verticalLayoutWidget_4);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        ql_chart_balance_value = new QLabel(verticalLayoutWidget_4);
        ql_chart_balance_value->setObjectName("ql_chart_balance_value");
        sizePolicy.setHeightForWidth(ql_chart_balance_value->sizePolicy().hasHeightForWidth());
        ql_chart_balance_value->setSizePolicy(sizePolicy);
        ql_chart_balance_value->setMinimumSize(QSize(0, 20));
        ql_chart_balance_value->setFont(font);
        ql_chart_balance_value->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_5->addWidget(ql_chart_balance_value, 0, Qt::AlignmentFlag::AlignVCenter);

        ql_chart_debt_value = new QLabel(verticalLayoutWidget_4);
        ql_chart_debt_value->setObjectName("ql_chart_debt_value");
        sizePolicy.setHeightForWidth(ql_chart_debt_value->sizePolicy().hasHeightForWidth());
        ql_chart_debt_value->setSizePolicy(sizePolicy);
        ql_chart_debt_value->setMinimumSize(QSize(0, 20));
        ql_chart_debt_value->setFont(font);
        ql_chart_debt_value->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_5->addWidget(ql_chart_debt_value, 0, Qt::AlignmentFlag::AlignVCenter);

        ql_chart_savings_value = new QLabel(verticalLayoutWidget_4);
        ql_chart_savings_value->setObjectName("ql_chart_savings_value");
        sizePolicy.setHeightForWidth(ql_chart_savings_value->sizePolicy().hasHeightForWidth());
        ql_chart_savings_value->setSizePolicy(sizePolicy);
        ql_chart_savings_value->setMinimumSize(QSize(0, 20));
        ql_chart_savings_value->setFont(font);
        ql_chart_savings_value->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_5->addWidget(ql_chart_savings_value, 0, Qt::AlignmentFlag::AlignVCenter);

        home_screen->setCentralWidget(centralwidget);
        menubar = new QMenuBar(home_screen);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 881, 36));
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
        ql_monthly_min->setText(QCoreApplication::translate("home_screen", "\320\234\320\265\321\201\321\217\321\207\320\275\321\213\320\271 \320\274\320\270\320\275\320\270\320\274\321\203\320\274", nullptr));
        ql_debt->setText(QCoreApplication::translate("home_screen", "\320\224\320\276\320\273\320\263", nullptr));
        ql_balance->setText(QCoreApplication::translate("home_screen", "\320\221\320\260\320\273\320\260\320\275\321\201", nullptr));
        ql_username->setText(QCoreApplication::translate("home_screen", "\320\230\320\274\321\217 \320\277\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\321\217", nullptr));
        tb_savings->setText(QString());
        ql_savings->setText(QCoreApplication::translate("home_screen", "\320\222\320\272\320\273\320\260\320\264\321\213", nullptr));
        pb_make_deposit->setText(QCoreApplication::translate("home_screen", "\320\236\321\204\320\276\321\200\320\274\320\270\321\202\321\214", nullptr));
        pb_my_savings->setText(QCoreApplication::translate("home_screen", "\320\234\320\276\320\270 \320\262\320\272\320\273\320\260\320\264\321\213", nullptr));
        ql_loans->setText(QCoreApplication::translate("home_screen", "\320\232\321\200\320\265\320\264\320\270\321\202\321\213", nullptr));
        tb_loans->setText(QString());
        pb_make_loan->setText(QCoreApplication::translate("home_screen", "\320\236\321\204\320\276\321\200\320\274\320\270\321\202\321\214", nullptr));
        pb_my_loans->setText(QCoreApplication::translate("home_screen", "\320\234\320\276\320\270 \320\272\321\200\320\265\320\264\320\270\321\202\321\213", nullptr));
        ql_modules->setText(QCoreApplication::translate("home_screen", "\320\234\320\276\320\264\321\203\320\273\320\270", nullptr));
        pb_mod_savings->setText(QCoreApplication::translate("home_screen", "\320\222\320\272\320\273\320\260\320\264\321\213", nullptr));
        pb_mod_loans->setText(QCoreApplication::translate("home_screen", "\320\232\321\200\320\265\320\264\320\270\321\202\321\213", nullptr));
        tb_modules->setText(QString());
        pb_next_month->setText(QCoreApplication::translate("home_screen", "\320\232 \321\201\320\273\320\265\320\264\321\203\321\216\321\211\320\265\320\274\321\203 \320\274\320\265\321\201\321\217\321\206\321\203 \320\270\320\263\321\200\321\213", nullptr));
        ql_month->setText(QCoreApplication::translate("home_screen", "  \320\242\320\265\320\272\321\203\321\211\320\270\320\271 \320\274\320\265\321\201\321\217\321\206: ", nullptr));
        ql_chart_balance->setText(QCoreApplication::translate("home_screen", "\320\221\320\260\320\273\320\260\320\275\321\201", nullptr));
        ql_chart_debt->setText(QCoreApplication::translate("home_screen", "\320\241\321\203\320\274\320\274\320\260 \320\264\320\276\320\273\320\263\320\260", nullptr));
        ql_chart_savings->setText(QCoreApplication::translate("home_screen", "\320\241\321\203\320\274\320\274\320\260 \320\262\320\272\320\273\320\260\320\264\320\260", nullptr));
        ql_chart_balance_value->setText(QCoreApplication::translate("home_screen", "0", nullptr));
        ql_chart_debt_value->setText(QCoreApplication::translate("home_screen", "0", nullptr));
        ql_chart_savings_value->setText(QCoreApplication::translate("home_screen", "0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class home_screen: public Ui_home_screen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOME_SCREEN_H
