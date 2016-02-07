/********************************************************************************
** Form generated from reading UI file 'settingsdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSDIALOG_H
#define UI_SETTINGSDIALOG_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingsDialogClass
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *repositoryTab;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *e_RepositoryFile;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btn_BrowseRepository;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_3;
    QCheckBox *cb_MultiConfig;
    QSpacerItem *verticalSpacer;
    QWidget *buildTab;
    QVBoxLayout *verticalLayout_6;
    QGroupBox *groupBox_9;
    QVBoxLayout *verticalLayout_11;
    QCheckBox *cb_LogVerbose;
    QCheckBox *cb_ClearLogBeforeBuild;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *e_SourceDirectory;
    QPushButton *btn_BrowseSource;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QComboBox *cb_Platform;
    QSpacerItem *horizontalSpacer_2;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLineEdit *e_IncludeFirst;
    QPushButton *btn_BrowseIncludeFirst;
    QLabel *label_3;
    QLineEdit *e_IncludeLast;
    QPushButton *btn_BrowseIncludeLast;
    QGroupBox *groupBox_5;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *e_BuildDirectory;
    QPushButton *btn_BrowseBuildDirectory;
    QGroupBox *groupBox_6;
    QHBoxLayout *horizontalLayout_5;
    QLineEdit *e_InstallDirectory;
    QPushButton *btn_BrowseInstallDirectory;
    QWidget *toolsTab;
    QVBoxLayout *verticalLayout_8;
    QGroupBox *groupBox_7;
    QVBoxLayout *verticalLayout_7;
    QLineEdit *e_ToolPath;
    QSpacerItem *verticalSpacer_2;
    QWidget *samplesTab;
    QVBoxLayout *verticalLayout_10;
    QGroupBox *groupBox_8;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout_6;
    QLineEdit *e_AppDirectory;
    QPushButton *btn_BrowseAppDirectory;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_4;
    QComboBox *cb_Programmer;
    QSpacerItem *horizontalSpacer_3;
    QCheckBox *cb_AbsolutePathInSamples;
    QSpacerItem *verticalSpacer_3;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SettingsDialogClass)
    {
        if (SettingsDialogClass->objectName().isEmpty())
            SettingsDialogClass->setObjectName(QString::fromUtf8("SettingsDialogClass"));
        SettingsDialogClass->resize(378, 472);
        SettingsDialogClass->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        verticalLayout = new QVBoxLayout(SettingsDialogClass);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidget = new QTabWidget(SettingsDialogClass);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setTabPosition(QTabWidget::North);
        tabWidget->setTabShape(QTabWidget::Rounded);
        repositoryTab = new QWidget();
        repositoryTab->setObjectName(QString::fromUtf8("repositoryTab"));
        verticalLayout_4 = new QVBoxLayout(repositoryTab);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        groupBox = new QGroupBox(repositoryTab);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        e_RepositoryFile = new QLineEdit(groupBox);
        e_RepositoryFile->setObjectName(QString::fromUtf8("e_RepositoryFile"));

        verticalLayout_2->addWidget(e_RepositoryFile);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btn_BrowseRepository = new QPushButton(groupBox);
        btn_BrowseRepository->setObjectName(QString::fromUtf8("btn_BrowseRepository"));

        horizontalLayout->addWidget(btn_BrowseRepository);


        verticalLayout_2->addLayout(horizontalLayout);


        verticalLayout_4->addWidget(groupBox);

        groupBox_2 = new QGroupBox(repositoryTab);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        verticalLayout_3 = new QVBoxLayout(groupBox_2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        cb_MultiConfig = new QCheckBox(groupBox_2);
        cb_MultiConfig->setObjectName(QString::fromUtf8("cb_MultiConfig"));

        verticalLayout_3->addWidget(cb_MultiConfig);


        verticalLayout_4->addWidget(groupBox_2);

        verticalSpacer = new QSpacerItem(20, 174, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer);

        tabWidget->addTab(repositoryTab, QString());
        buildTab = new QWidget();
        buildTab->setObjectName(QString::fromUtf8("buildTab"));
        verticalLayout_6 = new QVBoxLayout(buildTab);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        groupBox_9 = new QGroupBox(buildTab);
        groupBox_9->setObjectName(QString::fromUtf8("groupBox_9"));
        verticalLayout_11 = new QVBoxLayout(groupBox_9);
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setContentsMargins(11, 11, 11, 11);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        cb_LogVerbose = new QCheckBox(groupBox_9);
        cb_LogVerbose->setObjectName(QString::fromUtf8("cb_LogVerbose"));

        verticalLayout_11->addWidget(cb_LogVerbose);

        cb_ClearLogBeforeBuild = new QCheckBox(groupBox_9);
        cb_ClearLogBeforeBuild->setObjectName(QString::fromUtf8("cb_ClearLogBeforeBuild"));

        verticalLayout_11->addWidget(cb_ClearLogBeforeBuild);


        verticalLayout_6->addWidget(groupBox_9);

        groupBox_3 = new QGroupBox(buildTab);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        verticalLayout_5 = new QVBoxLayout(groupBox_3);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        e_SourceDirectory = new QLineEdit(groupBox_3);
        e_SourceDirectory->setObjectName(QString::fromUtf8("e_SourceDirectory"));

        horizontalLayout_2->addWidget(e_SourceDirectory);

        btn_BrowseSource = new QPushButton(groupBox_3);
        btn_BrowseSource->setObjectName(QString::fromUtf8("btn_BrowseSource"));

        horizontalLayout_2->addWidget(btn_BrowseSource);


        verticalLayout_5->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label = new QLabel(groupBox_3);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_3->addWidget(label);

        cb_Platform = new QComboBox(groupBox_3);
        cb_Platform->setObjectName(QString::fromUtf8("cb_Platform"));

        horizontalLayout_3->addWidget(cb_Platform);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        verticalLayout_5->addLayout(horizontalLayout_3);


        verticalLayout_6->addWidget(groupBox_3);

        groupBox_4 = new QGroupBox(buildTab);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        gridLayout = new QGridLayout(groupBox_4);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_2 = new QLabel(groupBox_4);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        e_IncludeFirst = new QLineEdit(groupBox_4);
        e_IncludeFirst->setObjectName(QString::fromUtf8("e_IncludeFirst"));

        gridLayout->addWidget(e_IncludeFirst, 0, 1, 1, 1);

        btn_BrowseIncludeFirst = new QPushButton(groupBox_4);
        btn_BrowseIncludeFirst->setObjectName(QString::fromUtf8("btn_BrowseIncludeFirst"));

        gridLayout->addWidget(btn_BrowseIncludeFirst, 0, 2, 1, 1);

        label_3 = new QLabel(groupBox_4);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        e_IncludeLast = new QLineEdit(groupBox_4);
        e_IncludeLast->setObjectName(QString::fromUtf8("e_IncludeLast"));

        gridLayout->addWidget(e_IncludeLast, 1, 1, 1, 1);

        btn_BrowseIncludeLast = new QPushButton(groupBox_4);
        btn_BrowseIncludeLast->setObjectName(QString::fromUtf8("btn_BrowseIncludeLast"));

        gridLayout->addWidget(btn_BrowseIncludeLast, 1, 2, 1, 1);


        verticalLayout_6->addWidget(groupBox_4);

        groupBox_5 = new QGroupBox(buildTab);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        horizontalLayout_4 = new QHBoxLayout(groupBox_5);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        e_BuildDirectory = new QLineEdit(groupBox_5);
        e_BuildDirectory->setObjectName(QString::fromUtf8("e_BuildDirectory"));

        horizontalLayout_4->addWidget(e_BuildDirectory);

        btn_BrowseBuildDirectory = new QPushButton(groupBox_5);
        btn_BrowseBuildDirectory->setObjectName(QString::fromUtf8("btn_BrowseBuildDirectory"));

        horizontalLayout_4->addWidget(btn_BrowseBuildDirectory);


        verticalLayout_6->addWidget(groupBox_5);

        groupBox_6 = new QGroupBox(buildTab);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        horizontalLayout_5 = new QHBoxLayout(groupBox_6);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        e_InstallDirectory = new QLineEdit(groupBox_6);
        e_InstallDirectory->setObjectName(QString::fromUtf8("e_InstallDirectory"));

        horizontalLayout_5->addWidget(e_InstallDirectory);

        btn_BrowseInstallDirectory = new QPushButton(groupBox_6);
        btn_BrowseInstallDirectory->setObjectName(QString::fromUtf8("btn_BrowseInstallDirectory"));

        horizontalLayout_5->addWidget(btn_BrowseInstallDirectory);


        verticalLayout_6->addWidget(groupBox_6);

        tabWidget->addTab(buildTab, QString());
        toolsTab = new QWidget();
        toolsTab->setObjectName(QString::fromUtf8("toolsTab"));
        verticalLayout_8 = new QVBoxLayout(toolsTab);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        groupBox_7 = new QGroupBox(toolsTab);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        verticalLayout_7 = new QVBoxLayout(groupBox_7);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        e_ToolPath = new QLineEdit(groupBox_7);
        e_ToolPath->setObjectName(QString::fromUtf8("e_ToolPath"));

        verticalLayout_7->addWidget(e_ToolPath);


        verticalLayout_8->addWidget(groupBox_7);

        verticalSpacer_2 = new QSpacerItem(20, 265, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_8->addItem(verticalSpacer_2);

        tabWidget->addTab(toolsTab, QString());
        samplesTab = new QWidget();
        samplesTab->setObjectName(QString::fromUtf8("samplesTab"));
        verticalLayout_10 = new QVBoxLayout(samplesTab);
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setContentsMargins(11, 11, 11, 11);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        groupBox_8 = new QGroupBox(samplesTab);
        groupBox_8->setObjectName(QString::fromUtf8("groupBox_8"));
        verticalLayout_9 = new QVBoxLayout(groupBox_8);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        e_AppDirectory = new QLineEdit(groupBox_8);
        e_AppDirectory->setObjectName(QString::fromUtf8("e_AppDirectory"));

        horizontalLayout_6->addWidget(e_AppDirectory);

        btn_BrowseAppDirectory = new QPushButton(groupBox_8);
        btn_BrowseAppDirectory->setObjectName(QString::fromUtf8("btn_BrowseAppDirectory"));

        horizontalLayout_6->addWidget(btn_BrowseAppDirectory);


        verticalLayout_9->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_4 = new QLabel(groupBox_8);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_7->addWidget(label_4);

        cb_Programmer = new QComboBox(groupBox_8);
        cb_Programmer->setObjectName(QString::fromUtf8("cb_Programmer"));

        horizontalLayout_7->addWidget(cb_Programmer);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_3);


        verticalLayout_9->addLayout(horizontalLayout_7);

        cb_AbsolutePathInSamples = new QCheckBox(groupBox_8);
        cb_AbsolutePathInSamples->setObjectName(QString::fromUtf8("cb_AbsolutePathInSamples"));
        cb_AbsolutePathInSamples->setChecked(true);

        verticalLayout_9->addWidget(cb_AbsolutePathInSamples);


        verticalLayout_10->addWidget(groupBox_8);

        verticalSpacer_3 = new QSpacerItem(20, 230, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_10->addItem(verticalSpacer_3);

        tabWidget->addTab(samplesTab, QString());

        verticalLayout->addWidget(tabWidget);

        buttonBox = new QDialogButtonBox(SettingsDialogClass);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);

#ifndef QT_NO_SHORTCUT
        label->setBuddy(cb_Platform);
        label_2->setBuddy(e_IncludeFirst);
        label_3->setBuddy(e_IncludeLast);
        label_4->setBuddy(cb_Platform);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(tabWidget, e_RepositoryFile);
        QWidget::setTabOrder(e_RepositoryFile, btn_BrowseRepository);
        QWidget::setTabOrder(btn_BrowseRepository, cb_MultiConfig);
        QWidget::setTabOrder(cb_MultiConfig, cb_LogVerbose);
        QWidget::setTabOrder(cb_LogVerbose, cb_ClearLogBeforeBuild);
        QWidget::setTabOrder(cb_ClearLogBeforeBuild, e_SourceDirectory);
        QWidget::setTabOrder(e_SourceDirectory, btn_BrowseSource);
        QWidget::setTabOrder(btn_BrowseSource, cb_Platform);
        QWidget::setTabOrder(cb_Platform, e_IncludeFirst);
        QWidget::setTabOrder(e_IncludeFirst, btn_BrowseIncludeFirst);
        QWidget::setTabOrder(btn_BrowseIncludeFirst, e_IncludeLast);
        QWidget::setTabOrder(e_IncludeLast, btn_BrowseIncludeLast);
        QWidget::setTabOrder(btn_BrowseIncludeLast, e_BuildDirectory);
        QWidget::setTabOrder(e_BuildDirectory, btn_BrowseBuildDirectory);
        QWidget::setTabOrder(btn_BrowseBuildDirectory, e_InstallDirectory);
        QWidget::setTabOrder(e_InstallDirectory, btn_BrowseInstallDirectory);
        QWidget::setTabOrder(btn_BrowseInstallDirectory, e_ToolPath);
        QWidget::setTabOrder(e_ToolPath, e_AppDirectory);
        QWidget::setTabOrder(e_AppDirectory, btn_BrowseAppDirectory);
        QWidget::setTabOrder(btn_BrowseAppDirectory, cb_Programmer);
        QWidget::setTabOrder(cb_Programmer, cb_AbsolutePathInSamples);
        QWidget::setTabOrder(cb_AbsolutePathInSamples, buttonBox);

        retranslateUi(SettingsDialogClass);
        QObject::connect(buttonBox, SIGNAL(accepted()), SettingsDialogClass, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SettingsDialogClass, SLOT(reject()));
        QObject::connect(btn_BrowseAppDirectory, SIGNAL(clicked()), SettingsDialogClass, SLOT(browseFolder()));
        QObject::connect(btn_BrowseSource, SIGNAL(clicked()), SettingsDialogClass, SLOT(browseFolder()));
        QObject::connect(btn_BrowseIncludeFirst, SIGNAL(clicked()), SettingsDialogClass, SLOT(browseFolder()));
        QObject::connect(btn_BrowseIncludeLast, SIGNAL(clicked()), SettingsDialogClass, SLOT(browseFolder()));
        QObject::connect(btn_BrowseBuildDirectory, SIGNAL(clicked()), SettingsDialogClass, SLOT(browseFolder()));
        QObject::connect(btn_BrowseInstallDirectory, SIGNAL(clicked()), SettingsDialogClass, SLOT(browseFolder()));
        QObject::connect(btn_BrowseRepository, SIGNAL(clicked()), SettingsDialogClass, SLOT(browseFile()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SettingsDialogClass);
    } // setupUi

    void retranslateUi(QDialog *SettingsDialogClass)
    {
        SettingsDialogClass->setWindowTitle(QApplication::translate("SettingsDialogClass", "SettingsDialog", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("SettingsDialogClass", "Repository File", 0, QApplication::UnicodeUTF8));
        btn_BrowseRepository->setText(QApplication::translate("SettingsDialogClass", "Browse...", 0, QApplication::UnicodeUTF8));
        btn_BrowseRepository->setProperty("browseTarget", QVariant(QApplication::translate("SettingsDialogClass", "e_RepositoryFile", 0, QApplication::UnicodeUTF8)));
        btn_BrowseRepository->setProperty("fileFilter", QVariant(QApplication::translate("SettingsDialogClass", "*.nut", 0, QApplication::UnicodeUTF8)));
        groupBox_2->setTitle(QApplication::translate("SettingsDialogClass", "Configurations", 0, QApplication::UnicodeUTF8));
        cb_MultiConfig->setText(QApplication::translate("SettingsDialogClass", "Enable multiple configurations", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(repositoryTab), QApplication::translate("SettingsDialogClass", "Repository", 0, QApplication::UnicodeUTF8));
        groupBox_9->setTitle(QApplication::translate("SettingsDialogClass", "General", 0, QApplication::UnicodeUTF8));
        cb_LogVerbose->setText(QApplication::translate("SettingsDialogClass", "Verbose compiler log messages", 0, QApplication::UnicodeUTF8));
        cb_ClearLogBeforeBuild->setText(QApplication::translate("SettingsDialogClass", "Clear build log before builds", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("SettingsDialogClass", "Source Directory", 0, QApplication::UnicodeUTF8));
        btn_BrowseSource->setText(QApplication::translate("SettingsDialogClass", "Browse...", 0, QApplication::UnicodeUTF8));
        btn_BrowseSource->setProperty("browseTarget", QVariant(QApplication::translate("SettingsDialogClass", "e_SourceDirectory", 0, QApplication::UnicodeUTF8)));
        label->setText(QApplication::translate("SettingsDialogClass", "Platform", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("SettingsDialogClass", "Include Directories", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("SettingsDialogClass", "First", 0, QApplication::UnicodeUTF8));
        btn_BrowseIncludeFirst->setText(QApplication::translate("SettingsDialogClass", "Browse...", 0, QApplication::UnicodeUTF8));
        btn_BrowseIncludeFirst->setProperty("browseTarget", QVariant(QApplication::translate("SettingsDialogClass", "e_IncludeFirst", 0, QApplication::UnicodeUTF8)));
        label_3->setText(QApplication::translate("SettingsDialogClass", "Last", 0, QApplication::UnicodeUTF8));
        btn_BrowseIncludeLast->setText(QApplication::translate("SettingsDialogClass", "Browse...", 0, QApplication::UnicodeUTF8));
        btn_BrowseIncludeLast->setProperty("browseTarget", QVariant(QApplication::translate("SettingsDialogClass", "e_IncludeLast", 0, QApplication::UnicodeUTF8)));
        groupBox_5->setTitle(QApplication::translate("SettingsDialogClass", "Build Directory", 0, QApplication::UnicodeUTF8));
        btn_BrowseBuildDirectory->setText(QApplication::translate("SettingsDialogClass", "Browse...", 0, QApplication::UnicodeUTF8));
        btn_BrowseBuildDirectory->setProperty("browseTarget", QVariant(QApplication::translate("SettingsDialogClass", "e_BuildDirectory", 0, QApplication::UnicodeUTF8)));
        groupBox_6->setTitle(QApplication::translate("SettingsDialogClass", "Install Directory", 0, QApplication::UnicodeUTF8));
        btn_BrowseInstallDirectory->setText(QApplication::translate("SettingsDialogClass", "Browse...", 0, QApplication::UnicodeUTF8));
        btn_BrowseInstallDirectory->setProperty("browseTarget", QVariant(QApplication::translate("SettingsDialogClass", "e_InstallDirectory", 0, QApplication::UnicodeUTF8)));
        tabWidget->setTabText(tabWidget->indexOf(buildTab), QApplication::translate("SettingsDialogClass", "Build", 0, QApplication::UnicodeUTF8));
        groupBox_7->setTitle(QApplication::translate("SettingsDialogClass", "Tool Paths", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(toolsTab), QApplication::translate("SettingsDialogClass", "Tools", 0, QApplication::UnicodeUTF8));
        groupBox_8->setTitle(QApplication::translate("SettingsDialogClass", "Application Directory", 0, QApplication::UnicodeUTF8));
        btn_BrowseAppDirectory->setText(QApplication::translate("SettingsDialogClass", "Browse...", 0, QApplication::UnicodeUTF8));
        btn_BrowseAppDirectory->setProperty("browseTarget", QVariant(QApplication::translate("SettingsDialogClass", "e_AppDirectory", 0, QApplication::UnicodeUTF8)));
        label_4->setText(QApplication::translate("SettingsDialogClass", "Programmer", 0, QApplication::UnicodeUTF8));
        cb_AbsolutePathInSamples->setText(QApplication::translate("SettingsDialogClass", "Use absolute paths in generated Makefiles", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(samplesTab), QApplication::translate("SettingsDialogClass", "Samples", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SettingsDialogClass: public Ui_SettingsDialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSDIALOG_H
