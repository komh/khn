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

#ifndef K_HELP_NDX_FILE_H
#define K_HELP_NDX_FILE_H

#include <string>
#include <vector>

using namespace std;

struct KHelpNdxEntry
{
    string strKeyWord;
    bool   fPrefix;
    string strViewer;
    string strBook;
    string strTopic;
};

class KHelpNdxFile
{
public :
    KHelpNdxFile( const string& strFilename );
    ~KHelpNdxFile();

    bool Search( const string& strSearchString,
                 const string& strExtension = "");

    int Invoke() const;

private :
    vector< string >        _vstrExtensions;
    vector< KHelpNdxEntry > _vkhneEntry;
    KHelpNdxEntry           _khneFound;
};

inline size_t findNextNonSep( const string& str, char sep = ' ',
                              size_t pos = 0 )
{
    size_t nextPos = str.find_first_not_of( sep, pos );

    return ( nextPos == string::npos ) ? str.length() : nextPos;
}

inline size_t findNextSep( const string& str, char sep = ' ',
                           size_t pos = 0 )
{
    size_t lastPos = str.find_first_of( sep, pos );

    return ( lastPos == string::npos ) ? str.length() : lastPos;
}

inline size_t findLastSep( const string& str, char sep = ' ',
                           size_t pos = string::npos )
{
    size_t lastPos = str.find_last_of( sep, pos );

    return ( lastPos == string::npos ) ? str.length() : lastPos;
}
#endif
