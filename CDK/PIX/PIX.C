//---------------------------------------------------------------------------
//		Copyright (C) 1991-2, Microsoft Corporation
//
// You have a royalty-free right to use, modify, reproduce and distribute
// the Sample Custom Control Files (and/or any modified version) in any way
// you find useful, provided that you agree that Microsoft has no warranty,
// obligation or liability for any Custom Control File.
//---------------------------------------------------------------------------
// Pix.c
//---------------------------------------------------------------------------
// Contains control procedure for PIX control
//---------------------------------------------------------------------------

#include <windows.h>
#include <vbapi.h>
#include "pictblt.h"
#include "pix.h"
#include "pixvb1.h"


//---------------------------------------------------------------------------
// Global Variables
//---------------------------------------------------------------------------
HANDLE hmodDLL;


//---------------------------------------------------------------------------
// Standard Error Values
//---------------------------------------------------------------------------
#define ERR_None		0
#define ERR_OutOfMemory 	7   // Error$(7) = "Out of memory"
#define ERR_BadIndex	      381   // Error$(381) = "Invalid property array index"
#define ERR_BadPixFmt	    32000   // User-defined error


//---------------------------------------------------------------------------
// Local Prototypes
//---------------------------------------------------------------------------
ERR ErrCopyHlstr(HLSTR FAR *lphlstrDest, HLSTR hlstrSrc);
VOID NEAR PaintPix(HCTL hctl, HDC hdc, LPRECT lprect);
#define LppixDEREF(hctl)  ((PPIX)VBDerefControl(hctl))


//---------------------------------------------------------------------------
// Private macros
//---------------------------------------------------------------------------
#define SETOPAQUE(hctl)      VBSetControlFlags(hctl, CTLFLG_GRAPHICALOPAQUE, CTLFLG_GRAPHICALOPAQUE)
#define SETTRANSLUCENT(hctl) VBSetControlFlags(hctl, CTLFLG_GRAPHICALTRANSLUCENT, CTLFLG_GRAPHICALTRANSLUCENT)
#define SETTRANSPARENT(hctl) VBSetControlFlags(hctl, CTLFLG_GRAPHICALOPAQUE|CTLFLG_GRAPHICALTRANSLUCENT, 0)


//---------------------------------------------------------------------------
// Pix Control Procedure
//---------------------------------------------------------------------------
LONG FAR PASCAL _export PixCtlProc
(
    HCTL   hctl,
    HWND   hwnd,
    USHORT msg,
    USHORT wp,
    LONG   lp
)
{
    PPIX ppix = NULL;

    switch (msg)
	{
	// *** NOTE: Only windowed controls receive WM_PAINT
	case WM_PAINT:
	    {
	    RECT rect;

	    GetClientRect(hwnd, &rect);
            if (wp)
		PaintPix(hctl, (HDC)wp, &rect);
	    else
		{
                PAINTSTRUCT ps;

		BeginPaint(hwnd, &ps);
		PaintPix(hctl, ps.hdc, &rect);
		EndPaint(hwnd, &ps);
		}
	    return 0L;
	    }

	// *** NOTE: Only Graphical controls receive VBM_PAINT
	case VBM_PAINT:
	    PaintPix(hctl, (HDC)wp, (LPRECT)lp);
	    return 0L;

	// *** NOTE: Both Graphical and windowed controls receive WM_NCCREATE
	case WM_NCCREATE:
	    // When being created, let's clear the CTLFLG_GRAPHICALTRANSLUCENT
	    // which is set by default for Graphical controls.
	    if (VBGetVersion() >= VB200_VERSION)
		{
		VBSetControlFlags(hctl, CTLFLG_GRAPHICALTRANSLUCENT, 0);
		VBSetControlFlags(hctl, CTLFLG_USESPALETTE, CTLFLG_USESPALETTE);
		}
	    break;

	// *** NOTE: Both Graphical and windowed controls receive WM_NCDESTROY
	case WM_NCDESTROY:
	    ppix = (PPIX)VBDerefControl(hctl);
	    VBFreePic(ppix->hpicPict);
	    ppix = (PPIX)VBDerefControl(hctl);
	    if (ppix->hlstrMyTag)
	      VBDestroyHlstr(ppix->hlstrMyTag);
	    ppix = (PPIX)VBDerefControl(hctl);
	    if (ppix->hlstrMyTagMsg)
	      VBDestroyHlstr(ppix->hlstrMyTagMsg);
	    break;

        case VBM_GETPROPERTY:
	    switch (wp)
		{
		case IPROP_PIX_LIST:	// Get element of List prop array
                    {
		    LONG	 i;
		    LPDATASTRUCT lpds = (LPDATASTRUCT)lp;
		    LPSTR	 lpstr;

		    i = lpds->index[0].data;
                    if (i < 0 || i >= ARRMAX)
			return ERR_BadIndex;

		    ppix = (PPIX)VBDerefControl(hctl);
		    if (ppix->List[i] == NULL)
			{
			lpds->data = (LONG)VBCreateHsz((_segment)hctl,"");
			// *** ppix may now be invalid due to call to VB API ***
			return ERR_None;
                        }
                    lpstr = VBDerefHsz(ppix->List[i]);
		    lpds->data = (LONG)VBCreateHsz((_segment)hctl, lpstr);
		    // *** ppix may now be invalid due to call to VB API ***
		    return ERR_None;
		    }

		case IPROP_PIX_MYTAG:
		    // WARNING: For DT_HLSTR properties which use PF_fGetData,
		    // WARNING: we must ensure that NULL is never returned!
		    // WARNING: So, if *lp is NULL, let's create a zero-
		    // WARNING: length hlstr, and return that!
		    if (*(HLSTR FAR *)lp == NULL)
		      {
		      *(HLSTR FAR *)lp = VBCreateHlstr(NULL, 0);
		      if (*(HLSTR FAR *)lp == NULL)
			return ERR_OutOfMemory;
		      }
		    return ERR_None;

		case IPROP_PIX_MYTAGMSG:
		    {
		    HLSTR  hlstr = LppixDEREF(hctl)->hlstrMyTagMsg;
		    USHORT cb = VBGetHlstrLen(hlstr);
		    HLSTR  hlstrNew = VBCreateHlstr(NULL, cb);
		    ERR    err;

		    if (!hlstrNew)
		      return ERR_OutOfMemory;

		    err = VBSetHlstr(&hlstrNew, VBDerefHlstr(hlstr), cb);
		    if (err)
		      {
		      if (hlstrNew)
			VBDestroyHlstr(hlstrNew);
		      return err;
		      }
		    *(HLSTR FAR *)lp = hlstrNew;
		    return ERR_None;
		    }
                }
            break;

        case VBM_SETPROPERTY:
	    switch (wp)
		{
		case IPROP_PIX_LIST:	// Set element of List prop array
                    {
		    LONG	 i;
		    LPDATASTRUCT lpds =(LPDATASTRUCT)lp;
		    HSZ 	 hsz;

		    i = lpds->index[0].data;
                    if (i < 0 || i >= ARRMAX)
			return ERR_BadIndex;

		    ppix = (PPIX)VBDerefControl(hctl);
                    if (ppix->List[i])
			VBDestroyHsz(ppix->List[i]);
		    hsz = VBCreateHsz((_segment)hctl, (LPSTR)(lpds->data));
		    // *** ppix may now be invalid due to call to VB API ***
		    ppix = (PPIX)VBDerefControl(hctl);
                    ppix->List[i] = hsz;

		    return ERR_None;
                    }

                case IPROP_PIX_PICT:
		    if (VBGetVersion() >= VB200_VERSION)
                        VBLinkPostAdvise(hctl);
                    return ERR_None;

		case IPROP_PIX_MYTAGMSG:
		    // WARNING: We must never call VBGetHlstr() in response
		    // WARNING: to VBM_SETPROPERTY, since this VB API
		    // WARNING: has the side affect of freeing the hlstr
		    // WARNING: passed in, if it was a temp hlstr.
		    // WARNING: Since we do not own the hlstr, we are
		    // WARNING: forbidden to free it, and hence must not
		    // WARNING: call VBGetHlstr() or VBDestroyHlstr()
		    // WARNING: on the hlstr passed in lp.  We also cannot
		    // WARNING: call VBSetHlstr(xx,lp,-1), since this form
		    // WARNING: of VBSetHlstr() will also free lp if it is a
		    // WARNING: temp string.
		    return ErrCopyHlstr(&LppixDEREF(hctl)->hlstrMyTagMsg, (HLSTR)lp);
                }
            break;

	case VBM_CHECKPROPERTY:
	    switch (wp)
		{
                case IPROP_PIX_PICT:
                    {
		    PIC pic;

		    if (VBGetVersion() >= VB200_VERSION)
			{
			// Need to call VBGetPicEx to get the
			// hpal field to be filled in
			VBGetPicEx((HPIC)lp, &pic, VB_VERSION);

			// Mark palette aware, as necessary
			VBSetControlFlags(hctl, CTLFLG_HASPALETTE,
			    (pic.picType == PICTYPE_BITMAP &&
			     pic.picData.bmp.hpal != NULL)
					      ? CTLFLG_HASPALETTE
					      : 0);
			}
		    else
			VBGetPic((HPIC)lp, &pic);

		    switch (pic.picType)
			{
			case PICTYPE_BITMAP:
			    if (VBGetVersion() >= VB200_VERSION)
				{
				VBInvalidateRect(hctl, NULL, TRUE);
				VBSetControlFlags(hctl,
						  CTLFLG_GRAPHICALOPAQUE,
						  CTLFLG_GRAPHICALOPAQUE);
				}
			    else
				InvalidateRect(hwnd, NULL, TRUE);
			    return ERR_None;

                        case PICTYPE_NONE:
			    if (VBGetVersion() >= VB200_VERSION)
				{
				VBInvalidateRect(hctl, NULL, TRUE);
				VBSetControlFlags(hctl,
						  CTLFLG_GRAPHICALOPAQUE|CTLFLG_GRAPHICALTRANSLUCENT,
						  0);
				}
			    else
				InvalidateRect(hwnd, NULL, TRUE);
			    return ERR_None;

			// *** NOTE: If we supported PICTYPE_ICON, we would
			// *** NOTE: have to set CTLFLG_GRAPHICALTRANSLUCENT!
                        }
		    return VBSetErrorMessage(ERR_BadPixFmt,
					     "Picture format not supported.");
                    }
                }
	    break;


	case VBM_GETPALETTE:
	    {
	    PIC pic;

	    // Note that this message will only be sent under
	    // VB 2.0 or higher.  Therefore there is no need
	    // to check the VB version in processing this message.

	    ppix = (PPIX)VBDerefControl(hctl);
	    VBGetPicEx(ppix->hpicPict, &pic, VB_VERSION);

	    if (pic.picType == PICTYPE_BITMAP)
	      return (LONG)(SHORT)pic.picData.bmp.hpal;
	    else
	      return NULL;
	    }
        case VBM_LINKENUMFORMATS:
            if (LOWORD(lp) == 0)
                return CF_BITMAP;
            return NULL;

        case VBM_LINKGETDATA:
            {
            HPIC     hpic;
            PIC      pic;

            // Bitmaps and DIB's and metafiles are special cases for DDE.
            // HBITMAPS, DIB's and metafiles are not passed directly, but
            // instead are passed in a block of memory which contains the
            // HBITMAP, handles to DIBs or metafiles.  All other formats are
            // passed directly.  CF_TEXT, for instance, can be accessed
            // directly as (LPSZ)GlobalLock(((LPLINKDATA)lp)->hData).

            // Note that DIB's are the preferred format for DDE: when
            // bitmaps are passed between applications, palette information
            // is not included, leading to problems when transferring 256
            // bitmaps.

            if (wp != CF_BITMAP)
                return LINK_DATA_FORMATBAD;

            hpic = ((PPIX)VBDerefControl(hctl))->hpicPict;
            VBGetPicEx(hpic, &pic, VB_VERSION);

            if (pic.picType == PICTYPE_BITMAP)
                {
                BITMAP   bmp;
                LONG     lDataLen;
                HANDLE   hData, hDdeData;
                LPHANDLE lphnd;
                char FAR *pch;

                // All data allocated, regardless of format, must be
                // GMEM_MOVEABLE and GMEM_DDESHARE.

                hDdeData = GlobalAlloc(GMEM_MOVEABLE | GMEM_DDESHARE,
                                  sizeof(pic.picData.bmp.hbitmap) + 1);
                if (!hDdeData)
                    return LINK_DATA_OOM;

                // Copy the bitmap
                if (!GetObject(pic.picData.bmp.hbitmap, sizeof(BITMAP),
                              (LPSTR)&bmp))
                  return LINK_DATA_OOM;

                lDataLen = (LONG)bmp.bmHeight * bmp.bmWidthBytes *
                              bmp.bmPlanes;
                hData = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT,
                             lDataLen);

                if (!hData)
                  return LINK_DATA_OOM;

                pch = GlobalLock(hData);
                if (!GetBitmapBits((HBITMAP)pic.picData.bmp.hbitmap,
                              lDataLen, pch))
                  return LINK_DATA_OOM;

                lphnd = (LPHANDLE) GlobalLock(hDdeData);
                *lphnd = CreateBitmap(bmp.bmWidth, bmp.bmHeight,
                                      bmp.bmPlanes, bmp.bmBitsPixel,
                                      pch);

                GlobalUnlock(hData);
                GlobalFree(hData);
                GlobalUnlock(hDdeData);

                ((LPLINKDATA)lp)->cb = sizeof(hDdeData);
                ((LPLINKDATA)lp)->hData = hDdeData;
                return LINK_DATA_OK;
                }
              else
                return LINK_DATA_FORMATBAD;
            }

        case VBM_LINKSETDATA:
            {
            HPIC   hpic;
            LPVOID lpv;

            // Bitmaps and DIB's and metafiles are special cases for DDE.
            // HBITMAPS, DIB's and metafiles are not passed directly, but
            // instead are passed in a block of memory which contains the
            // HBITMAP, handles to DIBs or metafiles.  All other formats are
            // passed directly.  CF_TEXT, for instance, can be accessed
            // directly as (LPSZ)GlobalLock(((LPLINKDATA)lp)->hData).

            // Note that DIB's are the preferred format for DDE: when
            // bitmaps are passed between applications, palette information
            // is not included, leading to problems when transferring 256
            // bitmaps.

            // Assure that the clipboard format is of type text.
            if (wp != CF_BITMAP)
                return LINK_DATA_FORMATBAD;

            lpv = GlobalLock(((LPLINKDATA)lp)->hData);

            VBPicFromCF((HPIC FAR *) &hpic, *(HANDLE far *)lpv, wp);
            GlobalUnlock(((LPLINKDATA)lp)->hData);

            if (VBSetControlProperty(hctl, IPROP_PIX_PICT, (LONG)hpic))
                return LINK_DATA_SETFAILED;

            return LINK_DATA_OK;
            }

        case VBM_QPASTEOK:
            if (wp == PT_PASTELINK)
                return VBPasteLinkOk(NULL, hctl);
            break;
	}

    return VBDefControlProc(hctl, hwnd, msg, wp, lp);

}


//---------------------------------------------------------------------------
// Paint the bitmap into the Pix control.
//---------------------------------------------------------------------------
VOID NEAR PaintPix
(
    HCTL   hctl,
    HDC    hdc,
    LPRECT lprect
)
{
    HPIC     hpic;
    PIC      pic;
    BITMAP   bmp;
    HDC      hdcMem;
    HPEN     hpen, hpenOld;
    HPALETTE hpalSave = NULL;
    HPALETTE hpalOld = NULL;

    // Draw a border
    hpen = CreatePen(0, 1, COLOR_DEFBITON | COLOR_WINDOWFRAME);
    if (hpen)
      hpenOld = SelectObject(hdc, (HANDLE)hpen);
    Rectangle(hdc, lprect->left, lprect->top, lprect->right, lprect->bottom);
    if (hpen && hpenOld)
      {
      SelectObject(hdc, (HANDLE)hpenOld);
      DeleteObject((HANDLE)hpen);
      }

    // Paint the bitmap, if there is one
    hpic = ((PPIX)VBDerefControl(hctl))->hpicPict;

    if (VBGetVersion() >= VB200_VERSION)
	VBGetPicEx(hpic, &pic, VB_VERSION);
    else
	{
	// Initialize the hpal field to NULL since VBGetPic will not
	// do it.
	pic.picData.bmp.hpal = NULL;
	VBGetPic(hpic, &pic);
	}

    switch (pic.picType)
	{
	case PICTYPE_BITMAP:
	    GetObject(pic.picData.bmp.hbitmap, sizeof(BITMAP), (LPSTR)&bmp);
	    hdcMem = CreateCompatibleDC(hdc);

	    if (pic.picData.bmp.hpal)
	      {
	      if (!PictFMemDC(hdc))
		{
		// If the hdc is a memory DC, then PictStretchBlt will use
		// the palette of the destination DC correctly.
		// One condition that the hdc will be a memory dc is when
		// the control is being printed.  In that case, a rainbow
		// palette has already been selected into the hdc and
		// will be used for the printing.
		// NOTE: If this control was a windowed control under
		// NOTE: VB 2.0 of higher, then there is no need to
		// NOTE: select the palette into the destination DC
		// NOTE: because VB will already have done so.
		hpalOld = SelectPalette(hdc, pic.picData.bmp.hpal, TRUE);
		RealizePalette(hdc);
		}
	      // If the bitmap has a palette, select it into the memory dc
	      hpalSave = SelectPalette(hdcMem, pic.picData.bmp.hpal, FALSE);
	      RealizePalette(hdcMem);
	      }

	    SelectObject(hdcMem, pic.picData.bmp.hbitmap);
	    // Note that since we drew a border, the area into which we
	    // PictStretchBlt the bitmap is two pixels smaller.
	    // NOTE: We must use PictStretchBlt instead of StretchBlt
	    // NOTE: to handle printing 256-color bitmaps!
	    PictStretchBlt(hdc, lprect->left+1, lprect->top+1,
		       lprect->right  - lprect->left - 2,
		       lprect->bottom - lprect->top  - 2,
		       hdcMem, 0, 0,
		       bmp.bmWidth, bmp.bmHeight, SRCCOPY);

	    if (hpalOld)
	      {
	      SelectPalette(hdc, hpalOld, TRUE);
	      RealizePalette(hdc);
	      }
	    if (hpalSave)
	      {
	      SelectPalette(hdcMem, hpalSave, FALSE);
	      RealizePalette(hdcMem);
	      }

	    DeleteDC(hdcMem);
            break;

	case PICTYPE_NONE:
	    // Remain totally transparent if we don't have a picture
	    break;
	}
}


//---------------------------------------------------------------------------
// Make a copy of hlstrSrc, and store the resulting hlstr in *lphlstrDest.
// On entry *lphlstrDest may be NULL or a valid hlstr.	If NULL, a new hlstr
// will be allocated to hold hlstrSrc, and then this handle will be stored
// in *lphlstrDest.  If *lphlstrDest was originally non-NULL, then we try
// resizing *lphlstrDest to fit hlstrSrc, and failing that, we free the
// hlstr at *lphlstrDest, and allocate a new hlstr, storing that new handle
// back into *lphlstrDest.
//---------------------------------------------------------------------------
// WARNING: This routine is called from VBM_SETPROPERTY!!!!  We must never
// WARNING: call VBGetHlstr() in response to VBM_SETPROPERTY, since this VB
// WARNING: API has the side affect of freeing the hlstr passed in, if it was
// WARNING: a temp hlstr.  Since we do not own the hlstr, we are forbidden to
// WARNING: free it, and hence must not call VBGetHlstr() or VBDestroyHlstr()
// WARNING: on the hlstr passed in lp.	We also cannot call
// WARNING: VBSetHlstr(xx,lp,-1), since this form of VBSetHlstr() will also
// WARNING: free lp if it is a temp string.
//---------------------------------------------------------------------------
ERR ErrCopyHlstr
(
  HLSTR FAR *lphlstrDest,
  HLSTR      hlstrSrc
)
{
    ERR    err;
    HLSTR  hlstrOld = *lphlstrDest;
    USHORT cb = VBGetHlstrLen(hlstrSrc);
    HLSTR  hlstrNew;

    // To prevent using excessive amts of memory, let's just try re-allocate
    // this hlstr in place.
    if (hlstrOld)
      {
      err = VBResizeHlstr(hlstrOld, cb);
      if (!err)
	{
	// Successful, so lets copy the string data and return
	return VBSetHlstr(lphlstrDest, VBDerefHlstr(hlstrSrc), cb);
	}
      }

    // Unsuccessful at re-allocating in place.	So, we'll now try allocating
    // a *new* hlstr to contain lp, since VBResizeHlstr() didn't try
    // allocating in a new segment.  Note we cannot do
    // VBCreateHlstr(VBDerefHlstr(hlstrSrc), cb), since the create might
    // cause hlstrSrc to move after we've already Deref'd it.
    hlstrNew = VBCreateHlstr(NULL, cb);
    if (!hlstrNew)
      return ERR_OutOfMemory;

    // Successful, so lets copy the string data
    err = VBSetHlstr(&hlstrNew, VBDerefHlstr(hlstrSrc), cb);
    if (err)
      {
      // Failed, so let's clean up and return the error
      if (hlstrNew)
	VBDestroyHlstr(hlstrNew);
      return err;
      }

    // Success.  Let's keep the new value, and free the old
    *lphlstrDest = hlstrNew;
    if (hlstrOld)
      VBDestroyHlstr(hlstrOld);
    return ERR_None;
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

    // Register control(s)
    if (usVersion < VB_VERSION)
      return VBRegisterModel(hmodDLL, &modelPix_Vb1);
    else
      return VBRegisterModel(hmodDLL, &modelPix);
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
	return &modelinfoPix_Vb1;
    else
	return &modelinfoPix;
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
#endif

//---------------------------------------------------------------------------
