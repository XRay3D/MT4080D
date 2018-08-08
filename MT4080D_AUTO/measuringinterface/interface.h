#ifndef MI_H
#define MI_H

#include "relay.h"
#include <QObject>
#include <mt4080.h>

class MI {
public:
    MI();
    ~MI();
    static Relay* rel;
    static MT4080* mt;
};

#endif // MI_H
