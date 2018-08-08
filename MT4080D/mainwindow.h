#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QTimer>
#include <mt4080.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();
    void setVal(double value);

private slots:
    void on_pushButton_clicked(bool checked);
    void on_pushButton_2_clicked();
    void Display(const MT4080::Display_t& val);

private:
    Ui::MainWindow* ui;
    double val;

    MT4080* mt4080;
    QThread mt4080Thread;
};

#endif // MAINWINDOW_H
