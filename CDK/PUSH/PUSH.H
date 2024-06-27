//---------------------------------------------------------------------------
//		Copyright (C) 1991-92, Microsoft Corporation
//
// You have a royalty-free right to use, modify, reproduce and distribute
// the Sample Custom Control Files (and/or any modified version) in any way
// you find useful, provided that you agree that Microsoft has no warranty,
// obligation or liability for any Custom Control File.
//---------------------------------------------------------------------------
// Push.h
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Resource Information
//---------------------------------------------------------------------------
// Toolbox bitmap resource IDs.
//---------------------------------------------------------------------------
#define IDBMP_PUSH		8000
#define IDBMP_PUSHDOWN		8001
#define IDBMP_PUSHMONO		8003
#define IDBMP_PUSHEGA		8006


//---------------------------------------------------------------------------
// Change these for each new VBX file
//---------------------------------------------------------------------------
#define VBX_COMPANYNAME 	   "Microsoft Corporation\0"
#define VBX_FILEDESCRIPTION	   "Visual Basic Picture Push Custom Control Example\0"
#define VBX_INTERNALNAME	   "PUSH\0"
#define VBX_LEGALCOPYRIGHT	   "Copyright \251 Microsoft Corp. 1991-92\0"
#define VBX_LEGALTRADEMARKS	   "Microsoft\256 is a registered trademark of Microsoft Corporation. Visual Basic\231 is a trademark of Microsoft Corporation. Windows\231 is a trademark of Microsoft Corporation.\0"
#define VBX_ORIGINALFILENAME	   "PUSH.VBX\0"
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
#define OFFSETIN(struc, field)	  ((USHORT)&(((struc *)0)->field))


//---------------------------------------------------------------------------
// PUSH control data and structs
//---------------------------------------------------------------------------
typedef struct tagPUSH
    {
    HPIC hpicUp;
    HPIC hpicDown;
    } PUSH;

typedef PUSH FAR * LPPUSH;

#define LppushDEREF(hctl)     ((LPPUSH)VBDerefControl(hctl))


//---------------------------------------------------------------------------
// Control Procedure
//---------------------------------------------------------------------------
LONG FAR PASCAL _export PushCtlProc(HCTL, HWND, USHORT, USHORT, LONG);


//---------------------------------------------------------------------------
// Property info
//---------------------------------------------------------------------------
PROPINFO propinfoPictureUp =
    {
    "PictureUp",
    DT_PICTURE | PF_fGetData | PF_fSetCheck | PF_fSetData | PF_fSaveData,
    OFFSETIN(PUSH,hpicUp), 0
    };

PROPINFO propinfoPictureDown =
    {
    "PictureDown",
    DT_PICTURE | PF_fGetData | PF_fSetCheck | PF_fSetData | PF_fSaveData,
    OFFSETIN(PUSH,hpicDown), 0
    };


//---------------------------------------------------------------------------
// Property list
//---------------------------------------------------------------------------
// Define the consecutive indicies for the properties
//---------------------------------------------------------------------------
#define IPROP_PUSH_NAME 	  0x0000
#define IPROP_PUSH_INDEX	  0x0001
#define IPROP_PUSH_PARENT	  0x0002
#define IPROP_PUSH_BACKCOLOR	  0x0003
#define IPROP_PUSH_LEFT 	  0x0004
#define IPROP_PUSH_TOP		  0x0005
#define IPROP_PUSH_WIDTH	  0x0006
#define IPROP_PUSH_HEIGHT	  0x0007
#define IPROP_PUSH_ENABLED	  0x0008
#define IPROP_PUSH_VISIBLE	  0x0009
#define IPROP_PUSH_MOUSEPOINTER   0x000A
#define IPROP_PUSH_CAPTION	  0x000B
#define IPROP_PUSH_FONTNAME	  0x000C
#define IPROP_PUSH_FONTSIZE	  0x000D
#define IPROP_PUSH_FONTBOLD	  0x000E
#define IPROP_PUSH_FONTITALIC	  0x000F
#define IPROP_PUSH_FONTSTRIKE	  0x0010
#define IPROP_PUSH_FONTUNDER	  0x0011
#define IPROP_PUSH_DRAG 	  0x0012
#define IPROP_PUSH_DRAGICON	  0x0013
#define IPROP_PUSH_TABINDEX	  0x0014
#define IPROP_PUSH_TABSTOP	  0x0015
#define IPROP_PUSH_TAG		  0x0016
#define IPROP_PUSH_PICTUREUP	  0x0017
#define IPROP_PUSH_PICTUREDOWN	  0x0018
#define IPROP_PUSH_HWND 	  0x0019
#define IPROP_PUSH_HELPCONTEXTID  0x001A

PPROPINFO proplistPush[] =
    {
    PPROPINFO_STD_CTLNAME,
    PPROPINFO_STD_INDEX,
    PPROPINFO_STD_PARENT,
    PPROPINFO_STD_BACKCOLOR,
    PPROPINFO_STD_LEFT,
    PPROPINFO_STD_TOP,
    PPROPINFO_STD_WIDTH,
    PPROPINFO_STD_HEIGHT,
    PPROPINFO_STD_ENABLED,
    PPROPINFO_STD_VISIBLE,
    PPROPINFO_STD_MOUSEPOINTER,
    PPROPINFO_STD_CAPTION,
    PPROPINFO_STD_FONTNAME,
    PPROPINFO_STD_FONTSIZE,
    PPROPINFO_STD_FONTBOLD,
    PPROPINFO_STD_FONTITALIC,
    PPROPINFO_STD_FONTSTRIKE,
    PPROPINFO_STD_FONTUNDER,
    PPROPINFO_STD_DRAGMODE,
    PPROPINFO_STD_DRAGICON,
    PPROPINFO_STD_TABINDEX,
    PPROPINFO_STD_TABSTOP,
    PPROPINFO_STD_TAG,
    &propinfoPictureUp,
    &propinfoPictureDown,
    PPROPINFO_STD_HWND,
    PPROPINFO_STD_HELPCONTEXTID,
    NULL
    };


//---------------------------------------------------------------------------
// Event procedure parameter prototypes
//---------------------------------------------------------------------------
WORD Parms_I2[]   = {ET_I2};			// 1 x I2 parm
WORD Parms_2xI2[] = {ET_I2, ET_I2};		// 2 x I2 parm
WORD Parms_SD[]   = {ET_SD};			// 1 x SD parm

EVENTINFO Event_Click =
    {
    "Click",
    1,
    2,
    Parms_SD,
    "ButtonCaption as String"
    };


//---------------------------------------------------------------------------
// Event list
//---------------------------------------------------------------------------
// Define the consecutive indicies for the events
//---------------------------------------------------------------------------
#define EVENT_PUSH_CLICK	0
#define EVENT_PUSH_DRAGDROP	1
#define EVENT_PUSH_DRAGOVER	2
#define EVENT_PUSH_GOTFOCUS	3
#define EVENT_PUSH_KEYDOWN	4
#define EVENT_PUSH_KEYPRESS	5
#define EVENT_PUSH_KEYUP	6
#define EVENT_PUSH_LOSTFOCUS	7

PEVENTINFO eventlistPush[] =
    {
    &Event_Click,
    PEVENTINFO_STD_DRAGDROP,
    PEVENTINFO_STD_DRAGOVER,
    PEVENTINFO_STD_GOTFOCUS,
    PEVENTINFO_STD_KEYDOWN,
    PEVENTINFO_STD_KEYPRESS,
    PEVENTINFO_STD_KEYUP,
    PEVENTINFO_STD_LOSTFOCUS,
    NULL
    };


//---------------------------------------------------------------------------
// Model struct
//---------------------------------------------------------------------------
// Define the control model (using the event and property structures).
//---------------------------------------------------------------------------
MODEL modelPush =
    {
    VB_VERSION, 			// VB version being used
    MODEL_fFocusOk | MODEL_fMnemonic,	// MODEL flags
    (PCTLPROC)PushCtlProc,		// Control procedure
    CS_VREDRAW | CS_HREDRAW,		// Class style
    BS_PUSHBUTTON | BS_OWNERDRAW,	// Default Window style
    sizeof(PUSH),			// cbCtlExtra for PUSH structure
    IDBMP_PUSH, 			// Palette bitmap ID
    "Push",				// Default control name
    "PushButton",			// Visual Basic class name
    "Button",				// Parent class name
    proplistPush,			// Properties list
    eventlistPush,			// Events list
    IPROP_PUSH_CAPTION, 		// Default property
    EVENT_PUSH_CLICK,			// Default event
    IPROP_PUSH_CAPTION			// Property representing value of ctl
    };

LPMODEL modellistPush[] =
    {
    &modelPush,
    NULL
    };

MODELINFO modelinfoPush =
    {
    VB_VERSION, 			// VB version being used
    modellistPush			// MODEL list
    };

#endif // RC_INVOKED

//---------------------------------------------------------------------------
