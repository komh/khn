#define INCL_WIN
#include <os2.h>

#include <string>

#include <process.h>

#include "KHelpNdx.h"

#include "KHNClient.h"

MRESULT KHNClient::OnCreate( PVOID pCtrlData, PCREATESTRUCT pcs )
{
    _kef.CreateWindow( this, "", WS_VISIBLE | ES_MARGIN | ES_AUTOSCROLL,
                       0, 0, 0, 0, this, KWND_TOP, IDEF_SEARCHSTRING );

    return 0;
}

MRESULT KHNClient::OnDestroy()
{
    _kef.DestroyWindow();

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
    _kef.SetWindowPos( KWND_TOP, 10, 10, scxNew - 20, scyNew - 20,
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
            //KWindow kwndParent;

            //QueryWindow( QW_PARENT, kwndParent );
            //kwndParent.SetWindowPos( KWND_TOP, 0, 0, 0, 0, SWP_MINIMIZE );

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
    string strCmd;

    _kef.QueryWindowText( strSearchString );

    if( khn.Search( strSearchString ))
        khn.Invoke();

    GetParent().SetWindowPos( KWND_TOP, 0, 0, 0, 0, SWP_MINIMIZE );
}

