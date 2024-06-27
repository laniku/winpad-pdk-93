//---------------------------------------------------------------------------
//		Copyright (C) 1991-92, Microsoft Corporation
//
// You have a royalty-free right to use, modify, reproduce and distribute
// the Sample Custom Control Files (and/or any modified version) in any way
// you find useful, provided that you agree that Microsoft has no warranty,
// obligation or liability for any Custom Control File.
//---------------------------------------------------------------------------
// Circ3.c
//---------------------------------------------------------------------------
// Contains control procedure for CIRC3 control
//---------------------------------------------------------------------------

#include <windows.h>
#include <vbapi.h>
#include <string.h>
#include "circ3.h"	  // Declares Vb2.0 compatiable model information
#include "circ3vb1.h"	  // Declares Vb1.0 compatiable model information


//---------------------------------------------------------------------------
// Local Prototypes
//---------------------------------------------------------------------------
VOID NEAR PaintCircle(HCTL hctl, HWND hwnd, HDC hdc);
VOID NEAR RecalcArea(HCTL hctl, HWND hwnd);
VOID NEAR FlashCircle(HCTL hctl, HDC hdc);
BOOL NEAR InCircle(HCTL hctl, SHORT xcoord, SHORT ycoord);
VOID NEAR FireClickIn(HCTL hctl, HWND hwnd, SHORT x, SHORT y);
VOID NEAR FireClickOut(HCTL hctl);
HWND NEAR HwndInitFlashPopup(VOID);
VOID NEAR DisplayHelpTopic(CHAR chKeylist, LPSTR lpszKeyword);
BOOL _export FAR PASCAL FlashDlgProc(HWND hDlg, USHORT msg, USHORT wp, LONG lp);


//---------------------------------------------------------------------------
// Global Variables
//---------------------------------------------------------------------------
HANDLE hmodDLL;
WORD   cVbxUsers = 0;
BOOL   fDevTimeInited = FALSE;


//---------------------------------------------------------------------------
// Global Variables for FlashColor dialog
//---------------------------------------------------------------------------
BOOL   fDlgInUse = FALSE;
HCTL   hctlDialog;
USHORT ipropDialog;
LONG   colorOldDialog;


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
	    LPCIRC lpcirc = (LPCIRC)VBDerefControl(hctl);

	    lpcirc->CircleShape = SHAPE_CIRCLE;
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
		FireClickIn(hctl, hwnd, (SHORT)lp, (SHORT)HIWORD(lp));
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

        case WM_SETFONT:
	    LpcircDEREF(hctl)->hfont = (HFONT)wp;
            return 0;

        case WM_GETFONT:
	    return LpcircDEREF(hctl)->hfont;

        case WM_SETTEXT:
            {
	    HSZ    hsz;
	    LPCIRC lpcirc = LpcircDEREF(hctl);

	    if (lpcirc->hszCaption)
		{
		VBDestroyHsz(lpcirc->hszCaption);
		// *** lpcirc may now be invalid due to call to VB API ***
		}
	    hsz = VBCreateHsz((_segment)hctl, (LPSTR)lp);
	    // *** lpcirc may now be invalid due to call to VB API ***
	    LpcircDEREF(hctl)->hszCaption = hsz;
	    InvalidateRect(hwnd, NULL, TRUE);
	    return 0L;
            }

        case WM_GETTEXT:
            {
	    LPSTR  lpstr;
	    USHORT cch;
	    LPCIRC lpcirc = LpcircDEREF(hctl);

	    if (lpcirc->hszCaption == NULL)
		{
		*(LPSTR)lp = 0L;
		wp = 1;
		}
	    else
		{
		lpstr = VBDerefHsz(lpcirc->hszCaption);
		cch = (USHORT)(lstrlen(lpstr) + 1);
		if (wp > cch)
		    wp = cch;
		_fstrncpy((LPSTR)lp, lpstr, wp);
		((LPSTR)lp)[wp - 1] = '\0';
		}
            }
	    return (LONG)(wp - 1);

	case WM_GETTEXTLENGTH:
	    {
	    LPCIRC lpcirc = LpcircDEREF(hctl);

	    if (lpcirc->hszCaption == NULL)
                return 0L;
            else
		return lstrlen(VBDerefHsz(lpcirc->hszCaption));
	    }


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
                case IPROP_CIRCLE_CIRCLESHAPE:
		    LpcircDEREF(hctl)->CircleShape = (ENUM)lp;
		    RecalcArea(hctl, hwnd);
		    InvalidateRect(hwnd, NULL, TRUE);
		    return 0L;
		}
            break;

	case VBM_HELP:
	    switch (LOBYTE(wp))
		{
		case VBHELP_PROP:
		    // High byte identifies which property.
		    // Keyword is: "<property>"
		    switch (HIBYTE(wp))
			{
			case IPROP_CIRCLE_CIRCLESHAPE:
			    DisplayHelpTopic('P', "CircleShape");
			    return 0L;

			case IPROP_CIRCLE_FLASHCOLOR:
			    DisplayHelpTopic('P', "FlashColor");
			    return 0L;
			}
		    break;

		case VBHELP_EVT:
		    // High byte identifies which event
		    // Keyword is: "<event>"
		    switch (HIBYTE(wp))
			{
			case IEVENT_CIRCLE_CLICKIN:
			    DisplayHelpTopic('V', "ClickIn");
			    return 0L;

			case IEVENT_CIRCLE_CLICKOUT:
			    DisplayHelpTopic('V', "ClickOut");
			    return 0L;
			}
		    break;

		case VBHELP_CTL:
		    // High byte is unused.
		    // Keyword is: "<classname>"
		    DisplayHelpTopic('C', "CIRC3");
		    return 0L;
		}
	    break;

        case VBM_INITPROPPOPUP:
	    switch (wp)
		{
		// Un-commenting the following line will enable our custom
		// popup instead of the color palette, when setting the
		// backcolor:
		// case IPROP_CIRCLE_BACKCOLOR:
		case IPROP_CIRCLE_FLASHCOLOR:
		    {
		    if (fDlgInUse)
		      // Our dialog is already in use, so return NULL here
		      // to avoid bringing up a 2nd instance of the dialog.
		      // We could get around this restriction by storing
		      // hctlDialog, ipropDialog, and colorOldDialog as
		      // window words of hwndPopup.
		      // NOTE: In this specific case, because FlashColor
		      // is DT_COLOR, we could also just "break;" to go
		      // through default processing which would bring up
		      // the default color palette.
		      return NULL;

		    // Tell the hwndPopup which control and iprop we want
		    // the dialog to change
		    fDlgInUse	= TRUE;
		    hctlDialog	= hctl;
		    ipropDialog = wp;

		    return HwndInitFlashPopup();
		    }
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
    LPSTR  lpstr;
    LPCIRC lpcirc = LpcircDEREF(hctl);
    LPRECT lprect = &lpcirc->rectDrawInto;
    HFONT  hfontOld = NULL;

    hbr = (HBRUSH)SendMessage(GetParent(hwnd), WM_CTLCOLOR,
			      hdc, MAKELONG(hwnd, 0));
    if (hbr)
	hbrOld = SelectObject(hdc, hbr);
    Ellipse(hdc, lprect->left, lprect->top, lprect->right, lprect->bottom);

    if (lpcirc->hfont)
      hfontOld = SelectObject(hdc, lpcirc->hfont);
    lpstr = VBDerefHsz(lpcirc->hszCaption);
    DrawText(hdc, lpstr, -1, lprect, DT_VCENTER | DT_CENTER | DT_SINGLELINE);

    if (hbrOld)
	SelectObject(hdc, hbrOld);
    if (hfontOld)
	SelectObject(hdc, hfontOld);
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
    HBRUSH hbr;
    HBRUSH hbrOld = NULL;
    LPCIRC lpcirc = LpcircDEREF(hctl);
    LPRECT lprect = &lpcirc->rectDrawInto;

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
    if (lpcirc->CircleShape == SHAPE_OVAL)
        return;
    if (lprect->right > lprect->bottom)
	{
	lprect->left = (lprect->right - lprect->bottom) / 2;
	lprect->right = lprect->left + lprect->bottom;
	}
    else if (lprect->bottom > lprect->right)
	{
	lprect->top = (lprect->bottom - lprect->right) / 2;
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
    double a, b;
    double x, y;
    LPRECT lprect = &LpcircDEREF(hctl)->rectDrawInto;

    a = (lprect->right - lprect->left) / 2;
    b = (lprect->bottom - lprect->top) / 2;
    x = xcoord - (lprect->left + lprect->right) / 2;
    y = ycoord - (lprect->top + lprect->bottom) / 2;
    return ((x * x) / (a * a) + (y * y) / (b * b) <= 1);
}


//---------------------------------------------------------------------------
// TYPEDEF for parameters to the ClickIn event.
//---------------------------------------------------------------------------
typedef struct tagCLICKINPARMS
    {
    HLSTR      ClickString;
    float far *Y;
    float far *X;
    LPVOID     Index;
    } CLICKINPARMS;


//---------------------------------------------------------------------------
// Fire the ClickIn event, passing the x,y coords of the click.  Also pass
// the current caption of the Circle control, to demonstrate passing strings
// to event procedures.
//---------------------------------------------------------------------------
VOID NEAR FireClickIn
(
    HCTL  hctl,
    HWND  hwnd,
    SHORT x,
    SHORT y
)
{
    CLICKINPARMS params;
    float	 xTwips, yTwips;
    USHORT	 cbCaption, err;
    char	 strBuf[20];

    xTwips = (float)VBXPixelsToTwips(x);
    yTwips = (float)VBYPixelsToTwips(y);
    params.X = &xTwips;
    params.Y = &yTwips;

    cbCaption = (USHORT)GetWindowText(hwnd, strBuf, 20);
    params.ClickString = VBCreateHlstr(strBuf, cbCaption);
    err = VBFireEvent(hctl, IEVENT_CIRCLE_CLICKIN, &params);
    VBDestroyHlstr(params.ClickString);
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
// Use frame variables to "allocate" a MULTIKEYHELP structure to pass to
// WinHelp().
//---------------------------------------------------------------------------
VOID NEAR DisplayHelpTopic
(
    CHAR  chKeylist,
    LPSTR lpszKeyword
)
{
    char  rgch[100];
    MULTIKEYHELP FAR *lpmkh = rgch;

    lpmkh->mkSize = sizeof(MULTIKEYHELP) + lstrlen(lpszKeyword);
    if (lpmkh->mkSize > sizeof(rgch))
	return;

    lpmkh->mkKeylist = chKeylist;
    lstrcpy((LPSTR)lpmkh->szKeyphrase, lpszKeyword);
    WinHelp(GetActiveWindow(), "circ3.hlp", HELP_MULTIKEY, (DWORD)lpmkh);
}


//---------------------------------------------------------------------------
// Create our property popup-window.  Since we want to put up a dialog, this
// window never becomes visible.  Instead, when asked to become visible, it
// will post a message to itself, remining it to put up our dialog.
//
// NOTE: May return NULL!
//---------------------------------------------------------------------------
HWND NEAR HwndInitFlashPopup
(
    VOID
)
{
    return CreateWindow(CLASS_FLASHPOPUP, NULL, WS_POPUP,
			0, 0, 0, 0, NULL, NULL,
			hmodDLL, NULL);
}


//---------------------------------------------------------------------------
// We asked to show ourself, remain invisible and post a CM_OPENFLASHDLG to
// ourself.  When we receive this message, open the dialog box.
//---------------------------------------------------------------------------
LONG _export FAR PASCAL FlashPopupWndProc
(
    HWND   hwnd,
    USHORT msg,
    USHORT wp,
    LONG   lp
)
{
    extern HANDLE hmodDLL;

    switch (msg)
	{
	case WM_DESTROY:
	    fDlgInUse = FALSE;
	    break;

        case WM_SHOWWINDOW:
	    if (wp)
		{
		PostMessage(hwnd, CM_OPENFLASHDLG, 0, 0L);
		return 0L;
		}
            break;

	case CM_OPENFLASHDLG:
	    VBDialogBoxParam(hmodDLL, "FlashDlg", (FARPROC)FlashDlgProc, 0L);
	    return 0L;
	}

    return DefWindowProc(hwnd, msg, wp, lp);
}


//---------------------------------------------------------------------------
// An array mapping option buttons to RGB colors.
//---------------------------------------------------------------------------
long mpidcolor[] = { 0xff, 0xff00, 0xff0000 };


//---------------------------------------------------------------------------
// The Dialog Procedure for the FlashColor property dialog.
//---------------------------------------------------------------------------
BOOL FAR PASCAL _export FlashDlgProc
(
    HWND   hDlg,
    USHORT msg,
    USHORT wp,
    LONG   lp
)
{
    switch (msg)
	{
	case WM_INITDIALOG:
	    {
	    RECT rect;
	    int  nx, ny;	  // New x and y
	    int  width, height;
	    int  i;
	    LONG colorOld;

	    // Position dialog so it looks nice:
	    GetWindowRect(hDlg, &rect);
	    width  = rect.right - rect.left;
	    height = rect.bottom - rect.top;
	    nx = (GetSystemMetrics(SM_CXSCREEN) - width)  / 2;
	    ny = (GetSystemMetrics(SM_CYSCREEN) - height) / 3;
	    MoveWindow(hDlg, nx, ny, width, height, FALSE);

	    // Remember the old value of this property, so we can restore it
	    // on cancel:
	    if (VBGetControlProperty(hctlDialog, ipropDialog, &colorOld))
	      EndDialog(hDlg, FALSE);

	    // If the current color matches one of the option button colors,
	    // then set that option button:
	    for (i=0; i<sizeof(mpidcolor); i++)
		if (mpidcolor[i] == colorOld)
		    CheckRadioButton(hDlg, DI_REDOPT, DI_BLUEOPT, i+DI_REDOPT);

	    // Save away colorOld so we can use it later
	    colorOldDialog = colorOld;

	    return TRUE;
	    }

        case WM_COMMAND:
	    switch (wp)
		{
                case IDOK:
		    EndDialog(hDlg, TRUE);
                    return TRUE;

		case IDCANCEL:
		    {
		    // Restore the old value, since we're canceling:
		    VBSetControlProperty(hctlDialog, ipropDialog, colorOldDialog);

		    EndDialog(hDlg, FALSE);
		    return TRUE;
		    }

                case DI_REDOPT:
                case DI_GREENOPT:
		case DI_BLUEOPT:
		    {
		    CheckRadioButton(hDlg, DI_REDOPT, DI_BLUEOPT, wp);

		    VBSetControlProperty(hctlDialog, ipropDialog,
					 mpidcolor[wp-DI_REDOPT]);
		    return TRUE;
		    }
		}
            break;
	}
    return FALSE;
}


//---------------------------------------------------------------------------
// Register custom control. This routine is called by VB when the custom
// control DLL is loaded for use.
//---------------------------------------------------------------------------
BOOL FAR PASCAL _export VBINITCC
(
    USHORT usVersion,
    BOOL   fRuntime
)
{
    // Count the number of hosts using this VBX.  A host can be vb.exe,
    // any .exe compiled from vb which uses this custom control, or any
    // other program which loads and uses VBX files.
    ++cVbxUsers;

    // Register popup class if this is from the development environment.
    if (!fRuntime && !fDevTimeInited)
	{
	WNDCLASS class;

	class.style	    = 0;
	class.lpfnWndProc   = (FARPROC)FlashPopupWndProc;
	class.cbClsExtra    = 0;
	class.cbWndExtra    = 0;
	class.hInstance     = hmodDLL;
	class.hIcon	    = NULL;
	class.hCursor	    = NULL;
        class.hbrBackground = NULL;
	class.lpszMenuName  = NULL;
	class.lpszClassName = CLASS_FLASHPOPUP;

	if (!RegisterClass(&class))
	    return FALSE;

	// We successfully initialized the stuff we need at dev time
	fDevTimeInited = TRUE;
	}

    // Register control(s)
    if (usVersion < VB_VERSION)
	return VBRegisterModel(hmodDLL, &modelCircle_Vb1);
    else
	return VBRegisterModel(hmodDLL, &modelCircle);
}


//---------------------------------------------------------------------------
// Unregister custom control.  This routine is called by VB when the custom
// control DLL is being unloaded.
//---------------------------------------------------------------------------
VOID FAR PASCAL _export VBTERMCC
(
    VOID
)
{
    --cVbxUsers;
    if (cVbxUsers == 0 && fDevTimeInited)
	{
	// Free any resources created for Dev environment
	UnregisterClass(CLASS_FLASHPOPUP, hmodDLL);
	}
    return;
}


//---------------------------------------------------------------------------
// Provide custom control model information to host environment.
//---------------------------------------------------------------------------
LPMODELINFO FAR PASCAL _export VBGetModelInfo
(
    USHORT usVersion
)
{
    if (usVersion < VB_VERSION)
	return &modelinfoCircle_Vb1;
    else
	return &modelinfoCircle;
}


//---------------------------------------------------------------------------
// Initialize library.	This routine is called when the first client loads
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
