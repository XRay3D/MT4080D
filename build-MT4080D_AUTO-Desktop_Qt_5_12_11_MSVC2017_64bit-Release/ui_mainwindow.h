/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
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
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "chekableTableView/tableview.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *gbxConnection;
    QFormLayout *formLayout_2;
    QLabel *label_5;
    QComboBox *cbxMt4080;
    QLabel *label_6;
    QComboBox *cbxRelay;
    QPushButton *pbPing;
    QGroupBox *gbxSettings;
    QFormLayout *formLayout;
    QLabel *label_1;
    QSpinBox *sbxSkipMeas;
    QLabel *label_2;
    QSpinBox *sbxMeasCount;
    QLabel *label;
    QSpinBox *spinBox;
    QGroupBox *gbxMt4080;
    QGridLayout *gridLayout;
    QLineEdit *lineEdit_1;
    QDoubleSpinBox *lineEdit_2;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QDoubleSpinBox *lineEdit_5;
    QLineEdit *lineEdit_6;
    QLineEdit *lineEdit_7;
    QLineEdit *lineEdit_8;
    QLineEdit *lineEdit_9;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_rel;
    QSlider *hsRelPos;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QPushButton *pbStartMeas;
    QPushButton *pbClearTable;
    TableView *tableView;
    QStatusBar *statusBar;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(494, 644);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(6, 6, 6, 6);
        gbxConnection = new QGroupBox(centralWidget);
        gbxConnection->setObjectName(QString::fromUtf8("gbxConnection"));
        gbxConnection->setCheckable(true);
        formLayout_2 = new QFormLayout(gbxConnection);
        formLayout_2->setSpacing(6);
        formLayout_2->setContentsMargins(11, 11, 11, 11);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        formLayout_2->setLabelAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        formLayout_2->setContentsMargins(6, 6, 6, 6);
        label_5 = new QLabel(gbxConnection);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_5);

        cbxMt4080 = new QComboBox(gbxConnection);
        cbxMt4080->setObjectName(QString::fromUtf8("cbxMt4080"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(cbxMt4080->sizePolicy().hasHeightForWidth());
        cbxMt4080->setSizePolicy(sizePolicy);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, cbxMt4080);

        label_6 = new QLabel(gbxConnection);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_6);

        cbxRelay = new QComboBox(gbxConnection);
        cbxRelay->setObjectName(QString::fromUtf8("cbxRelay"));
        sizePolicy.setHeightForWidth(cbxRelay->sizePolicy().hasHeightForWidth());
        cbxRelay->setSizePolicy(sizePolicy);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, cbxRelay);

        pbPing = new QPushButton(gbxConnection);
        pbPing->setObjectName(QString::fromUtf8("pbPing"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/res/image2.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbPing->setIcon(icon);
        pbPing->setCheckable(true);

        formLayout_2->setWidget(2, QFormLayout::SpanningRole, pbPing);


        verticalLayout_2->addWidget(gbxConnection);

        gbxSettings = new QGroupBox(centralWidget);
        gbxSettings->setObjectName(QString::fromUtf8("gbxSettings"));
        gbxSettings->setCheckable(true);
        formLayout = new QFormLayout(gbxSettings);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setLabelAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        formLayout->setContentsMargins(6, 6, 6, 6);
        label_1 = new QLabel(gbxSettings);
        label_1->setObjectName(QString::fromUtf8("label_1"));
        label_1->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(0, QFormLayout::LabelRole, label_1);

        sbxSkipMeas = new QSpinBox(gbxSettings);
        sbxSkipMeas->setObjectName(QString::fromUtf8("sbxSkipMeas"));
        sizePolicy.setHeightForWidth(sbxSkipMeas->sizePolicy().hasHeightForWidth());
        sbxSkipMeas->setSizePolicy(sizePolicy);
        sbxSkipMeas->setMinimum(1);

        formLayout->setWidget(0, QFormLayout::FieldRole, sbxSkipMeas);

        label_2 = new QLabel(gbxSettings);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        sbxMeasCount = new QSpinBox(gbxSettings);
        sbxMeasCount->setObjectName(QString::fromUtf8("sbxMeasCount"));
        sizePolicy.setHeightForWidth(sbxMeasCount->sizePolicy().hasHeightForWidth());
        sbxMeasCount->setSizePolicy(sizePolicy);
        sbxMeasCount->setMinimum(1);

        formLayout->setWidget(1, QFormLayout::FieldRole, sbxMeasCount);

        label = new QLabel(gbxSettings);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label);

        spinBox = new QSpinBox(gbxSettings);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setMinimum(-9);
        spinBox->setMaximum(9);

        formLayout->setWidget(2, QFormLayout::FieldRole, spinBox);


        verticalLayout_2->addWidget(gbxSettings);

        gbxMt4080 = new QGroupBox(centralWidget);
        gbxMt4080->setObjectName(QString::fromUtf8("gbxMt4080"));
        gbxMt4080->setCheckable(true);
        gridLayout = new QGridLayout(gbxMt4080);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(6, 6, 6, 6);
        lineEdit_1 = new QLineEdit(gbxMt4080);
        lineEdit_1->setObjectName(QString::fromUtf8("lineEdit_1"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineEdit_1->sizePolicy().hasHeightForWidth());
        lineEdit_1->setSizePolicy(sizePolicy1);
        lineEdit_1->setAlignment(Qt::AlignCenter);
        lineEdit_1->setReadOnly(true);

        gridLayout->addWidget(lineEdit_1, 0, 0, 1, 1);

        lineEdit_2 = new QDoubleSpinBox(gbxMt4080);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        sizePolicy1.setHeightForWidth(lineEdit_2->sizePolicy().hasHeightForWidth());
        lineEdit_2->setSizePolicy(sizePolicy1);
        lineEdit_2->setAlignment(Qt::AlignCenter);
        lineEdit_2->setReadOnly(true);
        lineEdit_2->setButtonSymbols(QAbstractSpinBox::NoButtons);
        lineEdit_2->setDecimals(6);
        lineEdit_2->setMinimum(-1000000.000000000000000);
        lineEdit_2->setMaximum(1000000.000000000000000);

        gridLayout->addWidget(lineEdit_2, 0, 1, 1, 1);

        lineEdit_3 = new QLineEdit(gbxMt4080);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        sizePolicy1.setHeightForWidth(lineEdit_3->sizePolicy().hasHeightForWidth());
        lineEdit_3->setSizePolicy(sizePolicy1);
        lineEdit_3->setAlignment(Qt::AlignCenter);
        lineEdit_3->setReadOnly(true);

        gridLayout->addWidget(lineEdit_3, 0, 2, 1, 1);

        lineEdit_4 = new QLineEdit(gbxMt4080);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));
        sizePolicy1.setHeightForWidth(lineEdit_4->sizePolicy().hasHeightForWidth());
        lineEdit_4->setSizePolicy(sizePolicy1);
        lineEdit_4->setAlignment(Qt::AlignCenter);
        lineEdit_4->setReadOnly(true);

        gridLayout->addWidget(lineEdit_4, 1, 0, 1, 1);

        lineEdit_5 = new QDoubleSpinBox(gbxMt4080);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));
        sizePolicy1.setHeightForWidth(lineEdit_5->sizePolicy().hasHeightForWidth());
        lineEdit_5->setSizePolicy(sizePolicy1);
        lineEdit_5->setAlignment(Qt::AlignCenter);
        lineEdit_5->setReadOnly(true);
        lineEdit_5->setButtonSymbols(QAbstractSpinBox::NoButtons);
        lineEdit_5->setDecimals(6);
        lineEdit_5->setMinimum(-1000000.000000000000000);
        lineEdit_5->setMaximum(1000000.000000000000000);

        gridLayout->addWidget(lineEdit_5, 1, 1, 1, 1);

        lineEdit_6 = new QLineEdit(gbxMt4080);
        lineEdit_6->setObjectName(QString::fromUtf8("lineEdit_6"));
        sizePolicy1.setHeightForWidth(lineEdit_6->sizePolicy().hasHeightForWidth());
        lineEdit_6->setSizePolicy(sizePolicy1);
        lineEdit_6->setAlignment(Qt::AlignCenter);
        lineEdit_6->setReadOnly(true);

        gridLayout->addWidget(lineEdit_6, 1, 2, 1, 1);

        lineEdit_7 = new QLineEdit(gbxMt4080);
        lineEdit_7->setObjectName(QString::fromUtf8("lineEdit_7"));
        sizePolicy1.setHeightForWidth(lineEdit_7->sizePolicy().hasHeightForWidth());
        lineEdit_7->setSizePolicy(sizePolicy1);
        lineEdit_7->setAlignment(Qt::AlignCenter);
        lineEdit_7->setReadOnly(true);

        gridLayout->addWidget(lineEdit_7, 2, 0, 1, 1);

        lineEdit_8 = new QLineEdit(gbxMt4080);
        lineEdit_8->setObjectName(QString::fromUtf8("lineEdit_8"));
        sizePolicy1.setHeightForWidth(lineEdit_8->sizePolicy().hasHeightForWidth());
        lineEdit_8->setSizePolicy(sizePolicy1);
        lineEdit_8->setAlignment(Qt::AlignCenter);
        lineEdit_8->setReadOnly(true);

        gridLayout->addWidget(lineEdit_8, 2, 1, 1, 1);

        lineEdit_9 = new QLineEdit(gbxMt4080);
        lineEdit_9->setObjectName(QString::fromUtf8("lineEdit_9"));
        sizePolicy1.setHeightForWidth(lineEdit_9->sizePolicy().hasHeightForWidth());
        lineEdit_9->setSizePolicy(sizePolicy1);
        lineEdit_9->setAlignment(Qt::AlignCenter);
        lineEdit_9->setReadOnly(true);

        gridLayout->addWidget(lineEdit_9, 2, 2, 1, 1);

        gridLayout->setColumnStretch(0, 1);
        gridLayout->setColumnStretch(1, 1);
        gridLayout->setColumnStretch(2, 1);

        verticalLayout_2->addWidget(gbxMt4080);

        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        horizontalLayout = new QHBoxLayout(groupBox_2);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(6, 6, 6, 6);
        label_rel = new QLabel(groupBox_2);
        label_rel->setObjectName(QString::fromUtf8("label_rel"));
        label_rel->setMinimumSize(QSize(50, 0));
        label_rel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(label_rel);

        hsRelPos = new QSlider(groupBox_2);
        hsRelPos->setObjectName(QString::fromUtf8("hsRelPos"));
        hsRelPos->setMinimum(1);
        hsRelPos->setMaximum(29);
        hsRelPos->setPageStep(1);
        hsRelPos->setOrientation(Qt::Horizontal);
        hsRelPos->setTickPosition(QSlider::TicksBothSides);
        hsRelPos->setTickInterval(1);

        horizontalLayout->addWidget(hsRelPos);


        verticalLayout_2->addWidget(groupBox_2);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(6, 6, 6, 6);
        pbStartMeas = new QPushButton(groupBox);
        pbStartMeas->setObjectName(QString::fromUtf8("pbStartMeas"));
        pbStartMeas->setIcon(icon);
        pbStartMeas->setCheckable(true);

        verticalLayout->addWidget(pbStartMeas);

        pbClearTable = new QPushButton(groupBox);
        pbClearTable->setObjectName(QString::fromUtf8("pbClearTable"));

        verticalLayout->addWidget(pbClearTable);

        tableView = new TableView(groupBox);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        verticalLayout->addWidget(tableView);


        verticalLayout_2->addWidget(groupBox);

        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 494, 20));
        MainWindow->setMenuBar(menuBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        gbxConnection->setTitle(QApplication::translate("MainWindow", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\260 \321\201\320\262\321\217\320\267\320\270:", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "MT4080D:", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "\320\232\320\276\320\274\320\274\321\203\321\202\320\260\321\202\320\276\321\200:", nullptr));
        pbPing->setText(QApplication::translate("MainWindow", "\320\235\320\260\321\207\320\260\321\202\321\214 \320\276\320\277\321\200\320\276\321\201", nullptr));
        gbxSettings->setTitle(QApplication::translate("MainWindow", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213 \320\270\320\267\320\274\320\265\321\200\320\265\320\275\320\270\321\217:", nullptr));
        label_1->setText(QApplication::translate("MainWindow", "\320\232\320\276\320\273-\320\262\320\276 \320\277\321\200\320\276\321\203\321\211\320\265\320\275\320\275\321\213\321\205 \321\202\320\276\321\207\320\265\320\272:", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "\320\232\320\276\320\273-\320\262\320\276 \320\270\320\267\320\274\320\265\321\200\320\265\320\275\320\275\321\213\321\205 \321\202\320\276\321\207\320\265\320\272:", nullptr));
        label->setText(QApplication::translate("MainWindow", "x 10 ^ n:", nullptr));
        gbxMt4080->setTitle(QApplication::translate("MainWindow", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213 MT4080D", nullptr));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "\320\240\320\265\320\273\320\265 ", nullptr));
        label_rel->setText(QApplication::translate("MainWindow", "\320\237\320\276\320\267. 1:", nullptr));
        groupBox->setTitle(QApplication::translate("MainWindow", "\320\230\320\267\320\274\320\265\321\200\320\265\320\275\320\270\321\217", nullptr));
        pbStartMeas->setText(QApplication::translate("MainWindow", "\320\235\320\260\321\207\320\260\321\202\321\214 \320\270\320\267\320\274\320\265\321\200\320\265\320\275\320\270\320\265", nullptr));
        pbClearTable->setText(QApplication::translate("MainWindow", "\320\236\321\202\321\207\320\270\321\201\321\202\320\270\321\202\321\214 \320\262\321\213\320\261\321\200\320\260\320\275\320\275\320\276\320\265", nullptr));
        Q_UNUSED(MainWindow);
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
