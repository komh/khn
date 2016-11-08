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

#define INCL_WIN
#include <os2.h>

#include <string>

#include <process.h>

#include "khn.h"

#include "KHelpNdx.h"

#include "KHNClient.h"

using namespace std;

#define CHAR_COUNT  25

#define BORDER_SIZE 1

#define HORZ_MARGIN 10
#define VERT_MARGIN 10

void KHNClient::CalcClientRect( PRECTL prcl ) const
{
    KWindowPS kps;

    RECTL rcl = { 0, 0, 100, 100 };

    kps.GetPS( &_kef );
    kps.DrawText( 1, "H", &rcl, 0, 0, DT_QUERYEXTENT | DT_EXTERNALLEADING );
    kps.ReleasePS();

    LONG w = rcl.xRight - rcl.xLeft;
    LONG h = rcl.yTop - rcl.yBottom;

    prcl->xLeft   = 0;
    prcl->yBottom = 0;
    prcl->xRight  = w * CHAR_COUNT + BORDER_SIZE * 2 + HORZ_MARGIN * 2;
    prcl->yTop    = h + BORDER_SIZE * 2 + VERT_MARGIN * 2;
}

MRESULT KHNClient::OnControl( USHORT id, USHORT usNotifyCode,
                              ULONG ulControlSpec )
{
    if( id == IDEF_SEARCHSTRING && usNotifyCode == EN_SETFOCUS )
    {
        _kef.SetSel( 0, _kef.QueryWindowTextLength());

        return 0;
    }

    return KWindow::OnControl( id, usNotifyCode, ulControlSpec );
}

MRESULT KHNClient::OnCreate( PVOID pCtrlData, PCREATESTRUCT pcs )
{
    _kef.CreateWindow( this, "", WS_VISIBLE | ES_MARGIN | ES_AUTOSCROLL,
                       0, 0, 0, 0, this, KWND_TOP, IDEF_SEARCHSTRING );

    _kef.SetTextLimit( 256 );

    return 0;
}

MRESULT KHNClient::OnDestroy()
{
    _kef.DestroyWindow();

    return 0;
}

MRESULT KHNClient::OnMove()
{
    GetParent().StoreWindowPos( KHN_TITLE, KHN_POSITION_KEY );

    return 0;
}

MRESULT KHNClient::OnPaint()
{
    KWindowPS kps;
    RECTL     rcl;

    kps.BeginPaint( this, 0, &rcl );

    kps.FillRect( &rcl, SYSCLR_WINDOW );

    kps.EndPaint();

    return 0;
}

MRESULT KHNClient::OnSize( SHORT scxOld, SHORT scyOld,
                           SHORT scxNew, SHORT scyNew )
{
    _kef.SetWindowPos( KWND_TOP, HORZ_MARGIN, VERT_MARGIN,
                       scxNew - HORZ_MARGIN * 2, scyNew - VERT_MARGIN * 2,
                       SWP_SIZE | SWP_MOVE | SWP_SHOW );

    return 0;
}

MRESULT KHNClient::OnChar( USHORT fsFlags, UCHAR ucRepeat, UCHAR ucScanCode,
                           USHORT usCh, USHORT usVk )
{
    if( !( fsFlags & KC_KEYUP ) && ( fsFlags & KC_VIRTUALKEY ))
    {
        if( usVk == VK_ENTER || usVk == VK_NEWLINE )
        {
            InvokeViewer();

            return MRFROMLONG( TRUE );
        }
        else if( usVk == VK_ESC )
        {
            GetParent().SetWindowPos( KWND_TOP, 0, 0, 0, 0, SWP_MINIMIZE );

            KWindow kwndNextTop;
            GetParent().QueryWindow( QW_NEXTTOP, kwndNextTop );
            kwndNextTop.SetActiveWindow();
        }
    }


    return 0;
}

void KHNClient::InvokeViewer()
{
    KHelpNdx khn;
    string strSearchString;

    _kef.QueryWindowText( strSearchString );

    if( khn.Search( strSearchString ))
    {
        khn.Invoke();

        GetParent().SetWindowPos( KWND_TOP, 0, 0, 0, 0, SWP_MINIMIZE );
    }
    else
        MessageBox("Failed to search a topic in HELPNDX", KHN_TITLE,
                   MB_OK | MB_ERROR );
}

