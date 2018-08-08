#include "interface.h"

#include <QSemaphore>
#include <QThread>

QThread thread;
QSemaphore semafore;

Relay* MI::rel = nullptr;
MT4080* MI::mt = nullptr;

MI::MI()
{
    if (!semafore.available()) {
        rel = new Relay;
        rel->moveToThread(&thread);
        thread.connect(&thread, &QThread::finished, rel, &QObject::deleteLater);

        mt = new MT4080;
        mt->moveToThread(&thread);
        thread.connect(&thread, &QThread::finished, mt, &QObject::deleteLater);

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
