//---------------------------------------------------------------------------
//		Copyright (C) 1991-92, Microsoft Corporation
//
// You have a royalty-free right to use, modify, reproduce and distribute
// the Sample Custom Control Files (and/or any modified version) in any way
// you find useful, provided that you agree that Microsoft has no warranty,
// obligation or liability for any Custom Control File.
//---------------------------------------------------------------------------
// Circ1.h
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
// Control Procedure
//---------------------------------------------------------------------------
LONG FAR PASCAL _export CircleCtlProc(HCTL, HWND, USHORT, USHORT, LONG);


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
#define IPROP_CIRCLE_HWND		 12

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
    PPROPINFO_STD_HWND,
    NULL
    };


//---------------------------------------------------------------------------
// Event list
//---------------------------------------------------------------------------
// Define the consecutive indicies for the events
//---------------------------------------------------------------------------
#define IEVENT_CIRCLE_CLICK		  0
#define IEVENT_CIRCLE_DRAGDROP		  1
#define IEVENT_CIRCLE_DRAGOVER		  2

PEVENTINFO Circle_Events[] =
    {
    PEVENTINFO_STD_CLICK,
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
    WS_BORDER,				// Default Windows style
    0,					// Size of CIRCLE structure
    IDBMP_CIRCLE,			// Palette bitmap ID
    "Circle",				// Default control name
    "CIRC1",				// Visual Basic class name
    NULL,				// Parent class name
    Circle_Properties,			// Property information table
    Circle_Events,			// Event information table
    IPROP_CIRCLE_BACKCOLOR,		// Default property
    IEVENT_CIRCLE_CLICK,		// Default event
    -1					// Property representing value of ctl
    };

#endif	// RC_INVOKED

//---------------------------------------------------------------------------
