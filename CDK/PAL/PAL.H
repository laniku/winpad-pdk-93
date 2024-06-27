//---------------------------------------------------------------------------
//		Copyright (C) 1992 Microsoft Corporation
//
// You have a royalty-free right to use, modify, reproduce and distribute
// the Sample Custom Control Files (and/or any modified version) in any way
// you find useful, provided that you agree that Microsoft has no warranty,
// obligation or liability for any Custom Control File.
//---------------------------------------------------------------------------
// Pal.h
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Resource Information
//---------------------------------------------------------------------------
// Toolbox bitmap resource IDs numbers must be consecutive from N to N+5
//---------------------------------------------------------------------------
#define IDBMP_PAL	    8000
#define IDBMP_PALDOWN	    8001
#define IDBMP_PALMONO	    8003
#define IDBMP_PALEGA	    8006


//---------------------------------------------------------------------------
// Change these for each new VBX file
//---------------------------------------------------------------------------
#define VBX_COMPANYNAME 	   "Microsoft Corporation\0"
#define VBX_FILEDESCRIPTION	   "Visual Basic Palette Custom Control Example\0"
#define VBX_INTERNALNAME	   "PAL\0"
#define VBX_LEGALCOPYRIGHT	   "Copyright \251 Microsoft Corp. 1991-92\0"
#define VBX_LEGALTRADEMARKS	   "Microsoft\256 is a registered trademark of Microsoft Corporation. Visual Basic\231 is a trademark of Microsoft Corporation. Windows\231 is a trademark of Microsoft Corporation.\0"
#define VBX_ORIGINALFILENAME	   "PAL.VBX\0"
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
// PAL control data and structs
//---------------------------------------------------------------------------
typedef struct tagPAL
    {
    HPALETTE hpal;	  // The palette currently displayed
    } PAL;

typedef PAL FAR *PPAL;

#define PALDEREF(hctl) ((PPAL)VBDerefControl(hctl))


//---------------------------------------------------------------------------
// Control Procedure
//---------------------------------------------------------------------------
LONG _export FAR PASCAL PalCtlProc(HCTL, HWND, USHORT, USHORT, LONG);


//---------------------------------------------------------------------------
// Property info
//---------------------------------------------------------------------------
PROPINFO propinfoHPal =
    {
    "hPal",
    DT_SHORT | PF_fGetData | PF_fNoRuntimeW | PF_fNoShow,
    OFFSETIN(PAL,hpal),0
    };

PROPINFO propinfoPicture =
    {
    "Picture",
    DT_PICTURE | PF_fGetMsg | PF_fSetMsg
    };

PROPINFO propinfoLength =
    {
    "Length",
    DT_SHORT | PF_fGetMsg | PF_fSetMsg | PF_fNoShow
    };

PROPINFO propinfoEntry =
    {
    "Entry",
    DT_LONG | PF_fPropArray | PF_fGetMsg | PF_fSetMsg | PF_fNoShow
    };


//---------------------------------------------------------------------------
// Property list
//---------------------------------------------------------------------------
// Define the consecutive indicies for the properties
//---------------------------------------------------------------------------
#define IPROP_PAL_NAME		0x0000
#define IPROP_PAL_INDEX 	0x0001
#define IPROP_PAL_BACKCOLOR	0x0002
#define IPROP_PAL_LEFT		0x0003
#define IPROP_PAL_TOP		0x0004
#define IPROP_PAL_WIDTH 	0x0005
#define IPROP_PAL_HEIGHT	0x0006
#define IPROP_PAL_PARENT	0x0007
#define IPROP_PAL_TAG		0x0008
#define IPROP_PAL_BORDERSTYLEON 0x0009
#define IPROP_PAL_ALIGN 	0x000A
#define IPROP_PAL_HPAL		0x000B
#define IPROP_PAL_PICTURE	0x000C
#define IPROP_PAL_LENGTH	0x000D
#define IPROP_PAL_ENTRY 	0x000E
#define IPROP_PAL_HWND		0x000F

PPROPINFO proplistPal[] =
    {
    PPROPINFO_STD_NAME,
    PPROPINFO_STD_INDEX,
    PPROPINFO_STD_BACKCOLOR,
    PPROPINFO_STD_LEFT,
    PPROPINFO_STD_TOP,
    PPROPINFO_STD_WIDTH,
    PPROPINFO_STD_HEIGHT,
    PPROPINFO_STD_PARENT,
    PPROPINFO_STD_TAG,
    PPROPINFO_STD_BORDERSTYLEON,
    PPROPINFO_STD_ALIGN,
    &propinfoHPal,
    &propinfoPicture,
    &propinfoLength,
    &propinfoEntry,
    PPROPINFO_STD_HWND,
    NULL
    };


//---------------------------------------------------------------------------
// Event list (none)
//---------------------------------------------------------------------------
PEVENTINFO eventlistPal[] =
    {
    NULL
    };


//---------------------------------------------------------------------------
// Model struct
//---------------------------------------------------------------------------
// Define the control model (using the event and property structures).
//---------------------------------------------------------------------------
MODEL modelPal =
    {
    VB_VERSION, 			// VB version being used
    0,					// MODEL flags
    (PCTLPROC)PalCtlProc,		// Control procedure
    CS_VREDRAW | CS_HREDRAW,		// Class style
    WS_BORDER,				// Default Window style
    sizeof(PAL),			// cbCtlExtra for PAL structure
    IDBMP_PAL,				// Palette bitmap ID
    "Pal",				// Default control name
    "Palette",				// Visual Basic class name
    NULL,				// Parent class name
    proplistPal,			// Properties list
    eventlistPal,			// Events list
    IPROP_PAL_PICTURE,			// Default property
    0,					// Default event
    IPROP_PAL_PICTURE			// Property representing value of ctl
    };

LPMODEL modellistPal[] =
    {
    &modelPal,
    NULL
    };

MODELINFO modelinfoPal =
    {
    VB_VERSION, 			// VB version being used
    modellistPal			// MODEL list
    };

#endif  // RC_INVOKED

//---------------------------------------------------------------------------
