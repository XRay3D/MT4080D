#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QClipboard>
#include <QContextMenuEvent>
#include <QMenu>
#include <QMessageBox>
#include <QSerialPortInfo>
#include <QSettings>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QStackedBarSeries>
#include <qt_windows.h>

using namespace QtCharts;

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , start(QStringLiteral(":/res/image2.png"))
    , stop(QStringLiteral(":/res/image3.png"))
    , no(QStringLiteral("C:/Windows/Media/Windows Critical Stop.wav"))
    , yes(QStringLiteral("C:/Windows/Media/Windows Notify.wav"))

{
    ui->setupUi(this);

    //    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);

    foreach (QSerialPortInfo info, QSerialPortInfo::availablePorts()) {
        ui->comboBoxMt4080->addItem(info.portName());
    }

    CreateChart();

    mt4080 = new MT4080;
    mt4080->moveToThread(&mt4080Thread);
    ConnectSignals();

    mt4080Thread.start();

    readSettings();
}

MainWindow::~MainWindow()
{
    ui->pushButton->clicked(false);
    mt4080Thread.quit();
    mt4080Thread.wait();
    writeSettings();
    delete ui;
}

void MainWindow::Display(const MT4080::Display_t& val)
{
    ui->lineEdit_1->setText(val.firest.function);
    //    ui->lineEdit_2->setText(val.PrimaryValue);
    ui->lineEdit_3->setText(val.firest.unit);

    ui->lineEdit_4->setText(val.secopnd.function);
    if (ui->lineEdit_5->minimum() > val.secopnd.value)
        ui->lineEdit_5->setMinimum(val.secopnd.value);
    if (ui->lineEdit_5->maximum() < val.secopnd.value)
        ui->lineEdit_5->setMaximum(val.secopnd.value);
    ui->lineEdit_5->setValue(val.secopnd.value);
    ui->lineEdit_6->setText(val.secopnd.unit);

    ui->lineEdit_7->setText(val.speed);
    ui->lineEdit_8->setText(val.frequency);
    ui->lineEdit_9->setText(val.level);
}

void MainWindow::writeSettings()
{
    QSettings settings;

    settings.beginGroup("MainWindow");
    settings.setValue("size", size());
    settings.setValue("pos", pos());

    settings.setValue("WindowState", (int)windowState());

    settings.setValue("comboBoxMt4080", ui->comboBoxMt4080->currentIndex());

    settings.setValue("groupBox_mt4080", ui->groupBox_mt4080->isChecked());
    settings.setValue("groupBoxSettings", ui->groupBoxSettings->isChecked());

    settings.setValue("dsbMax", ui->dsbMax->value());
    settings.setValue("dsbMaxErr", ui->dsbMaxErr->value());
    settings.setValue("dsbMin", ui->dsbMin->value());
    settings.setValue("dsbMinErr", ui->dsbMinErr->value());
    settings.setValue("sbScale", ui->sbScale->value());

    settings.endGroup();
}

void MainWindow::UpdateChart(double val)
{
    if (min > val)
        min = val;
    if (max < val)
        max = val;
    if (values.size() > 1) {

        double mid = max - min;

        int bar[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        const double k = 0.11111111111111111111111111111111111111;
        const double step[]{
            min,
            min + mid * 1 * k,
            min + mid * 2 * k,
            min + mid * 3 * k,
            min + mid * 4 * k,
            min + mid * 5 * k,
            min + mid * 6 * k,
            min + mid * 7 * k,
            min + mid * 8 * k,
            max
        };

        for (const double value : values) {
            for (int j = 0; j < 9; ++j) {
                if (step[j] <= value && value <= step[j + 1]) {
                    ++bar[j];
                    break;
                }
            }
        }

        int maxRange = 0;
        QStringList categories;
        for (int j = 0; j < 9; ++j) {
            set->replace(j, bar[j]);
            maxRange = qMax(maxRange, bar[j]);
            categories.append(QString("%1-%2").arg(step[j], 0, 'g').arg(step[j + 1], 0, 'g'));
        }
        xAxis->setCategories(categories);
        yAxis->setRange(0, maxRange);
    }
}

void MainWindow::readSettings()
{
    QSettings settings;

    settings.beginGroup("MainWindow");
    resize(settings.value("size", QSize(400, 400)).toSize());
    move(settings.value("pos", QPoint(200, 200)).toPoint());

    setWindowState((Qt::WindowState)settings.value("WindowState").toInt());

    ui->comboBoxMt4080->setCurrentIndex(settings.value("comboBoxMt4080").toInt());
    ui->groupBox_mt4080->clicked(settings.value("groupBox_mt4080").toBool());
    ui->groupBoxSettings->clicked(settings.value("groupBoxSettings").toBool());

    ui->dsbMax->setValue(settings.value("dsbMax").toDouble());
    ui->dsbMaxErr->setValue(settings.value("dsbMaxErr").toDouble());
    ui->dsbMin->setValue(settings.value("dsbMin").toDouble());
    ui->dsbMinErr->setValue(settings.value("dsbMinErr").toDouble());
    ui->sbScale->setValue(settings.value("sbScale").toInt());

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

void MainWindow::MessageMoveBoard(int val)
{
    QMessageBox::information(this, "Внимание", QString("Поставите плату стороной %1").arg(val == 1 ? "1-29" : "30-58"), tr("Хорошо"));
}

void MainWindow::ConnectSignals()
{
    connect(&mt4080Thread, &QThread::finished, mt4080, &QObject::deleteLater);
    connect(mt4080, &MT4080::Display, this, &MainWindow::Display);
    connect(mt4080, &MT4080::Primary, this, &MainWindow::Primary);

    typedef void (QDoubleSpinBox::*func)(double);

    connect(ui->dsbMax, static_cast<func>(&QDoubleSpinBox::valueChanged), this, &MainWindow::dsb);
    connect(ui->dsbMaxErr, static_cast<func>(&QDoubleSpinBox::valueChanged), this, &MainWindow::dsb);
    connect(ui->dsbMin, static_cast<func>(&QDoubleSpinBox::valueChanged), this, &MainWindow::dsb);
    connect(ui->dsbMinErr, static_cast<func>(&QDoubleSpinBox::valueChanged), this, &MainWindow::dsb);

    connect(ui->groupBox_mt4080, &QGroupBox::clicked,
        [=](bool checked) {
            ui->groupBox_mt4080->setChecked(checked);
            ui->lineEdit_1->setEnabled(true);
            ui->lineEdit_2->setEnabled(true);
            ui->lineEdit_3->setEnabled(true);
            ui->lineEdit_4->setVisible(checked);
            ui->lineEdit_5->setVisible(checked);
            ui->lineEdit_6->setVisible(checked);
            ui->lineEdit_7->setVisible(checked);
            ui->lineEdit_8->setVisible(checked);
            ui->lineEdit_9->setVisible(checked);
        });

    connect(ui->groupBoxSettings, &QGroupBox::clicked,
        [=](bool checked) {
            ui->groupBoxSettings->setChecked(checked);
            ui->dsbMax->setVisible(checked);
            ui->dsbMaxErr->setVisible(checked);
            ui->dsbMin->setVisible(checked);
            ui->dsbMinErr->setVisible(checked);
            ui->lbSettings_1->setVisible(checked);
            ui->lbSettings_2->setVisible(checked);
            ui->lbSettings_3->setVisible(checked);
            ui->lbSettings_4->setVisible(checked);
            ui->label->setVisible(checked);
            ui->sbScale->setVisible(checked);
            if (checked)
                ui->groupBoxSettings->layout()->setMargin(6);
            else
                ui->groupBoxSettings->layout()->setMargin(0);
        });

    connect(ui->groupBoxConnection, &QGroupBox::clicked,
        [=](bool checked) {
            ui->label_5->setVisible(checked);
            ui->comboBoxMt4080->setVisible(checked);
            ui->pushButton->setVisible(checked);
            ui->pushButtonStartStopMeas->setVisible(checked);
            if (checked) {
                ui->gridLayoutConnection->setMargin(6);
                ui->groupBoxConnection->setTitle("Настройка связи:");
            } else {
                ui->gridLayoutConnection->setMargin(3);
                ui->groupBoxConnection->setTitle(QString("Настройка связи: (%1)").arg(ui->pushButton->isChecked() ? "Идёт опрос" : "Опрос остановлен"));
            }
        });

    connect(ui->pushButtonStartStopMeas, &QPushButton::clicked,
        [=](bool checked) {
            if (ui->pushButton->isChecked()) {
                ui->pushButtonStartStopMeas->setChecked(checked);
                if (checked) {
                    min = +std::numeric_limits<double>::max();
                    max = -std::numeric_limits<double>::max();
                } else {
                    checked = false;
                }
            } else {
                checked = false;
            }
            ui->pushButtonStartStopMeas->setChecked(checked);
            ui->pushButtonStartStopMeas->setText(checked ? "Остановить измерение" : "Начать измерение");
            ui->pushButtonStartStopMeas->setIcon(checked ? stop : start);
        });

    connect(ui->pushButton_clearTable, &QPushButton::clicked,
        [=]() {
            QMutexLocker locker(&mutex);
            reset();
            if (QMessageBox::question(this, "Сообщение", "pushButton_clearTable?") == QMessageBox::Yes) {
                ui->listWidget->clear();
                min = +std::numeric_limits<double>::max();
                max = -std::numeric_limits<double>::max();
            }
            values.clear();
        });

    connect(ui->pushButton, &QPushButton::clicked,
        [=](bool checked) {
            if (checked) {
                if (mt4080->Open(ui->comboBoxMt4080->currentText())) {
                    ui->pushButton->setText("Закончить опрос");
                    ui->pushButton->setIcon(stop);
                } else {
                    checked = false;
                }
            } else {
                mt4080->Close();
                ui->pushButton->setText("Начать опрос");
                ui->pushButton->setIcon(start);
            }
            ui->pushButton->setChecked(checked);
        });
}

void MainWindow::CreateChart()
{

    yAxis = new QValueAxis; // Ось X
    yAxis->setRange(0, 1); // Диапазон от 0 до времени которое соответстует SAMPLE_NUM точек

    xAxis = new QBarCategoryAxis; // Ось Y
    QStringList categories{ "1", "2", "3", "4", "5", "6", "7", "8", "9" };
    xAxis->append(categories);

    QChart* chart = new QChart();
    chart->setTitle("Bar chart");
    QStackedBarSeries* series = new QStackedBarSeries(chart);
    set = new QBarSet("Bar set " + QString::number(0));
    set->append(QList<qreal>{ 0, 0, 0, 0, 0, 0, 0, 0, 0 });
    series->append(set);
    series->setBarWidth(1);
    chart->addSeries(series);
    chart->setAxisX(xAxis, series); // Назначить ось xAxis, осью X для diagramA
    chart->setAxisY(yAxis, series);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setMargins(QMargins(2, 2, 2, 2));

    QChartView* chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing, true);
    chartView->chart()->legend()->hide();

    ui->verticalLayout->addWidget(chartView);
}

void MainWindow::Copy()
{
    QString str;
    if (ui->listWidget->count()) {
        for (int row = 0; row < ui->listWidget->count(); ++row) {
            str.append(ui->listWidget->item(row)->text());
            str.append("\r\n");
        }
        QApplication::clipboard()->setText(str);
    }
}

void MainWindow::contextMenuEvent(QContextMenuEvent* event)
{
    if (ui->listWidget->geometry().contains(event->pos())) {
        QMenu menu(this);
        menu.addAction(tr("Копировать данные"), [=]() { Copy(); }, QKeySequence::Copy);
        menu.exec(event->globalPos());
    }
}

void MainWindow::Primary(double val)
{
    if (!mutex.tryLock())
        return;

    val *= pow(10., ui->sbScale->value());

    if (ui->lineEdit_2->minimum() > val)
        ui->lineEdit_2->setMinimum(val);
    if (ui->lineEdit_2->maximum() < val)
        ui->lineEdit_2->setMaximum(val);

    ui->lineEdit_2->setValue(val);
    if (ui->pushButtonStartStopMeas->isChecked()) {
        if (border.maxErr > val && val > border.minErr) {
            if (++border.fl > 4) {
                if ((lastValue * 1.1 < val || val < lastValue * 0.9) && lastValue != 0.0) {
                    --border.fl;
                    mutex.unlock();
                    return;
                }
                QListWidgetItem* item;
                if (border.fl == 5) {
                    ui->listWidget->addItem("");
                    if (border.max > val && val > border.min)
                        yes.play();
                    else
                        no.play();
                }

                value += val;
                val = value / (border.fl - 4);
                lastValue = val;

                item = ui->listWidget->item(ui->listWidget->count() - 1);
                item->setText(QString::number(val).replace('.', ','));
                if (border.max > val && val > border.min)
                    item->setBackgroundColor(QColor(128, 255, 128));
                else
                    item->setBackgroundColor(QColor(255, 128, 128));
                ui->listWidget->scrollToItem(item);
            }
        } else {
            value /= border.fl - 4;
            if (value != 0) {
                values.append(value);
                UpdateChart(value);
            }
            reset();
        }
    }

    if (border.max > val && val > border.min)
        ui->lineEdit_2->setStyleSheet("QDoubleSpinBox{background-color:rgb(128, 255, 128)}");
    else
        ui->lineEdit_2->setStyleSheet("QDoubleSpinBox{background-color:rgb(255, 128, 128)}");

    timer.singleShot(50, Qt::CoarseTimer, [this]() { ui->lineEdit_2->setStyleSheet(""); });
    mutex.unlock();
}

void MainWindow::dsb(double)
{
    border.max = ui->dsbMax->value();
    border.maxErr = ui->dsbMaxErr->value();
    border.min = ui->dsbMin->value();
    border.minErr = ui->dsbMinErr->value();
    border.fl = 0;
}

void MainWindow::reset()
{
    value = 0.0;
    lastValue = 0.0;
    border.fl = 0;
}
