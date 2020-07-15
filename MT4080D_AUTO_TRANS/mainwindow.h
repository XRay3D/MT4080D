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
    void Display(const MT4080::Display_t& val);
    void Primary(double val);

    void on_checkBox_clicked(bool checked);

private:
    Ui::MainWindow* ui;

    double lastValue = 0.0;
    double value = 0.0;
    double barMin = 0.0;
    double barMax = 0.0;

    Model* model;
    MT4080* mt4080;

    QIcon start;
    QIcon stop;
    QMutex mutex;
    QSound no;
    QSound yes;

    QtCharts::QBarCategoryAxis* xAxis;
    QtCharts::QValueAxis* yAxis;
    QtCharts::QBarSet* set;

    QThread mt4080Thread;
    QTimer timer;
    QVector<double> values;

    void ConnectSignals();
    void CreateChart();
    void contextMenuEvent(QContextMenuEvent* event);

    void readSettings();
    void writeSettings();
    void UpdateChart();
    void dsb(double);
    void reset();

    /*typedef*/ struct border_t {
        double max;
        double maxErr;
        double min;
        double minErr;
        int fl;
    } /*border_t*/ border;

    //    border_t border;
};

#endif // MAINWINDOW_H
