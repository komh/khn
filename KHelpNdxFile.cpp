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

#include "KHelpNdxFile.h"

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

        pos = findNextNonSep( s );

        if( s[ pos ] == '(')
        {
            lastPos = findNextSep( s, ',');

            string strKeyWord( s.substr( pos + 1, lastPos - ( pos + 1 )));
            bool   fPrefix = false;

            pos = findNextSep( strKeyWord, '*');
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

                pos = findNextSep( strKeyWord, '*', pos + 1 );
            }

            KHelpNdxEntry khne;

            khne.strKeyWord = strKeyWord;
            khne.fPrefix    = fPrefix;

            pos = findNextNonSep( s, ' ', lastPos + 1 );

            size_t prevPos;

            for( prevPos = lastPos = pos; lastPos < s.length();
                 lastPos = findNextSep( s, ')', prevPos + 1 ))
                prevPos = lastPos;

            lastPos = prevPos;

            khne.strCmd = s.substr( pos, lastPos - pos );

            _vkhneEntry.push_back( khne );
        }
        else if( !s.compare( 0, 10, "EXTENSIONS"))
        {
            pos = findNextNonSep( s, ' ', 10 );
            if( pos != s.length() && s[ pos ] == ':' )
            {
                lastPos = pos;

                do
                {
                    pos = findNextNonSep( s, ' ', lastPos + 1 );

                    lastPos = findNextSep( s, ' ', pos );

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

bool KHelpNdxFile::Search( string& strCmd, const string& strSearchString,
                           const string& strExtension ) const
{
    bool fFound = false;

    for( vector< KHelpNdxEntry >::const_iterator it = _vkhneEntry.begin();
         it != _vkhneEntry.end(); ++it )
    {
        if( !it->fPrefix &&
            strSearchString.length() != it->strKeyWord.length())
            continue;

        if( !strSearchString.compare( 0, it->strKeyWord.length(),
                                      it->strKeyWord ))
        {
            strCmd = it->strCmd;
            size_t pos = strCmd.find_first_of('~');
            if( pos != string::npos )
                strCmd.replace( pos, 1, strSearchString );

            fFound = true;
            break;
        }
    }

    return fFound;
}
