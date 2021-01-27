/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
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
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
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
    QCheckBox *checkBox;
    QPushButton *pushButton;
    QComboBox *comboBoxMt4080;
    QPushButton *pushButtonStartStopMeas;
    QGroupBox *groupBoxSettings;
    QGridLayout *gridLayout_3;
    QDoubleSpinBox *dsbMinErr;
    QDoubleSpinBox *dsbMin;
    QLabel *lbSettings_3;
    QLabel *label;
    QLabel *lbSettings_4;
    QLabel *lbSettings_2;
    QLabel *lbSettings_1;
    QSpinBox *sbScale;
    QDoubleSpinBox *dsbMax;
    QDoubleSpinBox *dsbMaxErr;
    QPushButton *pbTranses;
    QComboBox *cbxTrans;
    QGroupBox *groupBox_mt4080;
    QGridLayout *gridLayout;
    QLineEdit *lineEdit_1;
    QLineEdit *lineEdit_6;
    QLineEdit *lineEdit_7;
    QDoubleSpinBox *lineEdit_2;
    QLineEdit *lineEdit_3;
    QDoubleSpinBox *lineEdit_5;
    QLineEdit *lineEdit_4;
    QLineEdit *lineEdit_9;
    QLineEdit *lineEdit_8;
    QPushButton *pushButton_clearTable;
    QTableView *tableView;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(411, 631);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBoxConnection = new QGroupBox(centralWidget);
        groupBoxConnection->setObjectName(QString::fromUtf8("groupBoxConnection"));
        groupBoxConnection->setCheckable(true);
        gridLayoutConnection = new QGridLayout(groupBoxConnection);
        gridLayoutConnection->setSpacing(6);
        gridLayoutConnection->setContentsMargins(11, 11, 11, 11);
        gridLayoutConnection->setObjectName(QString::fromUtf8("gridLayoutConnection"));
        gridLayoutConnection->setContentsMargins(6, 6, 6, 6);
        checkBox = new QCheckBox(groupBoxConnection);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        gridLayoutConnection->addWidget(checkBox, 0, 1, 1, 1);

        pushButton = new QPushButton(groupBoxConnection);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/res/image2.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton->setIcon(icon);
        pushButton->setCheckable(true);

        gridLayoutConnection->addWidget(pushButton, 1, 1, 1, 2);

        comboBoxMt4080 = new QComboBox(groupBoxConnection);
        comboBoxMt4080->setObjectName(QString::fromUtf8("comboBoxMt4080"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comboBoxMt4080->sizePolicy().hasHeightForWidth());
        comboBoxMt4080->setSizePolicy(sizePolicy);

        gridLayoutConnection->addWidget(comboBoxMt4080, 0, 2, 1, 1);

        pushButtonStartStopMeas = new QPushButton(groupBoxConnection);
        pushButtonStartStopMeas->setObjectName(QString::fromUtf8("pushButtonStartStopMeas"));
        pushButtonStartStopMeas->setIcon(icon);
        pushButtonStartStopMeas->setCheckable(true);

        gridLayoutConnection->addWidget(pushButtonStartStopMeas, 2, 1, 1, 2);


        verticalLayout->addWidget(groupBoxConnection);

        groupBoxSettings = new QGroupBox(centralWidget);
        groupBoxSettings->setObjectName(QString::fromUtf8("groupBoxSettings"));
        groupBoxSettings->setCheckable(true);
        gridLayout_3 = new QGridLayout(groupBoxSettings);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(6, 6, 6, 6);
        dsbMinErr = new QDoubleSpinBox(groupBoxSettings);
        dsbMinErr->setObjectName(QString::fromUtf8("dsbMinErr"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(dsbMinErr->sizePolicy().hasHeightForWidth());
        dsbMinErr->setSizePolicy(sizePolicy1);
        dsbMinErr->setReadOnly(false);
        dsbMinErr->setButtonSymbols(QAbstractSpinBox::NoButtons);
        dsbMinErr->setDecimals(3);
        dsbMinErr->setMaximum(1000000.000000000000000);

        gridLayout_3->addWidget(dsbMinErr, 0, 3, 1, 1);

        dsbMin = new QDoubleSpinBox(groupBoxSettings);
        dsbMin->setObjectName(QString::fromUtf8("dsbMin"));
        sizePolicy1.setHeightForWidth(dsbMin->sizePolicy().hasHeightForWidth());
        dsbMin->setSizePolicy(sizePolicy1);
        dsbMin->setReadOnly(false);
        dsbMin->setButtonSymbols(QAbstractSpinBox::NoButtons);
        dsbMin->setDecimals(3);
        dsbMin->setMaximum(1000000.000000000000000);

        gridLayout_3->addWidget(dsbMin, 0, 1, 1, 1);

        lbSettings_3 = new QLabel(groupBoxSettings);
        lbSettings_3->setObjectName(QString::fromUtf8("lbSettings_3"));
        lbSettings_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(lbSettings_3, 2, 0, 1, 1);

        label = new QLabel(groupBoxSettings);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(label, 4, 0, 1, 1);

        lbSettings_4 = new QLabel(groupBoxSettings);
        lbSettings_4->setObjectName(QString::fromUtf8("lbSettings_4"));
        lbSettings_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(lbSettings_4, 2, 2, 1, 1);

        lbSettings_2 = new QLabel(groupBoxSettings);
        lbSettings_2->setObjectName(QString::fromUtf8("lbSettings_2"));
        lbSettings_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(lbSettings_2, 0, 0, 1, 1);

        lbSettings_1 = new QLabel(groupBoxSettings);
        lbSettings_1->setObjectName(QString::fromUtf8("lbSettings_1"));
        lbSettings_1->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(lbSettings_1, 0, 2, 1, 1);

        sbScale = new QSpinBox(groupBoxSettings);
        sbScale->setObjectName(QString::fromUtf8("sbScale"));
        sizePolicy1.setHeightForWidth(sbScale->sizePolicy().hasHeightForWidth());
        sbScale->setSizePolicy(sizePolicy1);
        sbScale->setButtonSymbols(QAbstractSpinBox::NoButtons);
        sbScale->setMinimum(-10);
        sbScale->setMaximum(10);

        gridLayout_3->addWidget(sbScale, 4, 1, 1, 1);

        dsbMax = new QDoubleSpinBox(groupBoxSettings);
        dsbMax->setObjectName(QString::fromUtf8("dsbMax"));
        sizePolicy1.setHeightForWidth(dsbMax->sizePolicy().hasHeightForWidth());
        dsbMax->setSizePolicy(sizePolicy1);
        dsbMax->setReadOnly(false);
        dsbMax->setButtonSymbols(QAbstractSpinBox::NoButtons);
        dsbMax->setDecimals(3);
        dsbMax->setMaximum(1000000.000000000000000);

        gridLayout_3->addWidget(dsbMax, 2, 1, 1, 1);

        dsbMaxErr = new QDoubleSpinBox(groupBoxSettings);
        dsbMaxErr->setObjectName(QString::fromUtf8("dsbMaxErr"));
        sizePolicy1.setHeightForWidth(dsbMaxErr->sizePolicy().hasHeightForWidth());
        dsbMaxErr->setSizePolicy(sizePolicy1);
        dsbMaxErr->setReadOnly(false);
        dsbMaxErr->setButtonSymbols(QAbstractSpinBox::NoButtons);
        dsbMaxErr->setDecimals(3);
        dsbMaxErr->setMaximum(1000000.000000000000000);

        gridLayout_3->addWidget(dsbMaxErr, 2, 3, 1, 1);

        pbTranses = new QPushButton(groupBoxSettings);
        pbTranses->setObjectName(QString::fromUtf8("pbTranses"));

        gridLayout_3->addWidget(pbTranses, 4, 2, 1, 1);

        cbxTrans = new QComboBox(groupBoxSettings);
        cbxTrans->setObjectName(QString::fromUtf8("cbxTrans"));

        gridLayout_3->addWidget(cbxTrans, 4, 3, 1, 1);


        verticalLayout->addWidget(groupBoxSettings);

        groupBox_mt4080 = new QGroupBox(centralWidget);
        groupBox_mt4080->setObjectName(QString::fromUtf8("groupBox_mt4080"));
        groupBox_mt4080->setCheckable(true);
        gridLayout = new QGridLayout(groupBox_mt4080);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(6, 6, 6, 6);
        lineEdit_1 = new QLineEdit(groupBox_mt4080);
        lineEdit_1->setObjectName(QString::fromUtf8("lineEdit_1"));
        lineEdit_1->setMaximumSize(QSize(100, 16777215));
        lineEdit_1->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lineEdit_1, 2, 0, 1, 1);

        lineEdit_6 = new QLineEdit(groupBox_mt4080);
        lineEdit_6->setObjectName(QString::fromUtf8("lineEdit_6"));
        lineEdit_6->setMaximumSize(QSize(100, 16777215));
        lineEdit_6->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lineEdit_6, 3, 2, 1, 1);

        lineEdit_7 = new QLineEdit(groupBox_mt4080);
        lineEdit_7->setObjectName(QString::fromUtf8("lineEdit_7"));
        lineEdit_7->setMaximumSize(QSize(100, 16777215));
        lineEdit_7->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lineEdit_7, 4, 0, 1, 1);

        lineEdit_2 = new QDoubleSpinBox(groupBox_mt4080);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lineEdit_2->sizePolicy().hasHeightForWidth());
        lineEdit_2->setSizePolicy(sizePolicy2);
        lineEdit_2->setAlignment(Qt::AlignCenter);
        lineEdit_2->setReadOnly(true);
        lineEdit_2->setButtonSymbols(QAbstractSpinBox::NoButtons);
        lineEdit_2->setDecimals(3);
        lineEdit_2->setMaximum(1.000000000000000);

        gridLayout->addWidget(lineEdit_2, 2, 1, 1, 1);

        lineEdit_3 = new QLineEdit(groupBox_mt4080);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setMaximumSize(QSize(100, 16777215));
        lineEdit_3->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lineEdit_3, 2, 2, 1, 1);

        lineEdit_5 = new QDoubleSpinBox(groupBox_mt4080);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));
        sizePolicy2.setHeightForWidth(lineEdit_5->sizePolicy().hasHeightForWidth());
        lineEdit_5->setSizePolicy(sizePolicy2);
        lineEdit_5->setAlignment(Qt::AlignCenter);
        lineEdit_5->setReadOnly(true);
        lineEdit_5->setButtonSymbols(QAbstractSpinBox::NoButtons);
        lineEdit_5->setDecimals(3);
        lineEdit_5->setMaximum(1.000000000000000);

        gridLayout->addWidget(lineEdit_5, 3, 1, 1, 1);

        lineEdit_4 = new QLineEdit(groupBox_mt4080);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));
        lineEdit_4->setMaximumSize(QSize(100, 16777215));
        lineEdit_4->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lineEdit_4, 3, 0, 1, 1);

        lineEdit_9 = new QLineEdit(groupBox_mt4080);
        lineEdit_9->setObjectName(QString::fromUtf8("lineEdit_9"));
        lineEdit_9->setMaximumSize(QSize(100, 16777215));
        lineEdit_9->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lineEdit_9, 4, 2, 1, 1);

        lineEdit_8 = new QLineEdit(groupBox_mt4080);
        lineEdit_8->setObjectName(QString::fromUtf8("lineEdit_8"));
        sizePolicy2.setHeightForWidth(lineEdit_8->sizePolicy().hasHeightForWidth());
        lineEdit_8->setSizePolicy(sizePolicy2);
        lineEdit_8->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lineEdit_8, 4, 1, 1, 1);


        verticalLayout->addWidget(groupBox_mt4080);

        pushButton_clearTable = new QPushButton(centralWidget);
        pushButton_clearTable->setObjectName(QString::fromUtf8("pushButton_clearTable"));

        verticalLayout->addWidget(pushButton_clearTable);

        tableView = new QTableView(centralWidget);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        verticalLayout->addWidget(tableView);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 411, 21));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        groupBoxConnection->setTitle(QApplication::translate("MainWindow", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\260 \321\201\320\262\321\217\320\267\320\270:", nullptr));
        checkBox->setText(QApplication::translate("MainWindow", "MT4080D:", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "\320\235\320\260\321\207\320\260\321\202\321\214 \320\276\320\277\321\200\320\276\321\201", nullptr));
        pushButtonStartStopMeas->setText(QApplication::translate("MainWindow", "\320\235\320\260\321\207\320\260\321\202\321\214 \320\270\320\267\320\274\320\265\321\200\320\265\320\275\320\270\320\265", nullptr));
        groupBoxSettings->setTitle(QApplication::translate("MainWindow", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213 \320\270\320\267\320\274\320\265\321\200\320\265\320\275\320\270\321\217:", nullptr));
        lbSettings_3->setText(QApplication::translate("MainWindow", "Max:", nullptr));
        label->setText(QApplication::translate("MainWindow", "Scale:", nullptr));
        lbSettings_4->setText(QApplication::translate("MainWindow", "Max Error:", nullptr));
        lbSettings_2->setText(QApplication::translate("MainWindow", "Min:", nullptr));
        lbSettings_1->setText(QApplication::translate("MainWindow", "Min Error:", nullptr));
        pbTranses->setText(QApplication::translate("MainWindow", "\320\242\321\200\320\260\320\275\321\201\321\213", nullptr));
        groupBox_mt4080->setTitle(QApplication::translate("MainWindow", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213 MT4080D", nullptr));
        pushButton_clearTable->setText(QApplication::translate("MainWindow", "\320\236\321\202\321\207\320\270\321\201\321\202\320\270\321\202\321\214 \321\202\320\260\320\261\320\273\320\270\321\206\321\203", nullptr));
        Q_UNUSED(MainWindow);
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
