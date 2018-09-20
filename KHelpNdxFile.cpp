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

#define INCL_DOS
#include <os2.h>

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include <cstring>

#include "KHelpNdxFile.h"

using namespace std;

inline int strnicmp( const string& str1, const string& str2, size_t count )
{
    return ::strnicmp( str1.c_str(), str2.c_str(), count );
}

KHelpNdxFile::KHelpNdxFile( const string& strFilename )
{
    char szFilename[ CCHMAXPATH ];

    if( DosSearchPath( SEARCH_CUR_DIRECTORY | SEARCH_ENVIRONMENT,
                       "DPATH", strFilename.c_str(),
                       szFilename, sizeof( szFilename )))
        return;

    ifstream ifs( szFilename, ifstream::in );

    string s;
    size_t pos, lastPos;

    while( ifs.good())
    {
        getline( ifs, s );

        pos = findFirstNonSep( s );

        if( s[ pos ] == '(')
        {
            lastPos = findFirstSep( s, ',');

            string strKeyWord( s.substr( pos + 1, lastPos - ( pos + 1 )));
            bool   fPrefix = false;

            pos = findFirstSep( strKeyWord, '*');
            while( pos < strKeyWord.length())
            {
                if( strKeyWord[ pos + 1 ] == '*')
                    strKeyWord.erase( pos, 1 );
                else
                {
                    strKeyWord.erase( pos );
                    fPrefix = true;
                    break;
                }

                pos = findFirstSep( strKeyWord, '*', pos + 1 );
            }

            KHelpNdxEntry khne;

            khne.strKeyWord = strKeyWord;
            khne.fPrefix    = fPrefix;

            pos = findFirstNonSep( s, ' ', lastPos + 1 );
            lastPos = findFirstSep( s, ' ', pos + 1 );
            khne.strViewer = s.substr( pos, lastPos - pos );

            pos = findFirstNonSep( s, ' ', lastPos + 1 );
            lastPos = findFirstSep( s, ' ', pos + 1 );
            khne.strBook = s.substr( pos, lastPos - pos );

            pos = findFirstNonSep( s, ' ', lastPos + 1 );
            lastPos = findLastSep( s, ')');
            khne.strTopic = s.substr( pos, lastPos - pos );

            _vkhneEntry.push_back( khne );
        }
        else if( s.compare( pos, 10, "EXTENSIONS" ))
        {
            pos = findFirstNonSep( s, ' ', 10 );
            if( pos != s.length() && s[ pos ] == ':' )
            {
                lastPos = pos;

                do
                {
                    pos = findFirstNonSep( s, ' ', lastPos + 1 );

                    lastPos = findFirstSep( s, ' ', pos );

                    _vstrExtensions.push_back( s.substr( pos,
                                                         lastPos - pos ));
                } while( lastPos < s.length());
            }
        }
    }

    ifs.close();
}

KHelpNdxFile::~KHelpNdxFile()
{
}

bool KHelpNdxFile::Search( VKHNE& vkhneFound,
                           const string& strSearchString,
                           const string& strExtension ) const
{
    bool fFound = false;

    for( vector< KHelpNdxEntry >::const_iterator it = _vkhneEntry.begin();
         it != _vkhneEntry.end(); ++it )
    {
        if( !it->fPrefix &&
            strSearchString.length() != it->strKeyWord.length())
            continue;

        if( !strnicmp( strSearchString, it->strKeyWord,
                       it->strKeyWord.length()))
        {
            KHelpNdxEntry khneFound( *it );

            size_t pos = khneFound.strTopic.find_first_of('~');
            if( pos != string::npos )
                khneFound.strTopic.replace( pos, 1, strSearchString );

            khneFound.vstrExtensions = _vstrExtensions;

            khneFound.fCaseMatch =
                !strSearchString.compare( 0, it->strKeyWord.length(),
                                          it->strKeyWord );

            vkhneFound.push_back( khneFound );

            fFound = true;
        }
    }

    return fFound;
}

