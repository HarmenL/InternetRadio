/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSplitter>
#include <QtGui/QStatusBar>
#include <QtGui/QTableView>
#include <QtGui/QTextBrowser>
#include <QtGui/QTextEdit>
#include <QtGui/QToolBar>
#include <QtGui/QTreeView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSave_as;
    QAction *actionExit;
    QAction *actionBuild_Nut_OS;
    QAction *actionCreate_sample;
    QAction *actionSettings;
    QAction *actionHelp_Contents;
    QAction *actionAbout;
    QAction *actionBuildStop;
    QAction *actionFind;
    QAction *actionViewComponentTreeDisabledItems;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QSplitter *splitter_4;
    QSplitter *splitter_3;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QSplitter *splitter;
    QTreeView *componentTree;
    QSplitter *splitter_2;
    QTableView *detailsView;
    QTextBrowser *descriptionPanel;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout;
    QTextEdit *logPanel;
    QHBoxLayout *logControl;
    QSpacerItem *horizontalSpacer;
    QPushButton *logClear;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuView;
    QMenu *menuComponent_Tree;
    QMenu *menuBuild;
    QMenu *menuHelp;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(799, 661);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/buildlibrary_large.png"), QSize(), QIcon::Normal, QIcon::On);
        MainWindow->setWindowIcon(icon);
        MainWindow->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/open_large.png"), QSize(), QIcon::Normal, QIcon::On);
        actionOpen->setIcon(icon1);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/save_large.png"), QSize(), QIcon::Normal, QIcon::On);
        actionSave->setIcon(icon2);
        actionSave_as = new QAction(MainWindow);
        actionSave_as->setObjectName(QString::fromUtf8("actionSave_as"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionBuild_Nut_OS = new QAction(MainWindow);
        actionBuild_Nut_OS->setObjectName(QString::fromUtf8("actionBuild_Nut_OS"));
        actionBuild_Nut_OS->setIcon(icon);
        actionBuild_Nut_OS->setAutoRepeat(false);
        actionCreate_sample = new QAction(MainWindow);
        actionCreate_sample->setObjectName(QString::fromUtf8("actionCreate_sample"));
        actionSettings = new QAction(MainWindow);
        actionSettings->setObjectName(QString::fromUtf8("actionSettings"));
        actionHelp_Contents = new QAction(MainWindow);
        actionHelp_Contents->setObjectName(QString::fromUtf8("actionHelp_Contents"));
        actionHelp_Contents->setShortcutContext(Qt::ApplicationShortcut);
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionBuildStop = new QAction(MainWindow);
        actionBuildStop->setObjectName(QString::fromUtf8("actionBuildStop"));
        actionBuildStop->setEnabled(false);
        actionFind = new QAction(MainWindow);
        actionFind->setObjectName(QString::fromUtf8("actionFind"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/search_large.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionFind->setIcon(icon3);
        actionViewComponentTreeDisabledItems = new QAction(MainWindow);
        actionViewComponentTreeDisabledItems->setObjectName(QString::fromUtf8("actionViewComponentTreeDisabledItems"));
        actionViewComponentTreeDisabledItems->setCheckable(true);
        actionViewComponentTreeDisabledItems->setChecked(false);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_2 = new QVBoxLayout(centralwidget);
#ifndef Q_OS_MAC
        verticalLayout_2->setSpacing(6);
#endif
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        splitter_4 = new QSplitter(centralwidget);
        splitter_4->setObjectName(QString::fromUtf8("splitter_4"));
        splitter_4->setOrientation(Qt::Vertical);
        splitter_3 = new QSplitter(splitter_4);
        splitter_3->setObjectName(QString::fromUtf8("splitter_3"));
        splitter_3->setOrientation(Qt::Horizontal);
        layoutWidget = new QWidget(splitter_3);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        splitter = new QSplitter(layoutWidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        componentTree = new QTreeView(splitter);
        componentTree->setObjectName(QString::fromUtf8("componentTree"));
        componentTree->setEditTriggers(QAbstractItemView::AllEditTriggers);
        componentTree->setAlternatingRowColors(true);
        componentTree->setTextElideMode(Qt::ElideMiddle);
        componentTree->setHeaderHidden(false);
        splitter->addWidget(componentTree);
        componentTree->header()->setVisible(true);
        componentTree->header()->setCascadingSectionResizes(true);
        componentTree->header()->setStretchLastSection(true);

        horizontalLayout->addWidget(splitter);

        splitter_3->addWidget(layoutWidget);
        splitter_2 = new QSplitter(splitter_3);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setOrientation(Qt::Vertical);
        detailsView = new QTableView(splitter_2);
        detailsView->setObjectName(QString::fromUtf8("detailsView"));
        splitter_2->addWidget(detailsView);
        detailsView->horizontalHeader()->setStretchLastSection(true);
        detailsView->verticalHeader()->setVisible(false);
        detailsView->verticalHeader()->setHighlightSections(false);
        detailsView->verticalHeader()->setStretchLastSection(false);
        descriptionPanel = new QTextBrowser(splitter_2);
        descriptionPanel->setObjectName(QString::fromUtf8("descriptionPanel"));
        splitter_2->addWidget(descriptionPanel);
        splitter_3->addWidget(splitter_2);
        splitter_4->addWidget(splitter_3);
        layoutWidget2 = new QWidget(splitter_4);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        verticalLayout = new QVBoxLayout(layoutWidget2);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        logPanel = new QTextEdit(layoutWidget2);
        logPanel->setObjectName(QString::fromUtf8("logPanel"));
        QFont font;
        font.setFamily(QString::fromUtf8("Courier New"));
        logPanel->setFont(font);
        logPanel->setAcceptDrops(false);
        logPanel->setUndoRedoEnabled(false);
        logPanel->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        verticalLayout->addWidget(logPanel);

        logControl = new QHBoxLayout();
        logControl->setSpacing(15);
        logControl->setObjectName(QString::fromUtf8("logControl"));
        logControl->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        logControl->addItem(horizontalSpacer);

        logClear = new QPushButton(layoutWidget2);
        logClear->setObjectName(QString::fromUtf8("logClear"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(logClear->sizePolicy().hasHeightForWidth());
        logClear->setSizePolicy(sizePolicy);
        logClear->setMinimumSize(QSize(55, 24));
        logClear->setBaseSize(QSize(0, 0));

        logControl->addWidget(logClear);


        verticalLayout->addLayout(logControl);

        splitter_4->addWidget(layoutWidget2);

        verticalLayout_2->addWidget(splitter_4);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 799, 21));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuEdit = new QMenu(menubar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        menuView = new QMenu(menubar);
        menuView->setObjectName(QString::fromUtf8("menuView"));
        menuComponent_Tree = new QMenu(menuView);
        menuComponent_Tree->setObjectName(QString::fromUtf8("menuComponent_Tree"));
        menuBuild = new QMenu(menubar);
        menuBuild->setObjectName(QString::fromUtf8("menuBuild"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);
        QWidget::setTabOrder(componentTree, detailsView);
        QWidget::setTabOrder(detailsView, descriptionPanel);
        QWidget::setTabOrder(descriptionPanel, logPanel);
        QWidget::setTabOrder(logPanel, logClear);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuEdit->menuAction());
        menubar->addAction(menuView->menuAction());
        menubar->addAction(menuBuild->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionSave_as);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuEdit->addAction(actionFind);
        menuEdit->addAction(actionSettings);
        menuView->addAction(menuComponent_Tree->menuAction());
        menuComponent_Tree->addAction(actionViewComponentTreeDisabledItems);
        menuBuild->addAction(actionBuild_Nut_OS);
        menuBuild->addAction(actionBuildStop);
        menuBuild->addSeparator();
        menuBuild->addAction(actionCreate_sample);
        menuHelp->addAction(actionHelp_Contents);
        menuHelp->addSeparator();
        menuHelp->addAction(actionAbout);
        toolBar->addAction(actionOpen);
        toolBar->addAction(actionSave);
        toolBar->addAction(actionBuild_Nut_OS);
        toolBar->addAction(actionFind);

        retranslateUi(MainWindow);
        QObject::connect(logClear, SIGNAL(clicked()), logPanel, SLOT(clear()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Nut/OS Configurator", 0, QApplication::UnicodeUTF8));
        actionOpen->setText(QApplication::translate("MainWindow", "Open", 0, QApplication::UnicodeUTF8));
        actionOpen->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0, QApplication::UnicodeUTF8));
        actionSave->setText(QApplication::translate("MainWindow", "Save", 0, QApplication::UnicodeUTF8));
        actionSave->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", 0, QApplication::UnicodeUTF8));
        actionSave_as->setText(QApplication::translate("MainWindow", "Save As...", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", 0, QApplication::UnicodeUTF8));
        actionBuild_Nut_OS->setText(QApplication::translate("MainWindow", "Build Nut/OS", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionBuild_Nut_OS->setStatusTip(QApplication::translate("MainWindow", "Build Nut/OS Libraries", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionBuild_Nut_OS->setShortcut(QApplication::translate("MainWindow", "F7", 0, QApplication::UnicodeUTF8));
        actionCreate_sample->setText(QApplication::translate("MainWindow", "Create Sample Directory", 0, QApplication::UnicodeUTF8));
        actionSettings->setText(QApplication::translate("MainWindow", "Settings...", 0, QApplication::UnicodeUTF8));
        actionSettings->setShortcut(QApplication::translate("MainWindow", "Ctrl+T", 0, QApplication::UnicodeUTF8));
        actionHelp_Contents->setText(QApplication::translate("MainWindow", "Help Contents", 0, QApplication::UnicodeUTF8));
        actionHelp_Contents->setShortcut(QApplication::translate("MainWindow", "F1", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("MainWindow", "About", 0, QApplication::UnicodeUTF8));
        actionBuildStop->setText(QApplication::translate("MainWindow", "Stop", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionBuildStop->setStatusTip(QApplication::translate("MainWindow", "Cancel the current build", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionFind->setText(QApplication::translate("MainWindow", "Find...", 0, QApplication::UnicodeUTF8));
        actionFind->setShortcut(QApplication::translate("MainWindow", "Ctrl+F", 0, QApplication::UnicodeUTF8));
        actionViewComponentTreeDisabledItems->setText(QApplication::translate("MainWindow", "Disabled Items", 0, QApplication::UnicodeUTF8));
        logClear->setText(QApplication::translate("MainWindow", "Clear", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
        menuEdit->setTitle(QApplication::translate("MainWindow", "Edit", 0, QApplication::UnicodeUTF8));
        menuView->setTitle(QApplication::translate("MainWindow", "View", 0, QApplication::UnicodeUTF8));
        menuComponent_Tree->setTitle(QApplication::translate("MainWindow", "Component Tree", 0, QApplication::UnicodeUTF8));
        menuBuild->setTitle(QApplication::translate("MainWindow", "Build", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0, QApplication::UnicodeUTF8));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
