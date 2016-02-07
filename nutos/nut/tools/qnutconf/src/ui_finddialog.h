/********************************************************************************
** Form generated from reading UI file 'finddialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FINDDIALOG_H
#define UI_FINDDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FindDialogClass
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QComboBox *e_findstring;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btn_Next;
    QPushButton *btn_Cancel;

    void setupUi(QDialog *FindDialogClass)
    {
        if (FindDialogClass->objectName().isEmpty())
            FindDialogClass->setObjectName(QString::fromUtf8("FindDialogClass"));
        FindDialogClass->resize(319, 132);
        FindDialogClass->setSizeGripEnabled(true);
        verticalLayoutWidget = new QWidget(FindDialogClass);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(9, 19, 301, 101));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        e_findstring = new QComboBox(verticalLayoutWidget);
        e_findstring->setObjectName(QString::fromUtf8("e_findstring"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(e_findstring->sizePolicy().hasHeightForWidth());
        e_findstring->setSizePolicy(sizePolicy);
        e_findstring->setEditable(true);

        verticalLayout->addWidget(e_findstring);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btn_Next = new QPushButton(verticalLayoutWidget);
        btn_Next->setObjectName(QString::fromUtf8("btn_Next"));
        btn_Next->setDefault(true);

        horizontalLayout->addWidget(btn_Next);

        btn_Cancel = new QPushButton(verticalLayoutWidget);
        btn_Cancel->setObjectName(QString::fromUtf8("btn_Cancel"));

        horizontalLayout->addWidget(btn_Cancel);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(FindDialogClass);
        QObject::connect(btn_Next, SIGNAL(clicked()), FindDialogClass, SLOT(nextClicked()));
        QObject::connect(btn_Cancel, SIGNAL(clicked()), FindDialogClass, SLOT(hide()));

        QMetaObject::connectSlotsByName(FindDialogClass);
    } // setupUi

    void retranslateUi(QDialog *FindDialogClass)
    {
        FindDialogClass->setWindowTitle(QApplication::translate("FindDialogClass", "Find Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("FindDialogClass", "Find what:", 0, QApplication::UnicodeUTF8));
        btn_Next->setText(QApplication::translate("FindDialogClass", "Next", 0, QApplication::UnicodeUTF8));
        btn_Cancel->setText(QApplication::translate("FindDialogClass", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FindDialogClass: public Ui_FindDialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FINDDIALOG_H
