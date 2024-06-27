//---------------------------------------------------------------------------
//		Copyright (C) 1991-92, Microsoft Corporation
//
// You have a royalty-free right to use, modify, reproduce and distribute
// the Sample Custom Control Files (and/or any modified version) in any way
// you find useful, provided that you agree that Microsoft has no warranty,
// obligation or liability for any Custom Control File.
//---------------------------------------------------------------------------
// Circ3.h
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Resource Information
//---------------------------------------------------------------------------
// Toolbox bitmap resource IDs numbers.
//---------------------------------------------------------------------------
#define IDBMP_CIRCLE		8000
#define IDBMP_CIRCLEDOWN	8001
#define IDBMP_CIRCLEMONO	8003
#define IDBMP_CIRCLEEGA 	8006


//---------------------------------------------------------------------------
// Constants used by dialog boxes
//---------------------------------------------------------------------------
#define DI_OK	      1
#define DI_CANCEL     2
#define DI_REDOPT     105
#define DI_GREENOPT   106
#define DI_BLUEOPT    107


//---------------------------------------------------------------------------
// Change these for each new VBX file
//---------------------------------------------------------------------------
#define VBX_COMPANYNAME 	   "Microsoft Corporation\0"
#define VBX_FILEDESCRIPTION	   "Visual Basic Circle Custom Control Example\0"
#define VBX_INTERNALNAME	   "CIRC3\0"
#define VBX_LEGALCOPYRIGHT	   "Copyright \251 Microsoft Corp. 1991-92\0"
#define VBX_LEGALTRADEMARKS	   "Microsoft\256 is a registered trademark of Microsoft Corporation. Visual Basic\231 is a trademark of Microsoft Corporation. Windows\231 is a trademark of Microsoft Corporation.\0"
#define VBX_ORIGINALFILENAME	   "CIRC3.VBX\0"
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
LONG FAR PASCAL _export CircleCtlProc(HCTL, HWND, USHORT, USHORT, LONG);
LONG FAR PASCAL _export FlashPopupWndProc(HWND hwnd, USHORT msg, USHORT wp, LONG lp);


//---------------------------------------------------------------------------
// Global Variables and Constants
//---------------------------------------------------------------------------
extern	HANDLE hmodDLL;     // From ccinit.c
#define CLASS_FLASHPOPUP    "FCPopup"


//---------------------------------------------------------------------------
// CIRCLE control data and structs
//---------------------------------------------------------------------------
typedef struct tagCIRC
    {
    RECT    rectDrawInto;
    ENUM    CircleShape;    // Changed from SHORT to demonstrate ENUM prop
    LONG    FlashColor;
    HFONT   hfont;
    HSZ     hszCaption;
    } CIRC;

typedef CIRC FAR * LPCIRC;

#define LpcircDEREF(hctl)     ((LPCIRC)VBDerefControl(hctl))


//---------------------------------------------------------------------------
// Private messages
//---------------------------------------------------------------------------
#define CM_OPENFLASHDLG     WM_USER


//---------------------------------------------------------------------------
// Property info
//---------------------------------------------------------------------------
// List of enumeration for CircleShape ENUM property
#define SHAPE_CIRCLE	0
#define SHAPE_OVAL	1
#define SHAPE_MAX	1

PROPINFO Property_CircleShape =
    {
    "CircleShape",
    // Changed from SHORT to demonstrate an ENUM property
    DT_ENUM | PF_fGetData | PF_fSetMsg | PF_fSaveData,
    OFFSETIN(CIRC, CircleShape), 0,
    SHAPE_CIRCLE,
    "0 - Circle\0" "1 - Oval\0", SHAPE_MAX
    };

PROPINFO Property_FlashColor =
    {
    "FlashColor",
    DT_COLOR | PF_fGetData | PF_fSetData | PF_fSaveData | PF_fEditable,
    OFFSETIN(CIRC, FlashColor)
    };


//---------------------------------------------------------------------------
// Property list
//---------------------------------------------------------------------------
// Define the consecutive indicies for the properties
//---------------------------------------------------------------------------
#define IPROP_CIRCLE_CTLNAME		  0
#define IPROP_CIRCLE_INDEX                1
#define IPROP_CIRCLE_BACKCOLOR            2
#define IPROP_CIRCLE_LEFT                 3
#define IPROP_CIRCLE_TOP                  4
#define IPROP_CIRCLE_WIDTH                5
#define IPROP_CIRCLE_HEIGHT               6
#define IPROP_CIRCLE_VISIBLE              7
#define IPROP_CIRCLE_PARENT               8
#define IPROP_CIRCLE_DRAGMODE             9
#define IPROP_CIRCLE_DRAGICON            10
#define IPROP_CIRCLE_TAG                 11
#define IPROP_CIRCLE_CIRCLESHAPE         12
#define IPROP_CIRCLE_FLASHCOLOR          13
#define IPROP_CIRCLE_CAPTION             14
#define IPROP_CIRCLE_FONTNAME            15
#define IPROP_CIRCLE_FONTBOLD            16
#define IPROP_CIRCLE_FONTITALIC          17
#define IPROP_CIRCLE_FONTSTRIKE          18
#define IPROP_CIRCLE_FONTUNDER           19
#define IPROP_CIRCLE_FONTSIZE            20
#define IPROP_CIRCLE_BORDERSTYLE	 21
#define IPROP_CIRCLE_TABINDEX		 22
#define IPROP_CIRCLE_TABSTOP		 23
#define IPROP_CIRCLE_ENABLED		 24
#define IPROP_CIRCLE_MOUSEPOINTER	 25
#define IPROP_CIRCLE_HWND		 26
#define IPROP_CIRCLE_HELPCONTEXTID	 27

PPROPINFO Circle_Properties[] =
    {
    PPROPINFO_STD_CTLNAME,
    PPROPINFO_STD_INDEX,
    PPROPINFO_STD_BACKCOLOR,
    PPROPINFO_STD_LEFT,
    PPROPINFO_STD_TOP,
    PPROPINFO_STD_WIDTH,
    PPROPINFO_STD_HEIGHT,
    PPROPINFO_STD_VISIBLE,
    PPROPINFO_STD_PARENT,
    PPROPINFO_STD_DRAGMODE,
    PPROPINFO_STD_DRAGICON,
    PPROPINFO_STD_TAG,
    &Property_CircleShape,
    &Property_FlashColor,
    PPROPINFO_STD_CAPTION,
    PPROPINFO_STD_FONTNAME,
    PPROPINFO_STD_FONTBOLD,
    PPROPINFO_STD_FONTITALIC,
    PPROPINFO_STD_FONTSTRIKE,
    PPROPINFO_STD_FONTUNDER,
    PPROPINFO_STD_FONTSIZE,
    PPROPINFO_STD_BORDERSTYLEOFF,
    PPROPINFO_STD_TABINDEX,
    PPROPINFO_STD_TABSTOP,
    PPROPINFO_STD_ENABLED,
    PPROPINFO_STD_MOUSEPOINTER,
    PPROPINFO_STD_HWND,
    PPROPINFO_STD_HELPCONTEXTID,
    NULL
    };


//---------------------------------------------------------------------------
// Event info
//---------------------------------------------------------------------------
WORD Paramtypes_ClickIn[] = {ET_R4, ET_R4, ET_SD};

EVENTINFO Event_ClickIn =
    {
    "ClickIn",
    3,
    6,
    Paramtypes_ClickIn,
    "X As Single,Y As Single,Caption As String"
    };

EVENTINFO Event_ClickOut =
    {
    "ClickOut",
    0,
    0,
    NULL,
    NULL
    };


//---------------------------------------------------------------------------
// Event list
//---------------------------------------------------------------------------
// Define the consecutive indicies for the events
//---------------------------------------------------------------------------
#define IEVENT_CIRCLE_CLICKIN		  0
#define IEVENT_CIRCLE_CLICKOUT		  1
#define IEVENT_CIRCLE_DRAGDROP		  2
#define IEVENT_CIRCLE_DRAGOVER		  3

PEVENTINFO Circle_Events[] =
    {
    &Event_ClickIn,
    &Event_ClickOut,
    PEVENTINFO_STD_DRAGDROP,
    PEVENTINFO_STD_DRAGOVER,
    NULL
    };


//---------------------------------------------------------------------------
// Model struct
//---------------------------------------------------------------------------
// Define the control model (using the event and property structures).
//---------------------------------------------------------------------------
MODEL modelCircle =
    {
    VB_VERSION, 			// VB version being used
    MODEL_fFocusOk,			// MODEL flags
    (PCTLPROC)CircleCtlProc,		// Control procedure
    CS_VREDRAW | CS_HREDRAW,		// Class style
    0L, 				// Default Windows style
    sizeof(CIRC),			// Size of CIRC structure
    IDBMP_CIRCLE,			// Palette bitmap ID
    "Circle",				// Default control name
    "CIRC3",				// Visual Basic class name
    NULL,				// Parent class name
    Circle_Properties,			// Property information table
    Circle_Events,			// Event information table
    IPROP_CIRCLE_CIRCLESHAPE,		// Default property
    IEVENT_CIRCLE_CLICKIN,		// Default event
    IPROP_CIRCLE_CIRCLESHAPE		// Property representing value of ctl
    };

LPMODEL modellistCircle[] =
    {
    &modelCircle,
    NULL
    };

MODELINFO modelinfoCircle =
    {
    VB_VERSION, 			// VB version being used
    modellistCircle			// MODEL list
    };

#endif	// RC_INVOKED

//---------------------------------------------------------------------------
