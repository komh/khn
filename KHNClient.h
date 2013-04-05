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

#ifndef KHN_CLIENT_H
#define KHN_CLIENT_H

#define INCL_WIN
#include <os2.h>

#include "KPMLib.h"

#define IDEF_SEARCHSTRING 100

#define UM_FOCUSTOEF    ( WM_USER + 1 )

class KHNClient : public KWindow
{
public :
    KHNClient() {};
    virtual ~KHNClient() {};

    void CalcClientRect( PRECTL prcl ) const;

protected :
    virtual MRESULT KWndProc( ULONG msg, MPARAM mp1, MPARAM mp2 )
    {
        if( msg == UM_FOCUSTOEF )
        {
            _kef.SetFocus();

            return 0;
        }

        return KWindow::KWndProc( msg, mp1, mp2 );
    }

    virtual MRESULT OnChar( USHORT fsFlags, UCHAR ucRepeat, UCHAR ucScanCode,
                            USHORT usCh, USHORT usVk );
    virtual MRESULT OnControl( USHORT id, USHORT usNotifyCode,
                               ULONG ulControlSpec );
    virtual MRESULT OnCreate( PVOID pCtrlData, PCREATESTRUCT pcs );
    virtual MRESULT OnDestroy();
    virtual MRESULT OnMove();
    virtual MRESULT OnPaint();
    virtual MRESULT OnSize( SHORT scxOld, SHORT scyOld,
                            SHORT scxNew, SHORT scyNew );

    virtual MRESULT OnSetFocus( HWND hwnd, bool fFocus )
    {
        PostMsg( UM_FOCUSTOEF );

        return 0;
    }

private :
    KEntryField _kef;

    void InvokeViewer();
};
#endif

