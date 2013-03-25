#ifndef KHN_CLIENT_H
#define KHN_CLIENT_H

#define INCL_WIN
#include <os2.h>

#include <KPMLib.h>

#define IDEF_SEARCHSTRING 100

#define UM_FOCUSTOEF    ( WM_USER + 1 )

class KHNClient : public KWindow
{
public :
    KHNClient() {};
    virtual ~KHNClient() {};

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
    virtual MRESULT OnCreate( PVOID pCtrlData, PCREATESTRUCT pcs );
    virtual MRESULT OnDestroy();
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

