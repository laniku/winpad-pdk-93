//---------------------------------------------------------------------------
//		Copyright (C) 1991-92, Microsoft Corporation
//
// You have a royalty-free right to use, modify, reproduce and distribute
// the Sample Custom Control Files (and/or any modified version) in any way
// you find useful, provided that you agree that Microsoft has no warranty,
// obligation or liability for any Custom Control File.
//---------------------------------------------------------------------------
// Circ2.c
//---------------------------------------------------------------------------
// Contains control procedure for CIRC2 control
//---------------------------------------------------------------------------

#include <windows.h>
#include <vbapi.h>
#include "circ2.h"

//---------------------------------------------------------------------------
// Global Variables
//---------------------------------------------------------------------------
HANDLE hmodDLL;


//---------------------------------------------------------------------------
// Local Prototypes
//---------------------------------------------------------------------------
VOID NEAR PaintCircle(HCTL hctl, HWND hwnd, HDC hdc);
VOID NEAR RecalcArea(HCTL hctl, HWND hwnd);
VOID NEAR FlashCircle(HCTL hctl, HDC hdc);
BOOL NEAR InCircle(HCTL hctl, SHORT xcoord, SHORT ycoord);
VOID NEAR FireClickIn(HCTL hctl, SHORT x, SHORT y);
VOID NEAR FireClickOut(HCTL hctl);


//---------------------------------------------------------------------------
// Circle Control Procedure
//---------------------------------------------------------------------------
LONG FAR PASCAL _export CircleCtlProc
(
    HCTL   hctl,
    HWND   hwnd,
    USHORT msg,
    USHORT wp,
    LONG   lp
)
{
    switch (msg)
	{
	case WM_NCCREATE:
	    {
	    LPCIRC lpcirc = LpcircDEREF(hctl);

	    lpcirc->CircleShape = TRUE;
	    lpcirc->FlashColor = 128L;
	    VBSetControlProperty(hctl, IPROP_CIRCLE_BACKCOLOR, 255L);
	    // *** lpcirc may now be invalid due to call to VB API ***
	    break;
	    }

        case WM_LBUTTONDOWN:
        case WM_LBUTTONDBLCLK:
	    if (InCircle(hctl, (SHORT)lp, (SHORT)HIWORD(lp)))
		{
		HDC hdc = GetDC(hwnd);

		FlashCircle(hctl, hdc);
		ReleaseDC(hwnd, hdc);
		FireClickIn(hctl, (SHORT)lp, (SHORT)HIWORD(lp));
		}
	    else
		FireClickOut(hctl);
            break;

        case WM_LBUTTONUP:
	    if (InCircle(hctl, (SHORT)lp, (SHORT)HIWORD(lp)))
		{
		HDC hdc = GetDC(hwnd);

		PaintCircle(hctl, hwnd, hdc);
		ReleaseDC(hwnd, hdc);
		}
            break;

        case WM_PAINT:
            if (wp)
		PaintCircle(hctl, hwnd, (HDC)wp);
	    else
		{
                PAINTSTRUCT ps;

		BeginPaint(hwnd, &ps);
		PaintCircle(hctl, hwnd, ps.hdc);
		EndPaint(hwnd, &ps);
		}
            break;

        case WM_SIZE:
	    RecalcArea(hctl, hwnd);
            break;

        case VBM_SETPROPERTY:
	    switch (wp)
		{
		case IPROP_CIRCLE_SHAPE:
		    LpcircDEREF(hctl)->CircleShape = (SHORT)lp;
		    RecalcArea(hctl, hwnd);
		    InvalidateRect(hwnd, NULL, TRUE);
                    return 0;
		}
            break;

	}

    return VBDefControlProc(hctl, hwnd, msg, wp, lp);
}


//---------------------------------------------------------------------------
// Handle painting by drawing circle into the given hdc.
//---------------------------------------------------------------------------
VOID NEAR PaintCircle
(
    HCTL hctl,
    HWND hwnd,
    HDC  hdc
)
{
    HBRUSH hbr;
    HBRUSH hbrOld = NULL;
    LPRECT lprect = &LpcircDEREF(hctl)->rectDrawInto;

    hbr = (HBRUSH)SendMessage(GetParent(hwnd), WM_CTLCOLOR,
			      hdc, MAKELONG(hwnd, 0));
    if (hbr)
	hbrOld = SelectObject(hdc, hbr);
    Ellipse(hdc, lprect->left, lprect->top, lprect->right, lprect->bottom);
    if (hbrOld)
	SelectObject(hdc, hbrOld);	// Restore old brush
}


//---------------------------------------------------------------------------
// Paint the circle in the FlashColor.
//---------------------------------------------------------------------------
VOID NEAR FlashCircle
(
    HCTL hctl,
    HDC  hdc
)
{
    HBRUSH  hbr;
    HBRUSH  hbrOld = NULL;
    LPCIRC  lpcirc = LpcircDEREF(hctl);
    LPRECT  lprect = &lpcirc->rectDrawInto;

    hbr = CreateSolidBrush(RGBCOLOR(lpcirc->FlashColor));
    if (hbr)
	hbrOld = SelectObject(hdc, hbr);
    Ellipse(hdc, lprect->left, lprect->top, lprect->right, lprect->bottom);
    if (hbr)
	{
	SelectObject(hdc, hbrOld);
	DeleteObject(hbr);
	}
}


//---------------------------------------------------------------------------
// Use the hwnd's client size to determine the bounding rectangle for the
// circle.  If CircleShape is TRUE, then we need to calculate a square
// centered in lprect.
//---------------------------------------------------------------------------
VOID NEAR RecalcArea
(
    HCTL hctl,
    HWND hwnd
)
{
    LPCIRC lpcirc = LpcircDEREF(hctl);
    LPRECT lprect = &lpcirc->rectDrawInto;

    GetClientRect(hwnd, lprect);
    if (!lpcirc->CircleShape)
        return;
    if (lprect->right > lprect->bottom)
	{
	lprect->left  = (lprect->right - lprect->bottom) / 2;
	lprect->right = lprect->left + lprect->bottom;
	}
    else if (lprect->bottom > lprect->right)
	{
	lprect->top    = (lprect->bottom - lprect->right) / 2;
	lprect->bottom = lprect->top + lprect->right;
	}
}


//---------------------------------------------------------------------------
// Return TRUE if the given coordinates are inside of the circle.
//---------------------------------------------------------------------------
BOOL NEAR InCircle
(
    HCTL  hctl,
    SHORT xcoord,
    SHORT ycoord
)
{
    double  a, b;
    double  x, y;
    LPRECT  lprect = &LpcircDEREF(hctl)->rectDrawInto;

    a = (lprect->right	- lprect->left) / 2;
    b = (lprect->bottom - lprect->top)	/ 2;
    x = xcoord - (lprect->left + lprect->right)  / 2;
    y = ycoord - (lprect->top  + lprect->bottom) / 2;
    return ((x * x) / (a * a) + (y * y) / (b * b) <= 1);
}


//---------------------------------------------------------------------------
// TYPEDEF for parameters to the ClickIn event.
//---------------------------------------------------------------------------
typedef struct tagCLICKINPARMS
    {
    float far *Y;
    float far *X;
    LPVOID     Index;
    } CLICKINPARMS;


//---------------------------------------------------------------------------
// Fire the ClickIn event, passing the x,y coords of the click.
//---------------------------------------------------------------------------
VOID NEAR FireClickIn
(
    HCTL  hctl,
    SHORT x,
    SHORT y
)
{
    CLICKINPARMS params;
    float	 xTwips, yTwips;

    xTwips = (float)VBXPixelsToTwips(x);
    yTwips = (float)VBYPixelsToTwips(y);
    params.X = &xTwips;
    params.Y = &yTwips;
    VBFireEvent(hctl, IEVENT_CIRCLE_CLICKIN, &params);
}


//---------------------------------------------------------------------------
// Fire the ClickOut event.
//---------------------------------------------------------------------------
VOID NEAR FireClickOut
(
    HCTL hctl
)
{
    VBFireEvent(hctl, IEVENT_CIRCLE_CLICKOUT, NULL);
}


//---------------------------------------------------------------------------
// Initialize library. This routine is called when the first client loads
// the DLL.
//---------------------------------------------------------------------------
int FAR PASCAL LibMain
(
    HANDLE hModule,
    WORD   wDataSeg,
    WORD   cbHeapSize,
    LPSTR  lpszCmdLine
)
{
    // Avoid warnings on unused (but required) formal parameters
    wDataSeg	= wDataSeg;
    cbHeapSize	= cbHeapSize;
    lpszCmdLine = lpszCmdLine;

    hmodDLL = hModule;

    return 1;
}


//---------------------------------------------------------------------------
// Register custom control.  This routine is called by VB when the custom
// control DLL is loaded for use.
//---------------------------------------------------------------------------
BOOL FAR PASCAL _export VBINITCC
(
    USHORT usVersion,
    BOOL   fRuntime
)
{
    // Avoid warnings on unused (but required) formal parameters
    fRuntime  = fRuntime;
    usVersion = usVersion;

    // Register control(s)
    return VBRegisterModel(hmodDLL, &modelCircle);
}


//---------------------------------------------------------------------------
// WEP
//---------------------------------------------------------------------------
// C7 and QCWIN provide default a WEP:
//---------------------------------------------------------------------------
#if (_MSC_VER < 610)

int FAR PASCAL WEP(int fSystemExit);

//---------------------------------------------------------------------------
// For Windows 3.0 it is recommended that the WEP function reside in a
// FIXED code segment and be exported as RESIDENTNAME.  This is
// accomplished using the alloc_text pragma below and the related EXPORTS
// and SEGMENTS directives in the .DEF file.
//
// Read the comments section documenting the WEP function in the Windows
// 3.1 SDK "Programmers Reference, Volume 2: Functions" before placing
// any additional code in the WEP routine for a Windows 3.0 DLL.
//---------------------------------------------------------------------------
#pragma alloc_text(WEP_TEXT,WEP)

//---------------------------------------------------------------------------
// Performs cleanup tasks when the DLL is unloaded.  WEP() is
// called automatically by Windows when the DLL is unloaded (no
// remaining tasks still have the DLL loaded).	It is strongly
// recommended that a DLL have a WEP() function, even if it does
// nothing but returns success (1), as in this example.
//---------------------------------------------------------------------------
int FAR PASCAL WEP
(
    int fSystemExit
)
{
    // Avoid warnings on unused (but required) formal parameters
    fSystemExit = fSystemExit;

    return 1;
}
#endif // C6

//---------------------------------------------------------------------------
