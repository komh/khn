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
#include <process.h>

#include "KHelpNdx.h"

using namespace std;

KHelpNdx::KHelpNdx()
{
    const char *pcszHelpNdx = getenv("HELPNDX");

    if( !pcszHelpNdx )
        return;

    string strHelpNdx( pcszHelpNdx );

    size_t lastPos;

    for( size_t pos = findFirstNonSep( strHelpNdx, ' ');
         pos < strHelpNdx.length();
         pos = lastPos + 1 )
    {
        lastPos = findFirstSep( strHelpNdx, '+', pos );

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
    bool fFound = false;

    _vkhneFound.clear();

    for( vector< KHelpNdxFile >::iterator it = _vkhnf.begin();
         it != _vkhnf.end(); ++it )
    {
        if( it->Search( _vkhneFound, strSearchString, strExtension ))
            fFound = true;
    }

    return fFound;
}

int KHelpNdx::Invoke() const
{
    if( !_vkhneFound.empty())
    {
        const KHelpNdxEntry *pkhne = 0;

        enum MatchLevel { MatchNone, MatchLonger, MatchLongerCase,
                          MatchExact, MatchExactCase };
        MatchLevel matchLevel = MatchNone;

        int prefixLen = -1;

        // show the exactly matched entry if it is there
        for( VKHNE::const_iterator it = _vkhneFound.begin();
             it != _vkhneFound.end(); ++it )
        {
            if( !it->fPrefix )
            {
                // show the case-sensitively matched entry first
                if( it->fCaseMatch )
                {
                    pkhne = &( *it );

                    break;
                }

                // show the first appearing case-insensitively matched entry
                if( matchLevel < MatchExact )
                {
                    matchLevel = MatchExact;

                    pkhne = &( *it );
                }
            }
            else if( matchLevel < MatchExact )
            {
                int len = it->strKeyWord.length();

                if( it->fCaseMatch &&
                    ( matchLevel < MatchLongerCase || len > prefixLen ))
                {
                    matchLevel = MatchLongerCase;

                    prefixLen = len;
                    pkhne = &( *it );
                }
                else if( matchLevel < MatchLongerCase &&
                         len > prefixLen )
                {
                    matchLevel = MatchLonger;

                    prefixLen = len;
                    pkhne = &( *it );
                }
            }
        }

        return spawnlp( P_NOWAIT, pkhne->strViewer.c_str(),
                                  pkhne->strViewer.c_str(),
                                  pkhne->strBook.c_str(),
                                  pkhne->strTopic.c_str(), 0 );
    }

    return -1;
}

