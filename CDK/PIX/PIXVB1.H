//---------------------------------------------------------------------------
// PixVb1.h
//---------------------------------------------------------------------------
// Compatability file containing model for Vb1.0
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Property list
//---------------------------------------------------------------------------
PPROPINFO Pix_Properties_Vb1[] =
    {
    PPROPINFO_STD_NAME,
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
    NULL
    };


//---------------------------------------------------------------------------
// Event list
//---------------------------------------------------------------------------
PEVENTINFO Pix_Events_Vb1[] =
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
MODEL modelPix_Vb1 =
    {
    VB100_VERSION,			// VB version being used
    0,					// MODEL flags
    (PCTLPROC)PixCtlProc,		// Control procedures
    CS_VREDRAW | CS_HREDRAW,		// Class style
    0,					// Default Windows style
    sizeof(PIX),			// Size of PIX structure
    IDBMP_PIX,				// Palette bitmap ID
    "Pix",				// Default control name
    "Pix",				// Visual Basic class name
    NULL,				// Parent class name
    Pix_Properties_Vb1, 		// Property information table
    Pix_Events_Vb1,			// Event information table
    IPROP_PIX_PICT,			// Default property
    IEVENT_PIX_CLICK			// Default event
    };

LPMODEL modellistPix_Vb1[] =
    {
    &modelPix_Vb1,
    NULL
    };

MODELINFO modelinfoPix_Vb1 =
    {
    VB100_VERSION,			// VB version being used
    modellistPix_Vb1			// MODEL list
    };

//---------------------------------------------------------------------------
