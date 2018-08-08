#include "mainwindow.h"
#include <QApplication>

// http://exlmoto.ru/git-and-qt-creator/

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName("XrSoft");
    a.setApplicationName("MT4080D_AUTO");
    a.setApplicationDisplayName("Автомат");

    MainWindow w;
    w.show();

    return a.exec();
}
