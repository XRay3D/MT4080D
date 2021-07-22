#include "mainwindow.h"
#include "measuringinterface/interface.h"
#include "ui_mainwindow.h"

#include <QDateTime>
#include <QDebug>
#include <QMessageBox>
#include <QSerialPortInfo>

#include <chekableTableView/model.h>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , pos(0)
    , start(QStringLiteral(":/res/image2.png"))
    , stop(QStringLiteral(":/res/image3.png"))

{
    ui->setupUi(this);
    ui->tableView->initCheckBoxRadioButton();

    auto availablePorts { QSerialPortInfo::availablePorts().toVector() };
    std::ranges::sort(availablePorts, {}, [](QSerialPortInfo& spi) { return spi.portName().midRef(3).toUInt(); });
    for (auto&& portInfo : availablePorts) {
        if (portInfo.manufacturer().contains("Silicon Labs"))
            ui->cbxMt4080->addItem(portInfo.portName());
        if (portInfo.manufacturer().contains("FTDI"))
            ui->cbxRelay->addItem(portInfo.portName());
    }

    connect(MI::mt, &MT4080::display, this, &MainWindow::display);
    connect(MI::mt, &MT4080::primary, this, &MainWindow::primary);

    connect(ui->hsRelPos, &QSlider::valueChanged, MI::rel, &Relay::setEnabledRelay);
    connect(ui->hsRelPos, &QSlider::valueChanged, [&](int value) { ui->label_rel->setText(QString("Поз. %1:").arg(value)); });

    //    connect(rele, &RELAY::showMessage, ui->statusBar, &QStatusBar::showMessage);

    connect(ui->pbClearTable, &QPushButton::clicked, ui->tableView->model(), &Model::clearColumnData);

    connect(ui->gbxMt4080, &QGroupBox::clicked, [&](bool checked) {
        for (auto w : ui->gbxMt4080->findChildren<QWidget*>(QRegularExpression { "lineEdit_[4-9]{1}" }, Qt::FindDirectChildrenOnly))
            w->setVisible(checked);
        //        ui->lineEdit_4->setVisible(checked);
        //        ui->lineEdit_5->setVisible(checked);
        //        ui->lineEdit_6->setVisible(checked);
        //        ui->lineEdit_7->setVisible(checked);
        //        ui->lineEdit_8->setVisible(checked);
        //        ui->lineEdit_9->setVisible(checked);
        ui->lineEdit_1->setEnabled(true);
        ui->lineEdit_2->setEnabled(true);
        ui->lineEdit_3->setEnabled(true);
    });

    connect(ui->gbxSettings, &QGroupBox::clicked, [&](bool checked) {
        for (auto w : ui->gbxSettings->findChildren<QWidget*>(QString {}, Qt::FindDirectChildrenOnly))
            w->setVisible(checked);
        ui->formLayout->setMargin(checked ? 6 : 0);
    });

    connect(ui->gbxConnection, &QGroupBox::clicked, [&](bool checked) {
        for (auto w : ui->gbxConnection->findChildren<QWidget*>(QString {}, Qt::FindDirectChildrenOnly))
            w->setVisible(checked);
        ui->formLayout_2->setMargin(checked ? 6 : 0);
        if (checked) {
            ui->gbxConnection->setTitle("Настройка связи");
        } else {
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

void MainWindow::display(const MT4080::Display& val)
{
    ui->lineEdit_1->setText(val.primary.function);
    ui->lineEdit_2->setValue(val.primary.value * pow(10.0, ui->spinBox->value()));
    //ui->lineEdit_2->setPrefix(val.PrimaryFunction);
    //ui->lineEdit_2->setSuffix(val.PrimaryUnit);
    ui->lineEdit_3->setText(val.primary.unit);

    ui->lineEdit_4->setText(val.secondary.function);
    ui->lineEdit_5->setValue(val.secondary.value);
    //ui->lineEdit_2->setPrefix(val.SecondaryFunction);
    //ui->lineEdit_2->setSuffix(val.SecondaryUnit);
    ui->lineEdit_6->setText(val.secondary.unit);

    ui->lineEdit_7->setText(val.speed);
    ui->lineEdit_8->setText(val.frequency);
    ui->lineEdit_9->setText(val.level);

    ui->lineEdit_2->setStyleSheet("QDoubleSpinBox{background-color:rgb(255, 170, 170)}");
    QTimer::singleShot(50, Qt::CoarseTimer, [this]() { ui->lineEdit_2->setStyleSheet(""); });
}

void MainWindow::writeSettings()
{
    QSettings settings;

    settings.beginGroup("MainWindow");
    settings.setValue("geometry", saveGeometry());
    settings.setValue("state", saveState());

    settings.setValue("cbxMt4080", ui->cbxMt4080->currentText());
    settings.setValue("cbxRelay", ui->cbxRelay->currentText());

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
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("state").toByteArray());

    setWindowState((Qt::WindowState)settings.value("WindowState").toInt());

    ui->cbxMt4080->setCurrentText(settings.value("cbxMt4080").toString());
    ui->cbxRelay->setCurrentText(settings.value("cbxRelay").toString());

    emit ui->gbxMt4080->clicked(settings.value("gbxMt4080").toBool());
    emit ui->gbxSettings->clicked(settings.value("gbxSettings").toBool());

    ui->sbxSkipMeas->setValue(settings.value("sbxSkipMeas").toInt());
    ui->sbxMeasCount->setValue(settings.value("sbxMeasCount").toInt());
    ui->spinBox->setValue(settings.value("spinBox").toInt());

    settings.endGroup();
}

void MainWindow::MessageErrorRelaySwitch()
{
    QMessageBox::critical(this, "Ошибка!", "Не удалось переключить Коммутатор!", tr("Плохо!"));
}

void MainWindow::on_pbStartMeas_clicked(bool checked)
{
    if (ui->pbPing->isChecked()) {
        if (checked) {
            pos = -1;
            disconnect(ui->hsRelPos, &QSlider::valueChanged, MI::rel, &Relay::setChannel);
            connect(MI::mt, &MT4080::primary, this, &MainWindow::primary);
        } else {
            checked = false;
            disconnect(MI::mt, &MT4080::primary, this, &MainWindow::primary);
            connect(ui->hsRelPos, &QSlider::valueChanged, MI::rel, &Relay::setChannel);
        }
    } else {
        checked = false;
    }

    ui->tableView->setEnabledCheckBoxes(!checked);
    ui->pbStartMeas->setChecked(checked);
    ui->pbStartMeas->setText(checked ? "Остановить измерение"
                                     : "Начать измерение");
    ui->pbStartMeas->setIcon(checked ? stop
                                     : start);
}

void MainWindow::primary(double val)
{
    static int oneMessageBox;
    static double avg;
    if (!mutex.tryLock())
        return;
    do {

        if (!ui->pbStartMeas->isChecked())
            break;

        val *= pow(10.0, ui->spinBox->value());

        if (pos < 0) {
            oneMessageBox = 0;
            for (int ctr {}; auto&& checked : ui->tableView->model()->rowChecked()) {
                if (checked) {
                    pos = ctr;
                    break;
                }
                ++ctr;
            }
            if (pos < 0) {
                on_pbStartMeas_clicked(false);
                QMessageBox::critical(this, "Ошибка!", "Не выбрана ни одна позиция!", tr("Плохо!"));
                break;
            }
            counter = 0;
        }
        if (pos >= 58) {
            on_pbStartMeas_clicked(false);
            QMessageBox::information(this, "Сообщение", "Измерение закончилось!", tr("Хорошо"));
            break;
        }
        if (!ui->tableView->model()->rowChecked()[pos]) {
            ++pos;
            break;
        }

        if (counter == 0) {
            /*  */ if (oneMessageBox == 0 && pos < 29) {
                oneMessageBox = 1;
                if (QMessageBox::information(this, "Внимание", "Поставите плату стороной 1-29", QMessageBox::Ok, QMessageBox::Abort) == QMessageBox::Abort) {
                    on_pbStartMeas_clicked(false);
                    break;
                }
            } else if (oneMessageBox <= 1 && pos > 28) {
                oneMessageBox = 2;
                if (QMessageBox::information(this, "Внимание", "Поставите плату стороной 30-58", QMessageBox::Ok, QMessageBox::Abort) == QMessageBox::Abort) {
                    on_pbStartMeas_clicked(false);
                    break;
                }
            }
            auto channel = (pos % 29) + 1;
            ui->hsRelPos->setValue(channel);
            MI::rel->setChannel(channel);
        } else if (counter <= ui->sbxSkipMeas->value()) {
            ui->tableView->model()->setData(pos, val);
        } else if (counter <= (ui->sbxSkipMeas->value() + ui->sbxMeasCount->value())) {
            avg += val;
            ui->tableView->model()->setData(pos, avg / (counter - ui->sbxSkipMeas->value()));
        } else {
            ++pos;
            avg = 0;
            counter = 0;
            break;
        }
        ++counter;
    } while (0);
    mutex.unlock();
}

void MainWindow::on_pbPing_clicked(bool checked)
{
    if (checked) {
        do {
            if (!MI::rel->ping(ui->cbxRelay->currentText(), QSerialPort::Baud9600)) {
                QMessageBox::warning(this, "Ping", "cbxRelay");
                break;
            }
            if (!MI::mt->open(ui->cbxMt4080->currentText())) {
                QMessageBox::warning(this, "Ping", "cbxMt4080");
                break;
            }
            ui->pbPing->setText("Закончить опрос");
            ui->pbPing->setIcon(stop);
            //MI::rel->setChannels(0);
            return;
        } while (0);
        ui->pbPing->setChecked(false);
    } else {
        MI::mt->close();
        ui->pbPing->setText("Начать опрос");
        ui->pbPing->setIcon(start);
    }
}
