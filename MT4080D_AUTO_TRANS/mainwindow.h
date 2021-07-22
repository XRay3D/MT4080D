#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QListWidget>
#include <QMainWindow>
#include <QMutex>
#include <QSound>
#include <QThread>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QBarSet>
#include <QtCharts/QChartGlobal>
#include <QtCharts/QValueAxis>
#include <mt4080.h>

namespace Ui {
class MainWindow;
}

//class QTableWidgetItem;
class Model;

////using namespace QtCharts;
//QT_CHARTS_BEGIN_NAMESPACE
//class QBarCategoryAxis;
//class QValueAxis;
//class QBarSet;
//QT_CHARTS_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void display(const MT4080::Display& val);
    void on_cbxTrans_currentIndexChanged(int index);
    void on_checkBox_clicked(bool checked);
    void on_pbTranses_clicked();
    void on_tableView_customContextMenuRequested(const QPoint& pos);
    void primary(double val);

private:
    Ui::MainWindow* ui;

    double barMax = 0.0;
    double barMin = 0.0;
    double lastValue = 0.0;
    double value = 0.0;

    Model* model;
    MT4080* mt4080;

    QIcon start;
    QIcon stop;

    QMutex mutex;

    QSound no;
    QSound yes;

    QtCharts::QBarCategoryAxis* xAxis;
    QtCharts::QBarSet* set;
    QtCharts::QValueAxis* yAxis;

    QThread mt4080Thread;
    QTimer timer;
    std::vector<double> values;

    void connectUi();
    void createChart();
    void dsb(double);
    void readSettings();
    void reset();
    void updateChart();
    void writeSettings();

    struct Border {
        double max;
        double maxErr;
        double min;
        double minErr;
        int fl;
    } border;

    //    border_t border;
};

#endif // MAINWINDOW_H
