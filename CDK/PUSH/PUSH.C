//---------------------------------------------------------------------------
//		Copyright (C) 1991-92, Microsoft Corporation
//
// You have a royalty-free right to use, modify, reproduce and distribute
// the Sample Custom Control Files (and/or any modified version) in any way
// you find useful, provided that you agree that Microsoft has no warranty,
// obligation or liability for any Custom Control File.
//---------------------------------------------------------------------------
// Push.c
//---------------------------------------------------------------------------
// Picture Push Button Control
//---------------------------------------------------------------------------

#include <windows.h>
#include <vbapi.h>
#include "push.h"
#include "pushvb1.h"


//---------------------------------------------------------------------------
// Global Variables
//---------------------------------------------------------------------------
HANDLE hmodDLL;


//---------------------------------------------------------------------------
// Standard Error Values
//---------------------------------------------------------------------------
#define ERR_None	      0
#define ERR_InvPropVal	    380     // Error$(380) = "Invalid property value"


//---------------------------------------------------------------------------
// Local Prototypes
//---------------------------------------------------------------------------
VOID NEAR DrawBtn(HCTL hctl, LPDRAWITEMSTRUCT lpdi);


//---------------------------------------------------------------------------
// Event Procedure Parameter Profiles
//---------------------------------------------------------------------------
typedef struct tagPARAMS
    {
    HLSTR  ClickString;
    LPVOID Index;	  // Reserve space for index parameter to array ctl
    } PARAMS;


//---------------------------------------------------------------------------
// Push Control Procedure
//---------------------------------------------------------------------------
LONG FAR PASCAL _export PushCtlProc
(
    HCTL   hctl,
    HWND   hwnd,
    USHORT msg,
    USHORT wp,
    LONG   lp
)
{
    LONG lResult;

    // Message pre-processing
    switch (msg)
	{
	case WM_ERASEBKGND:
	    // Don't bother with erasing the background
	    return TRUE;

	case VBM_MNEMONIC:
	    // Act like a click
	    lp = MAKELONG(0,BN_CLICKED);
	    // **** FALL THROUGH ****

	case VBN_COMMAND:
	    switch (HIWORD(lp))
		{
		case BN_CLICKED:
		    {
		    PARAMS params;
		    char   szStrBuf[20];
		    USHORT cbCaption;
		    ERR    err;
		    LPSTR  lpstr;

		    cbCaption = (USHORT)GetWindowText(hwnd, szStrBuf, 20);
		    params.ClickString = VBCreateHlstr(szStrBuf, cbCaption);
		    err = VBFireEvent(hctl, EVENT_PUSH_CLICK, &params);
                    if (!err)
			{
			lpstr = VBDerefHlstr(params.ClickString);
                        if (lpstr == NULL)
			    {
			    szStrBuf[0] = '\0';
			    SetWindowText(hwnd, szStrBuf);
			    }
                        else
			    {
			    lpstr[VBGetHlstrLen(params.ClickString) - 1] = '\0';
                            SetWindowText(hwnd, lpstr);
			    }
			}
		    VBDestroyHlstr(params.ClickString);
		    }
		    break;
		}
	    return 0L;

	case VBM_SETPROPERTY:
	    switch (wp)
		{
		case IPROP_PUSH_CAPTION:
		    // To avoid a Windows problem, make sure text is
		    // under 255 bytes:
		    if (lstrlen((LPSTR)lp) > 255)
			*((LPSTR)lp + 255) = 0;
		    break;
		}
	    break;

	case VBM_CHECKPROPERTY:
	    switch (wp)
		{
		case IPROP_PUSH_PICTUREUP:
		case IPROP_PUSH_PICTUREDOWN:
		    {
		    PIC pic;

		    VBGetPic((HPIC)lp, &pic);
		    switch (pic.picType)
			{
			case PICTYPE_NONE:
			case PICTYPE_BITMAP:
			case PICTYPE_ICON:
			    InvalidateRect(hwnd, NULL, TRUE);
			    return ERR_None;
			}
		    return ERR_InvPropVal;
		    }
		}
	    break;

	case VBN_DRAWITEM:
	    DrawBtn(hctl, (LPDRAWITEMSTRUCT)lp);
	    return 0;
	}

    // Default processing:
    lResult = VBDefControlProc(hctl, hwnd, msg, wp, lp);

    // Message post-processing:
    switch (msg)
	{
	case WM_DESTROY:
	    VBFreePic(LppushDEREF(hctl)->hpicDown);
	    VBFreePic(LppushDEREF(hctl)->hpicUp);
	    break;
	}

    return lResult;
}


//---------------------------------------------------------------------------
// Paint the push button.
//---------------------------------------------------------------------------
VOID NEAR DrawBtn
(
    HCTL	     hctl,
    LPDRAWITEMSTRUCT lpdi
)
{
    HPIC    hpic;
    PIC     pic;
    LPPUSH  lppush = LppushDEREF(hctl);
    BITMAP  bmp;
    HDC     hdcMem;
    RECT    rect;
    SHORT   inflate;

    switch (lpdi->itemAction)
	{
	case ODA_SELECT:
	case ODA_DRAWENTIRE:
	    hpic = (lpdi->itemState & ODS_SELECTED) ? lppush->hpicDown
						    : lppush->hpicUp;
	    VBGetPic(hpic, &pic);
	    switch (pic.picType)
		{
		case PICTYPE_BITMAP:
		    GetObject(pic.picData.bmp.hbitmap, sizeof(BITMAP), (LPSTR)&bmp);
		    hdcMem = CreateCompatibleDC(lpdi->hDC);
		    SelectObject(hdcMem, pic.picData.bmp.hbitmap);
		    StretchBlt(lpdi->hDC, 0, 0,
			       lpdi->rcItem.right - lpdi->rcItem.left + 1,
			       lpdi->rcItem.bottom - lpdi->rcItem.top + 1,
			       hdcMem,	  0, 0, bmp.bmWidth, bmp.bmHeight,
			       SRCCOPY);
		    DeleteDC(hdcMem);
		    break;

		case PICTYPE_ICON:
		case PICTYPE_NONE:
		    {
		    HBRUSH  hbr;
		    RECT    rect;

		    hbr = (HBRUSH)SendMessage(GetParent(lpdi->hwndItem),
			WM_CTLCOLOR, lpdi->hDC, MAKELONG(lpdi->hwndItem, 0));
		    GetClipBox(lpdi->hDC, &rect);
		    FillRect(lpdi->hDC, &rect, hbr);
		    if (pic.picType == PICTYPE_ICON)
			DrawIcon(lpdi->hDC, 0, 0, pic.picData.wmf.hmeta);
		    else if (lpdi->itemState & ODS_SELECTED)
			InvertRect(lpdi->hDC, &rect);
		    }
		    break;
		}
	    // **** FALL THROUGH ****

	case ODA_FOCUS:
	    if (lpdi->itemState & ODS_FOCUS)
		{
		CopyRect((LPRECT)&rect, (LPRECT)&lpdi->rcItem);
		inflate = (SHORT)min(3,min(rect.right  - rect.left + 1,
				    rect.bottom - rect.top  + 1) / 5);
		InflateRect(&rect, -inflate, -inflate);
		DrawFocusRect(lpdi->hDC, &rect);
		}
	    break;
	}
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
    // Avoid warnings on unused (but required) formal parameters
    fRuntime = fRuntime;

    // Register control(s)
    if (usVersion < VB_VERSION)
	return VBRegisterModel(hmodDLL, &modelPush_Vb1);
    else
	return VBRegisterModel(hmodDLL, &modelPush);
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
	return &modelinfoPush_Vb1;
    else
	return &modelinfoPush;
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
    wDataSeg = wDataSeg;
    cbHeapSize = cbHeapSize;
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
