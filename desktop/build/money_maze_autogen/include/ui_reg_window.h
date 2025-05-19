/********************************************************************************
** Form generated from reading UI file 'reg_window.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REG_WINDOW_H
#define UI_REG_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_reg_window
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QLabel *label_2;
    QLineEdit *lineEdit_login;
    QLineEdit *lineEdit_password;
    QLabel *label_4;
    QLineEdit *lineEdit_confirmation;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label_5;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_2;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_create_account;

    void setupUi(QDialog *reg_window)
    {
        if (reg_window->objectName().isEmpty())
            reg_window->setObjectName("reg_window");
        reg_window->resize(400, 300);
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Window, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush);
        reg_window->setPalette(palette);
        gridLayoutWidget = new QWidget(reg_window);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(10, 70, 351, 143));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(gridLayoutWidget);
        label_3->setObjectName("label_3");
        QPalette palette1;
        QBrush brush1(QColor(0, 0, 0, 216));
        brush1.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush1);
        label_3->setPalette(palette1);
        QFont font;
        font.setFamilies({QString::fromUtf8("Gill Sans")});
        font.setPointSize(14);
        font.setBold(false);
        label_3->setFont(font);
        label_3->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName("label_2");
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush1);
        label_2->setPalette(palette2);
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Gill Sans")});
        font1.setPointSize(14);
        label_2->setFont(font1);
        label_2->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        lineEdit_login = new QLineEdit(gridLayoutWidget);
        lineEdit_login->setObjectName("lineEdit_login");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEdit_login->sizePolicy().hasHeightForWidth());
        lineEdit_login->setSizePolicy(sizePolicy);
        QPalette palette3;
        QBrush brush2(QColor(0, 0, 0, 217));
        brush2.setStyle(Qt::SolidPattern);
        palette3.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette3.setBrush(QPalette::Active, QPalette::Text, brush2);
        QBrush brush3(QColor(243, 244, 246, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette3.setBrush(QPalette::Active, QPalette::Base, brush3);
        palette3.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette3.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette3.setBrush(QPalette::Inactive, QPalette::Base, brush3);
        lineEdit_login->setPalette(palette3);
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Gill Sans")});
        font2.setPointSize(13);
        lineEdit_login->setFont(font2);
        lineEdit_login->setMaxLength(20);

        gridLayout->addWidget(lineEdit_login, 0, 1, 1, 1);

        lineEdit_password = new QLineEdit(gridLayoutWidget);
        lineEdit_password->setObjectName("lineEdit_password");
        sizePolicy.setHeightForWidth(lineEdit_password->sizePolicy().hasHeightForWidth());
        lineEdit_password->setSizePolicy(sizePolicy);
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette4.setBrush(QPalette::Active, QPalette::Base, brush3);
        palette4.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette4.setBrush(QPalette::Inactive, QPalette::Base, brush3);
        lineEdit_password->setPalette(palette4);
        lineEdit_password->setFont(font2);

        gridLayout->addWidget(lineEdit_password, 1, 1, 1, 1);

        label_4 = new QLabel(gridLayoutWidget);
        label_4->setObjectName("label_4");
        QPalette palette5;
        palette5.setBrush(QPalette::Active, QPalette::WindowText, brush1);
        QBrush brush4(QColor(0, 0, 0, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette5.setBrush(QPalette::Active, QPalette::Window, brush4);
        palette5.setBrush(QPalette::Inactive, QPalette::WindowText, brush1);
        palette5.setBrush(QPalette::Inactive, QPalette::Window, brush4);
        palette5.setBrush(QPalette::Disabled, QPalette::Base, brush4);
        palette5.setBrush(QPalette::Disabled, QPalette::Window, brush4);
        label_4->setPalette(palette5);
        label_4->setFont(font1);
        label_4->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);
        label_4->setWordWrap(true);

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        lineEdit_confirmation = new QLineEdit(gridLayoutWidget);
        lineEdit_confirmation->setObjectName("lineEdit_confirmation");
        sizePolicy.setHeightForWidth(lineEdit_confirmation->sizePolicy().hasHeightForWidth());
        lineEdit_confirmation->setSizePolicy(sizePolicy);
        QPalette palette6;
        palette6.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette6.setBrush(QPalette::Active, QPalette::Base, brush3);
        palette6.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette6.setBrush(QPalette::Inactive, QPalette::Base, brush3);
        lineEdit_confirmation->setPalette(palette6);
        lineEdit_confirmation->setFont(font2);

        gridLayout->addWidget(lineEdit_confirmation, 2, 1, 1, 1);

        verticalLayoutWidget = new QWidget(reg_window);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(0, 20, 401, 31));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(verticalLayoutWidget);
        label_5->setObjectName("label_5");
        QPalette palette7;
        QBrush brush5(QColor(79, 192, 83, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette7.setBrush(QPalette::Active, QPalette::WindowText, brush5);
        palette7.setBrush(QPalette::Active, QPalette::Base, brush5);
        palette7.setBrush(QPalette::Inactive, QPalette::WindowText, brush5);
        palette7.setBrush(QPalette::Inactive, QPalette::Base, brush5);
        label_5->setPalette(palette7);
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Gill Sans")});
        font3.setPointSize(16);
        label_5->setFont(font3);
        label_5->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(label_5);

        gridLayoutWidget_2 = new QWidget(reg_window);
        gridLayoutWidget_2->setObjectName("gridLayoutWidget_2");
        gridLayoutWidget_2->setGeometry(QRect(0, 240, 401, 41));
        gridLayout_2 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 0, 2, 1, 1);

        pushButton_create_account = new QPushButton(gridLayoutWidget_2);
        pushButton_create_account->setObjectName("pushButton_create_account");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton_create_account->sizePolicy().hasHeightForWidth());
        pushButton_create_account->setSizePolicy(sizePolicy1);
        QPalette palette8;
        palette8.setBrush(QPalette::Active, QPalette::WindowText, brush4);
        palette8.setBrush(QPalette::Active, QPalette::ButtonText, brush1);
        palette8.setBrush(QPalette::Inactive, QPalette::WindowText, brush4);
        palette8.setBrush(QPalette::Inactive, QPalette::ButtonText, brush1);
        pushButton_create_account->setPalette(palette8);
        pushButton_create_account->setFont(font3);

        gridLayout_2->addWidget(pushButton_create_account, 0, 1, 1, 1);


        retranslateUi(reg_window);

        QMetaObject::connectSlotsByName(reg_window);
    } // setupUi

    void retranslateUi(QDialog *reg_window)
    {
        reg_window->setWindowTitle(QCoreApplication::translate("reg_window", "Dialog", nullptr));
        label_3->setText(QCoreApplication::translate("reg_window", "\320\237\320\260\321\200\320\276\320\273\321\214", nullptr));
        label_2->setText(QCoreApplication::translate("reg_window", "\320\233\320\276\320\263\320\270\320\275", nullptr));
        label_4->setText(QCoreApplication::translate("reg_window", "\320\237\320\276\320\264\321\202\320\262\320\265\321\200\320\266\320\264\320\265\320\275\320\270\320\265", nullptr));
        label_5->setText(QCoreApplication::translate("reg_window", "\320\241\320\276\320\267\320\264\320\260\320\275\320\270\320\265 \320\275\320\276\320\262\320\276\320\263\320\276 \320\260\320\272\320\272\320\260\321\203\320\275\321\202\320\260", nullptr));
        pushButton_create_account->setText(QCoreApplication::translate("reg_window", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class reg_window: public Ui_reg_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REG_WINDOW_H
