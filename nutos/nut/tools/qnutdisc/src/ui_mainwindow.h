/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QTableView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_Sair;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QTableView *tv_Devices;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QPushButton *btn_refresh;
    QSpacerItem *horizontalSpacer_2;
    QMenuBar *menuBar;
    QMenu *menu_Arquivo;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(759, 349);
        action_Sair = new QAction(MainWindow);
        action_Sair->setObjectName(QString::fromUtf8("action_Sair"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tv_Devices = new QTableView(centralWidget);
        tv_Devices->setObjectName(QString::fromUtf8("tv_Devices"));
        tv_Devices->setStyleSheet(QString::fromUtf8("background: white;"));

        gridLayout->addWidget(tv_Devices, 0, 0, 1, 3);

        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setPixmap(QPixmap(QString::fromUtf8(":/logo.png")));
        label->setScaledContents(false);
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label, 1, 0, 1, 3);

        horizontalSpacer = new QSpacerItem(324, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 2, 0, 1, 1);

        btn_refresh = new QPushButton(centralWidget);
        btn_refresh->setObjectName(QString::fromUtf8("btn_refresh"));
        QFont font;
        font.setFamily(QString::fromUtf8("Lucida Sans"));
        font.setPointSize(8);
        font.setBold(false);
        font.setItalic(false);
        font.setUnderline(false);
        font.setWeight(50);
        font.setStrikeOut(false);
        btn_refresh->setFont(font);
        btn_refresh->setStyleSheet(QString::fromUtf8("border-width:1px;"));

        gridLayout->addWidget(btn_refresh, 2, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(324, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 2, 2, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 759, 21));
        menu_Arquivo = new QMenu(menuBar);
        menu_Arquivo->setObjectName(QString::fromUtf8("menu_Arquivo"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu_Arquivo->menuAction());
        menu_Arquivo->addSeparator();
        menu_Arquivo->addAction(action_Sair);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Ethernut Device Discovery Tool", 0, QApplication::UnicodeUTF8));
        action_Sair->setText(QApplication::translate("MainWindow", "&Exit", 0, QApplication::UnicodeUTF8));
        btn_refresh->setText(QApplication::translate("MainWindow", "&Update", 0, QApplication::UnicodeUTF8));
        menu_Arquivo->setTitle(QApplication::translate("MainWindow", "&File", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
