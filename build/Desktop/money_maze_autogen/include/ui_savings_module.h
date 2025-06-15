/********************************************************************************
** Form generated from reading UI file 'savings_module.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SAVINGS_MODULE_H
#define UI_SAVINGS_MODULE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_savings_module
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *ql_heading;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *ql_text;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *pb_next;

    void setupUi(QWidget *savings_module)
    {
        if (savings_module->objectName().isEmpty())
            savings_module->setObjectName("savings_module");
        savings_module->resize(440, 320);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(savings_module->sizePolicy().hasHeightForWidth());
        savings_module->setSizePolicy(sizePolicy);
        horizontalLayoutWidget = new QWidget(savings_module);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(10, 20, 421, 31));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        ql_heading = new QLabel(horizontalLayoutWidget);
        ql_heading->setObjectName("ql_heading");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(ql_heading->sizePolicy().hasHeightForWidth());
        ql_heading->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(ql_heading);

        verticalLayoutWidget_2 = new QWidget(savings_module);
        verticalLayoutWidget_2->setObjectName("verticalLayoutWidget_2");
        verticalLayoutWidget_2->setGeometry(QRect(10, 70, 421, 191));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        ql_text = new QLabel(verticalLayoutWidget_2);
        ql_text->setObjectName("ql_text");
        sizePolicy1.setHeightForWidth(ql_text->sizePolicy().hasHeightForWidth());
        ql_text->setSizePolicy(sizePolicy1);

        verticalLayout_2->addWidget(ql_text);

        verticalLayoutWidget = new QWidget(savings_module);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(60, 280, 311, 35));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        pb_next = new QPushButton(verticalLayoutWidget);
        pb_next->setObjectName("pb_next");
        QFont font;
        font.setFamilies({QString::fromUtf8("Gill Sans")});
        font.setPointSize(14);
        pb_next->setFont(font);

        verticalLayout->addWidget(pb_next);


        retranslateUi(savings_module);

        QMetaObject::connectSlotsByName(savings_module);
    } // setupUi

    void retranslateUi(QWidget *savings_module)
    {
        savings_module->setWindowTitle(QCoreApplication::translate("savings_module", "Form", nullptr));
        ql_heading->setText(QString());
        ql_text->setText(QString());
        pb_next->setText(QCoreApplication::translate("savings_module", "\320\224\320\260\320\273\320\265\320\265", nullptr));
    } // retranslateUi

};

namespace Ui {
    class savings_module: public Ui_savings_module {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SAVINGS_MODULE_H
