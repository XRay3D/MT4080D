#include "mainwindow.h"
#include "measuringinterface/interface.h"
#include "ui_mainwindow.h"

#include <QDateTime>
#include <QDebug>
#include <QMessageBox>
#include <QSerialPortInfo>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , Pos(0)
    , start(QStringLiteral(":/res/image2.png"))
    , stop(QStringLiteral(":/res/image3.png"))

{
    ui->setupUi(this);
    foreach (QSerialPortInfo info, QSerialPortInfo::availablePorts()) {
        ui->cbxMt4080->addItem(info.portName());
        ui->cbxRelay->addItem(info.portName());
    }
    connect(MI::mt, &MT4080::Primary, this, &MainWindow::Primary);
    connect(MI::mt, &MT4080::Display, this, &MainWindow::Display);

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

    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
    readSettings();
}

MainWindow::~MainWindow()
{
    on_pbPing_clicked(false);
    writeSettings();
    delete ui;
}

void MainWindow::Display(const MT4080::Display_t& val)
{
    ui->lineEdit_1->setText(val.firest.function);
    ui->lineEdit_2->setValue(val.firest.value);
    //ui->lineEdit_2->setPrefix(val.PrimaryFunction);
    //ui->lineEdit_2->setSuffix(val.PrimaryUnit);
    ui->lineEdit_3->setText(val.firest.unit);

    ui->lineEdit_4->setText(val.secopnd.function);
    ui->lineEdit_5->setValue(val.secopnd.value);
    //ui->lineEdit_2->setPrefix(val.SecondaryFunction);
    //ui->lineEdit_2->setSuffix(val.SecondaryUnit);
    ui->lineEdit_6->setText(val.secopnd.unit);

    ui->lineEdit_7->setText(val.speed);
    ui->lineEdit_8->setText(val.frequency);
    ui->lineEdit_9->setText(val.level);

    ui->lineEdit_2->setStyleSheet("QDoubleSpinBox{background-color:rgb(255, 128, 128)}");
    QTimer::singleShot(50, Qt::CoarseTimer, [&]() { ui->lineEdit_2->setStyleSheet(""); });
}

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

    settings.endGroup();
}

void MainWindow::MessageMeasureEnded()
{
    QMessageBox::information(this, "Сообщение", "Измерение закончилось!", tr("Хорошо"));
}

void MainWindow::MessageErrorRelaySwitch()
{
    QMessageBox::critical(this, "Ошибка!", "Не удалось переключить Коммутатор!", tr("Плохо!"));
}

void MainWindow::on_pbStartMeas_clicked(bool checked)
{
    if (ui->pbPing->isChecked()) {
        if (checked) {
            Pos = Counter = 0;
            disconnect(ui->hsRelPos, &QSlider::valueChanged, MI::rel, &Relay::SetEnabledRelay);
            connect(MI::mt, &MT4080::Primary, this, &MainWindow::Primary);
        } else {
            checked = false;
            disconnect(MI::mt, &MT4080::Primary, this, &MainWindow::Primary);
            connect(ui->hsRelPos, &QSlider::valueChanged, MI::rel, &Relay::SetEnabledRelay);
        }
    } else {
        checked = false;
    }

    ui->tableView->SetEnabledCheckBoxes(!checked);
    ui->pbStartMeas->setChecked(checked);
    ui->pbStartMeas->setText(checked ? "Остановить измерение" : "Начать измерение");
    ui->pbStartMeas->setIcon(checked ? stop : start);
}

void MainWindow::Primary(double val)
{
    static int oneMessageBox = 0;
    static QMap<int, bool> selected;

    if (mutex.tryLock(1)) {
        do {
            if (ui->pbStartMeas->isChecked()) {
                if (Pos == 0) {
                    oneMessageBox = 0;
                    selected = ui->tableView->IsChecked();
                    for (int i = 0; i < 58; ++i) {
                        if (selected.contains(i) && !selected[i])
                            selected.remove(i);
                    }
                    if (selected.contains(-1))
                        selected.remove(-1);
                    if (selected.isEmpty()) {
                        on_pbStartMeas_clicked(false);
                        QMessageBox::critical(this, "Ошибка!", "Не выбрана ни одна позиция!", tr("Плохо!"));
                        break;
                    }
                }

                if (Counter == 0) {
                    Pos = selected.firstKey() + 1;
                    if (Pos <= 29) {
                        ui->hsRelPos->setValue(Pos);
                        if (!oneMessageBox) {
                            oneMessageBox = 1;
                            QMessageBox::information(this, "Внимание", "Поставите плату стороной 1-29", tr("Хорошо"));
                        }
                        if (!MI::rel->SetEnabledRelay(Pos)) {
                            on_pbStartMeas_clicked(false);
                            MessageErrorRelaySwitch();
                        }
                    } else if (Pos > 29) {
                        ui->hsRelPos->setValue(Pos - 29);
                        if (oneMessageBox < 2) {
                            oneMessageBox = 2;
                            QMessageBox::information(this, "Внимание", "Поставите плату стороной 30-58", tr("Хорошо"));
                        }
                        if (!MI::rel->SetEnabledRelay(Pos - 29)) {
                            on_pbStartMeas_clicked(false);
                            MessageErrorRelaySwitch();
                        }
                    }
                } else if (Counter <= ui->sbxSkipMeas->value())
                    ui->tableView->SetData(Pos - 1, val);
                else if (Counter <= (ui->sbxSkipMeas->value() + ui->sbxMeasCount->value()))
                    ui->tableView->AddData(Pos - 1, val);
                else {
                    Counter = selected.firstKey();
                    selected.remove(Counter);
                    Counter = 0;
                    if (selected.isEmpty()) {
                        on_pbStartMeas_clicked(false);
                        MessageMeasureEnded();
                    }
                    break;
                }
                ++Counter;
                qDebug() << Counter;
            }
        } while (0);
        mutex.unlock();
    }
}

void MainWindow::on_pbPing_clicked(bool checked)
{
    if (checked) {
        do {
            if (!MI::rel->Ping(ui->cbxRelay->currentText())) {
                QMessageBox::warning(this, "Ping", "cbxRelay");
                break;
            }
            if (!MI::mt->Open(ui->cbxMt4080->currentText())) {
                QMessageBox::warning(this, "Ping", "cbxMt4080");
                break;
            }
            ui->pbPing->setText("Закончить опрос");
            ui->pbPing->setIcon(stop);
            //MI::rel->SetEnabledRelays(0);
            return;
        } while (0);
        ui->pbPing->setChecked(false);
    } else {
        MI::mt->Close();
        ui->pbPing->setText("Начать опрос");
        ui->pbPing->setIcon(start);
    }
}
