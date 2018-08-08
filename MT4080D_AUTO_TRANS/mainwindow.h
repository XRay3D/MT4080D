#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QListWidget>
#include <QMainWindow>
#include <QThread>
#include "mt4080.h"
#include <QSound>
#include <QMutex>
#include <QtCharts/QChartGlobal>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QBarSet>

namespace Ui {
class MainWindow;
}

class QTableWidgetItem;

////using namespace QtCharts;
//QT_CHARTS_BEGIN_NAMESPACE
//class QBarCategoryAxis;
//class QValueAxis;
//class QBarSet;
//QT_CHARTS_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

private slots:
    void Display(const MT4080::Display_t& val);
    void Primary(double val);

private:
    Ui::MainWindow* ui;

    double lastValue = 0.0;
    double value = 0.0;
    double min = 0.0;
    double max = 0.0;

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
    void Copy();
    void MessageErrorRelaySwitch();
    void MessageMeasureEnded();
    void MessageMoveBoard(int val);
    void readSettings();
    void writeSettings();
    void UpdateChart(double val);
    void dsb(double);
    void reset();

    typedef struct border_t {
        double max;
        double maxErr;
        double min;
        double minErr;
        int fl;
    } border_t;

    border_t border;
};

#endif // MAINWINDOW_H