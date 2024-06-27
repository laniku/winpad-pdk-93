//---------------------------------------------------------------------------
//		Copyright (C) 1991-92, Microsoft Corporation
//
// You have a royalty-free right to use, modify, reproduce and distribute
// the Sample Custom Control Files (and/or any modified version) in any way
// you find useful, provided that you agree that Microsoft has no warranty,
// obligation or liability for any Custom Control File.
//---------------------------------------------------------------------------
// Circ2.h
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


#ifndef RC_INVOKED
//---------------------------------------------------------------------------
// Macro for referencing member of structure
//---------------------------------------------------------------------------
#define OFFSETIN(struc,field)	  ((USHORT)&(((struc *)0)->field))


//---------------------------------------------------------------------------
// Control Procedure
//---------------------------------------------------------------------------
LONG FAR PASCAL _export CircleCtlProc(HCTL, HWND, USHORT, USHORT, LONG);


//---------------------------------------------------------------------------
// CIRC control data and structs
//---------------------------------------------------------------------------
typedef struct tagCIRC
    {
    RECT  rectDrawInto;
    SHORT CircleShape;
    LONG  FlashColor;
    } CIRC;

typedef CIRC FAR * LPCIRC;

#define LpcircDEREF(hctl)	((LPCIRC)VBDerefControl(hctl))


//---------------------------------------------------------------------------
// Property info
//---------------------------------------------------------------------------
PROPINFO Property_CircleShape =
    {
    "CircleShape",
    DT_SHORT | PF_fGetData | PF_fSetMsg | PF_fSaveData,
    OFFSETIN(CIRC, CircleShape), 0,
    0,
    NULL, 0
    };

PROPINFO Property_FlashColor =
    {
    "FlashColor",
    DT_COLOR | PF_fGetData | PF_fSetData | PF_fSaveData,
    OFFSETIN(CIRC, FlashColor), 0,
    0,
    NULL, 0
    };


//---------------------------------------------------------------------------
// Property list
//---------------------------------------------------------------------------
// Define the consecutive indicies for the properties
//---------------------------------------------------------------------------
#define IPROP_CIRCLE_CTLNAME              0
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
#define IPROP_CIRCLE_SHAPE		 12
#define IPROP_CIRCLE_FLASHCOLOR 	 13
#define IPROP_CIRCLE_HWND		 14

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
    PPROPINFO_STD_HWND,
    NULL
    };


//---------------------------------------------------------------------------
// Event info
//---------------------------------------------------------------------------
WORD Paramtypes_ClickIn[] = {ET_R4, ET_R4};

EVENTINFO Event_ClickIn =
    {
    "ClickIn",
    2,
    4,
    Paramtypes_ClickIn,
    "X As Single,Y As Single"
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
    0,					// MODEL flags
    (PCTLPROC)CircleCtlProc,		// Control procedure
    CS_VREDRAW | CS_HREDRAW,		// Class style
    0L, 				// Default Windows style
    sizeof(CIRC),			// Size of CIRC structure
    IDBMP_CIRCLE,			// Palette bitmap ID
    "Circle",				// Default control name
    "CIRC2",				// Visual Basic class name
    NULL,				// Parent class name
    Circle_Properties,			// Property information table
    Circle_Events,			// Event information table
    IPROP_CIRCLE_SHAPE, 		// Default property
    IEVENT_CIRCLE_CLICKIN,		// Default event
    IPROP_CIRCLE_SHAPE			// Property representing value of ctl
    };

#endif	// RC_INVOKED

//---------------------------------------------------------------------------
