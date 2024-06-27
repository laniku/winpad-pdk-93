/****************************************************************************\
*                                                                            *
* penwin.h -    Pen Windows functions, types, and definitions                *
*                                                                            *
*               Version 2.0                                                  *
*                                                                            *
*               Copyright (c) 1992-1993 Microsoft Corp. All rights reserved. *
*                                                                            *
*******************************************************************************
*
* The following symbols control inclusion of various parts of this file;
* (indented identifiers are included by the previous main identifier):
*
* #define:				To prevent inclusion of:
*
* PENVER					Pen Windows version number (0x0200).  To exclude
*							definitions introduced in version 2.0 (or above)
*							#define PENVER 0x0100 before #including <penwin.h>
*
* NOPENCTL				H/BEDIT, IEDIT, and pen-enabled USER controls, including:
*   NOPENBEDIT			 : Boxed Edit Control
*   NOPENIEDIT			 : Ink Edit Control
* NOPENDICT				Dictionary support
* NOPENGEST				Gesture macros and Gesture Mapper (1.0)
* NOPENINKPUT			Inking and Input APIs and definitions
* NOPENAPPS				Pen Applications: Screen Keyboard
* NOPENRES				Pen resources, including:
*   NOPENBMP			 : Pen-related bitmaps
*   NOPENCURS			 : Pen-related cursors
* NOPENDATA				PenData APIs and definitions
* NOPENDRIVER			Pen Driver definitions, incl OEM
* NOPENHRC				Handwriting Recognizer APIs and definitions
* NOPENMSGS				Pen Messages and definitions
* NOPENMISC				Miscellaneous Info and Utility APIs and definitions
* NOPENNLS				National Language Support
* NOPENRC1				Recognition Context APIs and definitions (1.0), including:
*   NOPENALC			 : Alphabet code definitions (1.0)
*   NOPENRECOG			 : Recognition APIs and definitions (1.0)
*   NOPENSYV			 : Symbol Value definitions (1.0)
* NOPENTARGET			Targeting APIs and definitions
* NOPENVIRTEVENT		Virtual Event layer APIs
* NOWINDOWS				Windows definitions
* NOWINUSER				used only by Windows USER
*
* Also, an "FBC" in the comments means that the feature exists only for
* backward compatibility. It should not be used by new applications.
\****************************************************************************/

#ifndef _INC_WINDOWS
#ifdef NOWINDOWS
#include <winmin.h>    	/* minimum windows.h defines and typedefs */
#else
#include <windows.h>
#endif //NOWINDOWS
#endif //_INC_WINDOWS

#ifndef _INC_PENWIN     /* prevent multiple includes */
#define _INC_PENWIN

#ifndef RC_INVOKED
#pragma pack(1)
#endif /* RC_INVOKED */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* If PENVER is not defined, assume version 2.0 */
#ifndef PENVER
#define PENVER  0x0200
#endif

#ifndef NOPENAPPS
#ifndef RC_INVOKED
#include <skbapi.h>
#endif /* !RC_INVOKED */
#endif /*!NOPENAPPS */

// subsets:
#ifdef NOPENCTL
	#define NOPENBEDIT
	#define NOPENIEDIT
#endif /* NOPENCTL */

#ifdef NOPENRC1
	#define NOPENALC
	#define NOPENRECOG
	#define NOPENSYV
#endif /* NOPENRC1 */

#ifdef NOPENRES
	#define NOPENBMP
	#define NOPENCURS
#endif /* NOPENRES */


/****** Definitions 1: for everything including RC compiler ****************/

//---------------------------------------------------------------------------
#ifndef NOPENALC

// Enabled Alphabet:
#define ALC_DEFAULT				0x00000000L	// nothing
#define ALC_LCALPHA				0x00000001L	// a..z
#define ALC_UCALPHA				0x00000002L	// A..Z
#define ALC_ALPHA					0x00000003L	// a..z A..Z
#define ALC_NUMERIC				0x00000004L	// 0..9
#define ALC_ALPHANUMERIC		0x00000007L	// a..z A..Z 0..9
#define ALC_PUNC					0x00000008L	// !-;`"?()&.,; and backslash
#define ALC_MATH					0x00000010L	// %^*()-+={}<>,/.
#define ALC_MONETARY				0x00000020L	// ,.$ or local
#define ALC_OTHER					0x00000040L	// @#|_~[]
#define ALC_ASCII					0x00000080L	// restrict to 7-bit chars 20..7f
#define ALC_WHITE					0x00000100L	// white space
#define ALC_NONPRINT				0x00000200L	// sp tab ret ctrl glyphs
#define ALC_DBCS					0x00000400L	// allow DBCS variety of SBCS
#define ALC_JIS1					0x00000800L	// kanji JPN, ShiftJIS 1 only
#define ALC_GESTURE				0x00004000L	// gestures
#define ALC_USEBITMAP			0x00008000L	// use rc.rgbfAlc to enable chars
#define ALC_HIRAGANA				0x00010000L	// hiragana JPN
#define ALC_KATAKANA				0x00020000L	// katakana JPN
#define ALC_KANJI					0x00040000L	// kanji JPN, ShiftJIS 1+2+3
#define ALC_OEM					0x0FF80000L	// OEM recognizer-specific
#define ALC_RESERVED				0xF0003000L	// avail for future use
#define ALC_NOPRIORITY			0x00000000L	// def for rc.alcPriority none

#define ALC_ALL					0x0000437FL	// everything but Japanese
#define ALC_SYSMINIMUM			0x0000410FL	// ALPHANUMERIC|PUNC|WHITE|GEST
#define ALC_KANJISYSMINIMUM	0x0003490FL	// SYSMINIMUM|HIRA|KATA|JIS1
#define ALC_KANJIALL				0x0007437FL	// ALL|HIRA|KATA|KANJI
#endif /*!NOPENALC */


//---------------------------------------------------------------------------
#ifndef NOPENBMP

// Public Bitmaps :
#define OBM_SKBBTNUP				32767
#define OBM_SKBBTNDOWN			32766
#define OBM_SKBBTNDISABLED		32765

#define OBM_ZENBTNUP				32764
#define OBM_ZENBTNDOWN			32763
#define OBM_ZENBTNDISABLED		32762

#define OBM_HANBTNUP				32761
#define OBM_HANBTNDOWN			32760
#define OBM_HANBTNDISABLED		32759

#define OBM_KKCBTNUP				32758
#define OBM_KKCBTNDOWN			32757
#define OBM_KKCBTNDISABLED		32756

#define OBM_SIPBTNUP				32755
#define OBM_SIPBTNDOWN			32754
#define OBM_SIPBTNDISABLED		32753

#define OBM_PTYBTNUP				32752
#define OBM_PTYBTNDOWN			32751
#define OBM_PTYBTNDISABLED		32750
#endif /*!NOPENBMP */


//---------------------------------------------------------------------------
#ifndef NOPENCURS
// Default pen cursor to indicate writing, points northwest
#define IDC_PEN					MAKEINTRESOURCE(32631)

// alternate select cursor: upsidedown standard arrow, points southeast
#define IDC_ALTSELECT			MAKEINTRESOURCE(32501)
#endif /*!NOPENCURS */


//---------------------------------------------------------------------------
#ifndef NOPENIEDIT

// IEdit Style Attributes
#define IES_BUTTON				0x0001	// control has pop-up menu button
#define IES_DISABLEMENU			0x0002	// disable ctl pop-up menu
#define IES_HSCROLL				0x0004	// ctl is horizontally scrollable
#define IES_VSCROLL				0x0008	// ctl is vertically scrollable
#define IES_BORDER				0x0010	// ctl has a border
#define IES_OWNERDRAW			0x0020	// ctl will be drawn by parent window
#define IES_RESERVED				0xFFC0	// reserved

// IEdit Pop-up Menu Command Items
#define IEM_UNDO					1			// Undo
#define IEM_CUT					2			// Cut
#define IEM_COPY					3			// Copy
#define IEM_PASTE					4			// Paste
#define IEM_CLEAR					5			// Clear 
#define IEM_DELETE				5			// Delete == Clear 
#define IEM_SELECTALL			6			// Select All Strokes
#define IEM_ERASE					7			// Use Eraser
#define IEM_PROPERTIES			8			// DoProperties
#define IEM_HELP					9			// Help
#define IEM_LASSO					10			// Use Lasso
#define IEM_RESIZE				11			// Resize
//													// NYI
#define IEM_COLOR					12			// Ink Color
#define IEM_NIB					13			// Ink Nib
#define IEM_SELECT				14			// Select...	
#define IEM_OPTIONS				15			// Options...
#define IEM_EDIT					16			// Edit... (Formats)
//										17-99		// Reserved
#define IEM_USER					100		// first menu item# available to app

#endif /*!NOPENIEDIT */

//---------------------------------------------------------------------------
#ifndef NOPENBEDIT
// box edit styles:
#define BXS_NONE					0x0000U	// none
#define BXS_RECT					0x0001U	// use rectangle instead of cusp
#define BXS_ENDTEXTMARK			0x0002U	// show mark at eot
#define BXS_MASK					0x0003U	// mask for above

#endif /*!NOPENBEDIT */




#ifndef RC_INVOKED	// ... rest of file of no interest to rc compiler

/****** Definitions 2: RC compiler excluded ********************************/

//---------------------------------------------------------------------------

#ifndef NOPENDATA

// PenData API constants:

// PenData Scaling (PDTS):
#define PDTS_LOMETRIC			0			// 0.01mm
#define PDTS_HIMETRIC			1			// 0.001mm
#define PDTS_HIENGLISH			2			// 0.001"
#define PDTS_STANDARDSCALE		2			// PDTS_HIENGLISH	alias
#define PDTS_DISPLAY				3			// display pixel
#define PDTS_SCALEMAX			3			// 
#define PDTS_ARBITRARY			4			// app-specific scaling
#define PDTS_SCALEMASK			0x000F	// scaling values in low nibble

// CreatePenData (CPD) and Pen Hardware (PHW) Flags;
// The order of PHW flags is important:
#define CPD_DEFAULT				0x047F	// CPD_TIME | PHW_ALL
#define CPD_USERBYTE				0x0100	// alloc 8 bits/stroke
#define CPD_USERWORD				0x0200	// alloc 16 bits/stroke
#define CPD_USERDWORD			0x0300	// alloc 32 bits/stroke
#define CPD_TIME					0x0400	// maintain abs time info per stroke

#define PHW_PRESSURE				0x0001	// report pressure in OEMdata if avail
#define PHW_HEIGHT				0x0002	// ditto height
#define PHW_ANGLEXY				0x0004	// ditto xy angle
#define PHW_ANGLEZ				0x0008	// ditto z angle
#define PHW_BARRELROTATION		0x0010	// ditto barrel rotation
#define PHW_OEMSPECIFIC			0x0020	// ditto OEM-specific value
#define PHW_PDK					0x0040	// report per-point PDK_xx in OEM data
#define PHW_ALL					0x007F	// report everything

// CompactPenData() API trim options:
#define PDTT_DEFAULT				0x0000         
#define PDTT_PENINFO				0x0100
#define PDTT_UPPOINTS			0x0200
#define PDTT_OEMDATA				0x0400
#define PDTT_COLLINEAR			0x0800 
#define PDTT_COLINEAR			0x0800 	// alt sp alias
#define PDTT_DECOMPRESS			0x4000	// decompress the data
#define PDTT_COMPRESS			0x8000
#define PDTT_ALL					0x0F00	// PENINFO|UPPOINTS|OEMDATA|COLLINEAR

// CompressPenData() API options:
#define CMPD_COMPRESS			0x0001
#define CMPD_DECOMPRESS			0x0002

// TrimPenData() API options:
#define TPD_RECALCSIZE			0x0000	// no trim, used for resize calc
#define TPD_USER					0x0080	// per-stroke user info
#define TPD_TIME					0x0100	// per-stroke timing info
#define TPD_UPPOINTS				0x0200	// x-y data up points
#define TPD_COLLINEAR			0x0400	// colinear and coincident points
#define TPD_COLINEAR				0x0400	// alt sp alias
#define TPD_PENINFO				0x0800	// PenInfo struct and all OEM
#define TPD_PHW					0x1000	// all OEM and pdk, but not stroke tick or user
#define TPD_OEMDATA				0x1000	// all OEM & PDK (Same as above)
#define TPD_EVERYTHING			0x1F80	// everything possible except down pts

// compact pen data trim options: matches PDTT_values (see above)
#define PDTS_COMPRESS2NDDERIV	0x0010	// compress using 2nd deriv
#define PDTS_COMPRESSMETHOD	0x00F0	// sum of compress method flags
#define PDTS_NOPENINFO			0x0100	// removes PENINFO struct from header
#define PDTS_NOUPPOINTS			0x0200	// remove up pts
#define PDTS_NOOEMDATA			0x0400	// remove OEM data
#define PDTS_NOCOLLINEAR		0x0800	// remove successive identical pts
#define PDTS_NOCOLINEAR			0x0800	// alt sp alias
#define PDTS_NOTICK				0x1000	// remove timing info (2.0)
#define PDTS_NOUSER				0x2000	// remove user info (2.0)
#define PDTS_COMPRESSED			0x8000	// perform lossless compression

// Ink (PenData) API flags and constants

// DrawPenDataEx() flags/options:
#define DPD_HDCPEN				0x0001	// use pen selected in HDC

// ANIMATEINFO options:
#define AI_SKIPUPSTROKES		0x0001	// ignore upstrokes in animation
#define AI_CBSTROKE				0xFFFF 	// Animate callback after every stroke

// ExtractPenDataPoints options (EPDP_xx):
#define EPDP_REMOVE				0x0001	// Remove points from the pendata

// ExtractPenDataStrokes options and modifiers (EPDS_xx):
#define EPDS_SELECT				0x0001	// selected strokes
#define EPDS_STROKEINDEX		0x0002	// index
#define EPDS_USER					0x0003	// user-specific value
#define EPDS_TIME					0x0004	// stroke time (ms)
#define EPDS_PENTIP				0x0005	// complete pentip
#define EPDS_TIPCOLOR			0x0006	// pentip color
#define EPDS_TIPWIDTH			0x0007	// pentip width
#define EPDS_TIPNIB				0x0008	// pentip nib style
#define EPDS_INKSET				0x0009	// inkset match

#define EPDS_EQ					0x0000	// default: same as
#define EPDS_LT					0x0010	// all strokes less than
#define EPDS_GT					0x0020	// all strokes greater than
#define EPDS_NOT					0x0040	// all strokes not matching
#define EPDS_NE					0x0040	// alias
#define EPDS_GTE					0x0050	// alias for NOT LT
#define EPDS_LTE					0x0060	// alias for NOT GT
#define EPDS_REMOVE				0x8000	// remove matching strokes from source

#ifndef IX_END
#define IX_END						0xFFFF	// means to or past last available index
#endif //!IX_END

// GetStrokeAttributes options (GSA_xx):
#define GSA_PENTIP				1	// get stroke pentip (color, width, nib)
#define GSA_PENTIPCLASS			2	// same as GSA_PENTIP
#define GSA_USER					3	// get stroke user value
#define GSA_USERCLASS			4	// get stroke's class user value
#define GSA_TIME					5	// get time of stroke
#define GSA_SIZE					6	// get size of stroke in points and bytes
#define GSA_SELECT				7	// get selection status of stroke
#define GSA_DOWN					8	// get up/down state of stroke

// GetStrokeTableAttributes options (GSA_xx):
#define GSA_PENTIPTABLE			9	// get table-indexed pentip
#define GSA_SIZETABLE			10	// get count of Stroke Class Table entries
#define GSA_USERTABLE			11	// get table-indexed user value


// SetStrokeAttributes options (SSA_xx):
#define SSA_PENTIP				1	// set stroke pentip (color, width, nib)
#define SSA_PENTIPCLASS			2	// set stroke's class pentip
#define SSA_USER					3	// set stroke user value
#define SSA_USERCLASS			4	// set stroke's class user value
#define SSA_TIME					5	// set time of stroke
#define SSA_SELECT				6	// set selection status of stroke
#define SSA_DOWN					7	// set up/down state of stroke

// SetStrokeTableAttributes options (SSA_xx) and return values (SSAR_xx):
#define SSA_PENTIPTABLE			8	// set table-indexed pentip
#define SSA_USERTABLE			9	// set table-indexed user value



// WritePenData() options:
#define WPD_DEFAULT				0x0000	// native file format
#define WPD_EXPORT				0x0001	// intergalactic standard file format

// General PenData API return values (PDR_xx):
#define PDR_NOHIT					3			// hit test failed
#define PDR_HIT					2			// hit test succeeded
#define PDR_OK						1			// success
#define PDR_CANCEL				0			// callback cancel or impasse

#define PDR_ERROR					(-1)		// parameter or unspecified error
#define PDR_PNDTERR				(-2)		// bad pendata
#define PDR_VERSIONERR			(-3)		// pendata version error
#define PDR_COMPRESSED			(-4)		// pendata is compressed
#define PDR_STRKINDEXERR		(-5)		// stroke index error
#define PDR_PNTINDEXERR			(-6)		// point index error
#define PDR_MEMERR				(-7)		// memory error
#define PDR_INKSETERR			(-8)		// bad inkset
#define PDR_ABORT					(-9)		// pendata has become invalid, e.g.
#define PDR_NA						(-10)		// option not available (pw kernel)

#define PDR_USERDATAERR			(-16)		// user data error
#define PDR_SCALINGERR			(-17)		// scale error
#define PDR_TIMESTAMPERR		(-18)		// timestamp error
#define PDR_OEMDATAERR			(-19)		// OEM data error
#define PDR_SCTERR				(-20)		// SCT error (full)

// PenTip:
#define PENTIP_NIBDEFAULT		((BYTE)0)		// default pen tip nib style
#define PENTIP_HEIGHTDEFAULT	((BYTE)0)		// default pen tip nib height
#define PENTIP_OPAQUE			((BYTE)0xFF)	// default opaque ink
#define PENTIP_HILITE			((BYTE)0x80)
#define PENTIP_TRANSPARENT		((BYTE)0)

// PenTip flag bits:
#define TIP_ERASECOLOR			1			// erase specific color pentip.rgb


#endif /*!NOPENDATA */

//---------------------------------------------------------------------------
#ifndef NOPENDICT

// Dictionary:
#define cbDictPathMax			255
#define DIRQ_QUERY				1
#define DIRQ_DESCRIPTION		2
#define DIRQ_CONFIGURE			3
#define DIRQ_OPEN					4
#define DIRQ_CLOSE				5
#define DIRQ_SETWORDLISTS		6
#define DIRQ_STRING				7
#define DIRQ_SUGGEST				8
#define DIRQ_ADD					9
#define DIRQ_DELETE				10
#define DIRQ_FLUSH				11
#define DIRQ_RCCHANGE			12
#define DIRQ_SYMBOLGRAPH		13
#define DIRQ_INIT					14
#define DIRQ_CLEANUP				15
#define DIRQ_COPYRIGHT			16
#define DIRQ_USER					4096
#endif /*!NOPENDICT */


//---------------------------------------------------------------------------
#ifndef NOPENDRIVER

// Pen driver:
#define BITPENUP					0x8000

// OEM-specific values for Pen Driver:
#define PDT_NULL					0
#define PDT_PRESSURE				1			// pressure supported
#define PDT_HEIGHT				2			// height above tablet
#define PDT_ANGLEXY				3			// xy (horiz) angle supported
#define PDT_ANGLEZ				4			// z (vert) angle supported
#define PDT_BARRELROTATION		5			// barrel is rotated
#define PDT_OEMSPECIFIC			16		// max

#define MAXOEMDATAWORDS			6			// rgwOemData[MAXOEMDATAWORDS]

// Pen Device Capabilities:
#define PDC_INTEGRATED			0x00000001L	// display==digitizer
#define PDC_PROXIMITY			0x00000002L	// detect non-contacting pen
#define PDC_RANGE					0x00000004L	// event on out-of-range
#define PDC_INVERT				0x00000008L	// pen opposite end detect
#define PDC_RELATIVE				0x00000010L	// pen driver coords
#define PDC_BARREL1				0x00000020L	// barrel button 1 present
#define PDC_BARREL2				0x00000040L	// ditto 2
#define PDC_BARREL3				0x00000080L	// ditto 3

// Pen Driver messages:
#define DRV_SetPenDriverEntryPoints    DRV_RESERVED+1
#define DRV_RemovePenDriverEntryPoints DRV_RESERVED+2
#define DRV_SetPenSamplingRate         DRV_RESERVED+3
#define DRV_SetPenSamplingDist         DRV_RESERVED+4
#define DRV_GetName                    DRV_RESERVED+5
#define DRV_GetVersion                 DRV_RESERVED+6
#define DRV_GetPenInfo                 DRV_RESERVED+7
#define DRV_PenPlayStart					DRV_RESERVED+8
#define DRV_PenPlayBack						DRV_RESERVED+9
#define DRV_PenPlayStop						DRV_RESERVED+10
#define DRV_GetCalibration             DRV_RESERVED+11
#define DRV_SetCalibration             DRV_RESERVED+12

// Pen Driver Kit states:
#define PDK_NULL					0x0000	// default to no flags set
#define PDK_UP						0x0000	// PDK_NULL alias
#define PDK_DOWN					0x0001	// pentip switch ON due to contact
#define PDK_BARREL1				0x0002	// barrel1 switch depressed
#define PDK_BARREL2				0x0004	// ditto 2
#define PDK_BARREL3				0x0008	// ditto 3
#define PDK_SWITCHES				0x000f	// sum of down + barrels 1,2,3
#define PDK_TRANSITION			0x0010	// set by GetPenHwData
#define PDK_UNUSED10				0x0020
#define PDK_UNUSED20				0x0040
#define PDK_INVERTED				0x0080	// other end of pen used as tip
#define PDK_PENIDMASK			0x0F00	// bits 8..11 physical pen id (0..15)
#define PDK_UNUSED1000			0x1000
#define PDK_INKSTOPPED			0x2000  // Inking stopped
#define PDK_OUTOFRANGE			0x4000	// pen left range (OEM data invalid)
#define PDK_DRIVER				0x8000	// pen (not mouse) event

#define PDK_TIPMASK				0x0001	// mask for testing PDK_DOWN

// Pen Collection Mode termination conditions:
// (note update doc for PCMINFO struct if change these)
#define PCM_PENUP					0x00000001L	// stop on penup
#define PCM_RANGE					0x00000002L	// stop on leaving range
#define PCM_INVERT				0x00000020L	// stop on tap of opposite end
#define PCM_RECTEXCLUDE			0x00002000L	// click in exclude rect
#define PCM_RECTBOUND			0x00004000L	// click outside bounds rect
#define PCM_TIMEOUT				0x00008000L	// no activity for timeout ms
// new for 2.0:
#define PCM_RGNBOUND				0x00010000L   // click outside the bounding region
#define PCM_RGNEXCLUDE			0x00020000L   // click in exclude region
#define PCM_DOPOLLING			0x00040000L   // polling mode
#define PCM_TAPNHOLD				0x00080000L   // check for Tap And Hold
#define PCM_VERMASK				0x70000000L   
#define PCM_ADDDEFAULTS			RC_LDEFAULTFLAGS /* 0x80000000L */

// Denotes the ID of the current packet
#define PID_CURRENT     (UINT)(-1)

#endif /*!NOPENDRIVER */


//---------------------------------------------------------------------------
#ifndef NOPENGEST

// Gesture Mapping aliases:
#define MAP_GESTOGES				(RCRT_GESTURE|RCRT_GESTURETRANSLATED)
#define MAP_GESTOVKEYS			(RCRT_GESTURETOKEYS|RCRT_ALREADYPROCESSED)
#endif /*!NOPENGEST */


//---------------------------------------------------------------------------
#ifndef NOPENHRC
#define APIREVIEWTODO		// define to use APIs after April review TODO 

#ifndef IX_LAST
#define IX_LAST					(0xffff)	// means last available index
#endif //!IX_LAST

#ifndef IX_END
#define IX_END						0xFFFF	// means to or past last available index
#endif //!IX_END

// Handwriting Recognizer:

// inkset returns:
#define ISR_ERROR					(-1)		// Memory or other error
#define ISR_BADINKSET			(-2)		// bad source inkset
#define ISR_BADINDEX				(-3)		// bad inkset index

// General HRC API return values (HRCR_xx):
#define HRCR_NORESULTS			4			// No possible results  to be found
#define HRCR_COMPLETE			3			// finished recognition
#define HRCR_GESTURE				2			// recognized gesture
#define HRCR_OK					1			// success
#define HRCR_INCOMPLETE			0			// recognizer is processing input
#define HRCR_ERROR				(-1)		// invalid param or unspecified error
#define HRCR_MEMERR				(-2)		// memory error
#define HRCR_INVALIDGUIDE		(-3)		// invalid GUIDE struct
#define HRCR_INVALIDPNDT		(-4)		// invalid pendata
#define HRCR_UNSUPPORTED		(-5)		// recognizer does not support feature
#define HRCR_CONFLICT			(-6)		// training conflict
#define HRCR_NA					(-7)		// function not available

// ProcessHRC time constants:
#define PH_MAX						0xFFFFFFFFL	// recognize rest of ink
#ifdef APIREVIEWTODO
#define PH_DEFAULT				0xFFFFFFFEL	// reasonable time
#define PH_MIN						0xFFFFFFFDL	// minimum time

#else
#define PH_DEFAULT				55L
#define PH_MIN						10L
#endif //APIREVIEWTODO

// CombineHMACRO options:
#define CH_OR						0			// union
#define CH_COPY					1			// copy of h1 only
#define CH_AND						2			// overlap (intersection) 
#define CH_DIFF					3			// in h1 that are not in h2
#define CH_XOR						4			// union but remove overlap

// SetCoercionHMACRO options:
#define SCH_NONE					0			// turn off coercion
#define SCH_REJECT				1			// recog results rejected if no match
#define SCH_ADVISE				2			// macro is hint only
#define SCH_FORCE					3			// some result is forced from macro

// CreateWordListHMACRO options:
#define CWLH_STRINGS				0			// WL from array of strings
#define CWLH_FILE					1			// WL from ANSI file, one per line

// SetScriptHR/E/C options:
#define SSH_RD						1			// to right and down (English)
#define SSH_RU						2			// to right and up
#define SSH_LD						3			// to left and down (Hebrew)
#define SSH_LU						4			// to left and up
#define SSH_DL						5			// down and to the left (Chinese)
#define SSH_DR						6			// down and to the right (Chinese)
#define SSH_UL						7			// up and to the left
#define SSH_UR						8			// up and to the right

// TrainHREC options:
#define TH_QUERY					0			// query the user if conflict
#define TH_FORCE					1			// ditto no query
#define TH_SUGGEST				2			// abandon training if conflict


#endif /*!NOPENHRC */

//---------------------------------------------------------------------------
#ifndef NOPENIEDIT

// Ink Edit Control (IEdit) definitions
// IEdit Notifications
#define IN_PDEVENT		((IEN_PDEVENT<<8)|0)	// pointing device event occurred
#define IN_ERASEBKGND	((IEN_NULL<<8)|1)		// control needs bkgnd erased
#define IN_PREPAINT		((IEN_PAINT<<8)|2)	// before control paints its ink
#define IN_PAINT			((IEN_NULL<<8)|3)		// control needs to be painted
#define IN_POSTPAINT		((IEN_PAINT<<8)|4)	// after control has painted
//								((IEN_NULL<<8)|5)		// unused
#define IN_CHANGE			((IEN_EDIT<<8)|6)		// contents changed & painted
#define IN_UPDATE			((IEN_EDIT<<8)|7)		// contents changed & !painted
#define IN_SETFOCUS		((IEN_FOCUS<<8)|8)	// IEdit is getting focus
#define IN_KILLFOCUS		((IEN_FOCUS<<8)|9)	// IEdit is losing focus
#define IN_MEMERR			((IEN_NULL<<8)|10)	// Memory error
#define IN_HSCROLL		((IEN_SCROLL<<8)|11)	// horz scrolled, not painted
#define IN_VSCROLL		((IEN_SCROLL<<8)|12)	// vert scrolled, not painted
#define IN_GESTURE		((IEN_EDIT<<8)|13)	// user has gestured on control
#define IN_COMMAND		((IEN_EDIT<<8)|14)	// command selected from menu
#define IN_CLOSE			((IEN_NULL<<8)|15)	// I-Edit is being closed

// IEdit Return Values
#define IER_OK						0			// success
#define IER_NO						0			// ctl cannot do request
#define IER_YES					1			// ctl can do request
#define IER_ERROR					2			// unspecified error; operation failed
#define IER_LPARAM				3			// bogus lParam value, bad handle, etc
#define IER_MEMERR				4			// memory error
#define IER_SECURITY				5			// security protection disallows action
#define IER_SELECTION			6			// nothing selected in control
#define IER_NOCOMMAND			7			// tried IE_GETCOMMAND w/no command
#define IER_NOGESTURE			8			// tried IE_GETGESTURE w/no gesture
#define IER_NOPDEVENT			9			// tried IE_GETPDEVENT when no event
#define IER_ZOOM2BIG				10			// tried to zoom larger than ctl rect
#define IER_OWNERDRAW			11			// can't set drawopts in ownerdraw ctl
#define IER_NOTINPAINT			12			// tried IE_GETPAINTSTRUCT when no paint
#define IER_SCALE					13			// merge:  incompatible scaling factors
#define IER_NOMENU				14			// tried IE_GETMENU w/no menu
#define IER_NA						15			// function not available


// IEdit	Notification Bits
#define IEN_NULL					0x0000	// null notification
#define IEN_PDEVENT				0x0001	// notify about pointing device events
#define IEN_PAINT					0x0002	// send painting-related notifications
#define IEN_FOCUS					0x0004	// send focus-related notifications
#define IEN_SCROLL				0x0008	// send scrolling notifications
#define IEN_EDIT					0x0010	// send editing/change notifications
#define IEN_RESERVED				0xFFE0	// reserved

// IEdit Background Options
#define IEB_DEFAULT				0			// default (use COLOR_WINDOW)
#define IEB_BRUSH					1			// paint background with brush
#define IEB_BIT_UL				2			// bitmap, upper-left aligned
#define IEB_BIT_CENTER			3			// bitmap, centered in control
#define IEB_BIT_TILE				4			// bitmap, tiled repeatedly in ctl
#define IEB_BIT_STRETCH			5			// bitmap, stretched to fit ctl
#define IEB_OWNERDRAW			6			// parent window will draw background
#define IEB_LAST					6			// last used value

// IEdit Security Options
#define IESEC_NOCOPY				0x0001	// copying disallowed
#define IESEC_NOCUT				0x0002	// cutting disallowed
#define IESEC_NOINKDISP			0x0004	// ink erased as it is entered
#define IESEC_NOINK				0x0008	// inking disallowed
#define IESEC_NOERASE			0x0010	// erasing disallowed
#define IESEC_NOPASTE			0x0020	// pasting disallowed
#define IESEC_NOGET				0x0040	// IE_GETINK message verboten
#define IESEC_NOSET				0x0080	// IE_SETINK message verboten
#define IESEC_NOUNDO				0x0100	// can't undo
#define IESEC_RESERVED			0xFE00	// reserved

// IEdit Drawing Options
#define IEDO_NONE					0x0000	// no drawing
#define IEDO_AS_INKED			0x0064	// ink drawn as it was inked
#define IEDO_FAST					0x07FF	// ink drawn as fast as possible (def)
#define IEDO_PCTMASK				0x07FF	// mask for percentage draw speed
#define IEDO_SKIP_UPSTROKES	0x1000	// skip upstrokes for timed draws
#define IEDO_CYCLE				0x2000	// bit indicating paint repeatedly
#define IEDO_OPTMASK				0xF000	// mask for draw option bits
#define IEDO_RESERVED			0xC800	// reserved bits

// IEdit Input Options
#define IEI_MOVE					0x0001	// move ink into ctl
#define IEI_RESIZE				0x0002	// resize ink to fit within ctl
#define IEI_CROP					0x0004	// discard ink outside of ctl
#define IEI_DISCARD				0x0008	// discard all ink if any outside ctl	
#define IEI_RESERVED				0xFFF0	// reserved

// IEdit Recognition Options
#define IEREC_NONE				0x0000	// No recognition
#define IEREC_GESTURE			0x0001	// Gesture recognition
#define IEREC_ALL					(IEREC_GESTURE)
#define IEREC_RESERVED			0xFFFE	// Reserved

// IEdit IE_SETINK options
#define IESI_REPLACE				0			// replace ink in control
#define IESI_APPEND				1			// append ink to existing control ink

// IEdit IE_GETINK options
#define IEGI_ALL					0			// get all ink from control
#define IEGI_SELECTION			1			// get selected ink from control

// IEdit IE_SETFORMAT/IE_GETFORMAT options
#define IESF_ALL					0x0001	// set/get stk fmt of all ink
#define IESF_SELECTION			0x0002	// set/get stk fmt of selected ink
#define IESF_STROKE				0x0004	// set/get stk fmt of specified stroke
//
#define IESF_TIPCOLOR			0x0008	// set color
#define IESF_TIPWIDTH			0x0010	// set width
#define IESF_PENTIP				(IESF_TIPCOLOR|IESF_TIPWIDTH)


// IEdit IE_SETZOOM options
#define IESZ_TOFIT				0			// zoom I-Edit to fit in client area

#endif /*!NOPENIEDIT */


//---------------------------------------------------------------------------
#ifndef NOPENINKPUT

// PenIn[k]put API constants

// Inkput:
#define PCMR_OK						0
#define PCMR_ALREADYCOLLECTING	(-1)
#define PCMR_INVALIDCOLLECTION	(-2)
#define PCMR_EVENTLOCK				(-3)
#define PCMR_INVALID_PACKETID		(-4)

#define PCMR_TERMTIMEOUT			(-5)
#define PCMR_TERMRANGE				(-6)
#define PCMR_TERMPENUP				(-7)
#define PCMR_TERMEX					(-8)
#define PCMR_TERMBOUND				(-9)
#define PCMR_APPTERMINATED			(-10)

#define PCMR_TAPNHOLD_LAST       (-11)
#define PCMR_TAP                 (-11)	// alias PCMR_TAPNHOLD_LAST
#define PCMR_SELECT              (-12)
#define PCMR_TAPNHOLD_FIRST      (-12)	// currently PCMR_SELECT

#define PCMR_OVERFLOW            (-13)
#define PCMR_ERROR               (-14)	// parameter or unspecified error
#define PCMR_DISPLAYERR				(-15)	// inking only
#define PCMR_NA						(-16)	// not available


#define PIT_RGNBOUND					0x0001
#define PIT_RGNEXCLUDE				0x0002
#define PIT_TIMEOUT					0x0004
#define PIT_TAPNHOLD					0x0008

#define PII_INKCLIPRECT				0x0001
#define PII_INKSTOPRECT				0x0002
#define PII_INKCLIPRGN				0x0004
#define PII_INKSTOPRGN				0x0008
#define PII_INKPENTIP				0x0010
#define PII_SAVEBACKGROUND			0x0020
#define PII_CLIPSTOP             0x0040

// Default Processing
#define LRET_DONE						1L
#define LRET_ABORT					(-1L)
#define LRET_HRC                 (-2L)
#define LRET_HPENDATA            (-3L)
#define LRET_PRIVATE             (-4L)
#endif /*!NOPENINKPUT */


//---------------------------------------------------------------------------
#ifndef NOPENMISC
// GetPenWinFlags() API flags:
#define PWF_KRNL						0x0001	// pen kernel loaded (proforma)
#define PWF_INPUT						0x0002	// pen input system loaded
#define PWF_PEN						0x0004	// pen drv loaded & hdwe init'd
#define PWF_INKDISPLAY				0x0008	// ink-compatible display drv loaded
#define PWF_RECOGNIZER				0x0010	// system recognizer installed
#define PWF_FULL						0x001F	// all elements present

// Get/SetPenMiscInfo:
// PMI_RCCHANGE is for WM_GLOBALRCCHANGE compatability only:
#define PMI_RCCHANGE					0	// invalid for Get/SetPenMiscInfo

#define PMI_BEDIT						1	// boxed edit info
#define PMI_IMECOLOR             2	// input method editor color
#define PMI_CXTABLET					3	// tablet width
#define PMI_CYTABLET					4	// tablet height
#define PMI_COUNTRY					5	// country
#define PMI_PENTIP					6	// pen tip: color, width, nib
#define PMI_LENS						7	// popup letter guides enabling
#define PMI_TIMEOUT					8	// handwriting timeout
#define PMI_TIMEOUTGEST				9	// gesture timeout
#define PMI_TIMEOUTSEL				10	// press&hold timieout
#define PMI_SYSFLAGS					11	// load configuration
#define PMI_INDEXFROMRGB			12	// color table index from RGB
#define PMI_RGBFROMINDEX			13	// RGB from color table index

#define PMI_SAVE						0x1000	// save setting to file


#ifdef KANJI
#define	SPMI_OK						0L
#define	SPMI_INVALIDBOXEDITINFO		1L
#define	SPMI_INIERROR				2L
#define	SPMI_INVALIDPMI				0x8000L

#define	GPMI_OK						0L
#define	GPMI_INVALIDPMI				0x8000L
#endif // KANJI

#define PMIR_OK						0L
#define PMIR_INDEX					(-1L)
#define PMIR_VALUE					(-2L)
#define PMIR_INVALIDBOXEDITINFO	(-3L)
#define PMIR_INIERROR				(-4L)
#define PMIR_ERROR					(-5L)

#endif /*!NOPENMISC */


//---------------------------------------------------------------------------
#ifndef NOPENRC1

// RC Options and Flags:
// generic defaults:
#define RC_WDEFAULT				0xFFFF
#define RC_LDEFAULT				0xFFFFFFFFL
#define RC_WDEFAULTFLAGS		0x8000
#define RC_LDEFAULTFLAGS		0x80000000L

// RegisterPenApp() API constants:
#define RPA_HEDIT					0x0001	// convert EDIT to HEDIT
#define RPA_KANJIFIXEDBEDIT	0x0002
#define RPA_DBCSPRIORITY		0x0004	// assume DBCS has priority (Japan)
#define RPA_DEFAULT				0x0001	// == RPA_HEDIT

// RC Definitions:
#define CL_NULL					0
#define CL_MINIMUM				1			// minimum confidence level
#define CL_MAXIMUM				100		// max (require perfect recog)
#define INKWIDTH_MINIMUM		0			// 0 invisible, 1..15 pixel widths
#define INKWIDTH_MAXIMUM		15			// max width in pixels
#define ENUM_MINIMUM				1
#define ENUM_MAXIMUM				4096
#define MAXDICTIONARIES			16			// rc.rglpdf[MAXDICTIONARIES]
#define cbRcLanguageMax			44			// rc.lpLanguage[cbRcLanguageMax]
#define cbRcUserMax				32			// rc.lpUser[cbRcUserMax]
#define cbRcrgbfAlcMax			32			// rc.rgbfAlc[cbRcrgbfAlcMax]
#define cwRcReservedMax			8			// rc.rgwReserved[cwRcReservedMax]
#define MAXHOTSPOT				8			// syg.rgpntHotSpots[MAXHOTSPOT]

// RCRESULT wResultsType values:
#define RCRT_DEFAULT				0x0000	// normal ret
#define RCRT_UNIDENTIFIED		0x0001 	// result contains unidentified results
#define RCRT_GESTURE				0x0002	// result is a gesture
#define RCRT_NOSYMBOLMATCH		0x0004	// nothing recognized (no ink match)
#define RCRT_PRIVATE				0x4000	// recognizer-specific symbol
#define RCRT_NORECOG				0x8000	// no recog attempted, only data ret
#define RCRT_ALREADYPROCESSED	0x0008	// GestMgr hooked it
#define RCRT_GESTURETRANSLATED 0x0010	// GestMgr translated it to ANSI value
#define RCRT_GESTURETOKEYS		0x0020	// ditto to set of virtual keys

// RC Options:
#define RCO_NOPOINTEREVENT		0x00000001L	// no recog tap, tap/hold
#define RCO_SAVEALLDATA			0x00000002L	// save pen data like upstrokes
#define RCO_SAVEHPENDATA		0x00000004L	// save pen data for app
#define RCO_NOFLASHUNKNOWN		0x00000008L	// no ? cursor on unknown
#define RCO_TABLETCOORD			0x00000010L	// tablet coords used in RC
#define RCO_NOSPACEBREAK		0x00000020L	// no space break recog -> dict
#define RCO_NOHIDECURSOR		0x00000040L	// display cursor during inking
#define RCO_NOHOOK				0x00000080L	// disallow ink hook (passwords)
#define RCO_BOXED					0x00000100L	// valid rc.guide provided
#define RCO_SUGGEST				0x00000200L	// for dict suggest
#define RCO_DISABLEGESMAP		0x00000400L	// disable gesture mapping
#define RCO_NOFLASHCURSOR		0x00000800L	// no cursor feedback
#define RCO_BOXCROSS				0x00001000L	// show + at boxedit center
#define RCO_COLDRECOG			0x00008000L	// result is from cold recog
#define RCO_SAVEBACKGROUND		0x00010000L   // Save background from ink
#define RCO_DODEFAULT			0x00020000L   // do default gesture processing

// RC Direction:
#define RCD_DEFAULT				0			// def none
#define RCD_LR						1			// left to right like English
#define RCD_RL						2			// right to left like Arabic
#define RCD_TB						3			// top to bottom like Japanese
#define RCD_BT						4			// bottom to top like some Chinese

// RC Preferences:
#define RCP_LEFTHAND				0x0001	// left handed input
#define RCP_MAPCHAR				0x0004	// fill in syg.lpsyc (ink) for training

// RC Orientation of Tablet:
#define RCOR_NORMAL				1			// tablet not rotated
#define RCOR_RIGHT				2			// rotated 90 deg anticlockwise
#define RCOR_UPSIDEDOWN			3			// rotated 180 deg
#define RCOR_LEFT					4			// rotated 90 deg clockwise

// RC Result Return Mode specification:
#define RRM_STROKE				0			// return results after each stroke
#define RRM_SYMBOL				1			// per symbol (e.g. boxed edits)
#define RRM_WORD					2			// on recog of a word
#define RRM_NEWLINE				3			// on recog of a line break
#define RRM_COMPLETE				16		// on PCM_xx specified completion

// RC International Preferences:
#define RCIP_ALLANSICHAR		0x0001	// all ANSI chars
#define RCIP_MASK					0x0001

// misc RC stuff:
#define wPntAll					(UINT)0xFFFF
#define iSycNull					(-1)
#define HKP_SETHOOK				0
#define HKP_UNHOOK				0xFFFF
#define HWR_RESULTS				0
#define HWR_APPWIDE				1
#define LPDFNULL					((LPDF)NULL)

// CorrectWriting() API constants:
#define CWR_STRIPCR				0x00000001L	// strip carriage ret (\r)
#define CWR_STRIPLF				0x00000002L	// strip	linefeed (\n)
#define CWR_STRIPTAB				0x00000004L	// strip tab (\t)
#define CWR_SINGLELINEEDIT		0x00000007L	// all of the above
#define CWR_TITLE					0x00000010L	// interp dwReserved as LPSTR
#define CWR_KKCONVERT			0x00000020L	// JPN initiate IME
#define CWR_SIMPLE				0x00000040L	// do simple dialog (lens)
#define CWR_HEDIT					0x00000080L   // lens for hedits
#define CWR_TEXTWINDOW			0x00000100L   // lens for standard text windows

// GetGlobalRC() API return codes:
#define GGRC_OK					0			// no err
#define GGRC_DICTBUFTOOSMALL	1			// lpDefDict buffer too small for path
#define GGRC_PARAMERROR			2			// invalid params: call ignored
#define GGRC_NA					3			// function not available

// SetGlobalRC() API return code flags:
#define SGRC_OK					0x0000	// no err
#define SGRC_USER					0x0001	// invalid User name
#define SGRC_PARAMERROR			0x0002	// param error: call ignored
#define SGRC_RC					0x0004	// supplied RC has errors
#define SGRC_RECOGNIZER			0x0008	// DefRecog name invalid
#define SGRC_DICTIONARY			0x0010	// lpDefDict path invalid
#define SGRC_INIFILE				0x0020	// error saving to penwin.ini
#define SGRC_NA					0x8000	// function not available

#endif /*!NOPENRC1 */


//---------------------------------------------------------------------------
#ifndef NOPENRECOG

// Recognition Error Codes/Returns:
#define REC_OEM					(-1024)	// first recognizer-specific debug val
#define REC_LANGUAGE				(-48)	// unsupported language field
#define REC_GUIDE					(-47)	// invalid GUIDE struct
#define REC_PARAMERROR			(-46)	// bad param
#define REC_INVALIDREF			(-45)	// invalid data ref param
#define REC_RECTEXCLUDE			(-44)	// invalid rect
#define REC_RECTBOUND			(-43)	// invalid rect
#define REC_PCM					(-42)	// invalid lPcm parameter
#define REC_RESULTMODE			(-41)
#define REC_HWND					(-40)	// invalid window to send results to
#define REC_ALC					(-39)	// invalid enabled alphabet
#define REC_ERRORLEVEL			(-38)	// invalid errorlevel
#define REC_CLVERIFY				(-37)	// invalid verification level
#define REC_DICT					(-36)	// invalid dict params
#define REC_HREC					(-35)	// invalid recognition handle
#define REC_BADEVENTREF			(-33)	// invalid wEventRef
#define REC_NOCOLLECTION		(-32)	// collection mode not set
#define REC_DEBUG					(-32)   // beginning of debug values
#define REC_POINTEREVENT		(-31)	// tap or tap&hold event
#define REC_BADHPENDATA			(-9)    // invalid hpendata header or locking
#define REC_OOM					(-8)		// out of memory error
#define REC_NOINPUT				(-7)		// no data collected before termination
#define REC_NOTABLET				(-6)		// tablet not physically present
#define REC_BUSY					(-5)		// another task is using recognizer
#define REC_BUFFERTOOSMALL		(-4)		// ret by GetPenHwEventData()
#define REC_ABORT					(-3)		// recog stopped by EndPenCollection()
#define REC_NA						(-2)		// function not available
#define REC_OVERFLOW				(-1)		// data overflow
#define REC_OK						0			// interrim completion
#define REC_TERMBOUND			1			// hit outside bounding rect
#define REC_TERMEX				2			// hit inside exclusion rect
#define REC_TERMPENUP			3			// pen up
#define REC_TERMRANGE			4			// pen left proximity
#define REC_TERMTIMEOUT			5			// no writing for timeout ms
#define REC_DONE					6			// normal completion
#define REC_TERMOEM				512		// first recognizer-specific retval
#endif /*!NOPENRECOG */


//---------------------------------------------------------------------------
#ifndef NOPENSYV

// SYV classes:
#define SYVHI_SPECIAL			0
#define SYVHI_ANSI				1
#define SYVHI_GESTURE			2
#define SYVHI_KANJI				3
#define SYVHI_SHAPE				4
#define SYVHI_UNICODE			5
#define SYVHI_VKEY				6

// special SYV values:
#define SYV_NULL					0x00000000L
#define SYV_UNKNOWN				0x00000001L
#define SYV_EMPTY					0x00000003L
#define SYV_BEGINOR				0x00000010L
#define SYV_ENDOR					0x00000011L
#define SYV_OR						0x00000012L
#define SYV_SOFTNEWLINE			0x00000020L
#define SYV_SPACENULL			0x00010000L	// SyvCharacterToSymbol('\0')

// SYV values for gestures:
#define SYV_SELECTFIRST			0x0002FFC0L   // . means tap in following
#define SYV_LASSO					0x0002FFC1L   // lasso o.
#define SYV_SELECTLEFT			0x0002FFC2L   // left text/anchor L.
#define SYV_SELECTRIGHT			0x0002FFC3L   // right text/extend J.
#define SYV_SELECTLAST			0x0002FFCFL   // 16 SYVs reserved for selection

#define SYV_CLEARCHAR			0x0002FFD2L   // pigtail
#define SYV_HELP					0x0002FFD3L   // ?.
#define SYV_KKCONVERT			0x0002FFD4L   // k.
#define SYV_CLEAR					0x0002FFD5L   // x.
#define SYV_INSERT				0x0002FFD6L   // ^.
#define SYV_CONTEXT				0x0002FFD7L   // 1.
#define SYV_EXTENDSELECT		0x0002FFD8L   // J. compatability
#define SYV_UNDO					0x0002FFD9L   // u.
#define SYV_COPY					0x0002FFDAL   // c.
#define SYV_CUT					0x0002FFDBL   // compatability
#define SYV_PASTE					0x0002FFDCL   // p.
#define SYV_CLEARWORD			0x0002FFDDL   // scratchout.
#define SYV_USER					0x0002FFDEL   // reserved
#define SYV_CORRECT				0x0002FFDFL   // e.

#define SYV_BACKSPACE			0x00020008L   // compatability
#define SYV_TAB					0x00020009L   // compatability
#define SYV_RETURN				0x0002000DL   // n. or r.
#define SYV_SPACE					0x00020020L   // s.

// Application specific gestures, Circle a-z and Circle A-Z:
#define SYV_APPGESTUREMASK		0x00020000L
#define SYV_CIRCLEUPA			0x000224B6L		// map into Unicode space
#define SYV_CIRCLEUPZ			0x000224CFL		// 	for circled letters
#define SYV_CIRCLELOA			0x000224D0L
#define SYV_CIRCLELOZ			0x000224E9L

// Gesture sets for EnableGestureSetHRC (bit flags):
#define GST_SEL					0x00000001L		// sel & lasso
#define GST_CLIP					0x00000002L		// cut copy paste
#define GST_WHITE					0x00000004L		// sp bs tab ret
#define GST_DEL					0x00000008L		// clear clearword
#define GST_EDIT					0x00000010L		// insert correct undo
#define GST_SYS					0x0000001FL		// all of the above
#define GST_CIRCLELO				0x00000100L		// lowercase circle
#define GST_CIRCLEUP				0x00000200L		// uppercase circle
#define GST_CIRCLE				0x00000300L		// all circle
#define GST_ALL					0x0000031FL		// all of the above

// SYV definitions for shapes:
#define SYV_SHAPELINE			0x00040001L
#define SYV_SHAPEELLIPSE		0x00040002L
#define SYV_SHAPERECT			0x00040003L
#define SYV_SHAPEMIN				SYV_SHAPELINE	// alias
#define SYV_SHAPEMAX				SYV_SHAPERECT	// alias
#endif /*!NOPENSYV */


//---------------------------------------------------------------------------
#ifndef NOPENTARGET

#define TPT_CLOSEST				0x0001   // Assign to the closest target   
#define TPT_INTERSECTINK		0x0002   // target with intersecting ink
#define TPT_TEXTUAL				0x0004   // apply textual heuristics
#define TPT_DEFAULT				(TPT_TEXTUAL | TPT_INTERSECTINK | TPT_CLOSEST)

#endif /*!NOPENTARGET */


//---------------------------------------------------------------------------
#ifndef NOPENVIRTEVENT

// Virtual Event Layer:
#define VWM_MOUSEMOVE			0x0001
#define VWM_MOUSELEFTDOWN		0x0002
#define VWM_MOUSELEFTUP			0x0004
#define VWM_MOUSERIGHTDOWN		0x0008
#define VWM_MOUSERIGHTUP		0x0010
#endif /*!NOPENVIRTEVENT */


/****** Messages and Defines ************************************************/

// Windows Messages WM_PENWINFIRST (0x0380) and WM_PENWINLAST (0x038F)
// are defined in windows.h and winmin.h


//---------------------------------------------------------------------------
#ifndef NOPENMSGS

#ifndef NOPENRECOG
#define WM_RCRESULT				(WM_PENWINFIRST+1)	// 0x381
#define WM_HOOKRCRESULT			(WM_PENWINFIRST+2)	// 0x382
#endif /*!NOPENRECOG */

#define WM_PENMISCINFO			(WM_PENWINFIRST+3)	// 0x383
#define WM_GLOBALRCCHANGE		(WM_PENWINFIRST+3)	// alias

#ifndef NOPENAPPS
#define WM_SKB						(WM_PENWINFIRST+4)	// 0x384
#endif /*!NOPENAPPS */

#define WM_PENCTL					(WM_PENWINFIRST+5)	// 0x385
#define WM_HEDITCTL				(WM_PENWINFIRST+5)	// FBC: alias
#define WM_IEDITCTL				(WM_PENWINFIRST+5)	// FBC: alias

// WM_HEDITCTL (WM_PENCTL) wParam options:
#define HE_GETRC					3		// FBC: get RC from HEDIT/BEDIT control
#define HE_SETRC					4		// FBC: ditto set
#define HE_GETINFLATE			5		// FBC: get inflate rect
#define HE_SETINFLATE			6		// FBC: ditto set
#define HE_GETUNDERLINE		 	7		// get underline mode
#define HE_SETUNDERLINE		 	8		// ditto set
#define HE_GETINKHANDLE		 	9		// get handle to captured ink
#define HE_SETINKMODE			10		// begin HEDIT cold recog mode
#define HE_STOPINKMODE			11		// end cold recog mode
#define HE_GETRCRESULTCODE	 	12		// FBC: get result of recog after HN_ENDREC
#define HE_DEFAULTFONT			13		// switch BEDIT to def font
#define HE_CHARPOSITION		 	14		// BEDIT byte offset -> char position
#define HE_CHAROFFSET			15		// BEDIT char position -> byte offset
#define HE_GETBOXLAYOUT		 	20		// get BEDIT layout
#define HE_SETBOXLAYOUT		 	21		// ditto set
#define HE_GETRCRESULT			22		// FBC: get RCRESULT after HN_RCRESULT
#define HE_KKCONVERT			 	30		// JPN start kana-kanji conversion
#define HE_GETKKCONVERT		 	31		// JPN get KK state
#define HE_CANCELKKCONVERT	 	32		// JPN cancel KK conversion
#define HE_FIXKKCONVERT		 	33		// JPN force KK result
#define HE_ENABLEALTLIST		40		// en/disable dropdown recog alt's
#define HE_SHOWALTLIST			41		// show dropdown (assume enabled)
#define HE_HIDEALTLIST			42		// hide dropdown alternatives

//------------------------------
#ifndef NOPENIEDIT

// WM_IEDITCTL (WM_PENCTL) wParam options:
#define IE_CANUNDO				100		// queries whether IEdit can do undo
#define IE_DOCOMMAND				101		// send command to IEdit
#define IE_EMPTYUNDOBUFFER		102		// clears IEdit's undo buffer
#define IE_GETAPPDATA			103		// gets the user-defined datum
#define IE_GETBKGND				104		// gets the background painting options
#define IE_GETCOMMAND			105		// gets particulars of user command
#define IE_GETCOUNT				106		// gets count of strokes in I-Edit
#define IE_GETDRAWOPTS			107		// gets the ink (re)painting options
#define IE_GETERASERTIP			108		// gets the current eraser pentip
#define IE_GETFORMAT				109		// gets format of stroke(s)
#define IE_GETGESTURE			110		// gets details on user gesture
#define IE_GETGRID				111		// gets the background grid
#define IE_GETINK					112		// gets ink from the control
#define IE_GETMENU				113		// gets handle to Iedit's pop-up menu
#define IE_GETMODIFY				114		// gets the modification (dirty) bit
#define IE_GETNOTIFY				115		// gets the notification bits
#define IE_GETPAINTDC			116		// gets the HDC for the Iedit
#define IE_GETPDEVENT			117		// gets details of last mouse/pen event
#define IE_GETPENTIP				118		// gets the current default ink pentip
#define IE_GETRECOG				119		// gets recognition options
#define IE_GETSECURITY			120		// gets the security options
#define IE_GETSEL					121		// gets selection status of a stroke
#define IE_GETSELCOUNT			122		// gets count of selected strokes
#define IE_GETSELITEMS			123		// gets indices of all selected strokes
#define IE_GETSTYLE				124		// gets IEdit control styles
#define IE_GETZOOM				125		// gets the zoom factor of the window
#define IE_SETAPPDATA			126		// sets the user-defined data area
#define IE_SETBKGND				127		// sets the background painting options
#define IE_SETDRAWOPTS			128		// sets the ink (re)painting options
#define IE_SETERASERTIP			129		// sets the current eraser pentip
#define IE_SETFORMAT				130		// sets format of stroke(s)
#define IE_SETGRID				131		// sets the background grid
#define IE_SETINK					132		//	sets the ink into the control
#define IE_SETMODIFY				133		// sets the modification (dirty) bit
#define IE_SETNOTIFY				134		// sets the notification bits
#define IE_SETPENTIP				135		// sets the current default ink pentip
#define IE_SETRECOG				136		// sets recognition options
#define IE_SETSECURITY			137		// sets the security options
#define IE_SETSEL					138		// sets selection status of a stroke
#define IE_SETSTYLE				139		// sets IEdit control styles
#define IE_SETZOOM				140		// sets the zoom factor of the window

#define IE_YUKMODE				199		// yuk--sets modes in I-Edit
#endif /*!NOPENIEDIT */

// JPN KanaKanji conversion subfunctions:
#define HEKK_DEFAULT				0			// def
#define HEKK_CONVERT				1			// convert in place
#define HEKK_CANDIDATE			2			// start conversion dialog

// HE_STOPINKMODE (stop cold recog) options:
#define HEP_NORECOG				0			// don't recog ink
#define HEP_RECOG					1			// recog ink
#define HEP_WAITFORTAP			2			// recog after tap in window

// WM_PENCTL notifications:
#define HN_ENDREC					4			// recog complete
#define HN_DELAYEDRECOGFAIL	5			// HE_STOPINKMODE (cold recog) failed
#define HN_RCRESULT				20			// HEDIT/BEDIT has an RCRESULT
#define HN_ENDKKCONVERT			30			// JPN KK conversion complete
#define HN_SELCHANGE				40			// bedit selection changed

//------------------------------
#ifndef NOPENBEDIT

// Boxed Edit Control:
// box edit alternative list:
#define HEAL_DEFAULT				-1L     // AltList def value for lParam

// box edit Info:
#define BEI_FACESIZE				32		// max size of font name, = LF_FACESIZE
#define BEIF_BOXCROSS			0x0001

// box edit size:
#define BESC_DEFAULT				0
#define BESC_ROMANFIXED			1
#define BESC_KANJIFIXED			2
#define BESC_USERDEFINED		3

#define BXD_CELLWIDTH          12
#define BXD_CELLHEIGHT         16
#define BXD_BASEHEIGHT         13
#define BXD_BASEHORZ           0
#define BXD_MIDFROMBASE        0
#define BXD_CUSPHEIGHT         2
#define BXD_ENDCUSPHEIGHT      4

#define BXDK_CELLWIDTH			32
#define BXDK_CELLHEIGHT			32
#define BXDK_BASEHEIGHT			28
#define BXDK_BASEHORZ			0
#define BXDK_MIDFROMBASE		0
#define BXDK_CUSPHEIGHT			28
#define BXDK_ENDCUSPHEIGHT		10

// IME colors for bedit
#define COLOR_BE_INPUT			   0 
#define COLOR_BE_INPUT_TEXT		1 
#define COLOR_BE_CONVERT		   2 
#define COLOR_BE_CONVERT_TEXT	   3 
#define COLOR_BE_CONVERTED		   4 
#define COLOR_BE_CONVERTED_TEXT	5 
#define COLOR_BE_UNCONVERT	      6 
#define COLOR_BE_UNCONVERT_TEXT	7 
#define COLOR_BE_CURSOR			   8 
#define COLOR_BE_CURSOR_TEXT	   9 
#define MAXIMECOLORS			      10

#endif /*!NOPENBEDIT */

// ComboBox notification extensions:
#define CBN_ENDREC				16
#define CBN_DELAYEDRECOGFAIL	17
#define CBN_RCRESULT				18


#define WM_PENMISC				(WM_PENWINFIRST+6)	// 0x386

// WM_PENMISC message constants:
#define PMSC_BEDITCHANGE		1	// broadcast when BEDIT changes
#define PMSC_PENUICHANGE		2	// JPN broadcast when PENUI changes
#define PMSC_SUBINPCHANGE		3	// JPN broadcast when SUBINPUT changes
#define PMSC_KKCTLENABLE		4	// JPN
#define PMSC_GETPCMINFO			5	// query the window's PCMINFO
#define PMSC_SETPCMINFO			6	// set the window's PCMINFO
#define PMSC_GETINKINGINFO		7	// query the window's INKINGINFO
#define PMSC_SETINKINGINFO		8	// set the window's INKINGINFO
#define PMSC_GETHRC				9	// query the window's HRC
#define PMSC_SETHRC				10	// set the window's HRC
#define PMSC_GETHRCRESULT		11	// get the window's HRCRESULT
#define PMSC_SETHRCRESULT		12	// set the window's HRCRESULT
#define PMSC_TARGETING			13	// query smart targeting properties of a window
#define PMSC_AREAGESTURE		14	// OBSOLETE TODO
#define PMSC_LOADPW				15	// broadcast load state on penwin
#define PMSC_INKSTOP				16	// 

// PMSCL_xx lParam values for PMSC_xx:
#define PMSCL_UNLOADED			0L	// penwin just unloaded
#define PMSCL_LOADED				1L	// penwin just loaded
#define PMSCL_UNLOADING			2L	// penwin about to unload

// PMSC_TARGETING submessage return values (can be OR'd)
#define PMSCR_TARGETABLE		0x0001	// the window is smart targetable
#define PMSCR_INKSTOP    		0x0002	// the window wants PE_PENDOWN messages



#define WM_CTLINIT				(WM_PENWINFIRST+7)	// 0x387

// WM_CTLINIT message constants:
#define CTLINIT_MSGBOX			0
#define CTLINIT_EDIT				1
#define CTLINIT_LISTBOX			2
#define CTLINIT_BTN				3
#define CTLINIT_DLG				4
#define CTLINIT_SCROLLBAR		5
#define CTLINIT_STATIC			6
#define CTLINIT_BEDIT			7
#define CTLINIT_COMBOBOX		8
#define CTLINIT_IEDIT			9
#define CTLINIT_MAX				10


#define WM_PENEVENT				(WM_PENWINFIRST+8)	// 0x388

// WM_PENEVENT message values for wParam:
#define PE_PENDOWN				1			// pen tip down
#define PE_PENUP					2			// pen tip went from down to up
#define PE_MOREPACKETS			3			// Many(TBD) points in buffer without
                                       // a tip transition
#define PE_TERMINATING			4			// Peninput about to terminate
#define PE_TERMINATED			5			// Peninput terminated
#define PE_BUFFERWARNING		6			// Buffer half full.
#define PE_BEGININPUT			7        // begin default input
#define PE_SETTARGETS         8        // set target data structure (TARGINFO)
#define PE_BEGINDATA          9        // init message to all targets
#define PE_MOREDATA           10       // target gets more data
#define PE_ENDDATA            11       // termination message to all targets
#define PE_GETPCMINFO         12       // get input collection info
#define PE_GETINKINGINFO      13       // get inking info
#define PE_ENDINPUT           14       // Input termination message to window
                                       // starting default input 
#endif /*!NOPENMSGS */


/****** Macros **************************************************************/

// misc macros:
//---------------------------------------------------------------------------
#ifndef NOPENDRIVER

#define FPenUpX(x)				((BOOL)(((x) & BITPENUP) != 0))
#define GetWEventRef()			(LOWORD(GetMessageExtraInfo()))
#endif /*!NOPENDRIVER */

//---------------------------------------------------------------------------
#ifndef NOPENSYV

// SYV macros:

#define FIsSpecial(syv)			(HIWORD((syv))==SYVHI_SPECIAL)
#define FIsAnsi(syv)				(HIWORD((syv))==SYVHI_ANSI)
#define FIsGesture(syv)			(HIWORD((syv))==SYVHI_GESTURE)
#define FIsKanji(syv)			(HIWORD((syv))==SYVHI_KANJI)
#define FIsShape(syv)			(HIWORD((syv))==SYVHI_SHAPE)
#define FIsUniCode(syv)			(HIWORD((syv))==SYVHI_UNICODE)
#define FIsVKey(syv)				(HIWORD((syv))==SYVHI_VKEY)

#define ChSyvToAnsi(syv)			((BYTE) (LOBYTE(LOWORD((syv)))))
#define WSyvToKanji(syv)			((UINT) (LOWORD((syv))))
#define SyvCharacterToSymbol(c)	((LONG)(unsigned char)(c) | 0x00010000)
#define SyvKanjiToSymbol(c)		((LONG)(UINT)(c) | 0x00030000)

#define FIsSelectGesture(syv)	\
   ((syv) >= SYVSELECTFIRST && (syv) <= SYVSELECTLAST)

#define FIsStdGesture(syv)		\
   (									\
   FIsSelectGesture(syv)		\
   || (syv)==SYV_CLEAR			\
   || (syv)==SYV_HELP			\
   || (syv)==SYV_EXTENDSELECT	\
   || (syv)==SYV_UNDO			\
   || (syv)==SYV_COPY			\
   || (syv)==SYV_CUT				\
   || (syv)==SYV_PASTE			\
   || (syv)==SYV_CLEARWORD		\
   || (syv)==SYV_KKCONVERT		\
   || (syv)==SYV_USER			\
   || (syv)==SYV_CORRECT		\
   )

#define FIsAnsiGesture(syv)	\
   (									\
   (syv) == SYV_BACKSPACE		\
   || (syv) == SYV_TAB			\
   || (syv) == SYV_RETURN		\
   || (syv) == SYV_SPACE		\
   )
#endif /*!NOPENSYV */

//---------------------------------------------------------------------------
#ifndef NOPENALC

// ALC macros:

#define MpAlcB(lprc,i)			((lprc)->rgbfAlc[((i) & 0xff) >> 3])
#define MpIbf(i)					((BYTE)(1 << ((i) & 7)))
#define SetAlcBitAnsi(lprc,i)	do {MpAlcB(lprc,i) |= MpIbf(i);} while (0)
#define ResetAlcBitAnsi(lprc,i) do {MpAlcB(lprc,i) &= ~MpIbf(i);} while (0)
#define IsAlcBitAnsi(lprc, i)	((MpAlcB(lprc,i) & MpIbf(i)) != 0)
#endif /*!NOPENALC */

//---------------------------------------------------------------------------
#ifndef NOPENGEST

// Gesture Macros:

#define FIsLoAppGesture(syv)	(syv >= SYV_CIRCLELOA && syv <= SYV_CIRCLELOZ)
#define FIsUpAppGesture(syv)	(syv >= SYV_CIRCLEUPA && syv <= SYV_CIRCLEUPZ)
#define FIsAppGesture(syv)		(syv>=SYV_CIRCLEUPA && syv<=SYV_CIRCLELOZ)
#define SyvAppGestureFromLoAnsi(ansi)	((DWORD)(BYTE)ansi- 'a'+SYV_CIRCLELOA)
#define SyvAppGestureFromUpAnsi(ansi)	((DWORD)(BYTE)ansi- 'A'+SYV_CIRCLEUPA)
#define AnsiFromSyvAppGesture(syv)		ChSyvToAnsi( \
	syv-(FIsUpAppGesture(syv)? SYV_CIRCLEUPA-(SYV)'A': SYV_CIRCLELOA-(SYV)'a'))

#define IsGestureToGesture(lprcresult) \
	(((lprcresult)->wResultstype & MAP_GESTOGES) == MAP_GESTOGES)

#define IsGestureToVkeys(lprcresult) \
	(((lprcresult)->wResultstype & MAP_GESTOVKEYS) == MAP_GESTOVKEYS)

#define SetAlreadyProcessed(lprcresult) \
	((lprcresult)->wResultsType = ((lprcresult)->wResultsType \
	& ~RCRT_GESTURETOKEYS) | RCRT_ALREADYPROCESSED)
#endif /*!NOPENGEST */


//---------------------------------------------------------------------------
#ifndef NOPENDATA

// draw 2.0 pendata using internal stroke formats:
#define DrawPenDataFmt(hdc, lprect, hpndt)\
	DrawPenDataEx(hdc, lprect, hpndt, 0, IX_END, 0, IX_END, NULL, 0)

#endif /*!NOPENDATA */

//---------------------------------------------------------------------------
#ifndef NOPENHRC

// Handwriting Recognizer:

// Intervals:
// difference of two absolute times (at2 > at1 for positive result):
#define dwDiffAT(at1, at2)\
	(1000L*((at2).sec - (at1).sec) - (DWORD)((at1).ms + (at2).ms))

// comparison of two absolute times (TRUE if at1 < at2):
#define FLTAbsTime(at1, at2)\
	((at1).sec < (at2).sec || ((at1).sec == (at2).sec && (at1).ms < (at2).ms))

#define FLTEAbsTime(at1, at2)\
	((at1).sec < (at2).sec || ((at1).sec == (at2).sec && (at1).ms <= (at2).ms))

#define FEQAbsTime(at1, at2)\
	((at1).sec == (at2).sec && (at1).ms == (at2).ms)

// test if abstime is within an interval:
#define FAbsTimeInInterval(at, lpi)\
	(FLTEAbsTime((lpi)->atBegin, at) && FLTEAbsTime(at, (lpi)->atEnd))

// test if interval (lpiT) is within an another interval (lpiS):
#define FIntervalInInterval(lpiT, lpiS)\
	(FLTEAbsTime((lpiS)->atBegin, (lpiT)->atBegin)\
	&& FLTEAbsTime((lpiT)->atEnd, (lpiS)->atEnd))

// test if interval (lpiT) intersects another interval (lpiS):
#define FIntervalXInterval(lpiT, lpiS)\
	(!(FLTAbsTime((lpiT)->atEnd, (lpiS)->atBegin)\
	|| FLTAbsTime((lpiS)->atEnd, (lpiT)->atBegin)))

// duration of an LPINTERVAL in ms:
#define dwDurInterval(lpi)	dwDiffAT((lpi)->atBegin, (lpi)->atEnd)

// fill a pointer to an ABSTIME structure from a count of seconds and ms:
#define MakeAbsTime(lpat, sec, ms) do {\
	(lpat)->sec = sec + ((ms) / 1000);\
	(lpat)->ms = (ms) % 1000;\
} while (0)

#endif /*!NOPENHRC */      

//---------------------------------------------------------------------------
#ifndef NOPENINKPUT

#define EventRefFromLparam(lParam)        (LOWORD((lParam)))
#define TerminationFromLparam(lParam)     ((int)(LOWORD((lParam))))
#define HpcmFromLparam(lParam)            ((HPCM)HIWORD((lParam)))
#endif   /*!NOPENINKPUT*/

//---------------------------------------------------------------------------
#ifndef NOPENTARGET
#define HwndFromHtrg(htrg)              ((HWND)(htrg))
#define HtrgFromHwnd(hwnd)               ((HTRG)(struct hwnd__ FAR *)(hwnd))
#endif /*!NOPENTARGET*/
//---------------------------------------------------------------------------
#ifndef NOWINUSER

// is this style of button penabled?: USER-Penwin
#define FPenabledBs(bs) (\
	((bs) == BS_CHECKBOX) || ((bs) == BS_AUTOCHECKBOX) || \
	((bs) == BS_3STATE) || ((bs) == BS_AUTO3STATE) || \
	((bs) == BS_RADIOBUTTON) || ((bs) == BS_AUTORADIOBUTTON))
#endif /*!NOWINUSER */




/****** Typedefs ************************************************************/

// simple:
typedef LONG						ALC;		// Enabled Alphabet
typedef int							CL;		// Confidence Level
typedef UINT						HKP;		// Hook Parameter
typedef int							REC;		// recognition result
typedef LONG						SYV;		// Symbol Value

DECLARE_HANDLE(HPCM);					   // Handle to Pen Collection Info
DECLARE_HANDLE(HPENDATA);					// handle to ink
DECLARE_HANDLE(HREC);						// handle to recognizer
typedef DWORD HTRG;

// pointer types:
typedef LPVOID						LPOEM;			// alias
typedef SYV FAR*					LPSYV;			// ptr to SYV
typedef HPENDATA FAR*			LPHPENDATA;		// ptr to HPENDATA

// function prototypes:
typedef int			(CALLBACK *ENUMPROC)(LPSYV, int, VOID FAR *);
typedef int			(CALLBACK *LPDF)(int, LPVOID, LPVOID, int, DWORD, DWORD);
typedef BOOL		(CALLBACK *RCYIELDPROC)(VOID);


// structures:


#if (WINVER < 0x0400)
typedef struct tagRECTL
{
   LONG     left;
   LONG     top;
   LONG     right;
   LONG     bottom;

} RECTL;
typedef RECTL*       PRECTL;
typedef RECTL NEAR*  NPRECTL;
typedef RECTL FAR*   LPRECTL;
typedef const RECTL FAR* LPCRECTL;
#endif // WINVER



typedef struct tagABSTIME
	{
	DWORD sec;	// number of seconds since 1/1/1970, ret by CRTlib time() fn
	WORD ms;		// additional offset in ms, 0..999
	}
	ABSTIME, FAR *LPABSTIME;

//---------------------------------------------------------------------------
#ifndef NOPENBEDIT

typedef struct tagBOXLAYOUT	 // box edit layout
   {
   int cyCusp;      				 // pixel height of box (BXS_RECT) or cusp
   int cyEndCusp;					 // pixel height of cusps at extreme ends
   UINT style;      				 // BXS_xx style
   DWORD dwReserved1;			 // reserved
   DWORD dwReserved2;			 // reserved
   DWORD dwReserved3;			 // reserved
   }
   BOXLAYOUT, FAR *LPBOXLAYOUT;


typedef struct tagIMECOLORS	// IME undetermine string color info.
	{
	int cColors;				// count of colors to be set/get
	int FAR *lpnElem;			// address of array of elements
	COLORREF FAR *lprgbIme;		// address of array of RGB values
	}
	IMECOLORS, FAR *LPIMECOLORS;


typedef struct tagCTLINITBEDIT // init struct for box edit
   {
   HWND hwnd;						 // box edit window handle
   int id;							 // its id
   int wSizeCategory;			 // BESC_xx
   DWORD dwReserved;				 // for future use
   }
   CTLINITBEDIT, FAR * LPCTLINITBEDIT;


typedef struct tagBOXEDITINFO	 // box edit Size Info
   {
   int cxBox;						 // width of a single box
   int cyBox;						 // ditto height
   int cxBase;						 // in-box x-margin to guideline
   int cyBase;						 // in-box y offset from top to baseline
   int cyMid;						 // 0 or distance from baseline to midline
   BOXLAYOUT boxlayout;			 // embedded BOXLAYOUT structure
   UINT wFlags;					 // BEIF_xx
   BYTE szFaceName[BEI_FACESIZE];	// font face name
   UINT wFontHeight;				 // font height
   UINT rgwReserved[8];			 // for future use
   }
   BOXEDITINFO, FAR *LPBOXEDITINFO;
#endif /*!NOPENBEDIT */


//---------------------------------------------------------------------------
#ifndef NOPENCTL

typedef struct tagCTLINITCOMBOBOX	// init struct for combo box
   {
   HWND hwnd;						 // combo box window handle
   int id;							 // its id
   BOOL fUseBedit;				 // T: use box edit in top control, else HEDIT
   }
   CTLINITCOMBOBOX, FAR * LPCTLINITCOMBOBOX;


typedef struct tagRECTOFS		 // rectangle offset for nonisometric inflation
   {
   int dLeft;						 // inflation leftwards from left side
   int dTop;						 // ditto upwards from top
   int dRight;						 // ditto rightwards from right
   int dBottom;					 // ditto downwards from bottom
   }
   RECTOFS, FAR *LPRECTOFS;
#endif /*!NOPENCTL */


//---------------------------------------------------------------------------
#ifndef NOPENDATA

typedef struct tagPENDATAHEADER	// main pen data header
   {
   UINT wVersion;					 // pen data format version
   UINT cbSizeUsed;        	 // size of pendata mem block in bytes
   UINT cStrokes;          	 // number of strokes (incl up-strokes)
   UINT cPnt;              	 // count of all points
   UINT cPntStrokeMax;			 // length (in points) of longest stroke
   RECT rectBound;				 // bounding rect of all down points
   UINT wPndts;            	 // PDTS_xx bits
   int  nInkWidth;				 // ink width in pixels
   DWORD rgbInk;					 // ink color
   }
   PENDATAHEADER, FAR *LPPENDATAHEADER, FAR *LPPENDATA;


typedef struct tagSTROKEINFO	 // stroke header
   {
   UINT cPnt;        			 // count of points in stroke
   UINT cbPnts;    				 // size of stroke in bytes
   UINT wPdk;        			 // state of stroke
   DWORD dwTick;    				 // time at beginning of stroke
   }
   STROKEINFO, FAR *LPSTROKEINFO;


typedef struct tagPENTIP	// Pen Tip characteristics
	{
   BYTE     btype;         // pen type/nib (calligraphic nib, etc.)
 	BYTE		bwidth;			// width of Nib (typically == nInkWidth)
 	BYTE		bheight;			// height of Nib
   COLORREF rgb;	         // pen color
	BYTE		bOpacity;		// 0=transparent, 0x80=hilite, 0xFF=opaque
	WORD		wFlags;			// TIP_xx flags
	BYTE		rgbReserved[4];// for future expansion
	}
	PENTIP, FAR *LPPENTIP;


typedef BOOL (CALLBACK *ANIMATEPROC)(HPENDATA, UINT, UINT, UINT FAR*, LPARAM);

typedef struct tagANIMATEINFO	// Animation parameters
	{
	UINT			uSpeedPct;			// speed percent to animate at
	ANIMATEPROC lpfnAnimateCB;		// callback function
	UINT			uPeriodCB;			// time between calls to callback in ms
	UINT			fuFlags;				// animation flags
	LPARAM		lParam;				// value to pass to callback
	DWORD			dwReserved;			// reserved
	}
	ANIMATEINFO, FAR *LPANIMATEINFO;

#endif /*!NOPENDATA */


//---------------------------------------------------------------------------
#ifndef NOPENDRIVER

typedef struct tagOEMPENINFO	 // OEM pen/tablet hdwe info
   {
   UINT wPdt;						 // pen data type
   UINT wValueMax;				 // largest val ret by device
   UINT wDistinct;				 // number of distinct readings possible
   }
   OEMPENINFO, FAR *LPOEMPENINFO;


typedef struct tagPENPACKET	 // pen packet
   {
   UINT wTabletX;					 // x in raw coords
   UINT wTabletY;					 // ditto y
   UINT wPDK;						 // state bits
   UINT rgwOemData[MAXOEMDATAWORDS];	// OEM-specific data
   }
   PENPACKET, FAR *LPPENPACKET;

typedef struct OEM_PenPacket
   {
   UINT wTabletX;					 // x in raw coords
   UINT wTabletY;					 // ditto y
   UINT wPDK;						 // state bits
   UINT rgwOemData[MAXOEMDATAWORDS];	// OEM-specific data
   DWORD dwTime;
   } OEM_PENPACKET, FAR * LPOEM_PENPACKET;


typedef struct tagPENINFO		 // pen/tablet hdwe info
   {
   UINT cxRawWidth;       		 // max x coord and tablet width in 0.001"
   UINT cyRawHeight;       	 // ditto y, height
   UINT wDistinctWidth;   		 // number of distinct x values tablet ret
   UINT wDistinctHeight;  		 // ditto y
   int nSamplingRate; 			 // samples / second
   int nSamplingDist; 			 // min distance to move before generating event
   LONG lPdc;        			 // Pen Device Capabilities
   int cPens;        			 // number of pens supported
   int cbOemData;    			 // width of OEM data packet
   OEMPENINFO rgoempeninfo[MAXOEMDATAWORDS];	// supported OEM data types
   UINT rgwReserved[7];     	 // for internal use
   UINT fuOEM;						 // which OEM data, timing, PDK_xx to report
   }
   PENINFO, FAR *LPPENINFO;

typedef struct tagCALBSTRUCT   // pen calibration
   {
   int wOffsetX;
   int wOffsetY;
   int wDistinctWidth;
   int wDistinctHeight;
   }
   CALBSTRUCT, FAR *LPCALBSTRUCT;

typedef BOOL		(CALLBACK *LPFNRAWHOOK)(LPPENPACKET);
#endif /*!NOPENDRIVER */


//---------------------------------------------------------------------------
#ifndef NOPENHRC

// Handwriting Recognizer:
typedef DWORD HMACRO;
typedef HMACRO FAR *LPHMACRO;

typedef DWORD HRC;
typedef HRC FAR *LPHRC;

typedef DWORD HRCRESULT;
typedef HRCRESULT FAR *LPHRCRESULT;

typedef VOID (CALLBACK *HRCYIELDPROC)(HRC, LPARAM);

// Inksets:
DECLARE_HANDLE(HINKSET);						// handle to an inkset
typedef HINKSET FAR*			LPHINKSET;		// ptr to HINKSET

typedef struct tagINTERVAL	// interval structure for inksets
	{
	ABSTIME atBegin;	// begining of 1-ms granularity interval
	ABSTIME atEnd;		// 1 ms past end of interval
	}
	INTERVAL, FAR *LPINTERVAL;

typedef struct tagBOXRESULTS
	{
   int      indxBox;
   HINKSET  hinksetBox;
   SYV      rgSyv[1];
	}
	BOXRESULTS, FAR *LPBOXRESULTS;


#endif /*!NOPENHRC */

//---------------------------------------------------------------------------
#ifndef NOPENIEDIT

typedef struct tagCTLINITIEDIT		// init struct for Ink Edit
	{
	HWND		hwnd;					// IEdit window handle
	int		id;					// its ID
	UINT		ieb;					// IEB_* (background) bits
	UINT		iedo;					// IEDO_* (draw options) bits
	UINT		iei;					// IEI_* (ink input) bits
	UINT		ien;					// IEN_* (notification) bits
	UINT		ierec;				// IEREC_* (recognition) bits
	UINT		ies;					// IES_* (style) bits
	UINT		iesec;				// IESEC_* (security) bits
	HPENDATA	hpndt;				// initial pendata (or NULL if none)
	UINT		pdts;					// initial pendata scale factor (PDTS_*)
	HGDIOBJ	hgdiobj;				// background brush or bitmap handle
	HPEN		hpenGrid;			// pen to use in drawing grid
	UINT		wVGrid;				// vertical gridline spacing
	UINT		wHGrid;				// horizontal gridline spacing
	DWORD		dwApp;				// application-defined data
	DWORD		dwReserved;			// reserved for future use
	}
	CTLINITIEDIT, FAR * LPCTLINITIEDIT;


typedef struct tagPDEVENT
	{
	HWND		hwnd;					// window handle of I-Edit
	UINT		wm;					// WM_* (window message) of event // TODO UINT?
	WPARAM	wParam;				// wParam of message
	LPARAM	lParam;				// lParam of message
	POINT		pt;					// event pt in I-Edit client co-ords
	BOOL		fPen;					// TRUE if pen (or other inking device)
	LONG		lExInfo;				// GetMessageExtraInfo() return value
	DWORD		dwReserved;			// for future use
	}
	PDEVENT, FAR * LPPDEVENT;


typedef struct tagSTRKFMT
	{
	WORD		iesf;					// stroke format flags and return bits
	UINT		iStrk;				// stroke index if IESF_STROKE
	PENTIP	tip;					// ink tip attributes
	DWORD		dwUser;				// user data for strokes
	DWORD		dwReserved;			// for future use
	}
	STRKFMT, FAR * LPSTRKFMT;
#endif /*!NOPENIEDIT */


//---------------------------------------------------------------------------
#ifndef NOPENINKPUT

typedef struct tagPCMINFO	// Pen Collection Mode Information
   {
   DWORD dwPcm;				// PCM_xxx flags
   RECT  rectBound;			// if finish on pendown outside this rect
   RECT  rectExclude;		// if finish on pendown inside this rect
   HRGN  hrgnBound;			// if finish on pendown outside this region
   HRGN  hrgnExclude;		// if finish on pendown inside this region
   DWORD dwTimeout;			// if finish after timeout, this many ms
   }
	PCMINFO, FAR *LPPCMINFO;


typedef  struct tagINKINGINFO	// Pen Inking Information
   {
   UINT     wFlags;			// One of the PII_xx flags
	PENTIP	tip;				// Pen type, size and color
   RECT     rectClip;      // Clipping rect for the ink
   RECT     rectInkStop;   // Rect in which a pen down stops inking
   HRGN     hrgnClip;      // Clipping region for the ink
   HRGN     hrgnInkStop;   // Region in which a pen down stops inking
   } 
	INKINGINFO, FAR *LPINKINGINFO;
#endif /*!NOPENINKPUT */


//---------------------------------------------------------------------------
#ifndef NOPENRC1

typedef struct tagSYC			 // Symbol Correspondence for Ink
   {
   UINT wStrokeFirst;			 // first stroke, inclusive
   UINT wPntFirst;				 // first point in first stroke, inclusive
   UINT wStrokeLast;				 // last stroke, inclusive
   UINT wPntLast;					 // last point in last stroke, inclusive
   BOOL fLastSyc;					 // T: no more SYCs follow for current SYE
   }
   SYC, FAR *LPSYC;
    

typedef struct tagSYE			 // Symbol Element
   {
   SYV syv;							 // symbol value
   LONG lRecogVal;				 // for internal use by recognizer
   CL cl;							 // confidence level
   int iSyc;						 // SYC index
   }
   SYE, FAR *LPSYE;


typedef struct tagSYG			 // Symbol Graph
   {
   POINT rgpntHotSpots[MAXHOTSPOT]; // hot spots (max 8)
   int cHotSpot;					 // number of valid hot spots in rgpntHotSpots
   int nFirstBox;					 // row-major index to box of 1st char in result
   LONG lRecogVal;				 // reserved for use by recoognizer
   LPSYE lpsye;					 // nodes of symbol graph
   int cSye;						 // number of SYEs in symbol graph
   LPSYC lpsyc;					 // ptr to corresp symbol ink
   int cSyc;						 // ditto count
   }
   SYG, FAR *LPSYG;


typedef struct tagGUIDE			 // guide structure
   {
   int xOrigin;    				 // left edge of first box (screen coord))
   int yOrigin;					 // ditto top edge
   int cxBox;						 // width of a single box
   int cyBox;						 // ditto height
   int cxBase;						 // in-box x-margin to guideline
   int cyBase;						 // in-box y offset from top to baseline
   int cHorzBox;					 // count of boxed columns
   int cVertBox;					 // ditto rows
   int cyMid;						 // 0 or distance from baseline to midline
   }
   GUIDE, FAR *LPGUIDE;


typedef struct tagRC				 // Recognition Context (RC)
   {
   HREC hrec;						 // handle of recognizer to use
   HWND hwnd;						 // window to send results to
   UINT wEventRef;        		 // index into ink buffer
   UINT wRcPreferences;			 // flags: RCP_xx Preferences
   LONG lRcOptions;				 // RCO_xx options
   RCYIELDPROC lpfnYield;		 // procedure called during Yield()
   BYTE lpUser[cbRcUserMax];	 // current writer
   UINT wCountry;					 // country code
   UINT wIntlPreferences;		 // flags: RCIP_xx
   char lpLanguage[cbRcLanguageMax];	// language strings
   LPDF rglpdf[MAXDICTIONARIES];			// list of dictionary functions
   UINT wTryDictionary;			 // max enumerations to search
   CL clErrorLevel;				 // level where recognizer should reject input
   ALC alc;							 // enabled alphabet
   ALC alcPriority;				 // prioritizes the ALC_ codes
   BYTE rgbfAlc[cbRcrgbfAlcMax];	// bit field for enabled characters
   UINT wResultMode;				 // RRM_xx when to send (asap or when complete)
   UINT wTimeOut;					 // recognition timeout in ms
   LONG lPcm;						 // flags: PCM_xx for ending recognition
   RECT rectBound;				 // bounding rect for inking (def:screen coords)
   RECT rectExclude;				 // pen down inside this terminates recognition
   GUIDE guide;					 // struct: defines guidelines for recognizer
   UINT wRcOrient;				 // RCOR_xx orientation of writing wrt tablet
   UINT wRcDirect;				 // RCD_xx direction of writing
   int nInkWidth;					 // ink width 0 (none) or 1..15 pixels
   COLORREF rgbInk;				 // ink color
   DWORD dwAppParam;				 // for application use
   DWORD dwDictParam;			 // for app use to be passed on to dictionaries
   DWORD dwRecognizer;			 // for app use to be passed on to recognizer
   UINT rgwReserved[cwRcReservedMax];	// reserved for future use by Windows
   }
   RC, FAR *LPRC;


typedef struct tagRCRESULT		 // Recognition Result
   {
   SYG syg;							 // symbol graph
   UINT wResultsType;			 // see RCRT_xx
   int cSyv;						 // count of symbol values
   LPSYV lpsyv;					 // NULL-term ptr to recog's best guess
   HANDLE hSyv;					 // globally-shared handle to lpsyv mem
   int nBaseLine;					 // 0 or baseline of input writing
   int nMidLine;					 // ditto midline
   HPENDATA hpendata;			 // pen data mem
   RECT rectBoundInk;			 // ink data bounds
   POINT pntEnd;					 // pt that terminated recog
   LPRC lprc;						 // recog context used
   }
   RCRESULT, FAR *LPRCRESULT;
#endif /*!NOPENRC1 */


//---------------------------------------------------------------------------
#ifndef NOPENTARGET

typedef struct tagTARGET		// Geometry for a single target.
   {
   unsigned short uFlags;              // flags to mark info about individual targets
   unsigned short idTarget;            // Index of the target within the TARGINFO.rgTarget[]
   HTRG  htrgTarget;        // 
   RECTL rectBound;           // Bounding rect of the target
   DWORD dwExtraInfo;         // Target specific extra info. to be filled
                              // during data collection
   BYTE  rgbReserved[2 * sizeof(RECTL)];     // Reserved for internal use; must be zero
   }
   TARGET, FAR *LPTARGET;


typedef struct tagTARGINFO		// A set of targets
   {
   WORD wFlags;					// flags
   HTRG htrgOwner;          //
   unsigned short cTargets;	// count of targets
   unsigned short iTargetLast;// last target, used by TargetPoints API
                              // if TPT_TEXTUAL flag is set
   TARGET rgTarget[1];   		// variable-length array of targets
   }
   TARGINFO, FAR *LPTARGINFO;

typedef struct tagINPPARAMS
   {
   unsigned short uFlags;
   HPENDATA     hpndt;
   TARGET       target;   // target structure
   }
	INPPARAMS, FAR *LPINPPARAMS;

#endif /*!NOPENTARGET */


//---------------------------------------------------------------------------
#ifndef NOWINUSER

typedef struct tagEPI   /* Edit Penwin Info struct */
  {
  HPENDATA hpndt;         /* ink handle */
  LPRCRESULT lprcrCur;    /* current lprcresult */
  REC      recCur;        /* current rec */
  HRC      hrc;
  HRCRESULT hrcr;
  PCMINFO  pcminfo;
  INKINGINFO inkinginfo;
  // TODO: TMP
  BYTE     rgb[sizeof(RC) - sizeof(HRC) - sizeof(HRCRESULT) - sizeof(PCMINFO) - sizeof(INKINGINFO)];
  RECTOFS  rofsInflate;   /* inflation rect for handwriting */
  WORD     fRuled:1;      /* Ruled edit? */
  WORD     fWaitForTap:1; /* Wait for tap in stopinkmode? */
  }
  EPI, NEAR *PEPI, FAR *LPEPI;
#endif /*!NOWINUSER */



/****** APIs and Prototypes *************************************************/

LRESULT CALLBACK	DefPenWindowProc(HWND, UINT, WPARAM, LPARAM);

//---------------------------------------------------------------------------
#ifndef NOPENAPPS

// Pen System Applications:
BOOL WINAPI			ShowKeyboard(HWND, UINT, LPPOINT, LPSKBINFO);
#endif /*!NOPENAPPS */

//---------------------------------------------------------------------------
#ifndef NOPENDATA

// PenData:
HPENDATA WINAPI	AddPointsPenData(HPENDATA, LPPOINT, LPVOID, LPSTROKEINFO);
LPPENDATA WINAPI	BeginEnumStrokes(HPENDATA);
HPENDATA WINAPI	CompactPenData(HPENDATA, UINT);
int WINAPI			CompressPenData(HPENDATA, UINT, DWORD);
HPENDATA WINAPI	CopyPenDataFromClip();
int WINAPI			CopyPenDataToClip(HPENDATA);
HPENDATA WINAPI	CreatePenData(LPPENINFO, int, UINT, UINT);
HPENDATA WINAPI	CreatePenDataEx(LPPENINFO, UINT, UINT, UINT);
BOOL WINAPI			DestroyPenData(HPENDATA);
VOID WINAPI			DrawPenData(HDC, LPRECT, HPENDATA);
int  WINAPI			DrawPenDataEx(HDC, LPRECT, HPENDATA, UINT, UINT, UINT, UINT,
							LPANIMATEINFO, UINT);
HPENDATA WINAPI	DuplicatePenData(HPENDATA, UINT);
LPPENDATA WINAPI	EndEnumStrokes(HPENDATA);
int WINAPI			ExtractPenDataStrokes(HPENDATA, UINT, LPARAM, LPHPENDATA, UINT);
BOOL WINAPI			GetPenDataInfo(HPENDATA, LPPENDATAHEADER, LPPENINFO, DWORD);
BOOL WINAPI			GetPenDataStroke(LPPENDATA, UINT, LPPOINT FAR *,
							LPVOID FAR *,	LPSTROKEINFO );
BOOL WINAPI			GetPointsFromPenData(HPENDATA, UINT, UINT, UINT, LPPOINT);
int WINAPI			GetStrokeAttributes(HPENDATA, UINT, LPVOID, UINT);
int WINAPI			GetStrokeTableAttributes(HPENDATA, UINT, LPVOID, UINT);
int WINAPI 			HitTestPenData(HPENDATA, LPPOINT, UINT, UINT FAR *, UINT FAR *);
int WINAPI			InsertPenDataPoints(HPENDATA, UINT, UINT, UINT,
							LPPOINT, LPVOID);
int  WINAPI			InsertPenDataStroke(HPENDATA, UINT, LPPOINT, LPVOID, 
							LPSTROKEINFO);
int  WINAPI			InsertPenData(HPENDATA, HPENDATA, UINT);
BOOL WINAPI			MetricScalePenData(HPENDATA, UINT);
BOOL WINAPI			OffsetPenData(HPENDATA, int, int);
HPENDATA WINAPI	ReadPenData(HFILE);
BOOL WINAPI			RedisplayPenData(HDC, HPENDATA, LPPOINT, LPPOINT,
							int, DWORD);
int  WINAPI			ExtractPenDataPoints(HPENDATA, UINT, UINT, UINT, LPPOINT,
							LPVOID, UINT);
int  WINAPI			RemovePenDataStrokes(HPENDATA, UINT, UINT);
BOOL WINAPI			ResizePenData(HPENDATA, LPRECT);
int  WINAPI			SetStrokeAttributes(HPENDATA, UINT, LPARAM, UINT);
int  WINAPI			SetStrokeTableAttributes(HPENDATA, UINT, LPARAM, UINT);
int WINAPI			TrimPenData(HPENDATA, DWORD, DWORD);
UINT WINAPI			WritePenData(HFILE, HPENDATA, UINT);


#endif /*!NOPENDATA */

//---------------------------------------------------------------------------
#ifndef NOPENDICT

// Dictionary:
BOOL WINAPI			DictionarySearch(LPRC, LPSYE, int, LPSYV, int);
#endif /*!NOPENDICT */

//---------------------------------------------------------------------------
#ifndef NOPENDRIVER

// Pen Hardware/Driver:
BOOL WINAPI			EndPenCollection(REC);
BOOL WINAPI			GetPenAsyncState(UINT);
REC  WINAPI			GetPenHwData(LPPOINT, LPVOID, int, UINT, LPSTROKEINFO);
REC  WINAPI			GetPenHwEventData(UINT, UINT, LPPOINT, LPVOID,
							int, LPSTROKEINFO);
BOOL WINAPI			IsPenEvent(UINT, LONG);
BOOL WINAPI			SetPenHook(HKP, LPFNRAWHOOK);
VOID WINAPI			UpdatePenInfo(LPPENINFO);
#endif /*!NOPENDRIVER */

//---------------------------------------------------------------------------
#ifndef NOPENGEST

// Gesture Management:
BOOL WINAPI			ExecuteGesture(HWND, SYV, LPRCRESULT);
#ifdef NOTPENWIN // Gesture Manager Engine	TODO
int WINAPI			CbChBuffFromIcd(UINT, LPSTR, int, UINT FAR*);
int WINAPI			CbSzFromIcd(LPSTR, LPDWORD, int, UINT FAR*);
int WINAPI			CIcdFromSz(LPSTR, LPDWORD, int, UINT FAR*);
VOID WINAPI			DeleteGestureMapping(LPSTR, LONG);
int WINAPI			FindReservedKey(UINT);
LONG WINAPI			FirstMappableGesture(LPSTR);
int WINAPI			GetPriorityGesMap(LPSTR, LONG, LPDWORD, int, UINT FAR*);
UINT WINAPI			IcdFromKeyStrokes(UINT, UINT FAR*, BOOL);
BOOL WINAPI			IsSpecialTask(LPSTR);
VOID WINAPI			MapInit(VOID);
VOID WINAPI			ModuleNameFromTask(HANDLE, LPSTR, int);
LONG WINAPI			NextMappableGesture(VOID);
LPSTR WINAPI		PGetAppMap(LPSTR);
VOID WINAPI			SetGestureMapping(LPSTR, LONG, LPDWORD, LPSTR, UINT);
#endif //NOTPENWIN
#endif /*!NOPENGEST */

//---------------------------------------------------------------------------
#ifndef NOPENHRC

// Handwriting Recognizer:
int		WINAPI AddPenDataHRC(HRC, HPENDATA);
int		WINAPI AddPenInputHRC(HRC, LPPOINT, LPVOID, UINT, LPSTROKEINFO);
HMACRO	WINAPI CombineHMACRO(HMACRO, HMACRO, UINT);
HMACRO	WINAPI CreateTemplateHMACRO(HREC, LPCSTR);
HMACRO	WINAPI CreateWordListHMACRO(HREC, LPVOID, UINT, DWORD);
HRC		WINAPI CreateCompatibleHRC(HRC, HREC);
HRC		WINAPI CreateHRCFromHRCRESULT(HRCRESULT, UINT, UINT);
HINKSET	WINAPI CreateInksetHRCRESULT(HRCRESULT, UINT, UINT);
HPENDATA WINAPI CreatePenDataHRC(HRC);
int		WINAPI DestroyHMACRO(HMACRO);
int		WINAPI DestroyHRC(HRC);
int		WINAPI DestroyHRCRESULT(HRCRESULT);
int		WINAPI EnableGestureSetHRC(HRC, SYV, BOOL);
int		WINAPI EndPenInputHRC(HRC);
int		WINAPI GetBoxMappingHRCRESULT(HRCRESULT, UINT, UINT, UINT FAR*);
int      WINAPI GetBoxResultsHRC(HRC, int, int, int, LPBOXRESULTS);
int		WINAPI GetConfidenceHRCRESULT(HRCRESULT);
int		WINAPI GetHotspotsHRCRESULT(HRCRESULT, UINT, LPPOINT);
int		WINAPI GetResultsHRC(HRC, ALC, LPHRCRESULT, UINT);
int		WINAPI GetSymbolsHRCRESULT(HRCRESULT, UINT, LPSYV, UINT);
int		WINAPI GetSymbolCountHRCRESULT(HRCRESULT);
int		WINAPI ProcessHRC(HRC, DWORD);
int		WINAPI SetAlphabetHRC(HRC, ALC, LPBYTE);
int		WINAPI SetCoercionHRC(HRC, UINT);
int		WINAPI SetGuideHRC(HRC, LPGUIDE, UINT);
int		WINAPI SetHmacroHRC(HRC, HMACRO);
int		WINAPI SetMaxResultsHRC(HRC, UINT);
int		WINAPI SetInternationalHREC(HREC, UINT, LPCSTR, UINT);
int		WINAPI SetInternationalHRC(HRC, UINT, LPCSTR, UINT);
int		WINAPI SetSymbolContextHRC(HRC, LPSYV, UINT, LPSYV, UINT);
int		WINAPI SetUserHREC(HREC, LPCSTR, UINT, UINT);
int		WINAPI SetYieldHRC(HRC, HRCYIELDPROC, UINT, LPARAM);
int		WINAPI TrainHREC(HREC, LPSYV, HPENDATA, UINT);


// Inksets:
BOOL		WINAPI AddInksetInterval(HINKSET, LPINTERVAL);
HINKSET	WINAPI CreateInkset(UINT);
BOOL		WINAPI DestroyInkset(HINKSET);
int		WINAPI GetInksetInterval(HINKSET, UINT, LPINTERVAL);
int		WINAPI GetInksetIntervalCount(HINKSET);

#endif /*!NOPENHRC */

//---------------------------------------------------------------------------
#ifndef NOPENINKPUT

// Pen Input/Inking:
int WINAPI			StopPenInput(HPCM, UINT, int);
int WINAPI			GetPenInput(HPCM, LPPOINT, LPVOID, UINT, UINT, LPSTROKEINFO);
int WINAPI			PeekPenInput(HPCM, UINT, LPPOINT, LPVOID, UINT);
int WINAPI			StartInking(HPCM, UINT, LPINKINGINFO);
HPCM WINAPI			StartPenInput(HWND, UINT, LPPCMINFO, LPINT);
int WINAPI			StopInking(HPCM);
int WINAPI        DoDefaultPenInput(HWND, UINT);
#endif /*!NOPENINKPUT */

//---------------------------------------------------------------------------
#ifndef NOPENMISC

// Miscellaneous/Utilities:
VOID WINAPI			BoundingRectFromPoints(LPPOINT, int, LPRECT);
BOOL WINAPI			DPtoTP(LPPOINT, int);
UINT WINAPI			GetPenAppFlags(VOID);
LONG WINAPI			GetPenMiscInfo(WPARAM, LPARAM);
UINT WINAPI			GetVersionPenWin(VOID);
UINT WINAPI			IsPenAware(VOID);
VOID WINAPI			RegisterPenApp(UINT, UINT);
LONG WINAPI			SetPenMiscInfo(WPARAM, LPARAM);
BOOL WINAPI			TPtoDP(LPPOINT, int);
#endif /*!NOPENMISC */

//---------------------------------------------------------------------------
#ifndef NOPENRC1

// RC:
BOOL WINAPI			CorrectWriting(HWND, LPSTR, UINT, LPVOID, DWORD, DWORD);
UINT WINAPI			EnumSymbols(LPSYG, UINT, ENUMPROC, LPVOID);
VOID WINAPI			FirstSymbolFromGraph(LPSYG, LPSYV, int, LPINT);
UINT WINAPI			GetGlobalRC(LPRC, LPSTR, LPSTR, int);
int  WINAPI			GetSymbolCount(LPSYG);
int  WINAPI			GetSymbolMaxLength(LPSYG);
VOID WINAPI			InitRC(HWND, LPRC);
HREC WINAPI			InstallRecognizer(LPSTR);
REC  WINAPI			ProcessWriting(HWND, LPRC);    
REC  WINAPI			Recognize(LPRC);
REC  WINAPI			RecognizeData(LPRC, HPENDATA);
UINT WINAPI			SetGlobalRC(LPRC, LPSTR, LPSTR);
BOOL WINAPI			SetRecogHook(UINT, UINT, HWND);
BOOL WINAPI			TrainContext(LPRCRESULT, LPSYE, int, LPSYC, int);
BOOL WINAPI			TrainInk(LPRC, HPENDATA, LPSYV);
VOID WINAPI			UninstallRecognizer(HREC);
#endif /*!NOPENRC1 */

//---------------------------------------------------------------------------
#ifndef NOPENSYV

// Symbol Values:
int  WINAPI			CharacterToSymbol(LPSTR, int, LPSYV);
BOOL WINAPI			SymbolToCharacter(LPSYV, int, LPSTR, LPINT);
#endif /*!NOPENSYV */

//---------------------------------------------------------------------------
#ifndef NOPENTARGET

// Ink Targeting:
int  WINAPI			TargetPoints(LPTARGINFO, LPPOINT, LPVOID, UINT, LPSTROKEINFO);

#endif /*!NOPENTARGET */


//---------------------------------------------------------------------------
#ifndef NOPENVIRTEVENT

// Virtual Event Layer:
VOID WINAPI			AtomicVirtualEvent(BOOL);
VOID WINAPI			PostVirtualKeyEvent(UINT, BOOL);
VOID WINAPI			PostVirtualMouseEvent(UINT, int, int);
#endif /*!NOPENVIRTEVENT */

//---------------------------------------------------------------------------

#ifdef KANJI
// Kanji
BOOL WINAPI KKConvert(HWND hwndConvert, HWND hwndCaller, LPSTR lpBuf, UINT cbBuf, LPPOINT lpPnt);
#endif // KANJI


#endif /* RC_INVOKED */	// ... all the way back from definitions:2

/****** End of Header Info *************************************************/


#ifdef __cplusplus
}
#endif /* __cplusplus */

#ifndef RC_INVOKED
#pragma pack()
#endif /* RC_INVOKED */

#endif /* #define _INC_PENWIN */
