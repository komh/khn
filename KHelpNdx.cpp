/*
    KHelpNdx, parsing library of KwikINF index files
    Copyright (C) 2013 by KO Myung-Hun <komh@chollian.net>

    This program is free software; you can redistribute it and/or modify it
    under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program; if not, write to the Free Software Foundation,
    Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
*/

#include <string>
#include <vector>

#include <cstdlib>

#include "KHelpNdx.h"

KHelpNdx::KHelpNdx() : _pkhnfFound( 0 )
{
    const char *pcszHelpNdx = getenv("HELPNDX");

    if( !pcszHelpNdx )
        return;

    string strHelpNdx( pcszHelpNdx );

    size_t lastPos;

    for( size_t pos = findNextNonSep( strHelpNdx, ' ');
         pos < strHelpNdx.length();
         pos = lastPos + 1 )
    {
        lastPos = findNextSep( strHelpNdx, '+', pos );

        _vkhnf.push_back( KHelpNdxFile( strHelpNdx.substr( pos,
                                                           lastPos - pos )));
    }
}

KHelpNdx::~KHelpNdx()
{
}

bool KHelpNdx::Search( const string& strSearchString,
                       const string& strExtension )
{
    for( vector< KHelpNdxFile >::iterator it = _vkhnf.begin();
         it != _vkhnf.end(); ++it )
    {
        if( it->Search( strSearchString, strExtension ))
        {
            _pkhnfFound = &( *it );

            return true;
        }
    }

    return false;
}

int KHelpNdx::Invoke() const
{
    if( _pkhnfFound )
        return _pkhnfFound->Invoke();

    return -1;
}

