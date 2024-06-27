//---------------------------------------------------------------------------
//		Copyright (C) 1992 Microsoft Corporation
//
// You have a royalty-free right to use, modify, reproduce and distribute
// the Sample Custom Control Files (and/or any modified version) in any way
// you find useful, provided that you agree that Microsoft has no warranty,
// obligation or liability for any Custom Control File.
//---------------------------------------------------------------------------
// XList.c
//---------------------------------------------------------------------------
// XList Custom Control
//---------------------------------------------------------------------------
// FUNCTIONS:
//
// XListCtlProc()      - Process Windows and Visual Basic messages
//	   CheckProperty()     - Validate setting of XLIST property
//	   SetPropertyArray()  - Set XLIST property stored in list item
//	   GetPropertyArray()  - Get value of XLIST property
//	   Methods()	       - Process standard listbox methods
//	   DrawItem()	       - Paint the item in the list
//	   MeasureItem()       - Return the height of the item in the list
// LibMain()	       - Perform DLL initialization tasks (DLL is loading)
// VBGetModelInfo()    - Return model info to host
// VBInitCC()	       - Perform VBX intialization tasks: register model
// WEP()	       - Perform DLL termination tasks (DLL is unloading)
//---------------------------------------------------------------------------

#include <windows.h>
#include <vbapi.h>
#include <memory.h>
#include "xlist.h"
#include "xlistvb1.h"

HANDLE hmodDLL;


//---------------------------------------------------------------------------
// Standard Error Values
//---------------------------------------------------------------------------
#define ERR_XLIST_NONE		    0
#define ERR_XLIST_BADINDEX	  381  // Error$(381) = "Invalid property array index"
#define ERR_XLIST_BADFORMAT	30000
#define ERR_XLIST_FONTSIZE	30001


//---------------------------------------------------------------------------
// Other Constants
//---------------------------------------------------------------------------
#define USE_DEFAULT_PROC	   -1


//---------------------------------------------------------------------------
// Local Prototypes
//---------------------------------------------------------------------------
LONG  NEAR PASCAL CheckProperty(USHORT iprop, LONG lp);
VOID  NEAR PASCAL DrawItem(HCTL hctl, LPDRAWITEMSTRUCT lpdi);
VOID  NEAR PASCAL FreeItemAttr(HWND hwnd, SHORT sIndex);
HFONT NEAR PASCAL GetFontHandle(LPSTR lpFontName, int nHeight);
int   NEAR PASCAL GetFontNameFromhFont(HFONT hFont, LPSTR szFontName);
LONG  NEAR PASCAL GetPropertyArray(HCTL hctl, HWND hwnd, USHORT iprop, LPDATASTRUCT lpds);
VOID  NEAR PASCAL MeasureItem(HCTL hctl, LPMEASUREITEMSTRUCT lpMI);
LONG  NEAR PASCAL Methods(HWND hwnd, USHORT meth, LONG lp);
LONG  NEAR PASCAL SetPropertyArray(HWND hwnd, USHORT iprop, LPDATASTRUCT lpds);


//---------------------------------------------------------------------------
// This routine is the subclassed window procedure.  Visual Basic passes
// VBM_, VBN_, and WM_ messages to this routine.  The custom control
// determines which messages to process.  Any messages that are not
// processed need to passed on to the default message processing routine
// VBDefControlProc().
//---------------------------------------------------------------------------
LONG FAR PASCAL _export XListCtlProc
(
    HCTL   hctl,
    HWND   hwnd,
    USHORT msg,
    USHORT wp,
    LONG   lp
)
{
    LONG    lRetVal;
    LPXLIST lpxlist;
    SHORT   sItems;
    SHORT   i;

    switch (msg)
	{
	case WM_CREATE:
	    // For each newly created control, set the default property
	    // values.
	    lpxlist = (LPXLIST)VBDerefControl(hctl);
	    lpxlist->itemDefHeight = DEFAULT_ITEM_HEIGHT;
	    lpxlist->bInvert = TRUE;
	    break;

	case VBM_METHOD:
	    // Respond to the AddItem and RemoveItem methods for the listbox.
	    lRetVal = Methods(hwnd, wp, lp);
	    if (lRetVal != USE_DEFAULT_PROC)
		return lRetVal;
	    break;

        case VBM_CHECKPROPERTY:
	    // Validate the property setting before it is saved.
	    lRetVal = CheckProperty(wp, lp);
	    if (lRetVal != USE_DEFAULT_PROC)
		return lRetVal;
	    break;

        case VBM_SETPROPERTY:
	    // Set the property value.
	    lRetVal = SetPropertyArray(hwnd, wp, (LPDATASTRUCT)lp);
	    if (lRetVal != USE_DEFAULT_PROC)
		return lRetVal;
	    break;

        case VBM_GETPROPERTY:
	    // Get the property value.
	    switch (wp)
		{
		case IPROP_XLIST_ITEMBACKCOLOR:
		case IPROP_XLIST_ITEMFONTNAME:
		case IPROP_XLIST_ITEMFONTSIZE:
		case IPROP_XLIST_ITEMFORECOLOR:
		case IPROP_XLIST_ITEMIMAGE:
		    lRetVal = GetPropertyArray(hctl, hwnd, wp, (LPDATASTRUCT)lp);
		    if (lRetVal != USE_DEFAULT_PROC)
			return lRetVal;
		    break;
		}
	    break;

	case VBN_DRAWITEM:
	    // Draw the specified item in the listbox.
	    DrawItem(hctl, (LPDRAWITEMSTRUCT)lp);
	    return 0;

	case VBN_MEASUREITEM:
	    // Return the height of the specified item in the listbox.
	    MeasureItem(hctl, (LPMEASUREITEMSTRUCT)lp);
	    return 0;

	case WM_DESTROY:
	    // Deallocate all memory associated with the listbox item.
	    sItems = (SHORT)SendMessage(hwnd, LB_GETCOUNT, 0, 0L);

	    for (i = 0; i < sItems; i++)
		FreeItemAttr(hwnd, i);
	    break;
	}

    return VBDefControlProc(hctl, hwnd, msg, wp, lp);
}


//---------------------------------------------------------------------------
// Deallocate the memory that is stored with each item in the listbox.
//---------------------------------------------------------------------------
VOID NEAR PASCAL FreeItemAttr
(
    HWND  hwnd,
    SHORT sIndex
)
{
    HANDLE hAttr;
    LPATTR lpAttr;

    hAttr = (HANDLE)SendMessage(hwnd, LB_GETITEMDATA, sIndex, 0L);
    if (hAttr == (HANDLE)NULL)
	return;

    lpAttr = (LPATTR)GlobalLock(hAttr);
    if (lpAttr == (LPATTR)NULL)
	return;

    if (lpAttr->hFont)
	DeleteObject(lpAttr->hFont);

    if (lpAttr->hPic)
	VBFreePic(lpAttr->hPic);

    GlobalUnlock(hAttr);
    GlobalFree(hAttr);
}


//---------------------------------------------------------------------------
// This routine validates the value of the property setting before it is
// saved.
//---------------------------------------------------------------------------
LONG NEAR PASCAL CheckProperty
(
    USHORT iprop,
    LONG   lp
)
{
    PIC pic;

    switch (iprop)
	{
	case IPROP_XLIST_ITEMIMAGE:
	    // Verify the ItemImage property is a valid bitmap file.
	    VBGetPic((HPIC)lp, &pic);
	    switch (pic.picType)
		{
		case PICTYPE_BITMAP:
		    return ERR_XLIST_NONE;

		default:
		    return VBSetErrorMessage(ERR_XLIST_BADFORMAT,
					     "Image format not supported.");
		}
	break;
	}

    return USE_DEFAULT_PROC;
}


//---------------------------------------------------------------------------
// This routine saves the value of the property setting, using the data
// storage area of the list item.
//---------------------------------------------------------------------------
LONG NEAR PASCAL SetPropertyArray
(
    HWND	 hwnd,
    USHORT	 iprop,
    LPDATASTRUCT lpds
)
{
    HANDLE  hAttr;
    HANDLE  hFontNew = NULL;
    LPATTR  lpAttr;
    LONG    lReturn;
    SHORT   i;

    switch (iprop)
	{
	case IPROP_XLIST_ITEMBACKCOLOR:
	case IPROP_XLIST_ITEMFONTNAME:
	case IPROP_XLIST_ITEMFONTSIZE:
	case IPROP_XLIST_ITEMFORECOLOR:
	case IPROP_XLIST_ITEMIMAGE:
	    break;

	default:
	   return USE_DEFAULT_PROC;
	}

    i = (SHORT)lpds->index[0].data;

    hAttr = (HANDLE)SendMessage(hwnd, LB_GETITEMDATA, i, 0L);
    if (hAttr == (HANDLE)LB_ERR)
	return ERR_XLIST_BADINDEX;

    lpAttr = (LPATTR)GlobalLock(hAttr);

    lReturn = 0;
    switch (iprop)
	{
	case IPROP_XLIST_ITEMBACKCOLOR:
	    lpAttr->cBack = (COLORREF)lpds->data;
	    break;

	case IPROP_XLIST_ITEMFONTNAME:
        hFontNew = GetFontHandle((LPSTR)lpds->data, lpAttr->fontSize);
        if (hFontNew) {
	        if (lpAttr->hFont)
                DeleteObject(lpAttr->hFont);
            lpAttr->hFont = hFontNew;
            }
        else
		    lReturn = ERR_XLIST_BADINDEX;
	    break;

	case IPROP_XLIST_ITEMFONTSIZE:
		{
		char szFontName[255];

	    if ((USHORT)lpds->data == lpAttr->fontSize)
			break;

	    lpAttr->fontSize = (USHORT)lpds->data;

		if (lpAttr->hFont == (HFONT)NULL)
			break;

		if (GetFontNameFromhFont(lpAttr->hFont, (LPSTR)szFontName) == 0)
			return ERR_XLIST_FONTSIZE;

        hFontNew = GetFontHandle((LPSTR)szFontName, lpAttr->fontSize);
        if (hFontNew) {
	        if (lpAttr->hFont)
                DeleteObject(lpAttr->hFont);
            lpAttr->hFont = hFontNew;
            }
        else
		    lReturn = ERR_XLIST_BADINDEX;
		
		}		
	    break;

	case IPROP_XLIST_ITEMFORECOLOR:
	    lpAttr->cFore = (COLORREF)lpds->data;
	    break;

	case IPROP_XLIST_ITEMIMAGE:
        if (lpAttr->hPic)
            VBFreePic(lpAttr->hPic);

	    lpAttr->hPic = (HPIC)lpds->data;
	    VBRefPic(lpAttr->hPic);
	    break;
	}

    GlobalUnlock(hAttr);

    if (lReturn == 0)
        InvalidateRect(hwnd, NULL, TRUE);

    return lReturn;
}


//---------------------------------------------------------------------------
// This routine retrieves the value of the property setting, using the data
// storage area of the list item.
//---------------------------------------------------------------------------
LONG NEAR PASCAL GetPropertyArray
(
    HCTL	 hctl,
    HWND	 hwnd,
    USHORT	 iprop,
    LPDATASTRUCT lpds
)
{
    HANDLE  hAttr;
    LPATTR  lpAttr;
    LONG    lReturn;
    LOGFONT logfont;
    SHORT   i;

    i = (SHORT)lpds->index[0].data;

    hAttr = (HANDLE)SendMessage(hwnd, LB_GETITEMDATA, i, 0L);
    if (hAttr == (HANDLE)LB_ERR)
	return ERR_XLIST_BADINDEX;

    lpAttr = (LPATTR)GlobalLock(hAttr);

    lReturn = 0;
    switch (iprop)
	{
	case IPROP_XLIST_ITEMBACKCOLOR:
	    lpds->data = (LONG)lpAttr->cBack;
	    break;

	case IPROP_XLIST_ITEMFONTNAME:
	    if ((GetObject(lpAttr->hFont, sizeof(LOGFONT), (LPSTR)&logfont)) == 0)
		return ERR_XLIST_BADINDEX;

	    lpds->data = (LONG)VBCreateHsz((_segment)hctl, (LPSTR)logfont.lfFaceName);
	    break;

	case IPROP_XLIST_ITEMFONTSIZE:
	    lpds->data = (LONG)lpAttr->fontSize;
	    break;

	case IPROP_XLIST_ITEMFORECOLOR:
	    lpds->data = (LONG)lpAttr->cFore;
	    break;

	case IPROP_XLIST_ITEMIMAGE:
	    lpds->data = (LONG)lpAttr->hPic;
	    break;
	}

    GlobalUnlock(hAttr);
    return lReturn;
}


//---------------------------------------------------------------------------
// This routine creates a font handle from the specified font name and font
// size.
//---------------------------------------------------------------------------
HFONT NEAR PASCAL GetFontHandle
(
    LPSTR lpFontName,
    int   nHeight
)
{
    LOGFONT logfont;

    // Set all logical font values to 0 (default).
    _fmemset(&logfont, '\0', sizeof(logfont));

    logfont.lfHeight = nHeight;
    lstrcpy((LPSTR)logfont.lfFaceName, lpFontName);

    return CreateFontIndirect(&logfont);
}


//---------------------------------------------------------------------------
// This routine returns the font name from a given a font handle.
//---------------------------------------------------------------------------
int NEAR PASCAL GetFontNameFromhFont
(
	HFONT hFont,
	LPSTR szFaceName
)
{
    LOGFONT logfont;

	if (GetObject(hFont, sizeof(LOGFONT), &logfont) == 0)
		return 0;

    lstrcpy((LPSTR)szFaceName, (LPSTR)logfont.lfFaceName);
    return 1;
}


//---------------------------------------------------------------------------
// This routine handles the AddItem and RemoveItem methods.
//---------------------------------------------------------------------------
LONG NEAR PASCAL Methods
(
    HWND   hwnd,
    USHORT meth,
    LONG   lp
)
{
    LPSTR   lpAddItem;
    LPDWORD lpdwArgv;
    SHORT   cIndex;
    HANDLE  hAttr;
    LPATTR  lpAttr;
    SHORT   cItems;
    LONG    lResult;

    lpdwArgv = (LPDWORD)lp;

    switch (meth)
	{
	case METH_ADDITEM:
	    cItems = (SHORT)SendMessage(hwnd, LB_GETCOUNT, 0, 0L);

	    if ((USHORT)lpdwArgv[0] == 3)
		{
		cIndex = (SHORT)lpdwArgv[2];
		if (cIndex >= cItems)
		    return ERR_XLIST_BADINDEX;
		}
	    else
		cIndex = -1;

	    lpAddItem = VBDerefHsz((HSZ)lpdwArgv[1]);
	    cIndex = SendMessage(hwnd, LB_INSERTSTRING, cIndex, (DWORD)lpAddItem);

	    // Allocate a structure and store the handle to it in the item
	    // that was just added to the listbox.
	    hAttr = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, sizeof(ATTR));
	    if (hAttr == (HANDLE)NULL)
		return 0;

	    lpAttr = (LPATTR)GlobalLock(hAttr);
	    lpAttr->cBack = GetSysColor(COLOR_WINDOW);
	    lpAttr->cFore = GetSysColor(COLOR_WINDOWTEXT);
	    GlobalUnlock(hAttr);
	    SendMessage(hwnd, LB_SETITEMDATA, cIndex, (DWORD)hAttr);
	    return 0L;

	case METH_REMOVEITEM:
	    cItems = (SHORT)SendMessage(hwnd, LB_GETCOUNT, 0, 0L);

	    cIndex = (SHORT)lpdwArgv[1];
	    if (cIndex >= cItems)
		return ERR_XLIST_BADINDEX;

	    // Deallocate any allocated values corresponding to the item that
	    // is being deleted from the listbox.
	    FreeItemAttr(hwnd, cIndex);

	    lResult = SendMessage(hwnd, LB_DELETESTRING, cIndex, 0L);
	    return ((lResult == LB_ERR) ? ERR_XLIST_BADINDEX : 0L);

    case METH_CLEAR:
	    // Deallocate all memory associated with the listbox item.
	    cItems = (SHORT)SendMessage(hwnd, LB_GETCOUNT, 0, 0L);

	    for (cIndex = 0; cIndex < cItems; cIndex++)
		    FreeItemAttr(hwnd, cIndex);

        SendMessage(hwnd, LB_RESETCONTENT, 0, 0L);
        return 0L;

    default:
        return USE_DEFAULT_PROC;
	}
}


//---------------------------------------------------------------------------
// This routine paints the item in the listbox, using the attributes stored
// with the item.
//---------------------------------------------------------------------------
VOID NEAR PASCAL DrawItem
(
    HCTL	     hctl,
    LPDRAWITEMSTRUCT lpdi
)
{
    CHAR     buffer[255];
    LPSTR    lpBuf;
    HBRUSH   hBrush;
    USHORT   usLen;
    COLORREF cBack;
    COLORREF cFore;
    HFONT    hFont;
    HFONT    hOldFont;
    PIC      pic;
    BITMAP   bmp;
    HDC      hdcMem;
    LPATTR   lpAttr;
    HANDLE   hAttr;
    HPIC     hPic;
    LPXLIST  lpxlist;
    SHORT    offset;

    switch (lpdi->itemAction)
	{
	case ODA_DRAWENTIRE:
	    hAttr = (HANDLE)SendMessage(lpdi->hwndItem, LB_GETITEMDATA, lpdi->itemID, 0L);
        if (hAttr) {
	        lpAttr = (LPATTR)GlobalLock(hAttr);
	        cBack = lpAttr->cBack;
	        cFore = lpAttr->cFore;
	        hFont = lpAttr->hFont;
	        hPic = lpAttr->hPic;
	        GlobalUnlock(hAttr);
        } else {
	        cBack = GetSysColor(COLOR_WINDOW);
	        cFore = GetSysColor(COLOR_WINDOWTEXT);
	        hFont = (HFONT)NULL;
	        hPic = (HPIC)NULL;
        }

		hBrush = CreateSolidBrush(cBack);
		FillRect(lpdi->hDC, (LPRECT)&lpdi->rcItem, hBrush);
		DeleteObject(hBrush);
		SetBkColor(lpdi->hDC, cBack);

	    offset = 0;
	    if (hPic)
		{
		VBGetPic(hPic, &pic);
		GetObject(pic.picData.bmp.hbitmap, sizeof(BITMAP), (LPSTR)&bmp);
		hdcMem = CreateCompatibleDC(lpdi->hDC);
		SelectObject(hdcMem, pic.picData.bmp.hbitmap);

		BitBlt(lpdi->hDC, lpdi->rcItem.left, lpdi->rcItem.top,
		    lpdi->rcItem.right - lpdi->rcItem.left + 1,
		    lpdi->rcItem.bottom - lpdi->rcItem.top + 1,
		    hdcMem, 0, 0, SRCCOPY);

		DeleteDC(hdcMem);
		offset = (SHORT)(bmp.bmWidth * 1.25);
		}

	    lpBuf = (LPSTR)buffer;
	    SendMessage(lpdi->hwndItem, LB_GETTEXT, lpdi->itemID, (DWORD)lpBuf);
	    usLen = (USHORT)lstrlen(lpBuf);

	    if (usLen)
		{
		SetTextColor(lpdi->hDC, cFore);

		hOldFont = NULL;
		if (hFont)
		    hOldFont = SelectObject(lpdi->hDC, hFont);

		lpdi->rcItem.left += offset;
		DrawText(lpdi->hDC, lpBuf, usLen, &lpdi->rcItem, DT_LEFT);

		if (hOldFont)
		    SelectObject(lpdi->hDC, hOldFont);
		}

	    if (lpdi->itemState != ODS_SELECTED)
		break;

	    /*	FALL THROUGH  */

	case ODA_SELECT:
	    lpxlist = (LPXLIST)VBDerefControl(hctl);
	    if (lpxlist->bInvert)
		InvertRect(lpdi->hDC, &lpdi->rcItem);
	    break;

	case ODA_FOCUS:
	    DrawFocusRect(lpdi->hDC, &lpdi->rcItem);
	    break;
	}
}


//---------------------------------------------------------------------------
// This routine retrieves the height of the items in the listbox.
//---------------------------------------------------------------------------
VOID NEAR PASCAL MeasureItem
(
    HCTL		hctl,
    LPMEASUREITEMSTRUCT lpMI
)
{
    LPXLIST lpxlist;

    lpxlist = (LPXLIST)VBDerefControl(hctl);

    // Convert the height to pixels before setting the value.
    if (lpxlist->itemDefHeight)
	lpMI->itemHeight = VBYTwipsToPixels(lpxlist->itemDefHeight);
    else
	lpMI->itemHeight = VBYTwipsToPixels(DEFAULT_ITEM_HEIGHT);
}


//---------------------------------------------------------------------------
// This routine is called when the first client loads the DLL.
//---------------------------------------------------------------------------
BOOL FAR PASCAL LibMain
(
    HANDLE hmod,
    HANDLE wDataSeg,
    USHORT cbHeapSize,
    LPSTR  lpszCmdLine
)
{
    // Avoid warnings on unused (but required) formal parameters.
    lpszCmdLine = lpszCmdLine;
    wDataSeg	= wDataSeg;

    hmodDLL = hmod;

    return TRUE;
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
	return (LPMODELINFO)&modelXList_Vb1;
    else
	return (LPMODELINFO)&modelXList;
}


//---------------------------------------------------------------------------
// This routine is called by VB when the custom control DLL is loaded for
// use.
//---------------------------------------------------------------------------
BOOL FAR PASCAL _export VBInitCC
(
    USHORT usVersion,
    BOOL   bRuntime
)
{
    // Avoid warnings on unused (but required) formal parameters.
    bRuntime  = bRuntime;

    // Register the XList control according to the VB version.
    if (usVersion < VB_VERSION)
	return VBRegisterModel(hmodDLL, &modelXList_Vb1);
    else
	return VBRegisterModel(hmodDLL, &modelXList);
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
