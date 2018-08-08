/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBoxConnection;
    QGridLayout *gridLayoutConnection;
    QPushButton *pushButton;
    QComboBox *comboBoxMt4080;
    QLabel *label_5;
    QPushButton *pushButtonStartStopMeas;
    QGroupBox *groupBoxSettings;
    QFormLayout *formLayout;
    QLabel *lbSettings_1;
    QDoubleSpinBox *dsbMinErr;
    QLabel *lbSettings_2;
    QDoubleSpinBox *dsbMin;
    QLabel *lbSettings_3;
    QDoubleSpinBox *dsbMax;
    QLabel *lbSettings_4;
    QDoubleSpinBox *dsbMaxErr;
    QLabel *label;
    QSpinBox *sbScale;
    QGroupBox *groupBox_mt4080;
    QGridLayout *gridLayout;
    QLineEdit *lineEdit_6;
    QLineEdit *lineEdit_1;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QLineEdit *lineEdit_7;
    QLineEdit *lineEdit_8;
    QLineEdit *lineEdit_9;
    QDoubleSpinBox *lineEdit_5;
    QDoubleSpinBox *lineEdit_2;
    QPushButton *pushButton_clearTable;
    QListWidget *listWidget;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(274, 645);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        groupBoxConnection = new QGroupBox(centralWidget);
        groupBoxConnection->setObjectName(QStringLiteral("groupBoxConnection"));
        groupBoxConnection->setCheckable(true);
        gridLayoutConnection = new QGridLayout(groupBoxConnection);
        gridLayoutConnection->setSpacing(6);
        gridLayoutConnection->setContentsMargins(11, 11, 11, 11);
        gridLayoutConnection->setObjectName(QStringLiteral("gridLayoutConnection"));
        gridLayoutConnection->setContentsMargins(6, 6, 6, 6);
        pushButton = new QPushButton(groupBoxConnection);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/res/image2.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton->setIcon(icon);
        pushButton->setCheckable(true);

        gridLayoutConnection->addWidget(pushButton, 1, 0, 1, 2);

        comboBoxMt4080 = new QComboBox(groupBoxConnection);
        comboBoxMt4080->setObjectName(QStringLiteral("comboBoxMt4080"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comboBoxMt4080->sizePolicy().hasHeightForWidth());
        comboBoxMt4080->setSizePolicy(sizePolicy);

        gridLayoutConnection->addWidget(comboBoxMt4080, 0, 1, 1, 1);

        label_5 = new QLabel(groupBoxConnection);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutConnection->addWidget(label_5, 0, 0, 1, 1);

        pushButtonStartStopMeas = new QPushButton(groupBoxConnection);
        pushButtonStartStopMeas->setObjectName(QStringLiteral("pushButtonStartStopMeas"));
        pushButtonStartStopMeas->setIcon(icon);
        pushButtonStartStopMeas->setCheckable(true);

        gridLayoutConnection->addWidget(pushButtonStartStopMeas, 2, 0, 1, 2);


        verticalLayout->addWidget(groupBoxConnection);

        groupBoxSettings = new QGroupBox(centralWidget);
        groupBoxSettings->setObjectName(QStringLiteral("groupBoxSettings"));
        groupBoxSettings->setCheckable(true);
        formLayout = new QFormLayout(groupBoxSettings);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setLabelAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        formLayout->setContentsMargins(6, 6, 6, 6);
        lbSettings_1 = new QLabel(groupBoxSettings);
        lbSettings_1->setObjectName(QStringLiteral("lbSettings_1"));
        lbSettings_1->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(0, QFormLayout::LabelRole, lbSettings_1);

        dsbMinErr = new QDoubleSpinBox(groupBoxSettings);
        dsbMinErr->setObjectName(QStringLiteral("dsbMinErr"));
        dsbMinErr->setReadOnly(false);
        dsbMinErr->setButtonSymbols(QAbstractSpinBox::NoButtons);
        dsbMinErr->setDecimals(3);
        dsbMinErr->setMaximum(1e+6);

        formLayout->setWidget(0, QFormLayout::FieldRole, dsbMinErr);

        lbSettings_2 = new QLabel(groupBoxSettings);
        lbSettings_2->setObjectName(QStringLiteral("lbSettings_2"));
        lbSettings_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(1, QFormLayout::LabelRole, lbSettings_2);

        dsbMin = new QDoubleSpinBox(groupBoxSettings);
        dsbMin->setObjectName(QStringLiteral("dsbMin"));
        dsbMin->setReadOnly(false);
        dsbMin->setButtonSymbols(QAbstractSpinBox::NoButtons);
        dsbMin->setDecimals(3);
        dsbMin->setMaximum(1e+6);

        formLayout->setWidget(1, QFormLayout::FieldRole, dsbMin);

        lbSettings_3 = new QLabel(groupBoxSettings);
        lbSettings_3->setObjectName(QStringLiteral("lbSettings_3"));
        lbSettings_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(2, QFormLayout::LabelRole, lbSettings_3);

        dsbMax = new QDoubleSpinBox(groupBoxSettings);
        dsbMax->setObjectName(QStringLiteral("dsbMax"));
        dsbMax->setReadOnly(false);
        dsbMax->setButtonSymbols(QAbstractSpinBox::NoButtons);
        dsbMax->setDecimals(3);
        dsbMax->setMaximum(1e+6);

        formLayout->setWidget(2, QFormLayout::FieldRole, dsbMax);

        lbSettings_4 = new QLabel(groupBoxSettings);
        lbSettings_4->setObjectName(QStringLiteral("lbSettings_4"));
        lbSettings_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(3, QFormLayout::LabelRole, lbSettings_4);

        dsbMaxErr = new QDoubleSpinBox(groupBoxSettings);
        dsbMaxErr->setObjectName(QStringLiteral("dsbMaxErr"));
        dsbMaxErr->setReadOnly(false);
        dsbMaxErr->setButtonSymbols(QAbstractSpinBox::NoButtons);
        dsbMaxErr->setDecimals(3);
        dsbMaxErr->setMaximum(1e+6);

        formLayout->setWidget(3, QFormLayout::FieldRole, dsbMaxErr);

        label = new QLabel(groupBoxSettings);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label);

        sbScale = new QSpinBox(groupBoxSettings);
        sbScale->setObjectName(QStringLiteral("sbScale"));
        sbScale->setButtonSymbols(QAbstractSpinBox::NoButtons);
        sbScale->setMinimum(-10);
        sbScale->setMaximum(10);

        formLayout->setWidget(4, QFormLayout::FieldRole, sbScale);


        verticalLayout->addWidget(groupBoxSettings);

        groupBox_mt4080 = new QGroupBox(centralWidget);
        groupBox_mt4080->setObjectName(QStringLiteral("groupBox_mt4080"));
        groupBox_mt4080->setCheckable(true);
        gridLayout = new QGridLayout(groupBox_mt4080);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(6, 6, 6, 6);
        lineEdit_6 = new QLineEdit(groupBox_mt4080);
        lineEdit_6->setObjectName(QStringLiteral("lineEdit_6"));
        lineEdit_6->setMaximumSize(QSize(50, 16777215));
        lineEdit_6->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lineEdit_6, 3, 2, 1, 1);

        lineEdit_1 = new QLineEdit(groupBox_mt4080);
        lineEdit_1->setObjectName(QStringLiteral("lineEdit_1"));
        lineEdit_1->setMaximumSize(QSize(50, 16777215));
        lineEdit_1->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lineEdit_1, 2, 0, 1, 1);

        lineEdit_3 = new QLineEdit(groupBox_mt4080);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setMaximumSize(QSize(50, 16777215));
        lineEdit_3->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lineEdit_3, 2, 2, 1, 1);

        lineEdit_4 = new QLineEdit(groupBox_mt4080);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));
        lineEdit_4->setMaximumSize(QSize(50, 16777215));
        lineEdit_4->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lineEdit_4, 3, 0, 1, 1);

        lineEdit_7 = new QLineEdit(groupBox_mt4080);
        lineEdit_7->setObjectName(QStringLiteral("lineEdit_7"));
        lineEdit_7->setMaximumSize(QSize(50, 16777215));
        lineEdit_7->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lineEdit_7, 4, 0, 1, 1);

        lineEdit_8 = new QLineEdit(groupBox_mt4080);
        lineEdit_8->setObjectName(QStringLiteral("lineEdit_8"));
        lineEdit_8->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lineEdit_8, 4, 1, 1, 1);

        lineEdit_9 = new QLineEdit(groupBox_mt4080);
        lineEdit_9->setObjectName(QStringLiteral("lineEdit_9"));
        lineEdit_9->setMaximumSize(QSize(50, 16777215));
        lineEdit_9->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lineEdit_9, 4, 2, 1, 1);

        lineEdit_5 = new QDoubleSpinBox(groupBox_mt4080);
        lineEdit_5->setObjectName(QStringLiteral("lineEdit_5"));
        lineEdit_5->setAlignment(Qt::AlignCenter);
        lineEdit_5->setReadOnly(true);
        lineEdit_5->setButtonSymbols(QAbstractSpinBox::NoButtons);
        lineEdit_5->setDecimals(3);
        lineEdit_5->setMaximum(1);

        gridLayout->addWidget(lineEdit_5, 3, 1, 1, 1);

        lineEdit_2 = new QDoubleSpinBox(groupBox_mt4080);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineEdit_2->sizePolicy().hasHeightForWidth());
        lineEdit_2->setSizePolicy(sizePolicy1);
        lineEdit_2->setAlignment(Qt::AlignCenter);
        lineEdit_2->setReadOnly(true);
        lineEdit_2->setButtonSymbols(QAbstractSpinBox::NoButtons);
        lineEdit_2->setDecimals(3);
        lineEdit_2->setMaximum(1);

        gridLayout->addWidget(lineEdit_2, 2, 1, 1, 1);


        verticalLayout->addWidget(groupBox_mt4080);

        pushButton_clearTable = new QPushButton(centralWidget);
        pushButton_clearTable->setObjectName(QStringLiteral("pushButton_clearTable"));

        verticalLayout->addWidget(pushButton_clearTable);

        listWidget = new QListWidget(centralWidget);
        listWidget->setObjectName(QStringLiteral("listWidget"));

        verticalLayout->addWidget(listWidget);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 274, 21));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        groupBoxConnection->setTitle(QApplication::translate("MainWindow", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\260 \321\201\320\262\321\217\320\267\320\270:", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "\320\235\320\260\321\207\320\260\321\202\321\214 \320\276\320\277\321\200\320\276\321\201", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "MT4080D:", Q_NULLPTR));
        pushButtonStartStopMeas->setText(QApplication::translate("MainWindow", "\320\235\320\260\321\207\320\260\321\202\321\214 \320\270\320\267\320\274\320\265\321\200\320\265\320\275\320\270\320\265", Q_NULLPTR));
        groupBoxSettings->setTitle(QApplication::translate("MainWindow", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213 \320\270\320\267\320\274\320\265\321\200\320\265\320\275\320\270\321\217:", Q_NULLPTR));
        lbSettings_1->setText(QApplication::translate("MainWindow", "Min Error:", Q_NULLPTR));
        lbSettings_2->setText(QApplication::translate("MainWindow", "Min:", Q_NULLPTR));
        lbSettings_3->setText(QApplication::translate("MainWindow", "Max:", Q_NULLPTR));
        lbSettings_4->setText(QApplication::translate("MainWindow", "Max Error:", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Scale:", Q_NULLPTR));
        groupBox_mt4080->setTitle(QApplication::translate("MainWindow", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213 MT4080D", Q_NULLPTR));
        pushButton_clearTable->setText(QApplication::translate("MainWindow", "\320\236\321\202\321\207\320\270\321\201\321\202\320\270\321\202\321\214 \321\202\320\260\320\261\320\273\320\270\321\206\321\203", Q_NULLPTR));
        Q_UNUSED(MainWindow);
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
