//---------------------------------------------------------------------------
//		Copyright (C) 1992 Microsoft Corporation
//
// You have a royalty-free right to use, modify, reproduce and distribute
// the Sample Custom Control Files (and/or any modified version) in any way
// you find useful, provided that you agree that Microsoft has no warranty,
// obligation or liability for any Custom Control File.
//---------------------------------------------------------------------------
// Pal.c
//---------------------------------------------------------------------------
// PALette Control
//---------------------------------------------------------------------------

#include <windows.h>
#include <string.h>
#include <vbapi.h>
#include "pal.h"

extern  MODEL modelPal;

VOID   PaintPalette(HCTL hctl, HWND hwnd, HDC hdc);
HPALETTE CopyPalette(HPALETTE hpal);

HANDLE	hmodDLL;    // Module handle for the DLL

#define ERR_OOM 7   // Out of memory error

//---------------------------------------------------------------------------
// PAL control function
//---------------------------------------------------------------------------
LONG _export FAR PASCAL PalCtlProc
(
  HCTL    hctl,
  HWND    hwnd,
  USHORT  msg,
  USHORT  wp,
  LONG    lp
)
{
  LONG    lResult;

  // Message pre-processing
  switch(msg)
    {
    case WM_NCCREATE:
      // For convenience, mark this control as always using a palette,
      // but for windowed controls this will only take effect if we later
      // also set CTLFLG_HASPALETTE.
      VBSetControlFlags(hctl, CTLFLG_USESPALETTE, CTLFLG_USESPALETTE);
      break;

    case WM_PAINT:
      if (wp)
	// Handle "subclass paint", where wp == hdc
	PaintPalette(hctl, hwnd, (HDC)wp);
      else
        {
        PAINTSTRUCT ps;

        BeginPaint(hwnd, &ps);
	PaintPalette(hctl, hwnd, ps.hdc);
        EndPaint(hwnd, &ps);
        }
      break;

    case VBM_GETPALETTE:
      // Return the palette we want realized.
      // Turning off our palette awareness with VBSetControlFlags()
      // when we have no palette will prevent us from returning NULL here.
      return PALDEREF(hctl)->hpal;

    case VBM_GETPROPERTY:
      switch (wp)
        {
	case IPROP_PAL_PICTURE:
	  // For the Picture property we build an HPIC value composed
	  // of a 0 by 0 bitmap and a copy of our current HPALETTE
	  {
	  PPAL	    ppal;
	  PIC	    pic;
	  HPIC	    hpic;
	  HPALETTE  hpal;
	  HBITMAP   hbmp;
	  HDC	    hdcScr;

	  ppal = PALDEREF(hctl);

	  if (!ppal->hpal)
	    {
	    // No palette - no picture
	    *(HPIC FAR *)lp = HPIC_NULL;
	    return 0;
	    }

	  // Make a copy of the palette we're using
	  hpal = CopyPalette(ppal->hpal);
	  if (!hpal)
	    return ERR_OOM;

	  // Create a 1x1 bitmap to go with the palette
	  hdcScr = GetDC(NULL);
	  hbmp = CreateBitmap(1, 1,
			      (BYTE)GetDeviceCaps(hdcScr, PLANES),
			      (BYTE)GetDeviceCaps(hdcScr, BITSPIXEL),
			      NULL);
	  ReleaseDC(NULL, hdcScr);
	  if (!hbmp)
	    {
	    DeleteObject(hpal);
	    return ERR_OOM;
	    }

	  // Create HPIC from HBMP and HPAL
	  pic.picType = PICTYPE_BITMAP;
	  pic.picData.bmp.hbitmap = hbmp;
	  pic.picData.bmp.hpal = hpal;
	  hpic = VBAllocPicEx(&pic, VB_VERSION);
	  if (!hpic)
	    {
	    DeleteObject(hpal);
	    DeleteObject(hbmp);
	    return ERR_OOM;
	    }

	  // Return the HPIC but don't call VBRefPic because we're
	  // not holding a reference to this picture
	  *(HPIC FAR *)lp = hpic;
	  return 0;
	  }

	case IPROP_PAL_LENGTH:
	  // The Length property just returns the palette length
	  {
	  PPAL	    ppal;
	  HPALETTE  hpal;
	  SHORT     palNumEntries;

	  ppal = PALDEREF(hctl);

	  hpal = ppal->hpal;
	  if (!hpal)
	    // Fall back to the default palette
	    hpal = GetStockObject(DEFAULT_PALETTE);
	  GetObject((HANDLE)hpal, sizeof(WORD), (LPSTR)&palNumEntries);
	  *(SHORT FAR *)lp = palNumEntries;
	  return 0;
	  }

	case IPROP_PAL_ENTRY:
	  // The Entry array property returns the color RGB value
	  // of the palette entry at the given index
	  {
	  PPAL	    ppal;
	  HPALETTE  hpal;
	  PALETTEENTRY palentry;
	  LPDATASTRUCT pds = (LPDATASTRUCT)lp;
	  SHORT index = (SHORT)(pds->index[0].data);

	  ppal = PALDEREF(hctl);

	  hpal = ppal->hpal;
	  if (!hpal)
	    hpal = GetStockObject(DEFAULT_PALETTE);
	  if (!GetPaletteEntries(hpal, index, 1, &palentry))
	    return VBSetErrorMessage(32000, "invalid palette index");
	  pds->data = RGB(palentry.peRed, palentry.peGreen, palentry.peBlue);
	  return 0;
	  }
	}
      break;

    case VBM_SETPROPERTY:
      switch (wp)
        {
	case IPROP_PAL_PICTURE:
	  // For the Picture we just copy the palette from the HPIC
	  {
	  PIC  pic;
	  PPAL ppal;

	  ppal = PALDEREF(hctl);

	  // Get the picture information and validate the type
	  VBGetPicEx((HPIC)lp, &pic, VB_VERSION);
	  switch (pic.picType)
	    {
	    case PICTYPE_NONE:
	    case PICTYPE_BITMAP:
	      // Free old HPAL
	      if (ppal->hpal)
		DeleteObject(ppal->hpal);
	      if (pic.picType == PICTYPE_NONE)
		ppal->hpal = NULL;
	      else
		ppal->hpal = CopyPalette(pic.picData.bmp.hpal);
	      InvalidateRect(hwnd, NULL, TRUE);
	      VBSetControlFlags(hctl, CTLFLG_HASPALETTE,
	      (ppal->hpal != NULL) ? CTLFLG_HASPALETTE : 0);
	      return 0;
	    }
	  return VBSetErrorMessage(32001, "bitmaps only");
	  }

	case IPROP_PAL_LENGTH:
	  // The Length property causes the palette to be extended
	  // (with black entries) or truncated to a specific length
	  {
	  PPAL	   ppal;
	  HPALETTE hpal;

	  ppal = PALDEREF(hctl);

	  hpal = ppal->hpal;
	  if (!hpal)
	    {
	    // Fall back to the default palette
	    hpal = CopyPalette(GetStockObject(DEFAULT_PALETTE));
	    if (!hpal)
	      return ERR_OOM;
	    ppal->hpal = hpal;
	    }
	  // Windows does all the real work here!!
	  if (!ResizePalette(hpal, (WORD)lp))
	    return VBSetErrorMessage(32002, "can't resize palette");
	  InvalidateRect(hwnd, NULL, TRUE);
	  VBSetControlFlags(hctl, CTLFLG_HASPALETTE, CTLFLG_HASPALETTE);
	  return 0;
	  }

	case IPROP_PAL_ENTRY:
	  // The Entry array property sets the color RGB value
	  // of the palette entry at the given index
	  {
	  PPAL		ppal;
	  HPALETTE	hpal;
	  PALETTEENTRY	palentry;
	  LPDATASTRUCT	pds = (LPDATASTRUCT)lp;
	  SHORT 	index = (SHORT)(pds->index[0].data);
	  // Use RGBCOLOR macro to translate SysColors
	  COLOR 	color = RGBCOLOR(pds->data);

	  ppal = PALDEREF(hctl);

	  hpal = ppal->hpal;
	  if (!hpal)
	    {
	    // Fall back to the default palette
	    hpal = CopyPalette(GetStockObject(DEFAULT_PALETTE));
	    if (!hpal)
	      return ERR_OOM;
	    ppal->hpal = hpal;
	    }
	  // Build an entry and set it
	  palentry.peRed   = GetRValue(color);
	  palentry.peGreen = GetGValue(color);
	  palentry.peBlue  = GetBValue(color);
	  palentry.peFlags = 0;
	  if (!SetPaletteEntries(hpal, index, 1, &palentry))
	    return VBSetErrorMessage(32003, "invalid palette index");
	  InvalidateRect(hwnd, NULL, TRUE);
	  VBSetControlFlags(hctl, CTLFLG_HASPALETTE, CTLFLG_HASPALETTE);
	  return 0;
	  }
        }
      break;
    }

  // Default processing:
  lResult = VBDefControlProc(hctl, hwnd, msg, wp, lp);

  // Message post-processing:
  switch (msg)
    {
    case WM_DESTROY:
      {
      PPAL  ppal;

      ppal = PALDEREF(hctl);
      // Free old HPAL
      if (ppal->hpal)
	{
	DeleteObject(ppal->hpal);
	ppal->hpal = NULL;
	}
      }
      break;
    }
  return lResult;
}


//---------------------------------------------------------------------------
// Handle the painting of the window.
//---------------------------------------------------------------------------
VOID PaintPalette
(
  HCTL hctl,
  HWND hwnd,
  HDC  hdc
)
{
  RECT	   rect;
  HPALETTE hpal;
  HPALETTE hpalOld;
  int	   i;
  int	   stripe;
  HBRUSH   hbr;
  int	   palNumEntries;

  hpal = PALDEREF(hctl)->hpal;
  if (!hpal)
    hpal = GetStockObject(DEFAULT_PALETTE);

  GetClientRect(hwnd, &rect);

  hpalOld = SelectPalette(hdc, hpal, TRUE);
  RealizePalette(hdc);

  GetObject((HANDLE)hpal, sizeof(WORD), (LPSTR)&palNumEntries);
  stripe = rect.right / (int)palNumEntries;
  if (stripe == 0)
    stripe = 1;
  ++stripe;
  for (i = 0; i < palNumEntries; i++)
    {
    // A palette-relative brush is used for drawing.
    hbr = CreateSolidBrush(PALETTEINDEX(i));
    if (hbr)
      {
      hbr = SelectObject(hdc, hbr);
      PatBlt(hdc, i*stripe, 0, stripe, rect.bottom, PATCOPY);
      hbr = SelectObject(hdc, hbr);
      DeleteObject(hbr);
      }
    }
  SelectPalette(hdc, hpalOld, TRUE);
  RealizePalette(hdc);
}


//---------------------------------------------------------------------------
// Makes a copy of a GDI logical palette.  Returns a handle to the new
// palette.
//---------------------------------------------------------------------------
HPALETTE CopyPalette
(
    HPALETTE hpal
)
{
    PLOGPALETTE ppal;
    int         nNumEntries;

    if (!hpal)
        return NULL;

    GetObject(hpal,sizeof(int),(LPSTR)&nNumEntries);

    if (nNumEntries == 0)
        return NULL;

    ppal = (PLOGPALETTE)LocalAlloc(LPTR, (WORD)(sizeof(LOGPALETTE) +
    nNumEntries * sizeof(PALETTEENTRY)));

    if (!ppal)
        return NULL;

    ppal->palVersion  = 0x300;
    ppal->palNumEntries = (WORD)nNumEntries;

    GetPaletteEntries(hpal,0, (WORD)nNumEntries, ppal->palPalEntry);

    hpal = CreatePalette(ppal);

    LocalFree((HANDLE)ppal);
    return hpal;
}


//---------------------------------------------------------------------------
// Register custom control.  This routine is called by VB when the custom
// control DLL is loaded for use.
//---------------------------------------------------------------------------
BOOL FAR PASCAL _export VBINITCC
(
  USHORT usVersion,
  BOOL	 fRuntime
)
{
  // Avoid warnings on unused (but required) formal parameters
  fRuntime = fRuntime;

  // Avoid loading under earlier version of VB
  if (usVersion < VB200_VERSION)
    {
    MessageBox(NULL,
	       "Requires Visual Basic 2.0",
	       "Palette Control",
	       MB_OK | MB_TASKMODAL);
    return FALSE;
    }

  // Register control(s)
  return VBRegisterModel(hmodDLL, &modelPal);
}


//---------------------------------------------------------------------------
// Provide custom control model information to host environment.
//---------------------------------------------------------------------------
LPMODELINFO FAR PASCAL _export VBGetModelInfo
(
  USHORT usVersion
)
{
  // Avoid warnings on unused (but required) formal parameters
  usVersion = usVersion;

  return &modelinfoPal;
}


//---------------------------------------------------------------------------
// Initialize library. This routine is called when the first client loads
// the DLL.
//---------------------------------------------------------------------------
int FAR PASCAL LibMain
(
  HANDLE hModule,
  WORD	 wDataSeg,
  WORD	 cbHeapSize,
  LPSTR  lpszCmdLine
)
{
  // Avoid warnings on unused (but required) formal parameters
  wDataSeg    = wDataSeg;
  cbHeapSize  = cbHeapSize;
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
