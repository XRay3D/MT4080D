#pragma once

#include "mt4080.h"
#include "mymodel.h"
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
    static inline UsedMap selected;

private slots:
    void on_pbStartMeas_clicked(bool checked);
    void primary(double val);
    void on_pbPing_clicked(bool checked);

signals:
    void startMeasure();

private:
    void display(double val);

    Ui::MainWindow* ui;
    int counter = 0;
    int currentPos = 0;
    int timerId = 0;
    void writeSettings();
    void readSettings();

    bool sideMessageBox = false;

    enum Message {
        MeasureEnded,
        ErrorRelaySwitch,
        Side_01_29,
        Side_30_58,
    };

    void showMessage(Message msg);

    QIcon start;
    QIcon stop;
    QMutex mutex;
    QSemaphore semaphore;
    // QObject interface
protected:
    void timerEvent(QTimerEvent* event) override;
};
