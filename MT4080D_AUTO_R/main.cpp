#include "mainwindow.h"
#include <QApplication>
#include "measuringinterface/interface.h"

// http://exlmoto.ru/git-and-qt-creator/

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    a.setOrganizationName("XrSoft");
    a.setApplicationName("MT4080D_AUTO");
    a.setApplicationDisplayName("Автомат");

    MI mi;
    Q_UNUSED(mi)

    MainWindow w;
    w.show();
    return a.exec();
}
