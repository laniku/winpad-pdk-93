//---------------------------------------------------------------------------
//		Copyright (C) 1992, Microsoft Corporation
//
// You have a royalty-free right to use, modify, reproduce and distribute
// the Sample Custom Control Files (and/or any modified version) in any way
// you find useful, provided that you agree that Microsoft has no warranty,
// obligation or liability for any Custom Control File.
//---------------------------------------------------------------------------
// XList.h
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Resource Information
//---------------------------------------------------------------------------
// Toolbox bitmap resource IDs numbers.
//---------------------------------------------------------------------------
#define IDBMP_XLISTUP     8000
#define IDBMP_XLISTDOWN   8001
#define IDBMP_XLISTMONO   8003
#define IDBMP_XLISTEGA    8006


//---------------------------------------------------------------------------
// Change these for each new VBX file
//---------------------------------------------------------------------------
#define VBX_COMPANYNAME 	   "Microsoft Corporation\0"
#define VBX_FILEDESCRIPTION	   "Visual Basic XList Custom Control Example\0"
#define VBX_INTERNALNAME	   "XLIST\0"
#define VBX_LEGALCOPYRIGHT	   "Copyright \251 Microsoft Corp. 1991-92\0"
#define VBX_LEGALTRADEMARKS	   "Microsoft\256 is a registered trademark of Microsoft Corporation. Visual Basic\231 is a trademark of Microsoft Corporation. Windows\231 is a trademark of Microsoft Corporation.\0"
#define VBX_ORIGINALFILENAME	   "XLIST.VBX\0"
#define VBX_PRODUCTNAME 	   "Microsoft\256 Visual Basic\231 for Windows\231\0"


//---------------------------------------------------------------------------
// Update these fields for each build.
//---------------------------------------------------------------------------
#define VBX_VERSION		    2,00,6,01
#define VBX_VERSION_STR 	   "2.00.601\0"


#ifndef RC_INVOKED
//---------------------------------------------------------------------------
// Macro for referencing member of structure
//---------------------------------------------------------------------------
#define OFFSETIN(struc, field)	    ((USHORT)&(((struc *)0)->field))


//---------------------------------------------------------------------------
// Control and Window Procedures
//---------------------------------------------------------------------------
LONG FAR PASCAL _export XListCtlProc(HCTL, HWND, USHORT, USHORT, LONG);


//---------------------------------------------------------------------------
// Global Constants
//---------------------------------------------------------------------------
#define DEFAULT_ITEM_HEIGHT  195


//---------------------------------------------------------------------------
// Structure describing listbox entry
//---------------------------------------------------------------------------
typedef struct tagATTR
    {
    COLORREF cBack;
    COLORREF cFore;
    HFONT    hFont;
    HPIC     hPic;
    USHORT   fontSize;
    } ATTR, FAR *LPATTR;


//---------------------------------------------------------------------------
// XLIST control data and structs
//---------------------------------------------------------------------------
typedef struct tagXLIST
    {
    LONG itemDefHeight;
    BOOL bInvert;
    } XLIST, FAR * LPXLIST;


//---------------------------------------------------------------------------
// Property info
//---------------------------------------------------------------------------
PROPINFO Property_ItemBackColor =
    {
    "ItemBackColor",
    DT_COLOR | PF_fPropArray| PF_fGetMsg | PF_fSetMsg  | PF_fNoShow
    };

PROPINFO Property_ItemDefHeight =
    {
    "ItemDefHeight",
    DT_YSIZE | PF_fGetData | PF_fSetData | PF_fSaveData,
    OFFSETIN(XLIST, itemDefHeight)
    };

PROPINFO Property_ItemFontName =
    {
    "ItemFontName",
    DT_HSZ | PF_fPropArray| PF_fGetMsg | PF_fSetMsg  | PF_fNoShow
    };

PROPINFO Property_ItemFontSize =
    {
    "ItemFontSize",
    DT_SHORT | PF_fPropArray| PF_fGetMsg | PF_fSetMsg  | PF_fNoShow
    };

PROPINFO Property_ItemForeColor =
    {
    "ItemForeColor",
    DT_COLOR | PF_fPropArray| PF_fGetMsg | PF_fSetMsg  | PF_fNoShow
    };

PROPINFO Property_ItemImage =
    {
    "ItemImage",
    DT_PICTURE | PF_fPropArray | PF_fGetMsg | PF_fSetMsg | PF_fNoShow
    };

PROPINFO Property_ItemInvert =
    {
    "ItemInvert",
    DT_BOOL | PF_fGetData | PF_fSetData | PF_fSaveData,
    OFFSETIN(XLIST, bInvert)
    };


//---------------------------------------------------------------------------
// Property list
//---------------------------------------------------------------------------
// Define the consecutive indicies for the properties
//---------------------------------------------------------------------------
#define IPROP_XLIST_CTLNAME		 0
#define IPROP_XLIST_INDEX		 1
#define IPROP_XLIST_TAG 		 2
#define IPROP_XLIST_LEFT		 3
#define IPROP_XLIST_HEIGHT		 6
#define IPROP_XLIST_ITEMBACKCOLOR	 9
#define IPROP_XLIST_ITEMDEFHEIGHT	10
#define IPROP_XLIST_ITEMFONTNAME	11
#define IPROP_XLIST_ITEMFONTSIZE	12
#define IPROP_XLIST_ITEMFORECOLOR	13
#define IPROP_XLIST_ITEMIMAGE		14
#define IPROP_XLIST_ITEMINVERT		15

PPROPINFO XList_Properties[] =
    {
    PPROPINFO_STD_CTLNAME,
    PPROPINFO_STD_INDEX,
    PPROPINFO_STD_TAG,
    PPROPINFO_STD_LEFT,
    PPROPINFO_STD_TOP,
    PPROPINFO_STD_WIDTH,
    PPROPINFO_STD_HEIGHT,
    PPROPINFO_STD_FONTNAME,
    PPROPINFO_STD_FONTSIZE,
    &Property_ItemBackColor,
    &Property_ItemDefHeight,
    &Property_ItemFontName,
    &Property_ItemFontSize,
    &Property_ItemForeColor,
    &Property_ItemImage,
    &Property_ItemInvert,
    PPROPINFO_STD_HWND,
    PPROPINFO_STD_HELPCONTEXTID,
    PPROPINFO_STD_ALIGN,
    NULL
    };


//---------------------------------------------------------------------------
// Event list
//---------------------------------------------------------------------------
// Define the consecutive indicies for the events
//---------------------------------------------------------------------------
#define IEVENT_XLIST_CLICK            0

PEVENTINFO XList_Events[] =
    {
    PEVENTINFO_STD_CLICK,
    NULL
    };


//---------------------------------------------------------------------------
// Model struct
//---------------------------------------------------------------------------
// Define the control model (using the event and property structures).
//---------------------------------------------------------------------------
MODEL modelXList =
    {
    VB_VERSION, 			// VB version being used
    MODEL_fFocusOk | MODEL_fArrows	// MODEL flags
		   | MODEL_fInitMsg,
    (PCTLPROC)XListCtlProc,             // Control procedures
    CS_DBLCLKS | CS_HREDRAW		// Class style
	       | CS_VREDRAW,
    WS_VSCROLL | WS_BORDER		// Window style
	       | WS_CHILD
	       | LBS_NOTIFY
	       | LBS_OWNERDRAWVARIABLE
	       | LBS_HASSTRINGS,
    sizeof(XLIST),			// Size of XLIST structure
    IDBMP_XLISTUP,			// Palette bitmap ID
    "XList",				// Default control name
    "XListBox", 			// Visual Basic class name
    "LISTBOX",				// Parent class name
    XList_Properties,                   // Property information table
    XList_Events,			// Event information table
    -1					// Property representing value of ctl
    };

LPMODEL modelListXlist[] =
    {
    &modelXList,
    NULL
    };

MODELINFO modelInfoXList =
    {
    VB_VERSION,                         // VB version being used
    modelListXlist                      // MODEL list
    };

#endif  // RC_INVOKED

//---------------------------------------------------------------------------
