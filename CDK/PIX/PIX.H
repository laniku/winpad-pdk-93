//---------------------------------------------------------------------------
//		Copyright (C) 1991-92, Microsoft Corporation
//
// You have a royalty-free right to use, modify, reproduce and distribute
// the Sample Custom Control Files (and/or any modified version) in any way
// you find useful, provided that you agree that Microsoft has no warranty,
// obligation or liability for any Custom Control File.
//---------------------------------------------------------------------------
// Pix.h
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Resource Information
//---------------------------------------------------------------------------
// Toolbox bitmap resource IDs numbers.
//---------------------------------------------------------------------------
#define IDBMP_PIX	       8000
#define IDBMP_PIXDOWN	       8001
#define IDBMP_PIXMONO	       8003
#define IDBMP_PIXEGA	       8006


//---------------------------------------------------------------------------
// Change these for each new VBX file
//---------------------------------------------------------------------------
#define VBX_COMPANYNAME 	   "Microsoft Corporation\0"
#define VBX_FILEDESCRIPTION	   "Visual Basic Pix Custom Control Example\0"
#define VBX_INTERNALNAME	   "PIX\0"
#define VBX_LEGALCOPYRIGHT	   "Copyright \251 Microsoft Corp. 1991-92\0"
#define VBX_LEGALTRADEMARKS	   "Microsoft\256 is a registered trademark of Microsoft Corporation. Visual Basic\231 is a trademark of Microsoft Corporation. Windows\231 is a trademark of Microsoft Corporation.\0"
#define VBX_ORIGINALFILENAME	   "PIX.VBX\0"
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
// Pix control data and structs
//---------------------------------------------------------------------------
#define ARRMAX          10

typedef struct tagPIX
    {
    HSZ   List[ARRMAX];
    HPIC  hpicPict;
    HLSTR hlstrMyTag;
    HLSTR hlstrMyTagMsg;
    } PIX;

typedef PIX FAR * PPIX;


//---------------------------------------------------------------------------
// Control Procedure
//---------------------------------------------------------------------------
LONG FAR PASCAL _export PixCtlProc(HCTL, HWND, USHORT, USHORT, LONG);


//---------------------------------------------------------------------------
// Property info
//---------------------------------------------------------------------------
PROPINFO Property_Arr =
    {
    "List",
    DT_HSZ | PF_fPropArray| PF_fGetMsg | PF_fSetMsg  | PF_fNoShow,
    OFFSETIN(PIX, List)
    };

PROPINFO Property_Pict =
    {
    "Picture",
    DT_PICTURE | PF_fGetData | PF_fSetCheck | PF_fSetData | PF_fSaveData | PF_fSetMsg,
    OFFSETIN(PIX, hpicPict)
    };

PROPINFO Property_MyTag =
    {
    "MyTag",
    //-----------------------------------------------------------------
    // **** You must never use PF_fGetData alone when dealing with ****
    // **** DT_HLSTR properties!  See VBM_GETPROPERTY, case	   ****
    // **** IPROP_PIX_MYTAG for more information.		   ****
    //-----------------------------------------------------------------
    DT_HLSTR | PF_fGetData | PF_fGetMsg | PF_fSetData | PF_fSaveData | PF_fDefVal,
    OFFSETIN(PIX, hlstrMyTag),
    NULL
    };

PROPINFO Property_MyTagMsg =
    {
    "MyTagMsg",
    DT_HLSTR | PF_fGetMsg | PF_fSetMsg | PF_fSaveData | PF_fDefVal,
    OFFSETIN(PIX, hlstrMyTagMsg),
    NULL
    };


//---------------------------------------------------------------------------
// Property list
//---------------------------------------------------------------------------
// Define the consecutive indicies for the properties
//---------------------------------------------------------------------------
#define IPROP_PIX_CTLNAME              0
#define IPROP_PIX_INDEX                1
#define IPROP_PIX_BACKCOLOR            2
#define IPROP_PIX_LEFT                 3
#define IPROP_PIX_TOP                  4
#define IPROP_PIX_WIDTH                5
#define IPROP_PIX_HEIGHT               6
#define IPROP_PIX_VISIBLE              7
#define IPROP_PIX_PARENT               8
#define IPROP_PIX_DRAGMODE             9
#define IPROP_PIX_DRAGICON            10
#define IPROP_PIX_TAG                 11
#define IPROP_PIX_LIST                12
#define IPROP_PIX_PICT                13
#define IPROP_PIX_MYTAG 	      14
#define IPROP_PIX_LINKMODE            15
#define IPROP_PIX_LINKTOPIC           16
#define IPROP_PIX_LINKITEM            17
#define IPROP_PIX_LINKTIEMOUT         18
#define IPROP_PIX_MYTAGMSG	      19

PPROPINFO Pix_Properties[] =
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
    &Property_Arr,
    &Property_Pict,
    &Property_MyTag,
    PPROPINFO_STD_LINKTOPIC,
    PPROPINFO_STD_LINKITEM,
    PPROPINFO_STD_LINKTIMEOUT,
    PPROPINFO_STD_LINKMODE,     // Linkmode must be the last link property specified!
    &Property_MyTagMsg,
    NULL
    };


//---------------------------------------------------------------------------
// Event list
//---------------------------------------------------------------------------
// Define the consecutive indicies for the events
//---------------------------------------------------------------------------
#define IEVENT_PIX_CLICK               0
#define IEVENT_PIX_DRAGDROP            1
#define IEVENT_PIX_DRAGOVER            2
#define IEVENT_PIX_LINKERROR           3
#define IEVENT_PIX_LINKCLOSE           4
#define IEVENT_PIX_LINKOPEN            5
#define IEVENT_PIX_LINKCHANGE          6

PEVENTINFO Pix_Events[] =
    {
    PEVENTINFO_STD_CLICK,
    PEVENTINFO_STD_DRAGDROP,
    PEVENTINFO_STD_DRAGOVER,
    PEVENTINFO_STD_LINKERROR,
    PEVENTINFO_STD_LINKCLOSE,
    PEVENTINFO_STD_LINKOPEN,
    PEVENTINFO_STD_LINKCHANGE,
    NULL
    };


//---------------------------------------------------------------------------
// Model struct
//---------------------------------------------------------------------------
// Define the control model (using the event and property structures).
//---------------------------------------------------------------------------
MODEL modelPix =
    {
    VB_VERSION, 			// VB version being used
    MODEL_fGraphical |			// MODEL flags
      MODEL_fLoadMsg,			// Needed for DDE!
    (PCTLPROC)PixCtlProc,		// Control procedures
    0,					// Class style
    0,					// Default Windows style
    sizeof(PIX),			// Size of PIX structure
    IDBMP_PIX,				// Palette bitmap ID
    "Pix",				// Default control name
    "Pix",				// Visual Basic class name
    NULL,				// Parent class name
    Pix_Properties,			// Property information table
    Pix_Events, 			// Event information table
    IPROP_PIX_PICT,			// Default property
    IEVENT_PIX_CLICK,			// Default event
    IPROP_PIX_PICT			// Property representing value of ctl
    };

LPMODEL modellistPix[] =
    {
    &modelPix,
    NULL
    };

MODELINFO modelinfoPix =
    {
    VB100_VERSION,			// VB version being used
    modellistPix			// MODEL list
    };

#endif  // RC_INVOKED

//---------------------------------------------------------------------------
