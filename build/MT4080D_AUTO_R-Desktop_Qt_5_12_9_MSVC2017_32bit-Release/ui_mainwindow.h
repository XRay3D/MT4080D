/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "mytable.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QGroupBox *gbxSettings;
    QGridLayout *gridLayoutSettings;
    QLabel *label_1;
    QLabel *label_2;
    QSpinBox *sbxMeasCount;
    QSpinBox *sbxSkipMeas;
    QSpinBox *spinBox;
    QLabel *label;
    QPushButton *pbClearTable;
    QGroupBox *gbxConnection;
    QGridLayout *gridLayoutConnection;
    QLabel *label_5;
    QComboBox *cbxMt4080;
    QLabel *label_6;
    QComboBox *cbxRelay;
    QPushButton *pbPing;
    QLabel *label_rel;
    QPushButton *pbStartMeas;
    MyTable *tableView;
    QSlider *hsRelPos;
    QGroupBox *gbxMt4080;
    QGridLayout *gridLayout;
    QLineEdit *lineEdit_6;
    QLineEdit *lineEdit_1;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QLineEdit *lineEdit_7;
    QLineEdit *lineEdit_8;
    QLineEdit *lineEdit_9;
    QDoubleSpinBox *lineEdit_2;
    QDoubleSpinBox *lineEdit_5;
    QStatusBar *statusBar;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(494, 598);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(6, 6, 6, 6);
        gbxSettings = new QGroupBox(centralWidget);
        gbxSettings->setObjectName(QString::fromUtf8("gbxSettings"));
        gbxSettings->setCheckable(true);
        gridLayoutSettings = new QGridLayout(gbxSettings);
        gridLayoutSettings->setSpacing(6);
        gridLayoutSettings->setContentsMargins(11, 11, 11, 11);
        gridLayoutSettings->setObjectName(QString::fromUtf8("gridLayoutSettings"));
        gridLayoutSettings->setContentsMargins(6, 6, 6, 6);
        label_1 = new QLabel(gbxSettings);
        label_1->setObjectName(QString::fromUtf8("label_1"));
        label_1->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutSettings->addWidget(label_1, 0, 0, 1, 1);

        label_2 = new QLabel(gbxSettings);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutSettings->addWidget(label_2, 1, 0, 1, 1);

        sbxMeasCount = new QSpinBox(gbxSettings);
        sbxMeasCount->setObjectName(QString::fromUtf8("sbxMeasCount"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(sbxMeasCount->sizePolicy().hasHeightForWidth());
        sbxMeasCount->setSizePolicy(sizePolicy);
        sbxMeasCount->setMinimum(1);

        gridLayoutSettings->addWidget(sbxMeasCount, 1, 1, 1, 1);

        sbxSkipMeas = new QSpinBox(gbxSettings);
        sbxSkipMeas->setObjectName(QString::fromUtf8("sbxSkipMeas"));
        sizePolicy.setHeightForWidth(sbxSkipMeas->sizePolicy().hasHeightForWidth());
        sbxSkipMeas->setSizePolicy(sizePolicy);
        sbxSkipMeas->setMinimum(1);

        gridLayoutSettings->addWidget(sbxSkipMeas, 0, 1, 1, 1);

        spinBox = new QSpinBox(gbxSettings);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setMinimum(-9);
        spinBox->setMaximum(9);

        gridLayoutSettings->addWidget(spinBox, 2, 1, 1, 1);

        label = new QLabel(gbxSettings);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayoutSettings->addWidget(label, 2, 0, 1, 1);


        gridLayout_2->addWidget(gbxSettings, 1, 0, 1, 2);

        pbClearTable = new QPushButton(centralWidget);
        pbClearTable->setObjectName(QString::fromUtf8("pbClearTable"));

        gridLayout_2->addWidget(pbClearTable, 6, 0, 1, 2);

        gbxConnection = new QGroupBox(centralWidget);
        gbxConnection->setObjectName(QString::fromUtf8("gbxConnection"));
        gbxConnection->setCheckable(true);
        gridLayoutConnection = new QGridLayout(gbxConnection);
        gridLayoutConnection->setSpacing(6);
        gridLayoutConnection->setContentsMargins(11, 11, 11, 11);
        gridLayoutConnection->setObjectName(QString::fromUtf8("gridLayoutConnection"));
        gridLayoutConnection->setContentsMargins(6, 6, 6, 6);
        label_5 = new QLabel(gbxConnection);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutConnection->addWidget(label_5, 0, 0, 1, 1);

        cbxMt4080 = new QComboBox(gbxConnection);
        cbxMt4080->setObjectName(QString::fromUtf8("cbxMt4080"));
        sizePolicy.setHeightForWidth(cbxMt4080->sizePolicy().hasHeightForWidth());
        cbxMt4080->setSizePolicy(sizePolicy);

        gridLayoutConnection->addWidget(cbxMt4080, 0, 1, 1, 1);

        label_6 = new QLabel(gbxConnection);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayoutConnection->addWidget(label_6, 1, 0, 1, 1);

        cbxRelay = new QComboBox(gbxConnection);
        cbxRelay->setObjectName(QString::fromUtf8("cbxRelay"));
        sizePolicy.setHeightForWidth(cbxRelay->sizePolicy().hasHeightForWidth());
        cbxRelay->setSizePolicy(sizePolicy);

        gridLayoutConnection->addWidget(cbxRelay, 1, 1, 1, 1);

        pbPing = new QPushButton(gbxConnection);
        pbPing->setObjectName(QString::fromUtf8("pbPing"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/res/image2.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbPing->setIcon(icon);
        pbPing->setCheckable(true);

        gridLayoutConnection->addWidget(pbPing, 2, 0, 1, 2);


        gridLayout_2->addWidget(gbxConnection, 0, 0, 1, 2);

        label_rel = new QLabel(centralWidget);
        label_rel->setObjectName(QString::fromUtf8("label_rel"));

        gridLayout_2->addWidget(label_rel, 4, 0, 1, 1);

        pbStartMeas = new QPushButton(centralWidget);
        pbStartMeas->setObjectName(QString::fromUtf8("pbStartMeas"));
        pbStartMeas->setIcon(icon);
        pbStartMeas->setCheckable(true);

        gridLayout_2->addWidget(pbStartMeas, 5, 0, 1, 2);

        tableView = new MyTable(centralWidget);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        gridLayout_2->addWidget(tableView, 7, 0, 1, 2);

        hsRelPos = new QSlider(centralWidget);
        hsRelPos->setObjectName(QString::fromUtf8("hsRelPos"));
        hsRelPos->setMinimum(1);
        hsRelPos->setMaximum(29);
        hsRelPos->setPageStep(1);
        hsRelPos->setOrientation(Qt::Horizontal);
        hsRelPos->setTickPosition(QSlider::TicksBothSides);
        hsRelPos->setTickInterval(1);

        gridLayout_2->addWidget(hsRelPos, 4, 1, 1, 1);

        gbxMt4080 = new QGroupBox(centralWidget);
        gbxMt4080->setObjectName(QString::fromUtf8("gbxMt4080"));
        gbxMt4080->setCheckable(true);
        gridLayout = new QGridLayout(gbxMt4080);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(6, 6, 6, 6);
        lineEdit_6 = new QLineEdit(gbxMt4080);
        lineEdit_6->setObjectName(QString::fromUtf8("lineEdit_6"));
        lineEdit_6->setAlignment(Qt::AlignCenter);
        lineEdit_6->setReadOnly(true);

        gridLayout->addWidget(lineEdit_6, 3, 2, 1, 1);

        lineEdit_1 = new QLineEdit(gbxMt4080);
        lineEdit_1->setObjectName(QString::fromUtf8("lineEdit_1"));
        lineEdit_1->setAlignment(Qt::AlignCenter);
        lineEdit_1->setReadOnly(true);

        gridLayout->addWidget(lineEdit_1, 2, 0, 1, 1);

        lineEdit_3 = new QLineEdit(gbxMt4080);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setAlignment(Qt::AlignCenter);
        lineEdit_3->setReadOnly(true);

        gridLayout->addWidget(lineEdit_3, 2, 2, 1, 1);

        lineEdit_4 = new QLineEdit(gbxMt4080);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));
        lineEdit_4->setAlignment(Qt::AlignCenter);
        lineEdit_4->setReadOnly(true);

        gridLayout->addWidget(lineEdit_4, 3, 0, 1, 1);

        lineEdit_7 = new QLineEdit(gbxMt4080);
        lineEdit_7->setObjectName(QString::fromUtf8("lineEdit_7"));
        lineEdit_7->setAlignment(Qt::AlignCenter);
        lineEdit_7->setReadOnly(true);

        gridLayout->addWidget(lineEdit_7, 4, 0, 1, 1);

        lineEdit_8 = new QLineEdit(gbxMt4080);
        lineEdit_8->setObjectName(QString::fromUtf8("lineEdit_8"));
        lineEdit_8->setAlignment(Qt::AlignCenter);
        lineEdit_8->setReadOnly(true);

        gridLayout->addWidget(lineEdit_8, 4, 1, 1, 1);

        lineEdit_9 = new QLineEdit(gbxMt4080);
        lineEdit_9->setObjectName(QString::fromUtf8("lineEdit_9"));
        lineEdit_9->setAlignment(Qt::AlignCenter);
        lineEdit_9->setReadOnly(true);

        gridLayout->addWidget(lineEdit_9, 4, 2, 1, 1);

        lineEdit_2 = new QDoubleSpinBox(gbxMt4080);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setAlignment(Qt::AlignCenter);
        lineEdit_2->setReadOnly(true);
        lineEdit_2->setButtonSymbols(QAbstractSpinBox::NoButtons);
        lineEdit_2->setDecimals(6);
        lineEdit_2->setMinimum(-1000000.000000000000000);
        lineEdit_2->setMaximum(1000000.000000000000000);

        gridLayout->addWidget(lineEdit_2, 2, 1, 1, 1);

        lineEdit_5 = new QDoubleSpinBox(gbxMt4080);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));
        lineEdit_5->setAlignment(Qt::AlignCenter);
        lineEdit_5->setReadOnly(true);
        lineEdit_5->setButtonSymbols(QAbstractSpinBox::NoButtons);
        lineEdit_5->setDecimals(6);
        lineEdit_5->setMinimum(-1000000.000000000000000);
        lineEdit_5->setMaximum(1000000.000000000000000);

        gridLayout->addWidget(lineEdit_5, 3, 1, 1, 1);


        gridLayout_2->addWidget(gbxMt4080, 3, 0, 1, 2);

        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 494, 21));
        MainWindow->setMenuBar(menuBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        gbxSettings->setTitle(QApplication::translate("MainWindow", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213 \320\270\320\267\320\274\320\265\321\200\320\265\320\275\320\270\321\217:", nullptr));
        label_1->setText(QApplication::translate("MainWindow", "\320\232\320\276\320\273-\320\262\320\276 \320\277\321\200\320\276\321\203\321\211\320\265\320\275\320\275\321\213\321\205 \321\202\320\276\321\207\320\265\320\272:", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "\320\232\320\276\320\273-\320\262\320\276 \320\270\320\267\320\274\320\265\321\200\320\265\320\275\320\275\321\213\321\205 \321\202\320\276\321\207\320\265\320\272:", nullptr));
        label->setText(QApplication::translate("MainWindow", "x 10 ^ n", nullptr));
        pbClearTable->setText(QApplication::translate("MainWindow", "\320\236\321\202\321\207\320\270\321\201\321\202\320\270\321\202\321\214 \321\202\320\260\320\261\320\273\320\270\321\206\321\203", nullptr));
        gbxConnection->setTitle(QApplication::translate("MainWindow", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\260 \321\201\320\262\321\217\320\267\320\270:", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "MT4080D:", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "\320\232\320\276\320\274\320\274\321\203\321\202\320\260\321\202\320\276\321\200:", nullptr));
        pbPing->setText(QApplication::translate("MainWindow", "\320\235\320\260\321\207\320\260\321\202\321\214 \320\276\320\277\321\200\320\276\321\201", nullptr));
        label_rel->setText(QApplication::translate("MainWindow", "\320\237\320\276\320\267. 1:", nullptr));
        pbStartMeas->setText(QApplication::translate("MainWindow", "\320\235\320\260\321\207\320\260\321\202\321\214 \320\270\320\267\320\274\320\265\321\200\320\265\320\275\320\270\320\265", nullptr));
        gbxMt4080->setTitle(QApplication::translate("MainWindow", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213 MT4080D", nullptr));
        Q_UNUSED(MainWindow);
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
