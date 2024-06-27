#ifdef __cplusplus 
extern "C" { 
#endif 
//---------------------------------------------------------------------------
//
//  VBAPI.H -
//	Copyright (c) 1991-1992, Microsoft Corp.  All Rights Reserved.
//
//	Include file for the Visual Basic Custom Control and DLL
//	application programming interface.
//
//---------------------------------------------------------------------------

#define VB100_VERSION	0x0100
#define VB200_VERSION	0x0200
#define VB_VERSION	VB200_VERSION

#define VBAPI FAR PASCAL

//---------------------------------------------------------------------------
// General types and modifiers
//---------------------------------------------------------------------------

#define FP    FAR  *
typedef   signed short	SHORT;		// ad lib
typedef unsigned short	USHORT; 	// ad lib
typedef unsigned int	FSHORT; 	// fs
typedef   signed char	CHAR;		// ch
typedef unsigned char	ENUM;		// enum
typedef unsigned long	ULONG;		// ul
typedef unsigned long	FLONG;		// fl
typedef SHORT	FP LPSHORT;
typedef USHORT          IPROP;          // iprop
typedef HANDLE		HFORMFILE;	// hformfile
typedef USHORT		ERR;		// err
typedef WORD		HPIC;		// hpic
typedef LPSTR		HSZ;		// hsz
typedef LPVOID		HLSTR;		// hlstr
typedef LPVOID		HAD;		// hAD - handle to Basic array desc.
typedef LPVOID		HCTL;		// hctl
typedef LONG (FAR PASCAL * PFNWP)(HWND hwnd, USHORT msg, WORD wp, LONG lp);		  // pfnwp
typedef LONG (FAR PASCAL * PCTLPROC)(HCTL hctl, HWND hwnd, USHORT msg, USHORT wp, LONG lp); // pctlproc

//---------------------------------------------------------------------------
// language Variant structures
//---------------------------------------------------------------------------

typedef struct
{
    LONG    lo;
    LONG    hi;
} CURRENCY;

typedef union
{
	SHORT	i2;
	LONG	i4;
	float	r4;
	double	r8;
	CURRENCY cy;
	HLSTR	hlstr;
} VALUE;

typedef VALUE far *	LPVAL;

// The size of Variant is needed when a Variant is passed by value
// or in a structure (user-defined type).

typedef struct
{
    char v[16];
} VARIANT;

typedef VARIANT FAR *LPVAR;

// variant type constants. these are the return value of GetVariantType.
// these are also defined in Constant.Txt for return value of VarType()

#define VT_EMPTY    0	// Empty
#define VT_NULL     1	// Null
#define VT_I2	    2	// Integer
#define VT_I4	    3	// Long
#define VT_R4	    4	// Single
#define VT_R8	    5	// Double
#define VT_CURRENCY 6	// Currency
#define VT_DATE     7	// Date
#define VT_STRING   8	// String

//---------------------------------------------------------------------------
// COLOR - a Windows RGB DWORD value.
//---------------------------------------------------------------------------
typedef unsigned long	COLOR;
typedef COLOR FAR *	LPCOLOR;	// lpcolor

#define COLOR_DEFBITON	0x80000000	// bit set -> Win SysColor, not RGB

// Get RGB value from a color.
#define RGBCOLOR(clr) \
  (((clr)&COLOR_DEFBITON)?(GetSysColor((int)((clr)&0xFFFF))):((clr)&0xFFFFFF))


//---------------------------------------------------------------------------
// Property data structure
//---------------------------------------------------------------------------
typedef struct tagDATASTRUCT
{
    LONG   data;	    // Data for Get/Set
    USHORT cindex;	    // Number of indecies
    struct
    {
	USHORT datatype;    // Type of nth index (Currently always DT_SHORT)
	LONG   data;	    // Value of nth index
    } index[1]; 	    // Currently, only 1-dim arrays supported
} DATASTRUCT;

typedef DATASTRUCT FAR	*LPDATASTRUCT;	// pds
typedef DATASTRUCT NEAR *NPDATASTRUCT;	// npds


//---------------------------------------------------------------------------
// VISUAL BASIC variable types
//---------------------------------------------------------------------------
#define ET_I2		1   // 16 bit signed integer scalar or array variable
#define ET_I4		2   // 32 bit signed integer scalar or array variable
#define ET_R4		3
#define ET_R8		4   // 64 bit real scalar or array variable
#define ET_CY		5   // 64 bit currency scalar or array variable
#define ET_HLSTR	6   // string scalar or array variable
#define ET_SD		6   // older, unpreferred equivalent to ET_HLSTR
#define ET_FS		7   // fixed-length string variable

//---------------------------------------------------------------------------
// Control Property definitions and structures.
//---------------------------------------------------------------------------

#define PF_datatype	    0x000000FFL
#define PF_fPropArray	    0x00000100L
#define PF_fSetData	    0x00000200L
#define PF_fSetMsg	    0x00000400L
#define PF_fNoShow	    0x00000800L
#define PF_fNoRuntimeW	    0x00001000L
#define PF_fGetData	    0x00002000L
#define PF_fGetMsg	    0x00004000L
#define PF_fSetCheck	    0x00008000L
#define PF_fSaveData	    0x00010000L
#define PF_fSaveMsg	    0x00020000L
#define PF_fLoadDataOnly    0x20010000L
#define PF_fLoadMsgOnly     0x20020000L
#define PF_fGetHszMsg	    0x00040000L
#define PF_fUpdateOnEdit    0x00080000L
#define PF_fEditable	    0x00100000L
#define PF_fPreHwnd	    0x00200000L
#define PF_fDefVal	    0x00400000L
#define PF_fNoInitDef	    0x00800000L
#define PF_fNoRuntimeR	    0x02000000L
#define PF_fNoMultiSelect   0x04000000L

typedef struct tagPROPINFO
  {
  PSTR	npszName;
  FLONG	fl;			// PF_ flags
  BYTE	offsetData;		// Offset into static structure
  BYTE	infoData;		// 0 or _INFO value for bitfield
  LONG	dataDefault;		// 0 or _INFO value for bitfield
  PSTR	npszEnumList;		// For type == DT_ENUM, this is
				// a near ptr to a string containing
				// all the values to be displayed
				// in the popup enumeration listbox.
				// Each value is an sz, with an
				// empty sz indicated the end of list.
  BYTE	enumMax;		// Maximum legal value for enum.
  } PROPINFO;

typedef PROPINFO  FAR  * LPPROPINFO;
typedef PROPINFO  NEAR * NPPROPINFO;
typedef PROPINFO  NEAR *  PPROPINFO;
typedef PPROPINFO FAR  * LPPROPLIST;
typedef PPROPINFO NEAR * NPPROPLIST;
typedef PPROPINFO NEAR *  PPROPLIST;

// Values for PROP PF_datatype

#define DT_HSZ	      0x01
#define DT_SHORT      0x02
#define DT_LONG       0x03
#define DT_BOOL       0x04
#define DT_COLOR      0x05
#define DT_ENUM       0x06
#define DT_REAL       0x07
#define DT_XPOS       0x08	// Scaled from float to long twips
#define DT_XSIZE      0x09	//   _SIZE scales without origin
#define DT_YPOS       0x0A	//   _POS subtracts origin
#define DT_YSIZE      0x0B	// uses parent's scale properties
#define DT_PICTURE    0x0C
#define DT_HLSTR      0x0D
#if VTOBJS
#define DT_DATETIME   0x0E
#define DT_DOUBLE     0x0F
#define DT_CURRENCY   0x10
#define DT_NULL       0x11
#define DT_HSZMEMO    0x12
#define DT_VTCOLL     0x70		/* VT Object collections	*/
#endif

//---------------------------------------------------------------------------
// Control event definitions and structures.
//---------------------------------------------------------------------------

#define EF_fNoUnload	0x00000001L

typedef struct tagEVENTINFO
  {
  PSTR		npszName;	// event procedure name suffix
  USHORT	cParms; 	// number of parameters
  USHORT	cwParms;	// # words of parameters
  PWORD		npParmTypes;	// list of parameter types
  PSTR		npszParmProf;	// event parameter profile string
  FLONG		fl;		// EF_ flags
  } EVENTINFO;

typedef EVENTINFO   NEAR * PEVENTINFO;
typedef PEVENTINFO  NEAR * PPEVENTINFO;
typedef EVENTINFO   NEAR * NPEVENTINFO;
typedef EVENTINFO   FAR  * LPEVENTINFO;
typedef NPEVENTINFO FAR  * LPEVENTLIST;
typedef NPEVENTINFO NEAR * NPEVENTLIST;

//---------------------------------------------------------------------------
// Standard control event list
//---------------------------------------------------------------------------

#define IEVENT_STD_CLICK	0x0000
#define IEVENT_STD_DBLCLICK	0x0001
#define IEVENT_STD_DRAGDROP	0x0002
#define IEVENT_STD_DRAGOVER	0x0003
#define IEVENT_STD_GOTFOCUS	0x0004
#define IEVENT_STD_KEYDOWN	0x0005
#define IEVENT_STD_KEYPRESS	0x0006
#define IEVENT_STD_KEYUP	0x0007
#define IEVENT_STD_LOSTFOCUS	0x0008
#define IEVENT_STD_MOUSEDOWN	0x0009
#define IEVENT_STD_MOUSEMOVE	0x000A
#define IEVENT_STD_MOUSEUP	0x000B
#define IEVENT_STD_LINKERROR    0x000C
#define IEVENT_STD_LINKOPEN     0x000D
#define IEVENT_STD_LINKCLOSE    0x000E
#define IEVENT_STD_LINKNOTIFY   0x000F
#define IEVENT_STD_LINKCHANGE   0x0010
#define IEVENT_STD_NONE 	0x0FFF
#define IEVENT_STD_LAST 	0x0FFF

#define PEVENTINFO_STD_CLICK	    ((PEVENTINFO)~IEVENT_STD_CLICK)
#define PEVENTINFO_STD_DBLCLICK     ((PEVENTINFO)~IEVENT_STD_DBLCLICK)
#define PEVENTINFO_STD_DRAGDROP     ((PEVENTINFO)~IEVENT_STD_DRAGDROP)
#define PEVENTINFO_STD_DRAGOVER     ((PEVENTINFO)~IEVENT_STD_DRAGOVER)
#define PEVENTINFO_STD_GOTFOCUS     ((PEVENTINFO)~IEVENT_STD_GOTFOCUS)
#define PEVENTINFO_STD_KEYDOWN	    ((PEVENTINFO)~IEVENT_STD_KEYDOWN)
#define PEVENTINFO_STD_KEYPRESS     ((PEVENTINFO)~IEVENT_STD_KEYPRESS)
#define PEVENTINFO_STD_KEYUP	    ((PEVENTINFO)~IEVENT_STD_KEYUP)
#define PEVENTINFO_STD_LOSTFOCUS    ((PEVENTINFO)~IEVENT_STD_LOSTFOCUS)
#define PEVENTINFO_STD_MOUSEDOWN    ((PEVENTINFO)~IEVENT_STD_MOUSEDOWN)
#define PEVENTINFO_STD_MOUSEMOVE    ((PEVENTINFO)~IEVENT_STD_MOUSEMOVE)
#define PEVENTINFO_STD_MOUSEUP	    ((PEVENTINFO)~IEVENT_STD_MOUSEUP)
#define PEVENTINFO_STD_LINKERROR    ((PEVENTINFO)~IEVENT_STD_LINKERROR)
#define PEVENTINFO_STD_LINKOPEN     ((PEVENTINFO)~IEVENT_STD_LINKOPEN)
#define PEVENTINFO_STD_LINKCLOSE    ((PEVENTINFO)~IEVENT_STD_LINKCLOSE)
#define PEVENTINFO_STD_LINKNOTIFY   ((PEVENTINFO)~IEVENT_STD_LINKNOTIFY)
#define PEVENTINFO_STD_LINKCHANGE   ((PEVENTINFO)~IEVENT_STD_LINKCHANGE)
#define PEVENTINFO_STD_NONE	    ((PEVENTINFO)~IEVENT_STD_NONE)
#define PEVENTINFO_STD_LAST	    ((PEVENTINFO)~IEVENT_STD_LAST)


//---------------------------------------------------------------------------
// Standard control properties
//---------------------------------------------------------------------------

#define IPROP_STD_NAME		    0x0000
#define IPROP_STD_CTLNAME	    IPROP_STD_NAME
#define IPROP_STD_INDEX 	    0x0001
#define IPROP_STD_HWND		    0x0002
#define IPROP_STD_BACKCOLOR	    0x0003
#define IPROP_STD_FORECOLOR	    0x0004
#define IPROP_STD_LEFT		    0x0005
#define IPROP_STD_TOP		    0x0006
#define IPROP_STD_WIDTH 	    0x0007
#define IPROP_STD_HEIGHT	    0x0008
#define IPROP_STD_ENABLED	    0x0009
#define IPROP_STD_VISIBLE	    0x000A
#define IPROP_STD_MOUSEPOINTER	    0x000B
#define IPROP_STD_CAPTION	    0x000C
#define IPROP_STD_FONTNAME	    0x000D
#define IPROP_STD_FONTBOLD	    0x000E
#define IPROP_STD_FONTITALIC	    0x000F
#define IPROP_STD_FONTSTRIKE	    0x0010
#define IPROP_STD_FONTUNDER	    0x0011
#define IPROP_STD_FONTSIZE	    0x0012
#define IPROP_STD_TABINDEX	    0x0013
#define IPROP_STD_PARENT	    0x0014
#define IPROP_STD_DRAGMODE	    0x0015
#define IPROP_STD_DRAGICON	    0x0016
#define IPROP_STD_BORDERSTYLEOFF    0x0017
#define IPROP_STD_TABSTOP	    0x0018
#define IPROP_STD_TAG		    0x0019
#define IPROP_STD_TEXT		    0x001B
#define IPROP_STD_BORDERSTYLEON     0x001C
#define IPROP_STD_CLIPCONTROLS	    0x001D
#define IPROP_STD_NONE		    0x001E
#define IPROP_STD_HELPCONTEXTID     0x001F
#define IPROP_STD_LINKMODE	    0x0020
#define IPROP_STD_LINKITEM	    0x0021
#define IPROP_STD_LINKTOPIC	    0x0022
#define IPROP_STD_LINKTIMEOUT	    0x0023
#define IPROP_STD_LEFTNORUN	    0x0024
#define IPROP_STD_TOPNORUN	    0x0025
#define IPROP_STD_ALIGN 	    0x0026
#define IPROP_STD_IMEMODE	    0x0027	// FK_IME
#define IPROP_STD_LAST		    0x0FFF

#define PPROPINFO_STD_NAME	    ((PPROPINFO)~IPROP_STD_NAME)
#define PPROPINFO_STD_CTLNAME	    ((PPROPINFO)~IPROP_STD_NAME)
#define PPROPINFO_STD_INDEX	    ((PPROPINFO)~IPROP_STD_INDEX)
#define PPROPINFO_STD_HWND	    ((PPROPINFO)~IPROP_STD_HWND)
#define PPROPINFO_STD_BACKCOLOR     ((PPROPINFO)~IPROP_STD_BACKCOLOR)
#define PPROPINFO_STD_FORECOLOR     ((PPROPINFO)~IPROP_STD_FORECOLOR)
#define PPROPINFO_STD_LEFT	    ((PPROPINFO)~IPROP_STD_LEFT)
#define PPROPINFO_STD_TOP	    ((PPROPINFO)~IPROP_STD_TOP)
#define PPROPINFO_STD_WIDTH	    ((PPROPINFO)~IPROP_STD_WIDTH)
#define PPROPINFO_STD_HEIGHT	    ((PPROPINFO)~IPROP_STD_HEIGHT)
#define PPROPINFO_STD_ENABLED	    ((PPROPINFO)~IPROP_STD_ENABLED)
#define PPROPINFO_STD_VISIBLE	    ((PPROPINFO)~IPROP_STD_VISIBLE)
#define PPROPINFO_STD_MOUSEPOINTER  ((PPROPINFO)~IPROP_STD_MOUSEPOINTER)
#define PPROPINFO_STD_CAPTION	    ((PPROPINFO)~IPROP_STD_CAPTION)
#define PPROPINFO_STD_FONTNAME	    ((PPROPINFO)~IPROP_STD_FONTNAME)
#define PPROPINFO_STD_FONTBOLD	    ((PPROPINFO)~IPROP_STD_FONTBOLD)
#define PPROPINFO_STD_FONTITALIC    ((PPROPINFO)~IPROP_STD_FONTITALIC)
#define PPROPINFO_STD_FONTSTRIKE    ((PPROPINFO)~IPROP_STD_FONTSTRIKE)
#define PPROPINFO_STD_FONTUNDER     ((PPROPINFO)~IPROP_STD_FONTUNDER)
#define PPROPINFO_STD_FONTSIZE	    ((PPROPINFO)~IPROP_STD_FONTSIZE)
#define PPROPINFO_STD_TABINDEX	    ((PPROPINFO)~IPROP_STD_TABINDEX)
#define PPROPINFO_STD_PARENT	    ((PPROPINFO)~IPROP_STD_PARENT)
#define PPROPINFO_STD_DRAGMODE	    ((PPROPINFO)~IPROP_STD_DRAGMODE)
#define PPROPINFO_STD_DRAGICON	    ((PPROPINFO)~IPROP_STD_DRAGICON)
#define PPROPINFO_STD_BORDERSTYLEOFF ((PPROPINFO)~IPROP_STD_BORDERSTYLEOFF)
#define PPROPINFO_STD_TABSTOP	    ((PPROPINFO)~IPROP_STD_TABSTOP)
#define PPROPINFO_STD_TAG	    ((PPROPINFO)~IPROP_STD_TAG)
#define PPROPINFO_STD_TEXT	    ((PPROPINFO)~IPROP_STD_TEXT)
#define PPROPINFO_STD_BORDERSTYLEON ((PPROPINFO)~IPROP_STD_BORDERSTYLEON)
#define PPROPINFO_STD_CLIPCONTROLS  ((PPROPINFO)~IPROP_STD_CLIPCONTROLS)
#define PPROPINFO_STD_NONE	    ((PPROPINFO)~IPROP_STD_NONE)
#define PPROPINFO_STD_HELPCONTEXTID ((PPROPINFO)~IPROP_STD_HELPCONTEXTID)
#define PPROPINFO_STD_LINKMODE	    ((PPROPINFO)~IPROP_STD_LINKMODE)
#define PPROPINFO_STD_LINKITEM	    ((PPROPINFO)~IPROP_STD_LINKITEM)
#define PPROPINFO_STD_LINKTOPIC     ((PPROPINFO)~IPROP_STD_LINKTOPIC)
#define PPROPINFO_STD_LINKTIMEOUT   ((PPROPINFO)~IPROP_STD_LINKTIMEOUT)
#define PPROPINFO_STD_LEFTNORUN     ((PPROPINFO)~IPROP_STD_LEFTNORUN)
#define PPROPINFO_STD_TOPNORUN	    ((PPROPINFO)~IPROP_STD_TOPNORUN)
#define PPROPINFO_STD_ALIGN	    ((PPROPINFO)~IPROP_STD_ALIGN)
#define PPROPINFO_STD_IMEMODE	    ((PPROPINFO)~IPROP_STD_IMEMODE) // FK_IME
#define PPROPINFO_STD_LAST	    ((PPROPINFO)~IPROP_STD_LAST)

//---------------------------------------------------------------------------
// Structure for VBM_DRAGOVER and VBM_DRAGDROP events
//---------------------------------------------------------------------------

typedef struct tagDRAGINFO
{
    HCTL   hctl;
    POINT  pt;
    USHORT state;	// Enter, Over, Exit; only used for VBM_DRAGOVER
} DRAGINFO;

typedef DRAGINFO NEAR * NPDRAGINFO;
typedef DRAGINFO FAR  * LPDRAGINFO;

#define DRAG_STATE_ENTER       0x00
#define DRAG_STATE_EXIT        0x01
#define DRAG_STATE_OVER        0x02

//---------------------------------------------------------------------------
// Control MODEL structure
//---------------------------------------------------------------------------
typedef struct tagMODEL
  {
  USHORT	usVersion;		// VB version used by control
  FLONG		fl;			// Bitfield structure
  PCTLPROC	pctlproc;		// The control proc.
  FSHORT	fsClassStyle;		// Window class style
  FLONG		flWndStyle;		// Default window style
  USHORT	cbCtlExtra;		// # bytes alloc'd for HCTL structure
  USHORT	idBmpPalette;		// BITMAP id for tool palette
  PSTR		npszDefCtlName;		// Default control name prefix
  PSTR		npszClassName;		// Visual Basic class name
  PSTR		npszParentClassName;	// Parent window class if subclassed
  NPPROPLIST	npproplist;		// Property list
  NPEVENTLIST	npeventlist;		// Event list
  BYTE		nDefProp;		// Index of default property
  BYTE		nDefEvent;		// Index of default event
  BYTE		nValueProp;		// Index of control value property
  } MODEL;

typedef MODEL FAR  *  LPMODEL;

#define MODEL_fArrows	    0x00000001L
#define MODEL_fFocusOk	    0x00000002L
#define MODEL_fMnemonic     0x00000004L
#define MODEL_fChildrenOk   0x00000008L
#define MODEL_fInitMsg	    0x00000010L
#define MODEL_fLoadMsg	    0x00000020L
#define MODEL_fDesInteract  0x00000040L
#define MODEL_fInvisAtRun   0x00000080L
#define MODEL_fGraphical    0x00000100L

//---------------------------------------------------------------------------
// MODELINFO structure
//---------------------------------------------------------------------------
typedef struct tagMODELINFO
  {
  USHORT	usVersion;		// VB version used by control
  LPMODEL FAR  *lplpmodel;		// pointer to null-terminated
  } MODELINFO;				//    list of LPMODELS

typedef MODELINFO FAR *LPMODELINFO;

//---------------------------------------------------------------------------
// Picture structure
//---------------------------------------------------------------------------
typedef struct tagPIC
{
    BYTE    picType;
    union
    {
	struct
	{
	  HBITMAP   hbitmap;		// bitmap
	  HPALETTE  hpal;		// accompanying palette
	} bmp;
	struct
	{
	  HANDLE    hmeta;		// Metafile
	  int	    xExt, yExt; 	// extent
	} wmf;
	struct
	{
	  HICON     hicon;		// Icon
	} icon;
    } picData;
    BYTE    picReserved[4];
} PIC;

typedef PIC FAR  *  LPPIC;

#define PICTYPE_NONE		0
#define PICTYPE_BITMAP		1
#define PICTYPE_METAFILE	2
#define PICTYPE_ICON		3

#define HPIC_INVALID		0xFFFF
#define HPIC_NULL		0

//---------------------------------------------------------------------------
// Mode constants
//---------------------------------------------------------------------------
#define MODE_DESIGN	1
#define MODE_RUN	2
#define MODE_BREAK	3
//---------------------------------------------------------------------------
// Control flags for use with VBSetControlFlags
//---------------------------------------------------------------------------
#define CTLFLG_HASPALETTE	    0x00000001L
#define CTLFLG_USESPALETTE	    0x00000002L
#define CTLFLG_GRAPHICALOPAQUE	    0x00000004L
#define CTLFLG_GRAPHICALTRANSLUCENT 0x00000008L


//---------------------------------------------------------------------------
// The VISUAL BASIC API routines
//---------------------------------------------------------------------------

// General routines

USHORT	VBAPI VBGetMode(VOID);
USHORT	VBAPI VBGetVersion(VOID);

// General control routines

LPVOID	VBAPI VBDerefControl(HCTL hctl);
LONG	VBAPI VBDefControlProc(HCTL hctl, HWND hwnd, USHORT msg, USHORT wp, LONG lp);
BOOL	VBAPI VBRegisterModel(HANDLE hmod, LPMODEL lpmdl);
HWND	VBAPI VBGetControlHwnd(HCTL hctl);
HANDLE	VBAPI VBGetHInstance(VOID);
LPMODEL VBAPI VBGetControlModel(HCTL hctl);
LPSTR	VBAPI VBGetControlName(HCTL hctl, LPSTR lpszName);
HCTL	VBAPI VBGetHwndControl(HWND hwnd);
LONG	VBAPI VBSendControlMsg(HCTL hctl, USHORT msg, USHORT wp, LONG lp);
LONG	VBAPI VBSuperControlProc(HCTL hctl, USHORT msg, USHORT wp, LONG lp);
ERR	VBAPI VBRecreateControlHwnd(HCTL hctl);
VOID	VBAPI VBDirtyForm(HCTL hctl);
ERR	VBAPI VBSetErrorMessage(ERR err, LPSTR lpstr);
VOID	VBAPI VBGetAppTitle(LPSTR lpstr, USHORT cbMax);
int	VBAPI VBDialogBoxParam(HANDLE hinst, LPSTR pszTemplateName, FARPROC lpDialogFunc, LONG lp);
ULONG	VBAPI VBSetControlFlags(HCTL hctl, ULONG mask, ULONG value);
HCTL	VBAPI VBGetCapture(VOID);
VOID	VBAPI VBSetCapture(HCTL hctl);
VOID	VBAPI VBReleaseCapture(VOID);
VOID	VBAPI VBMoveControl(HCTL hctl, LPRECT lprect, BOOL fRepaint);
VOID	VBAPI VBGetControlRect(HCTL hctl, LPRECT lprect);
VOID	VBAPI VBGetRectInContainer(HCTL hctl, LPRECT lprect);
VOID	VBAPI VBGetClientRect(HCTL hctl, LPRECT lprect);
VOID	VBAPI VBClientToScreen(HCTL hctl, LPPOINT lppt);
VOID	VBAPI VBScreenToClient(HCTL hctl, LPPOINT lppt);
BOOL	VBAPI VBIsControlVisible(HCTL hctl);
BOOL	VBAPI VBIsControlEnabled(HCTL hctl);
VOID	VBAPI VBInvalidateRect(HCTL hctl, LPRECT lprect, BOOL fEraseBkGnd);
VOID	VBAPI VBUpdateControl(HCTL hctl);

HCTL	VBAPI VBGetControl(HCTL hctl, WORD gc);
#define GC_FIRSTSIBLING       0x0000
#define GC_LASTSIBLING	      0x0001
#define GC_NEXTSIBLING	      0x0002
#define GC_PREVSIBLING	      0x0003
#define GC_CHILD	      0x0005
#define GC_CONTAINER	      0x1000
#define GC_FORM 	      0x1001
#define GC_FIRSTCONTROL       0x1002
#define GC_NEXTCONTROL	      0x1003
#define GC_FIRSTSELECTED      0x1004
#define GC_NEXTSELECTED       0x1005

VOID	VBAPI VBZOrder(HCTL hctl, WORD zorder);
#define ZORDER_FRONT	0
#define ZORDER_BACK	1

// Management of dynamically allocated strings

HSZ	VBAPI VBCreateHsz(HANDLE seg, LPSTR lpszString);
HSZ	VBAPI VBDestroyHsz(HSZ hsz);
LPSTR	VBAPI VBDerefHsz(HSZ hsz);
LPSTR	VBAPI VBLockHsz(HSZ hsz);
VOID	VBAPI VBUnlockHsz(HSZ hsz);

// Management of language strings

HLSTR	VBAPI VBCreateHlstr(LPVOID pb, USHORT cbLen);
HLSTR	VBAPI VBCreateTempHlstr(LPVOID pb, USHORT cbLen);
VOID	VBAPI VBDestroyHlstr(HLSTR hlstr);
LPSTR	VBAPI VBDerefHlstr(HLSTR hlstr);
LPSTR	VBAPI VBDerefHlstrLen(HLSTR hlstr, USHORT FAR *pCbLen);
LPSTR	VBAPI VBDerefZeroTermHlstr(HLSTR hlstr);
USHORT	VBAPI VBGetHlstr(HLSTR hlstr, LPVOID pb, USHORT cbLen);
USHORT	VBAPI VBGetHlstrLen(HLSTR hlstr);
ERR	VBAPI VBSetHlstr(HLSTR far *phlstr, LPVOID pb, USHORT cbLen);
ERR	VBAPI VBResizeHlstr(HLSTR hlstr, USHORT newCbLen);

// Management of language Variant data type

ERR	VBAPI VBCoerceVariant(LPVAR lpVar, SHORT vtype, LPVOID lpData);
SHORT	VBAPI VBGetVariantType(LPVAR lpVar);
SHORT	VBAPI VBGetVariantValue(LPVAR lpVar, LPVAL lpVal);
ERR	VBAPI VBSetVariantValue(LPVAR lpVar, SHORT vtype, LPVOID lpData);

// Management of language arrays

#define LOBOUND(x) ((SHORT)((x) & 0xFFFF))
#define HIBOUND(x) ((SHORT)((x) >> 16))

LPVOID VBAPI VBArrayElement(HAD hAD, SHORT cIndex, LPSHORT lpi);

LONG	VBAPI VBArrayBounds(HAD hAD, SHORT index);
#define AB_INVALIDINDEX     1	  // hAD or index is bad
USHORT	VBAPI VBArrayElemSize(HAD hAD);
LPVOID	VBAPI VBArrayFirstElem(HAD hAD);
SHORT	VBAPI VBArrayIndexCount(HAD hAD);

// VB Error routines

VOID	VBAPI VBRuntimeError(ERR err);

// Floating-point stack save/restore utilities
USHORT	VBAPI VBCbSaveFPState(LPVOID pb, USHORT cb);
VOID	VBAPI VBRestoreFPState(LPVOID pb);

// Firing Basic event procedures

ERR	VBAPI VBFireEvent(HCTL hctl, USHORT idEvent, LPVOID lpparams);

// Control property access

ERR	VBAPI VBGetControlProperty(HCTL hctl, USHORT idProp, LPVOID pdata);
ERR	VBAPI VBSetControlProperty(HCTL hctl, USHORT idProp, LONG data);

// Picture management functions

HPIC	VBAPI VBAllocPic(LPPIC lppic);
HPIC	VBAPI VBAllocPicEx(LPPIC lppic, USHORT usVersion);
VOID	VBAPI VBFreePic(HPIC hpic);
HPIC	VBAPI VBGetPic(HPIC hpic, LPPIC lppic);
HPIC	VBAPI VBGetPicEx(HPIC hpic, LPPIC lppic, USHORT usVersion);
ERR	VBAPI VBPicFromCF(HPIC FAR *lphpic, HANDLE hData, WORD wFormat);
HPIC	VBAPI VBRefPic(HPIC hpic);
VOID	VBAPI VBPaletteChanged(HCTL hctl);
COLOR	VBAPI VBTranslateColor(HCTL hctl, COLOR clr);

// File IO functions

ERR	VBAPI VBReadFormFile(HFORMFILE hformfile, LPVOID pb, WORD cb);
ERR	VBAPI VBWriteFormFile(HFORMFILE hformfile, LPVOID pb, WORD cb);
LONG	VBAPI VBSeekFormFile(HFORMFILE hformfile, LONG offset);
LONG	VBAPI VBRelSeekFormFile(HFORMFILE hformfile, LONG offset);
ERR	VBAPI VBReadBasicFile(USHORT usFileNo, LPVOID pb, WORD cb);
ERR	VBAPI VBWriteBasicFile(USHORT usFileNo, LPVOID pb, WORD cb);

// Conversion functions

LONG	VBAPI VBYPixelsToTwips(SHORT Pixels);
LONG	VBAPI VBXPixelsToTwips(SHORT Pixels);
SHORT	VBAPI VBYTwipsToPixels(LONG Twips);
SHORT	VBAPI VBXTwipsToPixels(LONG Twips);

// Link Interface functions

ERR	VBAPI VBLinkPostAdvise(HCTL hctl);
BOOL	VBAPI VBPasteLinkOk(HANDLE FAR *phTriplet, HCTL hctl);
VOID	VBAPI VBLinkMakeItemName(HCTL hctl, LPSTR lpszBuf);

// Exports from .VBX files

#ifndef NOCCEXPORTS
BOOL FAR PASCAL _export VBINITCC(USHORT usVersion, BOOL fRuntime);
VOID FAR PASCAL _export VBTERMCC(VOID);
LPMODELINFO FAR PASCAL _export VBGetModelInfo(USHORT usVersion);
#endif // !NOCCEXPORTS

// Misc functions

SHORT	VBAPI VBFormat(SHORT vtype, LPVOID lpData, LPSTR lpszFmt, LPVOID pb, USHORT cb);

#define CONTROLDEREF(type, hctl) ((P##type)(VBDerefControl(hctl)))


//---------------------------------------------------------------------------
// Visual Basic messages
//---------------------------------------------------------------------------
#define VBM__BASE		( WM_USER + 0x0C00 )

// All properties have been loaded.  Must set MODEL_fLoadMsg to receive.
#define VBM_CREATED		( VBM__BASE + 0x00 )

// Form load is complete or dynamic control is fully loaded.  Must set
// MODEL_fLoadMsg to receive.
#define VBM_LOADED		( VBM__BASE + 0x01 )

// Pre-hwnd properties are not yet loaded (no hwnd exists for control yet).
// Must set MODEL_fInitMsg to receive.
#define VBM_INITIALIZE		( VBM__BASE + 0x02 )

// Get a property value.
// [wp=iprop, lp=pdata], RetVal=ERR
#define VBM_GETPROPERTY 	( VBM__BASE + 0x03 )

// Verify a property value.
// [wp=iprop, lp=data], RetVal=ERR
#define VBM_CHECKPROPERTY	( VBM__BASE + 0x04 )

// Set a property value.
// [wp=iprop, lp=data], RetVal=ERR
#define VBM_SETPROPERTY 	( VBM__BASE + 0x05 )

// Write a property.
// [wp=iprop, lp=pfileref], RetVal=ERR
#define VBM_SAVEPROPERTY	( VBM__BASE + 0x06 )

// Read a property.
// [wp=iprop, lp=pfileref], RetVal=ERR
#define VBM_LOADPROPERTY	( VBM__BASE + 0x07 )

// Get the string representation of a property.
// [wp=iprop, lp=HSZ FAR *], RetVal=ERR
#define VBM_GETPROPERTYHSZ	( VBM__BASE + 0x08 )

// Create popup window used to change a property.
// [wp=iprop, lp=listbox hwnd], RetVal=popup hwnd
#define VBM_INITPROPPOPUP	( VBM__BASE + 0x09 )

// Determine if Paste/PasteLink is allowed.
// [wp=PASTETYPE], RetVal=BOOL
#define VBM_QPASTEOK		( VBM__BASE + 0x0A )

#define PT_PASTE	0
#define PT_PASTELINK	1

// Paste control-specific data from the clipboard.
// [wp=PASTETYPE], RetVal=ERR
#define VBM_PASTE		( VBM__BASE + 0x0B )

// Copy control specific data to the clipboard.
#define VBM_COPY		( VBM__BASE + 0x0C )

// Control activated upon receipt of a unique mnemonic key.
#define VBM_MNEMONIC		( VBM__BASE + 0x0D )

// Posted to fire a deferred event.
// [wp=event]
#define VBM_FIREEVENT		( VBM__BASE + 0x0E )

// Another control in drag mode drug over the control.
// [lp=pdraginfo]
#define VBM_DRAGOVER		( VBM__BASE + 0x0F )

// This message is sent to a control that has just had another control
// in drag mode dropped on it.
// [lp=pdraginfo]
#define VBM_DRAGDROP		( VBM__BASE + 0x10 )

// This message is sent when certain methods are invoked on controls
// [wp=METH_, lp=far *alParams], RetVal=ERR
#define VBM_METHOD		( VBM__BASE + 0x11 )

#define METH_ADDITEM	0x0001	// args are: cArgs, hszItem, [index]
#define METH_REMOVEITEM 0x0002	// args are: cArgs, index
#define METH_REFRESH	0x0003	// no args (lp == NULL)
#define METH_MOVE	0x0004	// args are: cArgs, left, [top, [width, [height]]]
#define METH_DRAG	0x0005	// args are: cArgs, [cmd]
#define METH_LINKSEND   0x0006  // no args (lp == NULL)
#define METH_ZORDER	0x0007	// args are: cArgs, pos
#define METH_CLEAR	0x000A	// no args (lp == NULL)

// Clear capture and internal state.
#define VBM_CANCELMODE		( VBM__BASE + 0x12 )

// Paint notification for graphical controls.
// [wp=hdc, lp=lprect]
#define VBM_PAINT		( VBM__BASE + 0x14 )

// Hit test for graphical controls.
// [lp=lphittest], RetVal = HT_
#define VBM_HITTEST		( VBM__BASE + 0x15 )

#define HT_ON		  7
#define HT_SOLID_NEAR	  6
#define HT_PATTERN_NEAR   5
#define HT_HOLLOW_NEAR	  4
#define HT_SOLID	  3
#define HT_PATTERN	  2
#define HT_HOLLOW	  1
#define HT_MISS 	  0
typedef struct tagHITTEST
  {
  POINT pt;	    // Point to test (in parent's coordinates)
  RECT	rect;	    // Rect of self (in parent's coordinates)
  } HITTEST;
typedef HITTEST FAR *LPHITTEST;

// Paint the multi-select handles
// [wp=hdc, lp=rect(in hdc coords)]
#define VBM_PAINTMULTISEL	( VBM__BASE + 0x16 )

// Paint the "gray rect" or ctl outline while moving/sizing ctl.
// [wp=hdc, lp=rect(in hdc coords)]
#define VBM_PAINTOUTLINE	( VBM__BASE + 0x17 )

// Palette change notification.
// [wp=fPalBack(for SelectPalette)], RetVal = return from RealizePalette
#define VBM_PALETTECHANGED	( VBM__BASE + 0x1B )

// Get control palette.
// RetVal = HPALETTE.
#define VBM_GETPALETTE		( VBM__BASE + 0x1C )

// Enumerate available formats.
// [wp=SUPPLIESDATAFORMAT | ACCEPTSDATAFORMAT]
// [LOWORD(lp)=ennumeration(0-x)]
#define VBM_LINKENUMFORMATS	( VBM__BASE + 0x1E )

// Ask a control for it's LINK item name.  Return item name as lpsz in lp.
// [wp=LINKSRCASK | LINKSRCTELL]
// [lp=lpszItemName]
#define VBM_LINKGETITEMNAME	( VBM__BASE + 0x1F )

// For Server items and client pokes.
// [wp=wFormat lp=LPLINKDATA]
#define VBM_LINKGETDATA 	( VBM__BASE + 0x20 )

// Used in client requests, advises, and server pokes.
// [wp=wFormat lp=LPLINKDATA]
#define VBM_LINKSETDATA 	( VBM__BASE + 0x21 )

// Get help on property or event name.
// [LOBYTE(wp)=VBHELP_, HIBYTE(wp)=iprop/ievent, lp=lpmodel]
#define VBM_HELP		( VBM__BASE + 0x22 )

#define VBHELP_PROP	0x0001
#define VBHELP_EVT	0x0002
#define VBHELP_CTL    	0x0003

// Get default size of control
// LOWORD(RetVal)=cx, HIWORD(RetVal)=cy
#define VBM_GETDEFSIZE		( VBM__BASE + 0x23 )

// Just like VBM_SAVE(LOAD)PROPERTY, but saves (loads) as text.
#define VBM_SAVETEXTPROPERTY	( VBM__BASE + 0x24 )
#define VBM_LOADTEXTPROPERTY	( VBM__BASE + 0x25 )

// Is char a mnemonic for this control?
// [wp=char] RetVal=TRUE/FALSE
#define VBM_ISMNEMONIC		( VBM__BASE + 0x26 )

// Does control want to see WM_KEYUP/WM_KEYDOWN for vk?  Sent only
// for keys which are normally trapped by VB.  E.g. Tab, Enter, etc.
// [wp=vk] RetVal=TRUE/FALSE
#define VBM_WANTSPECIALKEY	( VBM__BASE + 0x27 )

//Notifies a control that it has been selected in the property window.
//[wp=multiselect ON (TRUE) or OFF (FALSE)]
//[LOWORD(lp)=multiselect count (0 first, n last)]
#define VBM_SELECTED            ( VBM__BASE + 0x28 )

// Notifications reflected back to control from parent.
#define VBN__BASE		(VBM__BASE + 0x1000)

#define VBN_COMMAND		(VBN__BASE + WM_COMMAND)
#define VBN_CTLCOLOR		(VBN__BASE + WM_CTLCOLOR)
#define VBN_DRAWITEM		(VBN__BASE + WM_DRAWITEM)
#define VBN_MEASUREITEM 	(VBN__BASE + WM_MEASUREITEM)
#define VBN_DELETEITEM		(VBN__BASE + WM_DELETEITEM)
#define VBN_VKEYTOITEM		(VBN__BASE + WM_VKEYTOITEM)
#define VBN_CHARTOITEM		(VBN__BASE + WM_CHARTOITEM)
#define VBN_COMPAREITEM 	(VBN__BASE + WM_COMPAREITEM)
#define VBN_HSCROLL		(VBN__BASE + WM_HSCROLL)
#define VBN_VSCROLL		(VBN__BASE + WM_VSCROLL)
#define VBN_PARENTNOTIFY	(VBN__BASE + WM_PARENTNOTIFY)

// Data xfer structure for VBM_LINKGETDATA or VBM_LINKSETDATA

typedef struct tagLinkData
  {
  WORD     wReserved;
  DWORD    cb;      // size of data
  HANDLE   hData;   // Handle to data
  DWORD    dwReserved;
  } VBLINKDATA;

typedef VBLINKDATA FAR *LPLINKDATA;

// link modes

#define LINKMODENONE			0
#define LINKMODEAUTO			1
#define LINKMODEMANUAL			2
#define LINKMODENOTIFY                  3

#define LINKMODESERVERPOKE		1
#define LINKMODESERVERNOPOKE		2

#define VBDDEDATA VBLINKDATA
#define LPDDEDATA LPLINKDATA

// Various DDE defines

#define MAX_EXEC                        256
#define MAXLINKITEMNAME                 256

#define ACCEPTSDATAFORMAT                1
#define SUPPLIESDATAFORMAT               2

#define LINKSRCASK                       0
#define LINKSRCTELL                      1

#define LINK_DATA_OK			 0
#define LINK_DATA_OOM			 1
#define LINK_DATA_FORMATBAD		 2
#define LINK_DATA_SETFAILED		 3

#define errInitOnNonServerDesk   6  // Attempted to Initate on a channel that
				    // had linkmode set to None.

#define errAllServerChUsed       7  // The Server Channel array is filled.

#define errDataSettingFailed     8  // The Set quality failed possible string
				    // too long.

#define errOutOfMemoryForLink	11
#ifdef __cplusplus 
} 
#endif 
