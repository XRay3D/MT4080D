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
#include <ranges>

using namespace QtCharts;

class PopupItemDelegate : public QStyledItemDelegate {
public:
    using QStyledItemDelegate::QStyledItemDelegate;
    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override {
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

    for(const QSerialPortInfo& info : QSerialPortInfo::availablePorts()) {
        if(info.manufacturer().contains("Silicon"))
            ui->cbxPortMt4080->addItem(info.portName());
    }

    CreateChart();

    mt4080 = new MT4080;
    mt4080->moveToThread(&mt4080Thread);
    ConnectSignals();

    mt4080Thread.start();

    readSettings();
    //on_pbTranses_clicked();
}

MainWindow::~MainWindow() {
    ui->pushButton->clicked(false);
    mt4080Thread.quit();
    mt4080Thread.wait();
    writeSettings();
    delete ui;
}

void MainWindow::display(const MT4080::Display& val) {
    ui->lePrimFunc->setText(val.primary.function);
    //    ui->dsbxPrimValue->setText(val.PrimaryValue);
    ui->lePrimUnit->setText(val.primary.unit);

    ui->leSecondFunc->setText(val.secondary.function);

    if(ui->dsbxSecondValue->minimum() > val.secondary.value)
        ui->dsbxSecondValue->setMinimum(val.secondary.value);
    if(ui->dsbxSecondValue->maximum() < val.secondary.value)
        ui->dsbxSecondValue->setMaximum(val.secondary.value);

    ui->dsbxSecondValue->setValue(val.secondary.value);
    ui->leSecondUnit->setText(val.secondary.unit);

    ui->leSpeed->setText(val.speed);
    ui->leFreq->setText(val.frequency);
    ui->leLevel->setText(val.level);
}

void MainWindow::writeSettings() {
    QSettings settings;

    settings.beginGroup("MainWindow");
    settings.setValue("size", size());
    settings.setValue("pos", pos());

    settings.setValue("WindowState", static_cast<int>(windowState()));

    settings.setValue("cbxPortMt4080", ui->cbxPortMt4080->currentText());

    settings.setValue("grbxMt4080", ui->grbxMt4080->isChecked());
    settings.setValue("grbxSettings", ui->grbxSettings->isChecked());

    settings.setValue("dsbMax", ui->dsbMax->value());
    settings.setValue("dsbMaxErr", ui->dsbMaxErr->value());
    settings.setValue("dsbMin", ui->dsbMin->value());
    settings.setValue("dsbMinErr", ui->dsbMinErr->value());
    settings.setValue("sbScale", ui->sbScale->value());

    settings.endGroup();
}

void MainWindow::UpdateChart() {
    if(barMin > values.last())
        barMin = values.last();
    if(barMax < values.last())
        barMax = values.last();

    if(values.size() < 2)
        return;

    double mid = barMax - barMin;

    int bar[9]{}; // = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    const double k = 0.11111111111111111111111111111111111111;

    const double ranges[]{
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

    for(double v : values) {
        for(int j = 0; j < 9; ++j) {
            if(ranges[j] <= v && v <= ranges[j + 1]) {
                ++bar[j];
                break;
            }
        }
    }

    int maxRange = 0;
    QStringList categories;
    for(int j = 0; j < 9; ++j) {
        set->replace(j, bar[j]);
        maxRange = qMax(maxRange, bar[j]);
        categories.append(QString("%1-%2").arg(ranges[j], 0, 'g').arg(ranges[j + 1], 0, 'g'));
    }
    xAxis->setCategories(categories);
    yAxis->setRange(0, maxRange);
}

void MainWindow::readSettings() {
    QSettings settings;

    settings.beginGroup("MainWindow");

    resize(settings.value("size", QSize(400, 400)).toSize());
    move(settings.value("pos", QPoint(200, 200)).toPoint());

    setWindowState(static_cast<Qt::WindowState>(settings.value("WindowState").toInt()));

    ui->cbxPortMt4080->setCurrentText(settings.value("cbxPortMt4080").toString());
    ui->grbxMt4080->clicked(settings.value("grbxMt4080").toBool());
    ui->grbxSettings->clicked(settings.value("grbxSettings").toBool());

    ui->dsbMax->setValue(settings.value("dsbMax").toDouble());
    ui->dsbMaxErr->setValue(settings.value("dsbMaxErr").toDouble());
    ui->dsbMin->setValue(settings.value("dsbMin").toDouble());
    ui->dsbMinErr->setValue(settings.value("dsbMinErr").toDouble());
    ui->sbScale->setValue(settings.value("sbScale").toInt());

    settings.endGroup();
}

void MainWindow::ConnectSignals() {
    connect(&mt4080Thread, &QThread::finished, mt4080, &QObject::deleteLater);
    connect(mt4080, &MT4080::display, this, &MainWindow::display);
    connect(mt4080, &MT4080::primary, this, &MainWindow::primary);

    connect(ui->dsbMax, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::dsb);
    connect(ui->dsbMaxErr, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::dsb);
    connect(ui->dsbMin, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::dsb);
    connect(ui->dsbMinErr, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::dsb);

    connect(ui->grbxMt4080, &QGroupBox::clicked, [=](bool checked) {
        ui->lePrimFunc->setEnabled(true);
        ui->dsbxPrimValue->setEnabled(true);
        ui->lePrimUnit->setEnabled(true);
        ui->leSecondFunc->setVisible(checked);
        ui->dsbxSecondValue->setVisible(checked);
        ui->leSecondUnit->setVisible(checked);
        ui->leSpeed->setVisible(checked);
        ui->leFreq->setVisible(checked);
        ui->leLevel->setVisible(checked);
    });

    connect(ui->grbxSettings, &QGroupBox::clicked, [=](bool checked) {
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
        if(checked)
            ui->grbxSettings->layout()->setMargin(6);
        else
            ui->grbxSettings->layout()->setMargin(3);
    });

    connect(ui->groupBoxConnection, &QGroupBox::clicked, [=](bool checked) {
        ui->checkBox->setVisible(checked);
        ui->cbxPortMt4080->setVisible(checked);
        ui->pushButton->setVisible(checked);
        ui->pushButtonStartStopMeas->setVisible(checked);
        if(checked) {
            ui->gridLayoutConnection->setMargin(6);
            ui->groupBoxConnection->setTitle("Настройка связи:");
        } else {
            ui->gridLayoutConnection->setMargin(3);
            ui->groupBoxConnection->setTitle(QString("Настройка связи: (%1)").arg(ui->pushButton->isChecked() ? "Идёт опрос" : "Опрос остановлен"));
        }
    });

    connect(ui->pushButtonStartStopMeas, &QPushButton::clicked,
            [=](bool checked) {
                if(ui->pushButton->isChecked()) {
                    ui->pushButtonStartStopMeas->setChecked(checked);
                    if(checked) {
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
                if(QMessageBox::question(this, "Сообщение", "pushButton_clearTable?") == QMessageBox::Yes) {
                    model->clear();
                    barMin = +std::numeric_limits<double>::max();
                    barMax = -std::numeric_limits<double>::max();
                }
                values.clear();
            });

    connect(ui->pushButton, &QPushButton::clicked,
            [=](bool checked) {
                if(checked) {
                    if(mt4080->open(ui->cbxPortMt4080->currentText())) {
                        ui->pushButton->setText("Закончить опрос");
                        ui->pushButton->setIcon(stop);
                    } else {
                        checked = false;
                    }
                } else {
                    mt4080->close();
                    ui->pushButton->setText("Начать опрос");
                    ui->pushButton->setIcon(start);
                }
                ui->pushButton->setChecked(checked);
            });
}

void MainWindow::CreateChart() {
    QChart* chart = new QChart();
    chart->setTitle("Bar chart");
    QStackedBarSeries* series = new QStackedBarSeries(chart);
    set = new QBarSet("Bar set " + QString::number(0));
    set->append({0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0});
    series->append(set);
    series->setBarWidth(1);

    chart->addSeries(series);
    chart->createDefaultAxes();

    yAxis = static_cast<QValueAxis*>(chart->axes(Qt::Vertical).front());
    yAxis->setRange(0, 1); // Диапазон от 0 до времени которое соответстует SAMPLE_NUM точек
    xAxis = static_cast<QBarCategoryAxis*>(chart->axes(Qt::Horizontal).front());
    xAxis->append({"1", "2", "3", "4", "5", "6", "7", "8", "9"}); // Назначить ось xAxis, осью X для diagramA

    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setMargins({2, 2, 2, 2});

    QChartView* chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing, true);
    chartView->chart()->legend()->hide();

    ui->verticalLayout->addWidget(chartView);
}

void MainWindow::contextMenuEvent(QContextMenuEvent* event) {
    if(model && ui->tableView->geometry().contains(event->pos()) && ui->tableView->model()->rowCount()) {
        QMenu menu(this);
        menu.addAction(
            tr("Копировать данные"), [this]() { model->copy(); }, QKeySequence::Copy);
        menu.exec(event->globalPos());
    }
}

void MainWindow::primary(double val) {
    if(!mutex.tryLock())
        return;

    val *= pow(10., ui->sbScale->value());

    if(ui->dsbxPrimValue->minimum() > val)
        ui->dsbxPrimValue->setMinimum(val);

    if(ui->dsbxPrimValue->maximum() < val)
        ui->dsbxPrimValue->setMaximum(val);

    ui->dsbxPrimValue->setValue(val);
    if(ui->pushButtonStartStopMeas->isChecked()) {
        if(border.maxErr > val && val > border.minErr) {
            if(++border.fl > 4) {
                if((lastValue * 1.1 < val || val < lastValue * 0.9) && lastValue != 0.0) {
                    --border.fl;
                    mutex.unlock();
                    return;
                }
                if(border.fl == 5) {
                    model->addData(0.0, true);
                    if(border.max > val && val > border.min)
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
            if(value != 0.0) {
                values.append(value);
                UpdateChart();
            }
            reset();
        }
    }

    if(border.max > val && val > border.min)
        ui->dsbxPrimValue->setStyleSheet("QDoubleSpinBox{background-color:rgb(128, 255, 128)}");
    else
        ui->dsbxPrimValue->setStyleSheet("QDoubleSpinBox{background-color:rgb(255, 128, 128)}");

    timer.singleShot(50, Qt::CoarseTimer, [this] { ui->dsbxPrimValue->setStyleSheet(""); });
    mutex.unlock();
}

void MainWindow::dsb(double) {
    border.max = ui->dsbMax->value();
    border.maxErr = ui->dsbMaxErr->value();
    border.min = ui->dsbMin->value();
    border.minErr = ui->dsbMinErr->value();
    border.fl = 0;
}

void MainWindow::reset() {
    value = 0.0;
    lastValue = 0.0;
    border.fl = 0;
}

void MainWindow::on_checkBox_clicked(bool checked) {
    ui->cbxPortMt4080->clear();

    auto ports{QSerialPortInfo::availablePorts().toVector()};
    std::ranges::sort(ports, {}, [](const QSerialPortInfo& info) { return info.portName().midRef(3).toUInt(); });
    for(const QSerialPortInfo& info : ports) {
        if(checked || info.manufacturer().contains("Silicon"))
            ui->cbxPortMt4080->addItem(info.portName());
    }
}

void MainWindow::on_cbxTrans_currentIndexChanged(int) {
    ui->dsbMax->setValue(ui->cbxTrans->currentData(Trans::RangeMax).toDouble());
    ui->dsbMin->setValue(ui->cbxTrans->currentData(Trans::RangeMin).toDouble());
    ui->cbxTrans->setToolTip(ui->cbxTrans->currentData(Trans::Pins).toString());
    ui->pbTranses->setToolTip(ui->cbxTrans->currentData(Trans::Pins).toString());
}

void MainWindow::on_pbTranses_clicked() {
    auto dialog = QDialog();
    auto hboxLayout = new QHBoxLayout(&dialog);
    auto tv = new QTableView(&dialog);
    hboxLayout->addWidget(tv);
    hboxLayout->setMargin(6);

    struct SortFilterProxyModel : QSortFilterProxyModel {
        explicit SortFilterProxyModel(QObject* parent = nullptr)
            : QSortFilterProxyModel(parent) { }

    protected:
        bool lessThan(const QModelIndex& srcLeft, const QModelIndex& srcRight) const override {
            if(srcLeft.column() == TransModel::Marking) {
                static auto toDouble = [](const QModelIndex& index) { return index.data().toString().replace('/', '.').midRef(1).toDouble(); };
                return toDouble(srcLeft) < toDouble(srcRight);
            }
            return QSortFilterProxyModel::lessThan(srcLeft, srcRight);
        }
    };

    auto pm = new SortFilterProxyModel(tv);
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
    connect(tv->findChild<QAbstractButton*>(), &QAbstractButton::clicked, [tv] { tv->sortByColumn(0, Qt::AscendingOrder); });
    dialog.resize(1280, 720);
    dialog.exec();
}
