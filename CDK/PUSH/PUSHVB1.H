//---------------------------------------------------------------------------
// PushVb1.h
//---------------------------------------------------------------------------
// VB1.0 support for Push
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Property list
//---------------------------------------------------------------------------
// Define the consecutive indicies for the properties
//---------------------------------------------------------------------------
PPROPINFO proplistPush_Vb1[] =
    {
    PPROPINFO_STD_NAME,
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
    NULL
    };


//---------------------------------------------------------------------------
// Event list
//---------------------------------------------------------------------------
// Define the consecutive indicies for the events
//---------------------------------------------------------------------------
PEVENTINFO eventlistPush_Vb1[] =
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
MODEL modelPush_Vb1 =
    {
    VB100_VERSION,			// VB version being used
    MODEL_fFocusOk | MODEL_fMnemonic,	// MODEL flags
    (PCTLPROC)PushCtlProc,		// Control procedure
    CS_VREDRAW | CS_HREDRAW,		// Class style
    BS_PUSHBUTTON | BS_OWNERDRAW,	// Default Window style
    sizeof(PUSH),			// cbCtlExtra for PUSH structure
    IDBMP_PUSH, 			// Palette bitmap ID
    "Push",				// Default control name
    "PushButton",			// Visual Basic class name
    "Button",				// Parent class name
    proplistPush_Vb1,			// Properties list
    eventlistPush_Vb1,			// Events list
    IPROP_PUSH_CAPTION, 		// Default property
    EVENT_PUSH_CLICK,			// Default event
    IPROP_PUSH_CAPTION			// Property representing value of ctl
    };

LPMODEL modellistPush_Vb1[] =
    {
    &modelPush_Vb1,
    NULL
    };

MODELINFO modelinfoPush_Vb1 =
    {
    VB100_VERSION,			// VB version being used
    modellistPush_Vb1			// MODEL list
    };

//---------------------------------------------------------------------------
