#include "interface.h"

#include <QSemaphore>
#include <QThread>

QThread thread;
QSemaphore semafore;

MI::MI()
{
    if (!semafore.available()) {
        rel = new Relay;
        rel->moveToThread(&thread);
        thread.connect(&thread, &QThread::finished, rel, &QObject::deleteLater);

        //        mt = new MT4080;
        //        mt->moveToThread(&thread);
        //        thread.connect(&thread, &QThread::finished, mt, &QObject::deleteLater);

        scpi = new SCPI;
        scpi->moveToThread(&thread);
        thread.connect(&thread, &QThread::finished, scpi, &QObject::deleteLater);

        thread.start(QThread::NormalPriority);
    }
    semafore.release();
}

MI::~MI()
{
    semafore.acquire();
    if (!semafore.available()) {
        thread.quit();
        thread.wait();
    }
}
