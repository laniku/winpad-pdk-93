//---------------------------------------------------------------------------
//		Copyright (C) 1991-92, Microsoft Corporation
//
// You have a royalty-free right to use, modify, reproduce and distribute
// the Sample Custom Control Files (and/or any modified version) in any way
// you find useful, provided that you agree that Microsoft has no warranty,
// obligation or liability for any Custom Control File.
//---------------------------------------------------------------------------
// Cntr.h
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Resource Information
//---------------------------------------------------------------------------
// Toolbox bitmap resource IDs numbers.
//---------------------------------------------------------------------------
#define IDBMP_CNTR		8000
#define IDBMP_CNTRDOWN		8001
#define IDBMP_CNTRMONO		8003
#define IDBMP_CNTREGA		8006


//---------------------------------------------------------------------------
// Change these for each new VBX file
//---------------------------------------------------------------------------
#define VBX_COMPANYNAME 	   "Microsoft Corporation\0"
#define VBX_FILEDESCRIPTION	   "Visual Basic Counter Custom Control Example\0"
#define VBX_INTERNALNAME	   "CNTR\0"
#define VBX_LEGALCOPYRIGHT	   "Copyright \251 Microsoft Corp. 1991-92\0"
#define VBX_LEGALTRADEMARKS	   "Microsoft\256 is a registered trademark of Microsoft Corporation. Visual Basic\231 is a trademark of Microsoft Corporation. Windows\231 is a trademark of Microsoft Corporation.\0"
#define VBX_ORIGINALFILENAME	   "CNTR.VBX\0"
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
// Cntr control data and structs
//---------------------------------------------------------------------------
_segment segCntr;

#define BP _based(segCntr) *	// based pointer

#define BH BP BP		// based handle

typedef VOID BH BHVOID; 	// void handle

typedef CHAR BH BHSTR;		// handle to a string

typedef struct tagCNTR
    {
    HFONT   hFont;
    float   Value;
    CHAR    szVal[13];
    SHORT   DigitsLeft;
    SHORT   DigitsRight;
    LONG    colorBackRight;
    LONG    colorForeRight;
    SHORT   DigitWidth;
    SHORT   StartRoll;
    SHORT   RollVal;
    SHORT   Gap;
    HBITMAP hbmp[2];
    } CNTR;

typedef CNTR BP BPCNTR;

#define BpcntrDEREF(hctl)     ((BPCNTR)(VOID *)(SHORT)(LONG)VBDerefControl(hctl))


//---------------------------------------------------------------------------
// Control Procedure
//---------------------------------------------------------------------------
LONG FAR PASCAL _export CntrCtlProc(HCTL, HWND, USHORT, USHORT, LONG);


//---------------------------------------------------------------------------
// Property info
//---------------------------------------------------------------------------
PROPINFO propinfoCntrBackColorRight =
    {
    "BackColorRight",
    DT_COLOR | PF_fGetData | PF_fSetData | PF_fSetMsg | PF_fSaveData,
    OFFSETIN(CNTR,colorBackRight), 0
    };

PROPINFO propinfoCntrDigitsLeft =
    {
    "DigitsLeft",
    DT_SHORT | PF_fGetData | PF_fSetMsg | PF_fSaveData,
    OFFSETIN(CNTR,DigitsLeft), 0
    };

PROPINFO propinfoCntrDigitsRight =
    {
    "DigitsRight",
    DT_SHORT | PF_fGetData | PF_fSetMsg | PF_fSaveData,
    OFFSETIN(CNTR,DigitsRight), 0
    };

PROPINFO propinfoCntrForeColorRight =
    {
    "ForeColorRight",
    DT_COLOR | PF_fGetData | PF_fSetData | PF_fSetMsg | PF_fSaveData,
    OFFSETIN(CNTR,colorForeRight), 0
    };

PROPINFO propinfoCntrValue =
    {
    "Value",
    DT_REAL | PF_fGetData | PF_fSetMsg | PF_fSaveData,
    OFFSETIN(CNTR,Value), 0
    };


//---------------------------------------------------------------------------
// Property list
//---------------------------------------------------------------------------
// Define the consecutive indicies for the properties
//---------------------------------------------------------------------------
#define IPROP_CNTR_CTLNAME	  0x0000
#define IPROP_CNTR_INDEX	  0x0001
#define IPROP_CNTR_BACKCOLOR	  0x0002
#define IPROP_CNTR_FORECOLOR	  0x0003
#define IPROP_CNTR_LEFT 	  0x0004
#define IPROP_CNTR_TOP		  0x0005
#define IPROP_CNTR_WIDTH	  0x0006
#define IPROP_CNTR_HEIGHT	  0x0007
#define IPROP_CNTR_VISIBLE	  0x0008
#define IPROP_CNTR_FONTNAME	  0x0009
#define IPROP_CNTR_FONTSIZE	  0x000A
#define IPROP_CNTR_FONTBOLD	  0x000B
#define IPROP_CNTR_FONTITALIC	  0x000C
#define IPROP_CNTR_FONTSTRIKE	  0x000D
#define IPROP_CNTR_FONTUNDER	  0x000E
#define IPROP_CNTR_PARENT	  0x000F
#define IPROP_CNTR_DRAGMODE	  0x0010
#define IPROP_CNTR_DRAGICON	  0x0011
#define IPROP_CNTR_TAG		  0x0012
#define IPROP_CNTR_VALUE	  0x0013
#define IPROP_CNTR_DIGITSLEFT	  0x0014
#define IPROP_CNTR_DIGITSRIGHT	  0x0015
#define IPROP_CNTR_BACKCOLORRIGHT 0x0016
#define IPROP_CNTR_FORECOLORRIGHT 0x0017
#define IPROP_CNTR_HWND 	  0x0018

PPROPINFO proplistCntr[] =
    {
    PPROPINFO_STD_CTLNAME,
    PPROPINFO_STD_INDEX,
    PPROPINFO_STD_BACKCOLOR,
    PPROPINFO_STD_FORECOLOR,
    PPROPINFO_STD_LEFT,
    PPROPINFO_STD_TOP,
    PPROPINFO_STD_WIDTH,
    PPROPINFO_STD_HEIGHT,
    PPROPINFO_STD_VISIBLE,
    PPROPINFO_STD_FONTNAME,
    PPROPINFO_STD_FONTSIZE,
    PPROPINFO_STD_FONTBOLD,
    PPROPINFO_STD_FONTITALIC,
    PPROPINFO_STD_FONTSTRIKE,
    PPROPINFO_STD_FONTUNDER,
    PPROPINFO_STD_PARENT,
    PPROPINFO_STD_DRAGMODE,
    PPROPINFO_STD_DRAGICON,
    PPROPINFO_STD_TAG,
    &propinfoCntrValue,
    &propinfoCntrDigitsLeft,
    &propinfoCntrDigitsRight,
    &propinfoCntrBackColorRight,
    &propinfoCntrForeColorRight,
    PPROPINFO_STD_HWND,
    NULL
    };


//---------------------------------------------------------------------------
// Event list
//---------------------------------------------------------------------------
// Define the consecutive indicies for the events
//---------------------------------------------------------------------------
#define IEVENT_CNTR_DRAGDROP	0
#define IEVENT_CNTR_DRAGOVER	1

PEVENTINFO eventlistCntr[] =
    {
    PEVENTINFO_STD_DRAGDROP,
    PEVENTINFO_STD_DRAGOVER,
    NULL
    };


//---------------------------------------------------------------------------
// Model struct
//---------------------------------------------------------------------------
// Define the control model (using the event and property structures).
//---------------------------------------------------------------------------
MODEL modelCntr =
    {
    VB_VERSION, 			// VB version being used
    0,					// MODEL flags
    (PCTLPROC)CntrCtlProc,		// Control procedure
    CS_VREDRAW | CS_HREDRAW,		// Class style
    WS_BORDER,				// Default Window style
    sizeof(CNTR),			// Size of CNTR structure
    IDBMP_CNTR, 			// Palette bitmap ID
    "Counter",				// Default control name
    "Counter",				// Visual Basic class name
    NULL,				// Parent class name
    proplistCntr,			// Properties list
    eventlistCntr,			// Events list
    IPROP_CNTR_VALUE,			// Default property
    IEVENT_CNTR_DRAGDROP,		// Default event
    IPROP_CNTR_VALUE			// Property representing value of ctl
    };

LPMODEL modellistCntr[] =
    {
    &modelCntr,
    NULL
    };

MODELINFO modelinfoCntr =
    {
    VB_VERSION, 			// VB version being used
    modellistCntr			// MODEL list
    };

#endif  // RC_INVOKED

//---------------------------------------------------------------------------
