#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDateTime>
#include <QDebug>
#include <QSerialPortInfo>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    for (const QSerialPortInfo& info : QSerialPortInfo::availablePorts()) {
        ui->comboBox->addItem(info.portName());
    }
    mt4080 = new MT4080;
    mt4080->moveToThread(&mt4080Thread);
    connect(&mt4080Thread, &QThread::finished, mt4080, &QObject::deleteLater);
    connect(mt4080, &MT4080::Primary, this, &MainWindow::setVal);
    connect(mt4080, &MT4080::Display, this, &MainWindow::Display);
    //    connect(ui->lineEdit_min, &QLineEdit::textChanged, mt4080, &MT4080::setMin2);
    //    connect(ui->lineEdit_max, &QLineEdit::textChanged, mt4080, &MT4080::setMax2);
    mt4080Thread.start();
}

MainWindow::~MainWindow()
{
    on_pushButton_clicked(false);
    mt4080Thread.quit();
    mt4080Thread.wait();
    delete ui;
}

void MainWindow::on_pushButton_clicked(bool checked)
{
    if (checked) {
        if (mt4080->Open(ui->comboBox->currentText())) {
            ui->pushButton->setText("Закрыть");
        } else {
            checked = false;
        }
    } else {
        mt4080->Close();
        ui->pushButton->setText("Открыть");
    }
    ui->pushButton->setChecked(checked);
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->textBrowser->append(QString("%1").arg(val, 0, 'g', 6).replace('.', ','));
}

void MainWindow::Display(const MT4080::Display_t& val)
{
    ui->lineEdit->setText(val.firest.function);
    ui->lineEdit_2->setText(QString::number(val.firest.value));
    ui->lineEdit_3->setText(val.firest.unit);

    ui->lineEdit_4->setText(val.secopnd.function);
    ui->lineEdit_5->setText(QString::number(val.secopnd.value));
    ui->lineEdit_6->setText(val.secopnd.unit);

    ui->lineEdit_7->setText(val.speed);
    ui->lineEdit_8->setText(val.frequency);
    ui->lineEdit_9->setText(val.level);
}

void MainWindow::setVal(double value)
{
    val = value;
}
