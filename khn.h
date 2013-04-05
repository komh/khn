/*
    khn, invoker the viwer of KwikINF on-line documents
    Copyright (C) 2013 by KO Myung-Hun <komh@chollian.net>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

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

