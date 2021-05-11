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
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
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
    QComboBox *cbxPortMt4080;
    QPushButton *pushButtonStartStopMeas;
    QGroupBox *grbxSettings;
    QHBoxLayout *horizontalLayout;
    QFormLayout *formLayout;
    QLabel *lbSettings_2;
    QDoubleSpinBox *dsbMin;
    QLabel *lbSettings_3;
    QDoubleSpinBox *dsbMax;
    QLabel *label;
    QSpinBox *sbScale;
    QFormLayout *formLayout_2;
    QLabel *lbSettings_1;
    QDoubleSpinBox *dsbMinErr;
    QLabel *lbSettings_4;
    QDoubleSpinBox *dsbMaxErr;
    QPushButton *pbTranses;
    QComboBox *cbxTrans;
    QGroupBox *grbxMt4080;
    QGridLayout *gridLayout;
    QLineEdit *lePrimFunc;
    QLineEdit *leSecondUnit;
    QLineEdit *leSpeed;
    QDoubleSpinBox *dsbxPrimValue;
    QLineEdit *lePrimUnit;
    QDoubleSpinBox *dsbxSecondValue;
    QLineEdit *leSecondFunc;
    QLineEdit *leLevel;
    QLineEdit *leFreq;
    QPushButton *pushButton_clearTable;
    QSplitter *splitter;
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
        verticalLayout->setContentsMargins(6, 6, 6, 6);
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

        cbxPortMt4080 = new QComboBox(groupBoxConnection);
        cbxPortMt4080->setObjectName(QString::fromUtf8("cbxPortMt4080"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(cbxPortMt4080->sizePolicy().hasHeightForWidth());
        cbxPortMt4080->setSizePolicy(sizePolicy);

        gridLayoutConnection->addWidget(cbxPortMt4080, 0, 2, 1, 1);

        pushButtonStartStopMeas = new QPushButton(groupBoxConnection);
        pushButtonStartStopMeas->setObjectName(QString::fromUtf8("pushButtonStartStopMeas"));
        pushButtonStartStopMeas->setIcon(icon);
        pushButtonStartStopMeas->setCheckable(true);

        gridLayoutConnection->addWidget(pushButtonStartStopMeas, 2, 1, 1, 2);


        verticalLayout->addWidget(groupBoxConnection);

        grbxSettings = new QGroupBox(centralWidget);
        grbxSettings->setObjectName(QString::fromUtf8("grbxSettings"));
        grbxSettings->setCheckable(true);
        horizontalLayout = new QHBoxLayout(grbxSettings);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 6, 6, 6);
        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setLabelAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lbSettings_2 = new QLabel(grbxSettings);
        lbSettings_2->setObjectName(QString::fromUtf8("lbSettings_2"));
        lbSettings_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(0, QFormLayout::LabelRole, lbSettings_2);

        dsbMin = new QDoubleSpinBox(grbxSettings);
        dsbMin->setObjectName(QString::fromUtf8("dsbMin"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(dsbMin->sizePolicy().hasHeightForWidth());
        dsbMin->setSizePolicy(sizePolicy1);
        dsbMin->setReadOnly(false);
        dsbMin->setButtonSymbols(QAbstractSpinBox::NoButtons);
        dsbMin->setDecimals(3);
        dsbMin->setMaximum(1000000.000000000000000);

        formLayout->setWidget(0, QFormLayout::FieldRole, dsbMin);

        lbSettings_3 = new QLabel(grbxSettings);
        lbSettings_3->setObjectName(QString::fromUtf8("lbSettings_3"));
        lbSettings_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(1, QFormLayout::LabelRole, lbSettings_3);

        dsbMax = new QDoubleSpinBox(grbxSettings);
        dsbMax->setObjectName(QString::fromUtf8("dsbMax"));
        sizePolicy1.setHeightForWidth(dsbMax->sizePolicy().hasHeightForWidth());
        dsbMax->setSizePolicy(sizePolicy1);
        dsbMax->setReadOnly(false);
        dsbMax->setButtonSymbols(QAbstractSpinBox::NoButtons);
        dsbMax->setDecimals(3);
        dsbMax->setMaximum(1000000.000000000000000);

        formLayout->setWidget(1, QFormLayout::FieldRole, dsbMax);

        label = new QLabel(grbxSettings);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(2, QFormLayout::LabelRole, label);

        sbScale = new QSpinBox(grbxSettings);
        sbScale->setObjectName(QString::fromUtf8("sbScale"));
        sizePolicy1.setHeightForWidth(sbScale->sizePolicy().hasHeightForWidth());
        sbScale->setSizePolicy(sizePolicy1);
        sbScale->setButtonSymbols(QAbstractSpinBox::NoButtons);
        sbScale->setMinimum(-10);
        sbScale->setMaximum(10);

        formLayout->setWidget(2, QFormLayout::FieldRole, sbScale);


        horizontalLayout->addLayout(formLayout);

        formLayout_2 = new QFormLayout();
        formLayout_2->setSpacing(6);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        formLayout_2->setLabelAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lbSettings_1 = new QLabel(grbxSettings);
        lbSettings_1->setObjectName(QString::fromUtf8("lbSettings_1"));
        lbSettings_1->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_2->setWidget(0, QFormLayout::LabelRole, lbSettings_1);

        dsbMinErr = new QDoubleSpinBox(grbxSettings);
        dsbMinErr->setObjectName(QString::fromUtf8("dsbMinErr"));
        sizePolicy1.setHeightForWidth(dsbMinErr->sizePolicy().hasHeightForWidth());
        dsbMinErr->setSizePolicy(sizePolicy1);
        dsbMinErr->setReadOnly(false);
        dsbMinErr->setButtonSymbols(QAbstractSpinBox::NoButtons);
        dsbMinErr->setDecimals(3);
        dsbMinErr->setMaximum(1000000.000000000000000);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, dsbMinErr);

        lbSettings_4 = new QLabel(grbxSettings);
        lbSettings_4->setObjectName(QString::fromUtf8("lbSettings_4"));
        lbSettings_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_2->setWidget(1, QFormLayout::LabelRole, lbSettings_4);

        dsbMaxErr = new QDoubleSpinBox(grbxSettings);
        dsbMaxErr->setObjectName(QString::fromUtf8("dsbMaxErr"));
        sizePolicy1.setHeightForWidth(dsbMaxErr->sizePolicy().hasHeightForWidth());
        dsbMaxErr->setSizePolicy(sizePolicy1);
        dsbMaxErr->setReadOnly(false);
        dsbMaxErr->setButtonSymbols(QAbstractSpinBox::NoButtons);
        dsbMaxErr->setDecimals(3);
        dsbMaxErr->setMaximum(1000000.000000000000000);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, dsbMaxErr);

        pbTranses = new QPushButton(grbxSettings);
        pbTranses->setObjectName(QString::fromUtf8("pbTranses"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, pbTranses);

        cbxTrans = new QComboBox(grbxSettings);
        cbxTrans->setObjectName(QString::fromUtf8("cbxTrans"));

        formLayout_2->setWidget(2, QFormLayout::FieldRole, cbxTrans);


        horizontalLayout->addLayout(formLayout_2);


        verticalLayout->addWidget(grbxSettings);

        grbxMt4080 = new QGroupBox(centralWidget);
        grbxMt4080->setObjectName(QString::fromUtf8("grbxMt4080"));
        grbxMt4080->setCheckable(true);
        gridLayout = new QGridLayout(grbxMt4080);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(6, 6, 6, 6);
        lePrimFunc = new QLineEdit(grbxMt4080);
        lePrimFunc->setObjectName(QString::fromUtf8("lePrimFunc"));
        lePrimFunc->setMaximumSize(QSize(100, 16777215));
        lePrimFunc->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lePrimFunc, 2, 0, 1, 1);

        leSecondUnit = new QLineEdit(grbxMt4080);
        leSecondUnit->setObjectName(QString::fromUtf8("leSecondUnit"));
        leSecondUnit->setMaximumSize(QSize(100, 16777215));
        leSecondUnit->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(leSecondUnit, 3, 2, 1, 1);

        leSpeed = new QLineEdit(grbxMt4080);
        leSpeed->setObjectName(QString::fromUtf8("leSpeed"));
        leSpeed->setMaximumSize(QSize(100, 16777215));
        leSpeed->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(leSpeed, 4, 0, 1, 1);

        dsbxPrimValue = new QDoubleSpinBox(grbxMt4080);
        dsbxPrimValue->setObjectName(QString::fromUtf8("dsbxPrimValue"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(dsbxPrimValue->sizePolicy().hasHeightForWidth());
        dsbxPrimValue->setSizePolicy(sizePolicy2);
        dsbxPrimValue->setAlignment(Qt::AlignCenter);
        dsbxPrimValue->setReadOnly(true);
        dsbxPrimValue->setButtonSymbols(QAbstractSpinBox::NoButtons);
        dsbxPrimValue->setDecimals(3);
        dsbxPrimValue->setMaximum(1.000000000000000);

        gridLayout->addWidget(dsbxPrimValue, 2, 1, 1, 1);

        lePrimUnit = new QLineEdit(grbxMt4080);
        lePrimUnit->setObjectName(QString::fromUtf8("lePrimUnit"));
        lePrimUnit->setMaximumSize(QSize(100, 16777215));
        lePrimUnit->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lePrimUnit, 2, 2, 1, 1);

        dsbxSecondValue = new QDoubleSpinBox(grbxMt4080);
        dsbxSecondValue->setObjectName(QString::fromUtf8("dsbxSecondValue"));
        sizePolicy2.setHeightForWidth(dsbxSecondValue->sizePolicy().hasHeightForWidth());
        dsbxSecondValue->setSizePolicy(sizePolicy2);
        dsbxSecondValue->setAlignment(Qt::AlignCenter);
        dsbxSecondValue->setReadOnly(true);
        dsbxSecondValue->setButtonSymbols(QAbstractSpinBox::NoButtons);
        dsbxSecondValue->setDecimals(3);
        dsbxSecondValue->setMaximum(1.000000000000000);

        gridLayout->addWidget(dsbxSecondValue, 3, 1, 1, 1);

        leSecondFunc = new QLineEdit(grbxMt4080);
        leSecondFunc->setObjectName(QString::fromUtf8("leSecondFunc"));
        leSecondFunc->setMaximumSize(QSize(100, 16777215));
        leSecondFunc->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(leSecondFunc, 3, 0, 1, 1);

        leLevel = new QLineEdit(grbxMt4080);
        leLevel->setObjectName(QString::fromUtf8("leLevel"));
        leLevel->setMaximumSize(QSize(100, 16777215));
        leLevel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(leLevel, 4, 2, 1, 1);

        leFreq = new QLineEdit(grbxMt4080);
        leFreq->setObjectName(QString::fromUtf8("leFreq"));
        sizePolicy2.setHeightForWidth(leFreq->sizePolicy().hasHeightForWidth());
        leFreq->setSizePolicy(sizePolicy2);
        leFreq->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(leFreq, 4, 1, 1, 1);


        verticalLayout->addWidget(grbxMt4080);

        pushButton_clearTable = new QPushButton(centralWidget);
        pushButton_clearTable->setObjectName(QString::fromUtf8("pushButton_clearTable"));

        verticalLayout->addWidget(pushButton_clearTable);

        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Vertical);
        tableView = new QTableView(splitter);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        splitter->addWidget(tableView);

        verticalLayout->addWidget(splitter);

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
        grbxSettings->setTitle(QApplication::translate("MainWindow", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213 \320\270\320\267\320\274\320\265\321\200\320\265\320\275\320\270\321\217:", nullptr));
        lbSettings_2->setText(QApplication::translate("MainWindow", "Min:", nullptr));
        lbSettings_3->setText(QApplication::translate("MainWindow", "Max:", nullptr));
        label->setText(QApplication::translate("MainWindow", "Scale:", nullptr));
        lbSettings_1->setText(QApplication::translate("MainWindow", "Min Error:", nullptr));
        lbSettings_4->setText(QApplication::translate("MainWindow", "Max Error:", nullptr));
        pbTranses->setText(QApplication::translate("MainWindow", "\320\242\321\200\320\260\320\275\321\201\321\213", nullptr));
        grbxMt4080->setTitle(QApplication::translate("MainWindow", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213 MT4080D", nullptr));
        pushButton_clearTable->setText(QApplication::translate("MainWindow", "\320\236\321\202\321\207\320\270\321\201\321\202\320\270\321\202\321\214 \321\202\320\260\320\261\320\273\320\270\321\206\321\203", nullptr));
        Q_UNUSED(MainWindow);
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
