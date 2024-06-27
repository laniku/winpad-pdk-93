//---------------------------------------------------------------------------
// XListVb1.h
//---------------------------------------------------------------------------
// Compatability file containing model for Vb1.0
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Property list
//---------------------------------------------------------------------------
PPROPINFO XList_Properties_Vb1[] =
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
    NULL
    };


//---------------------------------------------------------------------------
// Event list
//---------------------------------------------------------------------------
PEVENTINFO XList_Events_Vb1[] =
    {
    PEVENTINFO_STD_CLICK,
    NULL
    };


//---------------------------------------------------------------------------
// Model struct
//---------------------------------------------------------------------------
// Define the control model (using the event and property structures).
//---------------------------------------------------------------------------
MODEL modelXList_Vb1 =
    {
    VB_VERSION, 			// VB version being used
    MODEL_fFocusOk | MODEL_fArrows	// MODEL flags
		   | MODEL_fInitMsg,
    (PCTLPROC)XListCtlProc,             // Control procedures
    CS_DBLCLKS | CS_HREDRAW		// Class style
	       | CS_VREDRAW,
    WS_VSCROLL | WS_BORDER		// Window style
	       | LBS_NOTIFY
	       | LBS_OWNERDRAWVARIABLE
	       | LBS_HASSTRINGS,
    sizeof(XLIST),			// Size of XLIST structure
    IDBMP_XLISTUP,			// Palette bitmap ID
    "XList",				// Default control name
    "XListBox", 			// Visual Basic class name
    "LISTBOX",				// Parent class name
    XList_Properties_Vb1,		// Property information table
    XList_Events_Vb1			// Event information table
    };

LPMODEL modelListXList_Vb1[] =
    {
    &modelXList_Vb1,
    NULL
    };

MODELINFO modelInfoXList_Vb1 =
    {
    VB100_VERSION,		      // VB version being used
    modelListXList_Vb1		      // MODEL list
    };

//---------------------------------------------------------------------------
