//---------------------------------------------------------------------------
//		Copyright (C) 1992, Microsoft Corporation
//
// You have a royalty-free right to use, modify, reproduce and distribute
// the Sample Custom Control Files (and/or any modified version) in any way
// you find useful, provided that you agree that Microsoft has no warranty,
// obligation or liability for any Custom Control File.
//---------------------------------------------------------------------------
// PictBlt.c
//---------------------------------------------------------------------------
// This file contains routines that are needed to support custom controls
// that display palette bitmaps to print correctly.  The routime
// PictStretchBlt is a substitute to the Windows API StretchBlt and BitBlt.
// Those Windows routines do now correctly trasfer the color information
// to the destination device context when the destination device context
// is a memory device context. To get around this limitation, PictStretchBlt
// calls GetDIBits and StretchDIBits.
//
// To print forms, VB forces the form and all the controls on the form
// to paint themselves to a memory device context, that contains a bitmap
// that will eventually get printed.
//---------------------------------------------------------------------------
#include <windows.h>
#include "pictblt.h"


//---------------------------------------------------------------------------
// Helpful Macros
//---------------------------------------------------------------------------
#define WIDTHBYTES(i)	((i+31)/32*4)	   /* ULONG aligned ! */


//---------------------------------------------------------------------------
// Returns the windows stock bitmap.  Once the stock bitmap has been
// obtained, it is stored in a static for future reference.
// Assumes that CreateCompatibleDC and CreateBitmap will not fail.
//---------------------------------------------------------------------------
HBITMAP PicthbmpStock
(
    VOID
)
{
    static HBITMAP hbmpStock = NULL;

    if (!hbmpStock)
	{
	HBITMAP hbmpTmp;
	HDC	hdcMem;

	hdcMem = CreateCompatibleDC(NULL);
	hbmpTmp = CreateBitmap(1,1,1,1, NULL);

	// Select the temporary bitmap into the memory DC to get access to
	// Windows stock object.
	hbmpStock = SelectObject(hdcMem, hbmpTmp);

	SelectObject(hdcMem, hbmpStock);
	DeleteObject(hbmpTmp);
	DeleteDC(hdcMem);
	}

    return hbmpStock;
}


//---------------------------------------------------------------------------
// Given an hdc, determine if the hdc is a memory hdc or a screen hdc.
// Return TRUE iff the hdc is a Memory hdc.
//---------------------------------------------------------------------------
BOOL PictFMemDC
(
    HDC hdc
)
{
    HBITMAP hbmpSave;

    hbmpSave = SelectObject(hdc, PicthbmpStock());
    if (hbmpSave)
	{
	SelectObject(hdc, hbmpSave);
	return TRUE;
	}
    return FALSE;
}


//---------------------------------------------------------------------------
// This is a replacement to StretchBlt.  StretchBlt does not work correctly
// with palettes when the destination hdc is a memory device context.  In that case,
// StretchBlt seems to copy the pixel values from the source to the
// destination without taking the palette of the device context into account.  To
// get around this problem, we need to call GetDIBits and StretchDIBits.
//
// If this routine detects that the destination hdc is not a memory device context, then
// it calls StretchBlt directly.
//
// Return TRUE if bitmap is drawn
//---------------------------------------------------------------------------
BOOL PictStretchBlt
(
    HDC   hdcDest,
    int   x,
    int   y,
    int   cx,
    int   cy,
    HDC   hdcSrc,
    int   xSrc,
    int   ySrc,
    int   cxSrc,
    int   cySrc,
    DWORD dwRop
)
{
    if (PictFMemDC(hdcDest))
	{
	HBITMAP hBitmap;
	LONG	lcbBits;
	HANDLE	hdib;
	HANDLE	hBits;
	LPSTR	lpBits;
	BITMAP	bm;
	BITMAPINFOHEADER FAR *lpbi;
	BOOL	fRet = FALSE;

	// Get the source bitmap out of the source hdc
	hBitmap = SelectObject(hdcSrc, PicthbmpStock());

	GetObject(hBitmap,sizeof(bm),(LPSTR)&bm);

	hdib = GlobalAlloc(GHND,(DWORD)(sizeof(BITMAPINFOHEADER) + 256L*sizeof(RGBQUAD)));
	if (!hdib)
	    goto q1;

	lpbi = (VOID FAR *)GlobalLock(hdib);

	lpbi->biSize	      = sizeof(BITMAPINFOHEADER);
	lpbi->biWidth	      = bm.bmWidth;
	lpbi->biHeight	      = bm.bmHeight;
	lpbi->biPlanes	      = 1;
	lpbi->biBitCount      = bm.bmPlanes * bm.bmBitsPixel;
	lpbi->biCompression   = BI_RGB;
	lpbi->biSizeImage     = 0;
	lpbi->biXPelsPerMeter = 0;
	lpbi->biYPelsPerMeter = 0;
	lpbi->biClrUsed       = 0;
	lpbi->biClrImportant  = 0;

	// Allocate memory and fetch the DIB image so we can use
	// StretchDIBits rather than StretchBlt, for better quality
	lcbBits = WIDTHBYTES((LONG)lpbi->biBitCount * (LONG)bm.bmWidth)
		  * (LONG)bm.bmHeight;

	hBits = GlobalAlloc(GMEM_MOVEABLE, lcbBits);
	if (!hBits)
	    goto q2;

	lpBits = (LPSTR)GlobalLock(hBits);

	GetDIBits(hdcSrc, hBitmap, 0, bm.bmHeight, lpBits,
		(LPBITMAPINFO)lpbi, DIB_RGB_COLORS);

	// StretchDIBits works from the bottom and goes up, as a result the
	// source Y location is relative the bottom of the bitmap, not the top.
	fRet = (0 != StretchDIBits(
			hdcDest, x, y, cx, cy,
			xSrc, bm.bmHeight - (ySrc + cySrc), cxSrc, cySrc,
			lpBits, (LPBITMAPINFO)lpbi, DIB_RGB_COLORS,
			dwRop));

	// Release the DIB bits
	GlobalUnlock(hBits);
	GlobalFree(hBits);
q2:
	GlobalUnlock(hdib);
	GlobalFree(hdib);

q1:
	// Put bitmap back into the source hdc
	SelectObject(hdcSrc, hBitmap);

	return fRet;
	}
    else
	{
	// Destination is not a Mem DC, safe to call StretchBlt.
	// *** NOTE ****
	// Note that Windows will map StretchBlt onto BilBlt, if
	// cx == cxSrc && cy == cySrc.
	return StretchBlt(hdcDest, x, y, cx, cy, hdcSrc, xSrc, ySrc,
			  cxSrc, cySrc, dwRop);
	}
}

//---------------------------------------------------------------------------
