#include "mainwindow.h"
#include "measuringinterface/interface.h"
#include "ui_mainwindow.h"

#include <QDateTime>
#include <QDebug>
#include <QMessageBox>
#include <QSerialPortInfo>

#include <coroutine>
#include <generator.hpp>

cppcoro::generator<const int> g(bool init = false)
{
    for (auto [key, _] : MainWindow::selected) {
        co_yield key;
    }
}

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , start(QStringLiteral(":/res/image2.png"))
    , stop(QStringLiteral(":/res/image3.png"))

{
    ui->setupUi(this);
    for (QSerialPortInfo& info : QSerialPortInfo::availablePorts()) {
        ui->cbxMt4080->addItem(info.portName());
        ui->cbxRelay->addItem(info.portName());
    }

    //    connect(MI::mt, &MT4080::Display, this, &MainWindow::Display);
    //    connect(MI::mt, &MT4080::Primary, this, &MainWindow::Primary);

    connect(MI::scpi, &SCPI::measureReady, this, &MainWindow::display);

    connect(this, &MainWindow::startMeasure, MI::scpi, &SCPI::getResistance4W, Qt::QueuedConnection);

    connect(ui->hsRelPos, &QSlider::valueChanged, MI::rel, &Relay::SetEnabledRelay);
    connect(ui->hsRelPos, &QSlider::valueChanged, [&](int value) { ui->label_rel->setText(QString("Поз. %1:").arg(value)); });

    //    connect(rele, &RELAY::showMessage, ui->statusBar, &QStatusBar::showMessage);

    connect(ui->pbClearTable, &QPushButton::clicked, ui->tableView, &MyTable::ClearColumnData);

    connect(ui->gbxMt4080, &QGroupBox::clicked, [&](bool checked) {
        ui->gbxMt4080->setChecked(checked);
        ui->lineEdit_4->setVisible(checked);
        ui->lineEdit_5->setVisible(checked);
        ui->lineEdit_6->setVisible(checked);
        ui->lineEdit_7->setVisible(checked);
        ui->lineEdit_8->setVisible(checked);
        ui->lineEdit_9->setVisible(checked);
        ui->lineEdit_1->setEnabled(true);
        ui->lineEdit_2->setEnabled(true);
        ui->lineEdit_3->setEnabled(true);
    });

    connect(ui->gbxSettings, &QGroupBox::clicked, [&](bool checked) {
        ui->gbxSettings->setChecked(checked);
        ui->label_1->setVisible(checked);
        ui->label_2->setVisible(checked);
        ui->sbxSkipMeas->setVisible(checked);
        ui->sbxMeasCount->setVisible(checked);
        if (checked)
            ui->gridLayoutSettings->setMargin(6);
        else
            ui->gridLayoutSettings->setMargin(3);
    });

    connect(ui->gbxConnection, &QGroupBox::clicked, [&](bool checked) {
        ui->label_5->setVisible(checked);
        ui->label_6->setVisible(checked);
        ui->cbxMt4080->setVisible(checked);
        ui->cbxRelay->setVisible(checked);
        ui->pbPing->setVisible(checked);
        if (checked) {
            ui->gridLayoutConnection->setMargin(6);
            ui->gbxConnection->setTitle("Настройка связи:");
        } else {
            ui->gridLayoutConnection->setMargin(3);
            ui->gbxConnection->setTitle(QString("Настройка связи: (%1)").arg(ui->pbPing->isChecked() ? "Идут измерения" : "Измерения остановлены"));
        }
    });

#ifndef QT_DEBUG
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
#endif

    readSettings();
}

MainWindow::~MainWindow()
{
    on_pbPing_clicked(false);
    writeSettings();
    delete ui;
}

//void MainWindow::Display(const MT4080::Display_t& val)
//{
//    ui->lineEdit_1->setText(val.firest.function);
//    ui->lineEdit_2->setValue(val.firest.value * pow(10.0, ui->spinBox->value()));
//    //ui->lineEdit_2->setPrefix(val.PrimaryFunction);
//    //ui->lineEdit_2->setSuffix(val.PrimaryUnit);
//    ui->lineEdit_3->setText(val.firest.unit);

//    ui->lineEdit_4->setText(val.secopnd.function);
//    ui->lineEdit_5->setValue(val.secopnd.value);
//    //ui->lineEdit_2->setPrefix(val.SecondaryFunction);
//    //ui->lineEdit_2->setSuffix(val.SecondaryUnit);
//    ui->lineEdit_6->setText(val.secopnd.unit);

//    ui->lineEdit_7->setText(val.speed);
//    ui->lineEdit_8->setText(val.frequency);
//    ui->lineEdit_9->setText(val.level);

//    ui->lineEdit_2->setStyleSheet("QDoubleSpinBox{background-color:rgb(255, 128, 128)}");
//    QTimer::singleShot(50, Qt::CoarseTimer, [&]() { ui->lineEdit_2->setStyleSheet(""); });
//}

void MainWindow::writeSettings()
{
    QSettings settings;

    settings.beginGroup("MainWindow");
    settings.setValue("size", size());
    settings.setValue("pos", pos());

    settings.setValue("WindowState", (int)windowState());

    settings.setValue("cbxMt4080", ui->cbxMt4080->currentIndex());
    settings.setValue("cbxRelay", ui->cbxRelay->currentIndex());

    settings.setValue("gbxMt4080", ui->gbxMt4080->isChecked());
    settings.setValue("gbxSettings", ui->gbxSettings->isChecked());

    settings.setValue("sbxSkipMeas", ui->sbxSkipMeas->value());
    settings.setValue("sbxMeasCount", ui->sbxMeasCount->value());
    settings.setValue("spinBox", ui->spinBox->value());

    settings.endGroup();
}

void MainWindow::readSettings()
{
    QSettings settings;

    settings.beginGroup("MainWindow");
    resize(settings.value("size", QSize(400, 400)).toSize());
    move(settings.value("pos", QPoint(200, 200)).toPoint());

    setWindowState((Qt::WindowState)settings.value("WindowState").toInt());

    ui->cbxMt4080->setCurrentIndex(settings.value("cbxMt4080").toInt());
    ui->cbxRelay->setCurrentIndex(settings.value("cbxRelay").toInt());
    emit ui->gbxMt4080->clicked(settings.value("gbxMt4080").toBool());
    emit ui->gbxSettings->clicked(settings.value("gbxSettings").toBool());

    ui->sbxSkipMeas->setValue(settings.value("sbxSkipMeas").toInt());
    ui->sbxMeasCount->setValue(settings.value("sbxMeasCount").toInt());
    ui->spinBox->setValue(settings.value("spinBox").toInt());

    settings.endGroup();
}

void MainWindow::messageMeasureEnded()
{
    QMessageBox::information(this, "Сообщение", "Измерение закончилось!", tr("Хорошо"));
}

void MainWindow::messageErrorRelaySwitch()
{
    QMessageBox::critical(this, "Ошибка!", "Не удалось переключить Коммутатор!", tr("Плохо!"));
}

void MainWindow::on_pbStartMeas_clicked(bool checked)
{
    do {
        if (ui->pbPing->isChecked()) {
            if (checked) {
                currentPos = counter = sideMessageBox = 0;

                selected = ui->tableView->IsChecked();
                for (int i = 0; i < 58; ++i) {
                    if (!selected[i])
                        selected.erase(i);
                }
                selected.erase(-1);

                if (!selected.size()) {
                    on_pbStartMeas_clicked(false);
                    QMessageBox::critical(this, "Ошибка!", "Не выбрана ни одна позиция!", tr("Плохо!"));
                    checked = false;
                    break;
                }

                disconnect(ui->hsRelPos, &QSlider::valueChanged, MI::rel, &Relay::SetEnabledRelay);
                connect(MI::scpi, &SCPI::measureReady, this, &MainWindow::primary);
            } else {
                checked = false;
                disconnect(MI::scpi, &SCPI::measureReady, this, &MainWindow::primary);
                connect(ui->hsRelPos, &QSlider::valueChanged, MI::rel, &Relay::SetEnabledRelay);
            }
        } else {
            checked = false;
        }
    } while (0);
    ui->tableView->SetEnabledCheckBoxes(!checked);
    ui->pbStartMeas->setChecked(checked);
    ui->pbStartMeas->setText(checked ? "Остановить измерение" : "Начать измерение");
    ui->pbStartMeas->setIcon(checked ? stop : start);
}

void MainWindow::primary(double val)
{
    val *= pow(10.0, ui->spinBox->value());

    if (mutex.tryLock(1)) {
        do {
            if (ui->pbStartMeas->isChecked()) {
                if (counter == 0) {

                    currentPos = selected.begin()->first + 1;
                    ui->hsRelPos->setValue(currentPos < 30 ? currentPos : currentPos - 29);

                    if /*  */ (currentPos < 30 && sideMessageBox == 0) {
                        ++sideMessageBox;
                        QMessageBox::information(this, "Внимание", "Поставите плату стороной 1-29", tr("Хорошо"));
                    } else if (currentPos > 29 && sideMessageBox == 1) {
                        ++sideMessageBox;
                        QMessageBox::information(this, "Внимание", "Поставите плату стороной 30-58", tr("Хорошо"));
                    }

                    if (!MI::rel->SetEnabledRelay(ui->hsRelPos->value())) {
                        on_pbStartMeas_clicked(false);
                        messageErrorRelaySwitch();
                    }
                } else if (counter <= ui->sbxSkipMeas->value()) {
                    ui->tableView->SetData(currentPos - 1, val);
                } else if (counter <= (ui->sbxSkipMeas->value() + ui->sbxMeasCount->value())) {
                    ui->tableView->AddData(currentPos - 1, val);
                } else {
                    counter = selected.begin()->first;
                    selected.erase(counter);
                    counter = 0;
                    if (!selected.size()) {
                        on_pbStartMeas_clicked(false);
                        messageMeasureEnded();
                    }
                    break;
                }
                ++counter;
            }
        } while (0);
        mutex.unlock();
    }
}

void MainWindow::on_pbPing_clicked(bool checked)
{
    if (checked) {
        do {
            if (!MI::rel->ping(ui->cbxRelay->currentText())) {
                QMessageBox::warning(this, "Ping", "Relay");
                break;
            }
            if (!MI::scpi->ping(ui->cbxMt4080->currentText())) {
                QMessageBox::warning(this, "Ping", "SCPI");
                break;
            }
            //            if (!MI::mt->Open(ui->cbxMt4080->currentText())) {
            //                QMessageBox::warning(this, "Ping", "cbxMt4080");
            //                break;
            //            }
            ui->pbPing->setText("Закончить опрос");
            ui->pbPing->setIcon(stop);
            //MI::rel->SetEnabledRelays(0);
            semaphore.tryAcquire(semaphore.available());
            timerId = startTimer(100);
            return;
        } while (0);
        ui->pbPing->setChecked(false);
    } else {
        //        MI::mt->Close();
        ui->pbPing->setText("Начать опрос");
        ui->pbPing->setIcon(start);
        if (timerId) {
            killTimer(timerId);
            timerId = 0;
        }
    }
}

QElapsedTimer t;

void MainWindow::display(double val)
{
    qDebug() << t.elapsed();
    ui->lineEdit_2->setValue(val);
    ui->lineEdit_2->setStyleSheet("QDoubleSpinBox{background-color:rgb(255, 128, 128)}");
    QTimer::singleShot(50, Qt::CoarseTimer, [&]() { ui->lineEdit_2->setStyleSheet(""); });
    semaphore.tryAcquire(semaphore.available());
}

void MainWindow::timerEvent(QTimerEvent* event)
{
    if (timerId == event->timerId()) {
        static int ctr;
        if (semaphore.available() == 0) {
            ctr = 0;
            qDebug("timerEvent");
            startMeasure();
            t.start();
            semaphore.release();
        } else {
            constexpr int N = 100;
            switch (++ctr) {
            case N + 0:
                MI::scpi->Write("*CLS");
                break;
            case N + 1:
                MI::scpi->Write("*RST");
                break;
            case N + 2:
                semaphore.tryAcquire(semaphore.available());
                break;
            default:
                break;
            }
        }
    }
}
