#ifndef KHN_H
#define KHN_H

#include "KPMLib.h"

#define KHN_VERSION "1.0.0"

#define ID_KHN 1

#define WC_KHN "KHN CLASS"

#define KHN_TITLE  "KHelpNdx"

#define KHN_POSITION_KEY "Position"

#ifdef DEBUG
#include <cstdio>

#define dprintf( ... ) \
do {\
    FILE* fp;\
    fp = fopen("khn.log", "at");\
    fprintf( fp, __VA_ARGS__ );\
    fclose( fp );\
} while( 0 )
#else
#define dprintf( ... ) do { } while( 0 )
#endif

class KHN : public KPMApp
{
public :
    KHN() : KPMApp() {}
    ~KHN() {}

    virtual int Run();
};
#endif

