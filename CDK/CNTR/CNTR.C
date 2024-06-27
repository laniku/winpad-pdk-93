//---------------------------------------------------------------------------
//		Copyright (C) 1991-92, Microsoft Corporation
//
// You have a royalty-free right to use, modify, reproduce and distribute
// the Sample Custom Control Files (and/or any modified version) in any way
// you find useful, provided that you agree that Microsoft has no warranty,
// obligation or liability for any Custom Control File.
//---------------------------------------------------------------------------
// Cntr.c
//---------------------------------------------------------------------------
// Cntr Display Control
//---------------------------------------------------------------------------

#include <windows.h>
#include <vbapi.h>
#include "cntr.h"

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
VOID NEAR DeleteBitMaps(BPCNTR bpcntr);
VOID NEAR PaintCntr(BPCNTR bpcntr, HWND hwnd, HDC hdc);
ERR  NEAR ErrSetCntrVal(BPCNTR bpcntr, HWND hwnd, float Val);
VOID NEAR SizeCntr(BPCNTR bpcntr, HWND hwnd);


//---------------------------------------------------------------------------
// Cntr Control Procedure
//---------------------------------------------------------------------------
LONG FAR PASCAL _export CntrCtlProc
(
    HCTL   hctl,
    HWND   hwnd,
    USHORT msg,
    USHORT wp,
    LONG   lp
)
{
    BPCNTR bpcntr = NULL;

    segCntr = (_segment)hctl;

    // Message pre-processing
    switch (msg)
	{
	case WM_NCDESTROY:
	    bpcntr = BpcntrDEREF(hctl);
	    DeleteBitMaps(bpcntr);
	    break;

	case WM_NCCREATE:
	    bpcntr = BpcntrDEREF(hctl);
	    bpcntr->hFont = NULL;
	    ErrSetCntrVal(bpcntr, hwnd, (float)0.0);
	    bpcntr->DigitsLeft = 3;
	    bpcntr->DigitsRight = 0;
	    bpcntr->colorBackRight = COLOR_HIGHLIGHT | 0x80000000;
	    bpcntr->colorForeRight = COLOR_HIGHLIGHTTEXT | 0x80000000;
	    break;

	case WM_GETMINMAXINFO:
	    ((LPPOINT)lp)[3].x = 4;
	    ((LPPOINT)lp)[3].y = 4;
	    return 1L;

	case WM_SIZE:
	    SizeCntr(BpcntrDEREF(hctl), hwnd);
	    break;

	case WM_SETFONT:
	    bpcntr = BpcntrDEREF(hctl);
	    bpcntr->hFont = (HFONT)wp;
	    DeleteBitMaps(bpcntr);
	    break;

	case WM_GETFONT:
	    return BpcntrDEREF(hctl)->hFont;

	case WM_ERASEBKGND:
	    return TRUE;

	case WM_PAINT:
	    if (wp)
		PaintCntr(BpcntrDEREF(hctl), hwnd, (HDC)wp);
	    else
		{
		PAINTSTRUCT ps;

		BeginPaint(hwnd, &ps);
		PaintCntr(BpcntrDEREF(hctl), hwnd, ps.hdc);
		EndPaint(hwnd, &ps);
		}
	    break;

	case VBM_SETPROPERTY:
	    switch (wp)
		{
		case IPROP_CNTR_DIGITSLEFT:
		    if ((SHORT)lp < 1 || (SHORT)lp > 6)
			return ERR_InvPropVal;
		    bpcntr = BpcntrDEREF(hctl);
		    bpcntr->DigitsLeft = (SHORT)lp;
		    SizeCntr(bpcntr, hwnd);
		    InvalidateRect(hwnd, NULL, FALSE);
		    return ERR_None;

		case IPROP_CNTR_DIGITSRIGHT:
		    if ((SHORT)lp < 0 || (SHORT)lp > 5)
			return ERR_InvPropVal;
		    bpcntr = BpcntrDEREF(hctl);
		    bpcntr->DigitsRight = (SHORT)lp;
		    SizeCntr(bpcntr, hwnd);
		    InvalidateRect(hwnd, NULL, FALSE);
		    // reset value to reevaluate roll factors
		    ErrSetCntrVal(BpcntrDEREF(hctl), hwnd, bpcntr->Value);
		    return ERR_None;

		case IPROP_CNTR_VALUE:
		    return ErrSetCntrVal(BpcntrDEREF(hctl), hwnd,
					 *(float FAR *)&(lp));

		case IPROP_CNTR_BACKCOLORRIGHT:
		case IPROP_CNTR_FORECOLORRIGHT:
		case IPROP_CNTR_BACKCOLOR:
		case IPROP_CNTR_FORECOLOR:
		    InvalidateRect(hwnd, NULL, FALSE);
		    DeleteBitMaps(BpcntrDEREF(hctl));
		    return ERR_None;
		}
	    break;
	}

    // Default processing:
    return VBDefControlProc(hctl, hwnd, msg, wp, lp);
}


//---------------------------------------------------------------------------
// Delete currently cached bitmaps.  Called when control size, font, or
// color has changed.  Bitmaps will be recalculated next time they are
// needed.
//---------------------------------------------------------------------------
VOID NEAR DeleteBitMaps
(
    BPCNTR bpcntr
)
{
    if (bpcntr->hbmp[0])
	{
	DeleteObject(bpcntr->hbmp[0]);
	bpcntr->hbmp[0] = NULL;
	}
    if (bpcntr->hbmp[1])
	{
	DeleteObject(bpcntr->hbmp[1]);
	bpcntr->hbmp[1] = NULL;
	}
}


//---------------------------------------------------------------------------
// Caluculate new bitmaps.  We will create and paint a new bitmap which looks
// like:
//	-+
//	0|
//	-+
//	1|
//	-+
//	2|
//	-+
//	:
//	-+
//	9|
//	-+
//	0|
//	-+
// using the correct colors and font.
//---------------------------------------------------------------------------
HBITMAP NEAR GetBitMap
(
    BPCNTR bpcntr,
    HWND   hwnd,
    SHORT  inx
)
{
    static  CHAR szDig[] = "01234567890";
    RECT    rcClient;
    RECT    rcDigit;
    SHORT   digit;
    SHORT   DigitHeight;
    HDC     hdcScr;
    HDC     hdcMem;
    HBITMAP hbmp;
    HBITMAP hbmpOld;
    HBRUSH  hbr;
    HFONT   hfontOld = NULL;

    if (bpcntr->hbmp[inx])
	return bpcntr->hbmp[inx];
    GetClientRect(hwnd, &rcClient);

    DigitHeight = rcClient.bottom + 1;
    rcDigit = rcClient;
    rcDigit.right = rcClient.right = bpcntr->DigitWidth - 1;
    rcClient.bottom = DigitHeight * 11;
    hdcScr = GetDC(NULL);
    hdcMem = CreateCompatibleDC(hdcScr);
    hbmp = CreateCompatibleBitmap(hdcScr, rcClient.right+1, rcClient.bottom+1);
    ReleaseDC(NULL, hdcScr);
    if (!hbmp)
	{
	DeleteDC(hdcMem);
	return NULL;
	}
    bpcntr->hbmp[inx] = hbmp;
    hbmpOld = SelectObject(hdcMem, hbmp);
    // set up colors, etc.
    if (!inx)
	hbr = (HBRUSH)SendMessage(GetParent(hwnd), WM_CTLCOLOR, hdcMem, MAKELONG(hwnd, 0));
    else
	{
	LONG BackColor = RGBCOLOR(bpcntr->colorBackRight);
	LONG ForeColor = RGBCOLOR(bpcntr->colorForeRight);

	hbr = CreateSolidBrush(BackColor);
	SetTextColor(hdcMem, ForeColor);
	}
    if (hbr)
	{
	FillRect(hdcMem, &rcClient, hbr);
	if (inx)
	    DeleteObject(hbr);
	}
    SetBkMode(hdcMem, TRANSPARENT);
    if (bpcntr->hFont)
	hfontOld = SelectObject(hdcMem, bpcntr->hFont);
    MoveTo(hdcMem, rcClient.right, 0);
    LineTo(hdcMem, rcClient.right, rcClient.bottom);

    for (digit = 0; digit <= 10; ++digit)
	{
	MoveTo(hdcMem, 0, rcDigit.bottom);
	LineTo(hdcMem, rcDigit.right, rcDigit.bottom);
	DrawText(hdcMem, &szDig[digit], 1, &rcDigit,
		 DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_NOCLIP);
	rcDigit.top += DigitHeight;
	rcDigit.bottom += DigitHeight;
	}
    if (hfontOld)
	SelectObject(hdcMem, hfontOld);
    SelectObject(hdcMem, hbmpOld);
    DeleteDC(hdcMem);
    return bpcntr->hbmp[inx];
}


//---------------------------------------------------------------------------
// Handle the resizing.  Calculate new width for digits and the size of the
// gap.  Delete the old bitmaps, so that new ones will be created on the next
// paint.
//---------------------------------------------------------------------------
VOID NEAR SizeCntr
(
    BPCNTR bpcntr,
    HWND   hwnd
)
{
    RECT  rcClient;
    SHORT digits;

    GetClientRect(hwnd, &rcClient);
    digits = bpcntr->DigitsLeft + bpcntr->DigitsRight;
    bpcntr->DigitWidth = (rcClient.right + 1) / digits;
    bpcntr->Gap = rcClient.right + 1 - digits * bpcntr->DigitWidth;
    DeleteBitMaps(bpcntr);
}


//---------------------------------------------------------------------------
// Handle setting a new value.
//---------------------------------------------------------------------------
ERR NEAR ErrSetCntrVal
(
    BPCNTR bpcntr,
    HWND   hwnd,
    float  Val
)
{
    LONG  ValInt;
    LONG  ValFrac;
    SHORT digit;
    SHORT last;
    SHORT StartRoll;
    CHAR  szVal[13];

    if (Val < (float)0.0)
	return ERR_InvPropVal;
    if (Val > (float)999999.0)
	return ERR_InvPropVal;
    bpcntr->Value = Val;
    ValInt = (LONG)Val;
    ValFrac = (LONG)((Val - (float)ValInt) * 1000000.0);
    wsprintf(szVal, "%06ld%06ld", ValInt, ValFrac);
    last = 6 + bpcntr->DigitsRight;
    StartRoll = last - 1;
    for (digit = last; digit >= 6 - bpcntr->DigitsLeft; --digit)
	if (digit == StartRoll - 1 && szVal[StartRoll] == '9')
	    --StartRoll;
    bpcntr->StartRoll = StartRoll;
    bpcntr->RollVal = (szVal[last] - '0') * 10;
    if (last < 11)
	bpcntr->RollVal += (szVal[last+1] - '0');
    lstrcpy(bpcntr->szVal, szVal);
    InvalidateRect(hwnd, NULL, FALSE);
    return ERR_None;
}


//---------------------------------------------------------------------------
// Handle painting.  Blit the correct portion of the stashed bitmaps for
// each digit.
//---------------------------------------------------------------------------
VOID NEAR PaintCntr
(
    BPCNTR bpcntr,
    HWND   hwnd,
    HDC    hdc
)
{
    RECT    rcDigit;
    SHORT   digit;
    HBRUSH  hbr;
    SHORT   roll;
    SHORT   top;
    HDC     hdcMem;
    HBITMAP hbmp;
    HBITMAP hbmpOld = NULL;

    hdcMem = CreateCompatibleDC(hdc);
    if (!hdcMem)
	return;

    // size the situation
    GetClientRect(hwnd, &rcDigit);

    hbr = (HBRUSH)SendMessage(GetParent(hwnd), WM_CTLCOLOR, hdc, MAKELONG(hwnd, 0));
    rcDigit.right = bpcntr->Gap;
    FillRect(hdc, &rcDigit, hbr);
    rcDigit.left  = rcDigit.right;
    rcDigit.right = rcDigit.left + bpcntr->DigitWidth;

    roll = (bpcntr->RollVal * rcDigit.bottom) / 100;
    for (digit = 6 - bpcntr->DigitsLeft; digit <= 5 + bpcntr->DigitsRight; ++digit)
	{
	hbmp = GetBitMap(bpcntr, hwnd, digit >= 6);
	if (!hbmp)
	    {
	    if (hbmpOld)
		SelectObject(hdcMem, hbmpOld);
	    DeleteDC(hdcMem);
	    return;
	    }
	hbmpOld = SelectObject(hdcMem, hbmp);
	if (RectVisible(hdc, &rcDigit))
	    {
	    top = (bpcntr->szVal[digit] - '0') * (rcDigit.bottom + 1);
	    if (digit >= bpcntr->StartRoll)
		top += roll;
	    BitBlt(hdc, rcDigit.left, 0, bpcntr->DigitWidth, rcDigit.bottom + 1,
		   hdcMem, 0, top, SRCCOPY);
	    }
	rcDigit.left  = rcDigit.right;
	rcDigit.right = rcDigit.left + bpcntr->DigitWidth;
	}
    if (hbmpOld)
	SelectObject(hdcMem, hbmpOld);
    DeleteDC(hdcMem);
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
    return VBRegisterModel(hmodDLL, &modelCntr);
}


//---------------------------------------------------------------------------
// Provide custom control model information to host environment.
//---------------------------------------------------------------------------
LPMODELINFO FAR PASCAL _export VBGetModelInfo
(
    USHORT usVersion
)
{
    return &modelinfoCntr;
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
