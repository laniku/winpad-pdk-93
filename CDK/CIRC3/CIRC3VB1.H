//---------------------------------------------------------------------------
//		Copyright (C) 1991-92, Microsoft Corporation
//
// You have a royalty-free right to use, modify, reproduce and distribute
// the Sample Custom Control Files (and/or any modified version) in any way
// you find useful, provided that you agree that Microsoft has no warranty,
// obligation or liability for any Custom Control File.
//---------------------------------------------------------------------------
// Circ3Vb1.h
//---------------------------------------------------------------------------
// VB1.0 support for Circ3
//---------------------------------------------------------------------------

#ifndef RC_INVOKED
//---------------------------------------------------------------------------
// Property list
//---------------------------------------------------------------------------
PPROPINFO Circle_Properties_Vb1[] =
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
    // Note STD_HELPCONTEXTID is not present because it's VB2.0 functionality
    NULL
    };


//---------------------------------------------------------------------------
// Event list
//---------------------------------------------------------------------------
PEVENTINFO Circle_Events_Vb1[] =
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
MODEL modelCircle_Vb1 =
    {
    VB100_VERSION,			// VB1.0 model information
    0,					// MODEL flags
    (PCTLPROC)CircleCtlProc,		// Control procedure
    CS_VREDRAW | CS_HREDRAW,		// Class style
    0L, 				// Default Windows style
    sizeof(CIRC),			// Size of CIRC structure
    IDBMP_CIRCLE,			// Palette bitmap ID
    "Circle",				// Default control name
    "CIRC3",				// Visual Basic class name
    NULL,				// Parent class name
    Circle_Properties_Vb1,		// Property information table
    Circle_Events_Vb1,			// Event information table
    IPROP_CIRCLE_CIRCLESHAPE,		// Default property
    IEVENT_CIRCLE_CLICKIN		// Default event
    };

LPMODEL modellistCircle_Vb1[] =
    {
    &modelCircle_Vb1,
    NULL
    };

MODELINFO modelinfoCircle_Vb1 =
    {
    VB100_VERSION,			// VB version being used
    modellistCircle_Vb1 		// MODEL list
    };

#endif	// RC_INVOKED

//---------------------------------------------------------------------------
