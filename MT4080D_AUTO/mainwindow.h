#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mt4080.h"
#include <QMainWindow>
#include <QMutex>
#include <QSettings>
#include <QThread>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

private slots:
    void Display(const MT4080::Display_t& val);
    void on_pbStartMeas_clicked(bool checked);
    void Primary(double val);
    void on_pbPing_clicked(bool checked);

private:
    Ui::MainWindow* ui;
    int Counter;
    int Pos;

    void writeSettings();
    void readSettings();

    void MessageMeasureEnded();
    void MessageErrorRelaySwitch();
    QIcon start;
    QIcon stop;
    QMutex mutex;
};

#endif // MAINWINDOW_H
