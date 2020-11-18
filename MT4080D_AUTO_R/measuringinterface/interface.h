#ifndef MI_H
#define MI_H

//#include "mt4080.h"
#include "relay.h"
#include "scpi.h"
#include <QObject>

class MI {
public:
    MI();
    ~MI();
    static inline Relay* rel;
    //    static inline MT4080* mt;
    static inline SCPI* scpi;
};

#endif // MI_H
