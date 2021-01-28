#include "mainwindow.h"
#include "model.h"
#include "transmodel.h"
#include "ui_mainwindow.h"

#include <QClipboard>
#include <QContextMenuEvent>
#include <QDebug>
#include <QMenu>
#include <QMessageBox>
#include <QSerialPortInfo>
#include <QSettings>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QStackedBarSeries>
//#include <qt_windows.h>
#include <QElapsedTimer>
#include <QHeaderView>
#include <QScrollBar>
#include <QSortFilterProxyModel>
#include <QStyledItemDelegate>

using namespace QtCharts;

class PopupItemDelegate : public QStyledItemDelegate {
public:
    using QStyledItemDelegate::QStyledItemDelegate;
    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override
    {
        return QStyledItemDelegate::sizeHint(option, index) + QSize(0, 10);
    }
};

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , start(QStringLiteral(":/res/image2.png"))
    , stop(QStringLiteral(":/res/image3.png"))
    , no(QStringLiteral("C:/Windows/Media/Windows Critical Stop.wav"))
    , yes(QStringLiteral("C:/Windows/Media/Windows Notify.wav"))

{
    ui->setupUi(this);

    ui->tableView->setModel(model = new Model(border.min, border.max));

    //    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);

    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->cbxTrans->setModel(new TransModel(ui->cbxTrans));
    ui->cbxTrans->setModelColumn(2);
    ui->cbxTrans->view()->setItemDelegate(new PopupItemDelegate(ui->cbxTrans));
    //    ui->cbxTrans->setStyleSheet("QComboBox {"
    //                                "   padding-left: 2px;"
    //                                "   text-align: center;"
    //                                "}");

    for (const QSerialPortInfo& info : QSerialPortInfo::availablePorts()) {
        if (info.manufacturer().contains("Silicon"))
            ui->comboBoxMt4080->addItem(info.portName());
    }

    CreateChart();

    mt4080 = new MT4080;
    mt4080->moveToThread(&mt4080Thread);
    ConnectSignals();

    mt4080Thread.start();

    readSettings();
    //on_pbTranses_clicked();
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

    settings.setValue("WindowState", static_cast<int>(windowState()));

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

void MainWindow::UpdateChart()
{
    if (barMin > values.last())
        barMin = values.last();
    if (barMax < values.last())
        barMax = values.last();

    if (values.size() < 2)
        return;

    double mid = barMax - barMin;

    int bar[9] {}; // = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    const double k = 0.11111111111111111111111111111111111111;

    const double ranges[] {
        barMin + mid * 0 * k,
        barMin + mid * 1 * k,
        barMin + mid * 2 * k,
        barMin + mid * 3 * k,
        barMin + mid * 4 * k,
        barMin + mid * 5 * k,
        barMin + mid * 6 * k,
        barMin + mid * 7 * k,
        barMin + mid * 8 * k,
        barMin + mid * 9 * k,
    };

    for (double v : values) {
        for (int j = 0; j < 9; ++j) {
            if (ranges[j] <= v && v <= ranges[j + 1]) {
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
        categories.append(QString("%1-%2").arg(ranges[j], 0, 'g').arg(ranges[j + 1], 0, 'g'));
    }
    xAxis->setCategories(categories);
    yAxis->setRange(0, maxRange);
}

void MainWindow::readSettings()
{
    QSettings settings;

    settings.beginGroup("MainWindow");

    resize(settings.value("size", QSize(400, 400)).toSize());
    move(settings.value("pos", QPoint(200, 200)).toPoint());

    setWindowState(static_cast<Qt::WindowState>(settings.value("WindowState").toInt()));

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

void MainWindow::ConnectSignals()
{
    connect(&mt4080Thread, &QThread::finished, mt4080, &QObject::deleteLater);
    connect(mt4080, &MT4080::Display, this, &MainWindow::Display);
    connect(mt4080, &MT4080::Primary, this, &MainWindow::Primary);

    connect(ui->dsbMax, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::dsb);
    connect(ui->dsbMaxErr, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::dsb);
    connect(ui->dsbMin, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::dsb);
    connect(ui->dsbMinErr, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::dsb);

    connect(ui->groupBox_mt4080, &QGroupBox::clicked, [=](bool checked) {
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

    connect(ui->groupBoxSettings, &QGroupBox::clicked, [=](bool checked) {
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
            ui->groupBoxSettings->layout()->setMargin(3);
    });

    connect(ui->groupBoxConnection, &QGroupBox::clicked, [=](bool checked) {
        ui->checkBox->setVisible(checked);
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
                    barMin = +std::numeric_limits<double>::max();
                    barMax = -std::numeric_limits<double>::max();
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
                model->clear();
                barMin = +std::numeric_limits<double>::max();
                barMax = -std::numeric_limits<double>::max();
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
    QChart* chart = new QChart();
    chart->setTitle("Bar chart");
    QStackedBarSeries* series = new QStackedBarSeries(chart);
    set = new QBarSet("Bar set " + QString::number(0));
    set->append(QList<qreal> { 0, 0, 0, 0, 0, 0, 0, 0, 0 });
    series->append(set);
    series->setBarWidth(1);

    chart->addSeries(series);
    chart->createDefaultAxes();

    yAxis = static_cast<QValueAxis*>(chart->axes(Qt::Vertical).first());
    yAxis->setRange(0, 1); // Диапазон от 0 до времени которое соответстует SAMPLE_NUM точек
    xAxis = static_cast<QBarCategoryAxis*>(chart->axes(Qt::Horizontal).first());
    xAxis->append(QStringList { "1", "2", "3", "4", "5", "6", "7", "8", "9" }); // Назначить ось xAxis, осью X для diagramA

    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setMargins(QMargins(2, 2, 2, 2));

    QChartView* chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing, true);
    chartView->chart()->legend()->hide();

    ui->verticalLayout->addWidget(chartView);
}

void MainWindow::contextMenuEvent(QContextMenuEvent* event)
{
    if (model && ui->tableView->geometry().contains(event->pos()) && ui->tableView->model()->rowCount()) {
        QMenu menu(this);
        menu.addAction(
            tr("Копировать данные"), [this]() { model->copy(); }, QKeySequence::Copy);
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
                if (border.fl == 5) {
                    model->addData(0.0, true);
                    if (border.max > val && val > border.min)
                        yes.play();
                    else
                        no.play();
                }
                value += val;
                val = value / (border.fl - 4);
                lastValue = val;
                model->addData(val);
                ui->tableView->verticalScrollBar()->setValue(ui->tableView->verticalScrollBar()->maximum());
            }
        } else {
            value /= border.fl - 4;
            if (value != 0.0) {
                values.append(value);
                UpdateChart();
            }
            reset();
        }
    }

    if (border.max > val && val > border.min)
        ui->lineEdit_2->setStyleSheet("QDoubleSpinBox{background-color:rgb(128, 255, 128)}");
    else
        ui->lineEdit_2->setStyleSheet("QDoubleSpinBox{background-color:rgb(255, 128, 128)}");

    timer.singleShot(50, Qt::CoarseTimer, [this] { ui->lineEdit_2->setStyleSheet(""); });
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

void MainWindow::on_checkBox_clicked(bool checked)
{
    ui->comboBoxMt4080->clear();
    for (const QSerialPortInfo& info : QSerialPortInfo::availablePorts()) {
        if (checked || info.manufacturer().contains("Silicon"))
            ui->comboBoxMt4080->addItem(info.portName());
    }
}

void MainWindow::on_cbxTrans_currentIndexChanged(int)
{
    ui->dsbMax->setValue(ui->cbxTrans->currentData(Trans::RangeMax).toDouble());
    ui->dsbMin->setValue(ui->cbxTrans->currentData(Trans::RangeMin).toDouble());
}

void MainWindow::on_pbTranses_clicked()
{
    auto dialog = QDialog();
    auto hboxLayout = new QHBoxLayout(&dialog);
    auto tv = new QTableView(&dialog);
    hboxLayout->addWidget(tv);
    hboxLayout->setMargin(6);
    auto pm = new QSortFilterProxyModel(tv);
    pm->setSourceModel(ui->cbxTrans->model());
    pm->sort(0, Qt::AscendingOrder);
    tv->setSortingEnabled(true);
    tv->setModel(pm);
    tv->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    tv->horizontalHeader()->setSectionResizeMode(6, QHeaderView::Stretch);
    tv->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    tv->verticalHeader()->setDefaultSectionSize(0);
    tv->hideColumn(0);
    tv->setAlternatingRowColors(true);
    tv->findChild<QAbstractButton*>()->disconnect();
    connect(tv->findChild<QAbstractButton*>(), &QAbstractButton::clicked, [tv, this] {
        //        qint64 tt = 0, ctr = 0;
        //        QElapsedTimer t;
        //        for (int k = 0; k < 100; ++k) {
        //            t.start();
        //            for (int i = 0; i < ui->cbxTrans->model()->columnCount(); ++i)
        //                tv->sortByColumn(i, Qt::AscendingOrder);
        //            tv->sortByColumn(0, Qt::AscendingOrder);
        //            tt += t.nsecsElapsed();
        //            qDebug() << (tt / (1000000.0 * ++ctr)) << "ms" << k;
        //        }
        tv->sortByColumn(0, Qt::AscendingOrder);
    });
    dialog.resize(1280, 720);
    dialog.exec();
    //QTimer::singleShot(100, [] { exit(0); });
}
