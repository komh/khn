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

#include <iostream>

#include <string>

#include "KHelpNdx.h"

int main( int argc, char *argv[])
{

    if( argc < 2 )
    {
        cerr << "Too few arguments!!!" << endl
             << argv[ 0 ] << " topic" << endl;

        return 1;
    }

    KHelpNdx khn;

    string strCmd;

    if( khn.Search( strCmd, argv[ 1 ]))
        cout << "command : " << strCmd << endl;

    return 0;
}
