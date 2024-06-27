/********************************************************************
 *
 * hhsystem.h - Microsoft Windows for Hand-held Computers
 *              functions, types and definitions
 *
 *              Version 1.00
 *
 *              Copyright (c) 1992-1993, Microsoft Corp.
 *              All Rights reserved.
 *
 ********************************************************************/
#ifndef _INC_HHSYSTEMH
#define _INC_HHSYSTEMH

#ifdef __cplusplus
extern "C" { /* Assume C declarations for C++ */
#endif /* __cplusplus */

#ifndef RC_INVOKED
#include "sosapi.h"
#endif /* RC_INVOKED */

/********************************************************************
 * General
 ********************************************************************/
#define HHAPI   WINAPI


/********************************************************************
 * Command Lists Functions
 ********************************************************************/
typedef HANDLE HCMDLST;

HCMDLST HHAPI HHLoadCommandList(HINSTANCE, LPCSTR);
HCMDLST HHAPI HHCreateCommandList(VOID);
BOOL    HHAPI HHDestroyCommandList(HCMDLST);
BOOL    HHAPI HHAppendCommandList(HCMDLST, WORD, LPCSTR);
BOOL    HHAPI HHIsCommandList (HCMDLST);
BOOL    HHAPI HHEnableCommandListItem (HCMDLST, BOOL, WORD, BOOL);

#define CMDLST    RCDATA

/********************************************************************
 * System Functions
 ********************************************************************/
UINT HHAPI HHGetVersion (void);

int HHAPI HHGetSystemMetrics(int);

/* HHGetSystemMetrics() codes */
#define HHSM_CXHSCROLL          0
#define HHSM_CYHSCROLL          1
#define HHSM_CXVSCROLL          2
#define HHSM_CYVSCROLL          3
#define HHSM_CXBORDER           4
#define HHSM_CYBORDER           5
#define HHSM_CXDRAGICON         6
#define HHSM_CYDRAGICON         7
#define HHSM_CXEDITDRAGICON     8
#define HHSM_CYEDITDRAGICON     9
#define HHSM_CXPALETTE          10
#define HHSM_CYPALETTE          11
#define HHSM_CXTRAY             12
#define HHSM_CYTRAY             13
#define HHSM_CXDOGEAR           14
#define HHSM_CYDOGEAR           15
#define HHSM_SYSHEIGHT          16
#define HHSM_SYSEXTERNLEADING   17
#define HHSM_SYSAVECHARWIDTH    18
#define HHSM_DESKTOP            19
#define HHSM_CANINK             20
#define HHSM_CYEDITMIN          21
#define HHSM_MAXDDTYPES         22
#define HHSM_CXLBDRAGICONCOL    23

HBITMAP HHAPI HHGetSystemBitmap(int);

#define HHSB_ADDRESSOBJ         0
#define HHSB_CALENDAROBJ        1
#define HHSB_MESSAGEOBJ         2
#define HHSB_MULTIPLEOBJ        3
#define HHSB_NOTEOBJ            4
#define HHSB_TEXTOBJ            5
#define HHSB_TEXTOBJPRESSED     6
#define HHSB_TODOOBJ            7
#define HHSB_DRAGICONLG         8
#define HHSB_DRAGICONSM         9
#define HHSB_TRAYEMPTY         10
#define HHSB_TRAYFULL          11
#define HHSB_LENS              12
#define HHSB_ERASER            13
#define HHSB_TEXTMODE          14
#define HHSB_INKMODE           15
#define HHSB_KEYBOARD          16

HCURSOR HHAPI HHGetSystemCursor(int);

#define HHSC_ARROW              0
#define HHSC_WAIT               1
#define HHSC_PEN                2
#define HHSC_ALTSELECT          3
#define HHSC_ERASE              4
#define HHSC_DRAGICON           5
#define HHSC_CIRCLENO           6
#define HHSC_QUESTION           7
#define HHSC_SCROLLING          8
#define HHSC_ADDRESSCOPY        9
#define HHSC_ADDRESSMOVE        10
#define HHSC_CALENDARCOPY       11
#define HHSC_CALENDARMOVE       12
#define HHSC_MESSAGECOPY        13
#define HHSC_MESSAGEMOVE        14
#define HHSC_MULTIPLECOPY       15
#define HHSC_MULTIPLEMOVE       16
#define HHSC_NOTECOPY           17
#define HHSC_NOTEMOVE           18
#define HHSC_TEXTCOPY           19
#define HHSC_TEXTMOVE           20
#define HHSC_TODOCOPY           21
#define HHSC_TODOMOVE           22
#define HHSC_DROPCOPYPOINT      23
#define HHSC_DROPCOPY           24
#define HHSC_DROPMOVEPOINT      25
#define HHSC_DROPMOVE           26

COLORREF HHAPI HHGetSystemColor (int);

#define HHCR_WINDOW             0
#define HHCR_BACKGROUND         1
#define HHCR_WINDOWFRAME        2
#define HHCR_WINDOWTEXT         3
#define HHCR_TEXTHIGHLIGHT      4
#define HHCR_BKGDHIGHLIGHT      5
#define HHCR_CTLTEXT            6
#define HHCR_CTLFACE            7
#define HHCR_CTLSHADOW          8
#define HHCR_CTLHIGHLIGHT       9
#define HHCR_GRAYTEXT           10

HGDIOBJ HHAPI HHGetSystemObject (int);

#define HHSO_WINDOW_BRUSH           0
#define HHSO_BACKGROUND_BRUSH       1
#define HHSO_WINDOWFRAME_BRUSH      2
#define HHSO_WINDOWTEXT_BRUSH       3
#define HHSO_TEXTHIGHLIGHT_BRUSH    4
#define HHSO_BKGDHIGHLIGHT_BRUSH    5
#define HHSO_CTLTEXT_BRUSH          6
#define HHSO_CTLFACE_BRUSH          7
#define HHSO_CTLSHADOW_BRUSH        8
#define HHSO_CTLHIGHLIGHT_BRUSH     9
#define HHSO_GRAYTEXT_BRUSH         10
#define HHSO_CTLFACEPAT_BRUSH       11
#define HHSO_CTLSHADOWPAT_BRUSH     12
#define HHSO_VAR_REGULAR_FONT       13
#define HHSO_VAR_BOLD_FONT          14
#define HHSO_DLG_TITLE_FONT         15
#define HHSO_APP_TITLE_FONT         16
#define HHSO_FIXED_FONT             17

DWORD HHAPI HHGetSystemInfo(int);
DWORD HHAPI HHSetSystemInfo(int, DWORD);

#define HHSI_DRAGDROP               0

#define HHSIF_INDRAGDROP            0x00000001



/********************************************************************
 * Tray Functions
 ********************************************************************/
VOID    HHAPI HHDeleteTray(HWND);
LRESULT HHAPI HHAddTrayType(DWORD, DWORD, LPSTR, DWORD, UINT);
VOID    HHAPI HHCopyTrayToCB(HWND);
HBITMAP HHAPI HHDuplicateBitmap(HBITMAP);

/********************************************************************
 * HHStatic Control
 ********************************************************************/
/* HHStatic Control Styles */
#define HHSS_LEFT               0x0000L
#define HHSS_CENTER             0x0001L
#define HHSS_RIGHT              0x0002L
#define HHSS_ICON               0x0003L
#define HHSS_LEFTNOWORDWRAP     0x000CL
#define HHSS_PRESSEDBEVEL       0x0020L
#define HHSS_RAISEDBEVEL        0x0040L

/* HHStatic Control Messages */
#define HHSTM_SETICON           (WM_USER+0)
#define HHSTM_GETICON           (WM_USER+1)

/********************************************************************
 * HHButton Control
 ********************************************************************/

/* HHButton Control Styles */
#define HHBS_PUSHBUTTON         0x0000L
#define HHBS_RESERVED1          0x0001L
#define HHBS_CHECKBOX           0x0002L
#define HHBS_AUTOCHECKBOX       0x0003L
#define HHBS_RADIOBUTTON        0x0004L
#define HHBS_RESERVED2          0x0005L
#define HHBS_RESERVED3          0x0006L
#define HHBS_GROUPBOX           0x0007L
#define HHBS_RESERVED4          0x0008L
#define HHBS_AUTORADIOBUTTON    0x0009L
#define HHBS_RESERVED5          0x000AL
#define HHBS_RESERVED6          0x000BL
#define HHBS_VERTICALBUTTON     0x000CL
#define HHBS_STICKYBUTTON       0x000DL
#define HHBS_AUTOSTICKYBUTTON   0x000EL
#define HHBS_TRAY               0x000FL
#define HHBS_DRAGICONBTN        0x0010L
#define HHBS_DRAGICONBMP        0x0011L
#define HHBS_LEFTTEXT           0x0020L
#define HHBS_ROTATERIGHT        0x0040L
#define HHBS_SPIN               0x0080L

/* HHButton Control Messages  */
#define HHBM_GETCHECK           (WM_USER+0)
#define HHBM_SETCHECK           (WM_USER+1)
#define HHBM_GETSTATE           (WM_USER+2)
#define HHBM_SETSTATE           (WM_USER+3)
#define HHBM_SETSTYLE           (WM_USER+4)
#define HHBM_GETBITMAP          (WM_USER+5)
#define HHBM_SETBITMAP          (WM_USER+6)
#define HHBM_GETDRAGICONCMDLST  (WM_USER+7)
#define HHBM_SETDRAGICONCMDLST  (WM_USER+8)
#define HHBM_GETDRAGICONCMD     (WM_USER+9)

/* HHButton Notification Codes */
#define HHBN_CLICKED            0
#define HHBN_TIMEOUT            1
#define HHBN_DBLCLK             2
#define HHBN_DRAGICONHELP       3
#define HHBN_DRAGICONCMDLST     4
#define HHBN_DRAGICONCMD        5

/********************************************************************
 * HHCombobox
 ********************************************************************/
/* Combo box styles */
#define HHCS_SIMPLE             0x0001L
#define HHCS_DROPDOWN           0x0002L
#define HHCS_DROPDOWNLIST       0x0003L
#define HHCS_AUTOHSCROLL        0x0040L
#define HHCS_SORT               0x0100L

/* Combo box messages */
#define HHCB_GETEDITSEL            (WM_USER+0)
#define HHCB_LIMITTEXT             (WM_USER+1)
#define HHCB_SETEDITSEL            (WM_USER+2)
#define HHCB_ADDSTRING             (WM_USER+3)
#define HHCB_DELETESTRING          (WM_USER+4)
#define HHCB_GETCOUNT              (WM_USER+6)
#define HHCB_GETCURSEL             (WM_USER+7)
#define HHCB_GETLBTEXT             (WM_USER+8)
#define HHCB_GETLBTEXTLEN          (WM_USER+9)
#define HHCB_INSERTSTRING          (WM_USER+10)
#define HHCB_RESETCONTENT          (WM_USER+11)
#define HHCB_FINDSTRING            (WM_USER+12)
#define HHCB_SELECTSTRING          (WM_USER+13)
#define HHCB_SETCURSEL             (WM_USER+14)
#define HHCB_SHOWDROPDOWN          (WM_USER+15)
#define HHCB_GETITEMDATA           (WM_USER+16)
#define HHCB_SETITEMDATA           (WM_USER+17)
#define HHCB_GETDROPPEDCONTROLRECT (WM_USER+18)
#define HHCB_GETDROPPEDSTATE       (WM_USER+23)
#define HHCB_FINDSTRINGEXACT       (WM_USER+24)

/* Combo box notification codes */
#define HHCN_ERRSPACE           (-1)
#define HHCN_SELCHANGE          1
#define HHCN_DBLCLK             2
#define HHCN_SETFOCUS           3
#define HHCN_KILLFOCUS          4
#define HHCN_EDITCHANGE         5
#define HHCN_EDITUPDATE         6
#define HHCN_DROPDOWN           7
#define HHCN_CLOSEUP            8
#define HHCN_SELENDOK           9
#define HHCN_SELENDCANCEL       10

/* Combo box message return values */
#define HHCB_OKAY               0
#define HHCB_ERR                (-1)
#define HHCB_ERRSPACE           (-2)

/********************************************************************
 * HHInk Control
 ********************************************************************/
/* Ink Control Styles */
#define HHIS_READONLY          0x0001L

/* Ink Control messages */
#define HHIM_BASE              (WM_USER+100)    /* Avoid NM_*, EM_*. */
#define HHIM_GETINK            (HHIM_BASE+0)
#define HHIM_SETINK            (HHIM_BASE+1)
#define HHIM_GETINKCOLOR       (HHIM_BASE+2)
#define HHIM_SETINKCOLOR       (HHIM_BASE+3)
#define HHIM_GETPENWIDTH       (HHIM_BASE+4)
#define HHIM_SETPENWIDTH       (HHIM_BASE+5)
#define HHIM_GETGRIDSIZE       (HHIM_BASE+6)
#define HHIM_SETGRIDSIZE       (HHIM_BASE+7)
#define HHIM_GETGRIDORIGIN     (HHIM_BASE+8)
#define HHIM_SETGRIDORIGIN     (HHIM_BASE+9)
#define HHIM_GETPENMODE        (HHIM_BASE+10)
#define HHIM_SETPENMODE        (HHIM_BASE+11)
#define HHIM_GETBITMAP         (HHIM_BASE+12)
#define HHIM_SETBITMAP         (HHIM_BASE+13)
#define HHIM_GETINKRECT        (HHIM_BASE+14)
#define HHIM_GETORIGIN         (HHIM_BASE+15)
#define HHIM_SETORIGIN         (HHIM_BASE+16)
#define HHIM_GETSCROLLSTEP     (HHIM_BASE+17)
#define HHIM_SETSCROLLSTEP     (HHIM_BASE+18)
#define HHIM_GETCHANGEINK      (HHIM_BASE+19)

#define HHIM_CANUNDO           HHEM_CANUNDO
#define HHIM_UNDO              HHEM_UNDO
#define HHIM_EMPTYUNDOBUFFER   HHEM_EMPTYUNDOBUFFER

/* Ink Control notifications */
#define HHIN_BASE              0x1000           /* Avoid edit EN_*, penwin HN_*. */
#define HHIN_SETFOCUS          (HHIN_BASE+1)
#define HHIN_KILLFOCUS         (HHIN_BASE+2)
#define HHIN_PENMODECHANGED    (HHIN_BASE+3)
#define HHIN_INKADDED          (HHIN_BASE+4)
#define HHIN_INKREMOVED        (HHIN_BASE+5)
#define HHIN_INKRECTCHANGED    (HHIN_BASE+6)
#define HHIN_ORIGINCHANGED     (HHIN_BASE+7)

/* Ink Control return value */
#define HHIC_OK                0
#define HHIC_ERR               (-1)

#define CTLCOLOR_INK           9

/* Paramater/Return values to HHIM_SETPENMODE and HHIM_GETPENMODE */
#define HHIMODE_NORMAL         0x0001
#define HHIMODE_ERASE          0x0002

/********************************************************************
 * HHPalette
 ********************************************************************/
/* Palette Messages */
#define HHPM_GETCTLHWND         (WM_USER+0)
#define HHPM_SETCTLHWND         (WM_USER+1)
#define HHPM_GETPENMODE         (WM_USER+2)
#define HHPM_SETPENMODE         (WM_USER+3)
#define HHPM_GETPLANE           (WM_USER+4)
#define HHPM_SETPLANE           (WM_USER+5)

/* Palette Notifications */
#define HHPN_SETFOCUS           1
#define HHPN_KILLFOCUS          2

/* Palette return values */
#define HHPL_OK                 0
#define HHPL_ERR                (-1)
#define HHPL_BADHWND            (-2)

#define CTLCOLOR_PALETTE        10

/********************************************************************
 * HHListbox
 ********************************************************************/
/* Listbox styles */
#define HHLS_NOTIFY             0x0001L
#define HHLS_SORT               0x0002L
#define HHLS_NOREDRAW           0x0004L
#define HHLS_DRAGABLE           0x0008L
#define HHLS_USECOLUMNS         0x0080L
#define HHLS_EXTENDEDSEL        0x0800L
#define HHLS_STANDARD           (HHLS_NOTIFY | HHLS_SORT | WS_VSCROLL | WS_BORDER)

/* Listbox messages */
#define HHLB_ADDSTRING          (WM_USER+1)
#define HHLB_INSERTSTRING       (WM_USER+2)
#define HHLB_DELETESTRING       (WM_USER+3)
#define HHLB_RESETCONTENT       (WM_USER+5)
#define HHLB_SETCURSEL          (WM_USER+7)
#define HHLB_GETCURSEL          (WM_USER+9)
#define HHLB_GETTEXT            (WM_USER+10)
#define HHLB_GETTEXTLEN         (WM_USER+11)
#define HHLB_GETCOUNT           (WM_USER+12)
#define HHLB_SELECTSTRING       (WM_USER+13)
#define HHLB_GETTOPINDEX        (WM_USER+15)
#define HHLB_FINDSTRING         (WM_USER+16)

#define HHLB_GETSELRANGE        (WM_USER+17)
#define HHLB_SETSELRANGE        (WM_USER+18)
#define HHLB_SETLBCOLUMNS       (WM_USER+19)

#define HHLB_SETTOPINDEX        (WM_USER+24)
#define HHLB_GETITEMRECT        (WM_USER+25)
#define HHLB_GETITEMDATA        (WM_USER+26)
#define HHLB_SETITEMDATA        (WM_USER+27)
#define HHLB_SETITEMHEIGHT      (WM_USER+33)
#define HHLB_GETITEMHEIGHT      (WM_USER+34)
#define HHLB_FINDSTRINGEXACT    (WM_USER+35)

#define HHLB_GETITEMINK         (WM_USER+37)
#define HHLB_SETITEMINK         (WM_USER+38)
#define HHLB_GETDRAGICONCOL     (WM_USER+39)
#define HHLB_SETDRAGICONCOL     (WM_USER+40)
#define HHLB_GETITEMSTATE       (WM_USER+41)
#define HHLB_SETITEMSTATE       (WM_USER+42)
#define HHLB_GETITEMLINES       (WM_USER+43)
#define HHLB_SETITEMLINES       (WM_USER+44)
#define HHLB_GETITEMDRAGICON    (WM_USER+45)
#define HHLB_SETITEMDRAGICON    (WM_USER+46)
#define HHLB_GETDEFAULTDRAGICON (WM_USER+47)
#define HHLB_SETDEFAULTDRAGICON (WM_USER+48)
#define HHLB_GETCMDLST          (WM_USER+49)
#define HHLB_SETCMDLST          (WM_USER+50)
#define HHLB_GETDRAGICONCMD     (WM_USER+51)
#define HHLB_GETDRAGICONITEMS   (WM_USER+52)

/* Listbox notification codes */
#define HHLBN_ERRSPACE          (-2)
#define HHLBN_ERR               (-1)
#define HHLBN_SELCHANGE         1
#define HHLBN_DBLCLK            2
#define HHLBN_SELCANCEL         3
#define HHLBN_SETFOCUS          4
#define HHLBN_KILLFOCUS         5
#define HHLBN_DRAGICONHELP      6
#define HHLBN_DRAGICONCMDLST    7
#define HHLBN_DRAGICONCMD       8

/* Listbox message return values */
#define HHLB_OKAY               0
#define HHLB_ERR                (-1)
#define HHLB_ERRSPACE           (-2)

/* Listbox item state flags */
#define LF_NORMAL               0x00
#define LF_BOLD                 0x01
#define LF_INK                  0x02
#define LF_MASK                 0x03

/* LbColumn flags */
#define LCF_LEFTALIGN           0x00
#define LCF_CENTERALIGN         0x01
#define LCF_RIGHTALIGN          0x02
#define LCF_NEWLINE             0x04
#define LCF_INK                 0x08

typedef struct tagLBCOLUMN
{
   WORD dpxWidth;
   BYTE bFlags;
}LBCOLUMN;
typedef LBCOLUMN FAR * LPLBCOLUMN;

typedef struct tagLBDRAGICON
{
   HBITMAP hbmUp;
   HBITMAP hbmDown;
}LBDRAGICON;
typedef LBDRAGICON FAR * LPLBDRAGICON;

#define HHLBITEMLINESMAX       4

/********************************************************************
 * HHScrollbar Control
 ********************************************************************/
#define HHSBS_HORZ              0x0000L
#define HHSBS_VERT              0x0001L
#define HHSBS_TOPALIGN          0x0002L
#define HHSBS_LEFTALIGN         0x0002L
#define HHSBS_BOTTOMALIGN       0x0004L
#define HHSBS_RIGHTALIGN        0x0004L

/********************************************************************
 * Tabbox control
 ********************************************************************/
#define HHTS_HORZ               0x0000L
#define HHTS_VERT               0x0001L
#define HHTS_TOP                0x0002L
#define HHTS_BOTTOM             0x0000L
#define HHTS_LEFT               0x0002L
#define HHTS_RIGHT              0x0000L
#define HHTS_FIXEDSIZE          0x0010L
#define HHTS_JUSTIFIED          0x0020L
#define HHTS_SORT               0x0040L
#define HHTS_NOREDRAW           0x0080L

#define HHTM_ADDTAB             (WM_USER+1)
#define HHTM_INSERTTAB          (WM_USER+2)
#define HHTM_DELETETAB          (WM_USER+3)
#define HHTM_GETTABCOUNT        (WM_USER+4)
#define HHTM_SETTOPTAB          (WM_USER+5)
#define HHTM_GETTOPTAB          (WM_USER+6)
#define HHTM_GETTABTEXT         (WM_USER+7)
#define HHTM_GETTABTEXTLEN      (WM_USER+8)
#define HHTM_SETFIXEDTABLEN     (WM_USER+9)
#define HHTM_GETFIXEDTABLEN     (WM_USER+10)
#define HHTM_GETTABCLICKED      (WM_USER+11)
#define HHTM_CLEARTABBOX        (WM_USER+12)
#define HHTM_GETTABRECT         (WM_USER+13)
#define HHTM_GETCLIENTRECT      (WM_USER+14)

#define HHTN_SETFOCUS           3
#define HHTN_KILLFOCUS          2
#define HHTN_TOPTABCHANGED      1
#define HHTB_ERR                (-1)
#define HHTB_ERRSPACE           (-2)

#define CTLCOLOR_TABBOX         7

int HHAPI HHFillTabbox (HWND, LPSTR);

/********************************************************************
 * DogEar control
 ********************************************************************/
#define HHDM_SHOWARROWS         (WM_USER+1)

#define HHDSA_SHOWBOTH          0
#define HHDSA_HIDENEXT          1
#define HHDSA_HIDEPREVIOUS      2

#define HHDN_NEXT               1
#define HHDN_PREVIOUS           2

#define CTLCOLOR_DOGEAR         8

/********************************************************************
 * HHedit control
 ********************************************************************/

/* HHEdit control styles */
#define HHES_LEFT               0x00000000L
#define HHES_CENTER             0x00000001L
#define HHES_RIGHT              0x00000002L
#define HHES_MULTILINE          0x00000004L
#define HHES_UPPERCASE          0x00000008L
#define HHES_LOWERCASE          0x00000010L
#define HHES_PASSWORD           0x00000020L
#define HHES_AUTOVSCROLL        0x00000040L
#define HHES_AUTOHSCROLL        0x00000080L
#define HHES_NOHIDESEL          0x00000100L
#define HHES_OEMCONVERT         0x00000400L
#define HHES_READONLY           0x00000800L
#define HHES_WANTRETURN         0x00001000L

/* HHEdit control messages */
#define HHEM_BASE                   (WM_USER+0)     /* Avoid NM_*, IM_*. */
#define HHEM_GETSEL                 (HHEM_BASE+0)
#define HHEM_SETSEL                 (HHEM_BASE+1)
#define HHEM_GETRECT                (HHEM_BASE+2)
#define HHEM_SETRECT                (HHEM_BASE+3)
#define HHEM_SETRECTNP              (HHEM_BASE+4)
#define HHEM_LINESCROLL             (HHEM_BASE+6)
#define HHEM_GETMODIFY              (HHEM_BASE+8)
#define HHEM_SETMODIFY              (HHEM_BASE+9)
#define HHEM_GETLINECOUNT           (HHEM_BASE+10)
#define HHEM_LINEINDEX              (HHEM_BASE+11)
#define HHEM_SETHANDLE              (HHEM_BASE+12)
#define HHEM_GETHANDLE              (HHEM_BASE+13)
#define HHEM_LINELENGTH             (HHEM_BASE+17)
#define HHEM_REPLACESEL             (HHEM_BASE+18)
#define HHEM_GETLINE                (HHEM_BASE+20)
#define HHEM_LIMITTEXT              (HHEM_BASE+21)
#define HHEM_CANUNDO                (HHEM_BASE+22)
#define HHEM_UNDO                   (HHEM_BASE+23)
#define HHEM_FMTLINES               (HHEM_BASE+24)
#define HHEM_LINEFROMCHAR           (HHEM_BASE+25)
#define HHEM_SETTABSTOPS            (HHEM_BASE+27)
#define HHEM_SETPASSWORDCHAR        (HHEM_BASE+28)
#define HHEM_EMPTYUNDOBUFFER        (HHEM_BASE+29)
#define HHEM_GETFIRSTVISIBLELINE    (HHEM_BASE+30)
#define HHEM_SETREADONLY            (HHEM_BASE+31)
#define HHEM_SETWORDBREAKPROC       (HHEM_BASE+32)
#define HHEM_GETWORDBREAKPROC       (HHEM_BASE+33)
#define HHEM_GETPASSWORDCHAR        (HHEM_BASE+34)
#define HHEM_POSFROMCHAR            (HHEM_BASE+35)
#define HHEM_GETLINEHEIGHT          (HHEM_BASE+40)    /* Mulitiline only */
#define HHEM_SETPANELWINDOW         (HHEM_BASE+41)    /* Mulitiline only */
#define HHEM_GETPANELWINDOW         (HHEM_BASE+42)    /* Mulitiline only */
#define HHEM_GETPANELLINES          (HHEM_BASE+43)    /* Mulitiline only */
#define HHEM_GETPANELLINESSHOWING   (HHEM_BASE+44)    /* Mulitiline only */
#define HHEM_GETLINESSCROLLED       (HHEM_BASE+45)    /* Mulitiline only */
#define HHEM_SHOWLENS               (HHEM_BASE+46)
#define HHEM_CHECKDRAGICON          (HHEM_BASE+48)
#define HHEM_GETMAXPIXELWIDTH       (HHEM_BASE+49)    /* Mulitiline only */
#define HHEM_GETAVECHARWIDTH        (HHEM_BASE+50)    /* Mulitiline only */
#define HHEM_GETXOFFSET             (HHEM_BASE+51)    /* Mulitiline only */
#define HHEM_GETMAXSCROLLLINES      (HHEM_BASE+52)    /* Mulitiline only */
#define HHEM_SETMAXSCROLLLINES      (HHEM_BASE+53)    /* Mulitiline only */
#define HHEM_GETMAXSCROLLPIXELWIDTH (HHEM_BASE+54)    /* Mulitiline only */
#define HHEM_SETMAXSCROLLPIXELWIDTH (HHEM_BASE+55)    /* Mulitiline only */
#define HHEM_GETLENSTYPE            (HHEM_BASE+56)
#define HHEM_SETLENSTYPE            (HHEM_BASE+57)
#define HHEM_CHARFROMPOS            (HHEM_BASE+58)
#define HHEM_REFORMAT               (HHEM_BASE+59)
#define HHEM_GETLIMITTEXT           (HHEM_BASE+60)

/* Flags for the LOWORD of lParam of the HHEM_SETPANELWINDOW message. */
#define HHSPW_USEPANELPARENT        0x0001

typedef int   (CALLBACK* HHEDITWORDBREAKPROC)(LPSTR lpch, int ichCurrent, int cch, int code);

/* HHEDITWORDBREAKPROC code values */
#define HHWB_LEFT               0
#define HHWB_RIGHT              1
#define HHWB_ISDELIMITER        2

/* Flags for HHEM_SETLENSTYPE */
#define HHLT_DEFAULT            0
#define HHLT_BOXLENS            1
#define HHLT_FULLKBD            2
#define HHLT_NUMKBD             3
#define HHLT_ATMKBD             4

/* HHEdit control notification codes */
/* Note that we want to avoid the HN_* values defined for penwin. (HN_ENDREC,
   HN_DELAYEDRECOGFAIL, HN_RCRESULT, HN_ENDKKCONVERT, and HN_SELCHANGE.) These
   are all below 0x0100. */
#define HHEN_BASE               0
#define HHEN_SETFOCUS           (HHEN_BASE+0x0100)
#define HHEN_KILLFOCUS          (HHEN_BASE+0x0200)
#define HHEN_CHANGE             (HHEN_BASE+0x0300)
#define HHEN_UPDATE             (HHEN_BASE+0x0400)
#define HHEN_ERRSPACE           (HHEN_BASE+0x0500)
#define HHEN_MAXTEXT            (HHEN_BASE+0x0501)
#define HHEN_HSCROLL            (HHEN_BASE+0x0601)
#define HHEN_VSCROLL            (HHEN_BASE+0x0602)
#define HHEN_SELCHANGE          (HHEN_BASE+0x0701)
#define HHEN_SCROLLCHANGE       (HHEN_BASE+0x0702)
#define HHEN_SCROLLRANGECHG     (HHEN_BASE+0x0703)
#define HHEN_ARROWOUTTOP        (HHEN_BASE+0x0704)
#define HHEN_ARROWOUTBOTTOM     (HHEN_BASE+0x0705)

/********************************************************************
 * HHnote control
 ********************************************************************/

/* HHNote control styles */
/* These are assumed to have the same values as
   the corresponding HHedit styles. */
#define HHNS_AUTOVSCROLL        0x00000040L
#define HHNS_AUTOHSCROLL        0x00000080L
#define HHNS_NOHIDESEL          0x00000100L
#define HHNS_OEMCONVERT         0x00000400L
#define HHNS_READONLY           0x00000800L
#define HHNS_WANTRETURN         0x00001000L

#define HHNS_STYLEMASK          (HHNS_AUTOVSCROLL | HHNS_AUTOHSCROLL | \
                                 HHNS_NOHIDESEL | HHNS_OEMCONVERT | \
                                 HHNS_READONLY | HHNS_WANTRETURN)

/* HHNote control messages */
#define HHNM_BASE               (WM_USER+200)   /* Avoid EM_*, IM_*. */
#define HHNM_GETPLANE           (HHNM_BASE+1)
#define HHNM_SETPLANE           (HHNM_BASE+2)
#define HHNM_GETTEXTHWND        (HHNM_BASE+3)
#define HHNM_GETINKHWND         (HHNM_BASE+4)

#define HHNM_CANUNDO            HHEM_CANUNDO
#define HHNM_UNDO               HHEM_UNDO
#define HHNM_EMPTYUNDOBUFFER    HHEM_EMPTYUNDOBUFFER

/* HHNote control notification codes */
#define HHNN_BASE               0x2000
#define HHNN_SETFOCUS           HHEN_SETFOCUS
#define HHNN_KILLFOCUS          HHEN_KILLFOCUS
#define HHNN_PLANECHANGE        (HHNN_BASE+3)

/* Note Control return value */
#define HHNT_OK                 0
#define HHNT_ERR                (-1)

/* Paramater/Return values to HHPM_GETPLANE, HHPM_SETPLANE,
   HHNM_GETPLANE and HHNM_SETPLANE */
#define HHNPLANE_TEXT           0x0001
#define HHNPLANE_INK            0x0002

/********************************************************************
 * Drag and drop support
 ********************************************************************/

/* The max number of DDD_* types in a drag and drop.
   This current value allows for some expansion. */
#define MAXDDTYPES              8

/* Drag and drop messages. */

/* Handheld systems specific messages */
#define WM_HANDHELDFIRST        0x358
#define WM_HANDHELDLAST         0x35F

#define WM_QUERYDRAG            (WM_HANDHELDFIRST +  1)
#define WM_DROPDATA             (WM_HANDHELDFIRST +  2)
#define WM_DRAGDROPREQUEST      (WM_HANDHELDFIRST +  3)

/* Drag and drop data types in the QUERYDRAG and DROPDATA. */
#define DDD_NONE                0xFFFFFFFFL
#define DDD_SOSID               0xFFFFFFFEL
#define DDD_TEXT                0xFFFFFFFDL
#define DDD_TEXTLIST            0xFFFFFFFCL
#define DDD_HBITMAP             0xFFFFFFFBL
#define DDD_HPENDATA            0xFFFFFFFAL

/* The data block sent with a WM_QUERYDRAG message. */
typedef struct tagQUERYDRAG
{
    WORD        wQueryType;         /* The type of query. */
    HWND        hwndSource;         /* The source of the query. */
    POINT       pt;                 /* The screen coordinate of the query. */
    BOOL        fIntercepted;       /* The message has already been intercepted
                                       by the parent or owner and the receiver
                                       should not process the message as normal.
                                       Non-positional drop controls should
                                       ignore the message and return 0L.
                                       Positional drop controls should do
                                       whatever cursor tracking they normally
                                       would but nothing else. They should
                                       then return any positional value as
                                       the LRESULT. A value of (~(0L)) is
                                       used indicate an illegal drop position
                                       such as beyond the last visible line
                                       in an edit. */
    DWORD       dwReserved1;
    DWORD       dwReserved2;
    DWORD       dwReserved3;
    DWORD       dwSOSType;          /* OBJTYPE_*: The type of the SOS IDs held
                                       by lpdwSOSIDs if they are homogeneous,
                                       otherwise OBJTYPE_UNKNOWN. */
    UINT        cSOSID;             /* The number of SOS IDs held by lpdwSOSIDs. */
    LPDWORD     lpdwSOSIDs;         /* If there is one SOS ID, then this field
                                       holds it directly. If there is more than
                                       one, it points to a global segment which
                                       holds the arrary of IDs.
                                       This list can not be edited
                                       by the destination. */
    UINT        cTypes;             /* The number of types in rgdwTypes[]. */
    DWORD       rgdwTypes[1];       /* The types of data available.
                                       This list can be edited
                                       by the destination. */
} QUERYDRAG;
typedef QUERYDRAG FAR *  LPQUERYDRAG;
typedef QUERYDRAG NEAR * NPQUERYDRAG;

/* Values for wQueryType in QUERYDRAG. */
#define QDT_START               1
#define QDT_MOVE                2
#define QDT_END                 3

/* The values for dwSOSType in QUERYDRAG are defined in HHapp.h in the SOS. */

/* Responses to a WM_QUERYDRAG message. */
#define QDR_DROPREFUSED         0x00000000L
#define QDR_DROPREFUSED1        0x00000001L
#define QDR_ENDOK               0x00000002L
#define QDR_DROPCOPYPOINT       0x00000003L
#define QDR_DROPCOPY            0x00000004L
#define QDR_DROPMOVEPOINT       0x00000005L
#define QDR_DROPMOVE            0x00000006L
#define QDR_DROPOVERSOURCE      0x00000007L

/* The data block sent with a WM_DROPDATA message. */
typedef struct tagDROPDATA
{
    WORD        wDropType;          /* The type of drop. */
    HWND        hwndSource;         /* The source of the drop. */
    POINT       pt;                 /* The screen coordinate of the drop. */
    BOOL        fIntercepted;       /* The message has already been intercepted
                                       by the parent or owner and the receiver
                                       should not process the message as normal.
                                       Non-positional drop controls should
                                       ignore the message. Positional drop
                                       controls should do whatever cursor
                                       tracking cleanup they normally would
                                       but nothing else. Both should return
                                       ((LPDROPDATA)lParam)->dwDDResult. */
    DWORD       dwReserved1;
    DWORD       dwReserved2;
    DWORD       dwReserved3;
    HCURSOR     hcurCopy;           /* Copy cursor.
                                       Used by controls such as the tray
                                       which may send the data on later.
                                       NULL uses system document copy
                                       cursor HHSC_DROPCOPY. */
    HCURSOR     hcurMove;           /* Move cursor.
                                       Used by controls such as the tray
                                       which may send the data on later.
                                       NULL uses system document move
                                       cursor HHSC_DROPMOVE. */
    DWORD       dwType;             /* The type of the data for DDT_DATA. */
    DWORD       dwSize;             /* The size of the data for DDT_DATA.
                                       The size includes the terminating
                                       NULL for the text formats.
                                       This will be 0 for data which is sent
                                       directly in lpData without using a
                                       separate global segment. */
    VOID FAR *  lpData;             /* The data for DDT_DATA.
                                       The SOS ID for DDD_SOSID with
                                       cSOSID == 1 is sent directly in lpData.
                                       The list of SOS IDs for DDD_SOSID
                                       with cSOSID > 1 is sent in a segment
                                       pointed to by lpData. The data for
                                       DDD_TEXT and DDD_TEXTLIST are sent in
                                       a segment pointed to by lpData. The
                                       handles for DDD_HBITMAP and DDD_HPENDATA
                                       are sent directly in lpData. */
    DWORD       dwSOSType;          /* If the data is of type DDD_SOSID, then
                                       this is the same as for QUERYDRAG. */
    UINT        cSOSID;             /* If the data is of type DDD_SOSID, then
                                       this is the same as for QUERYDRAG. */
    DWORD       dwDDResult;         /* The result from the last WM_DROPDATA. */
} DROPDATA;
typedef DROPDATA FAR *  LPDROPDATA;
typedef DROPDATA NEAR * NPDROPDATA;

/* Values for wDropType in DROPDATA. */
#define DDT_START               1
#define DDT_DATA                2
#define DDT_END                 3

/* Responses to a WM_DROPDATA message. */
#define DDR_UNKNOWNERROR        0x00000000L
#define DDR_UNKNOWNERROR1       0x00000001L
#define DDR_OK                  0x00000002L
#define DDR_BADTYPEERROR        0x00000003L
#define DDR_MEMERROR            0x00000004L
#define DDR_FILEERROR           0x00000005L
#define DDR_INTERNALERROR       0x00000006L
#define DDR_TOOMANYTYPES        0x00000007L

/* The data block sent with a WM_DRAGDROPREQUEST message. */
typedef struct tagDRAGDROPREQ
{
    WORD        wRequestType;       /* The type of request. */
    HWND        hwndSource;         /* The window sending the
                                       WM_DRAGDROPREQUEST message. */
    HWND        hwndDest;           /* The destination of the drop. */
    WORD        wControlID;         /* The ID of the drag icon or listbox
                                       control. */
    WORD        wStart;             /* The start index of the source
                                       item in the LB or ~0. */
    WORD        wEnd;               /* The end index of the source
                                       item in the LB or ~0. */
    HCURSOR     hcurCopy;           /* Copy cursor.
                                       NULL uses system document copy
                                       cursor HHSC_DROPCOPY. */
    HCURSOR     hcurMove;           /* Move cursor.
                                       NULL uses system document move
                                       cursor HHSC_DROPMOVE. */
    DWORD       dwReserved1;
    DWORD       dwReserved2;
    DWORD       dwReserved3;
    LPQUERYDRAG lpQueryDrag;        /* DDRT_START:    NULL to app. Pointer returned.
                                       DDRT_DROPDATA: Edited version of list
                                                      from the last WM_QUERYDRAG.
                                       DDRT_END:      NULL.
                                                Any memory allocated durring
                                                DDRT_START should be freed
                                                durring DDRT_END.
                                       */
    DWORD       dwQDResult;         /* DDRT_START:    QDR_DROPREFUSED;
                                       DDRT_DROPDATA: From the last WM_QUERYDRAG.
                                       DDRT_END:      From the last WM_QUERYDRAG.
                                       */
    DROPDATA    DropData;           /* The drop data block for the app to use.
                                       The app must use this for the DDT_DATA
                                       messages or fill in DropData.dwDDResult
                                       from the last DDT_DATA since the control
                                       will use it later. */
} DRAGDROPREQ;
typedef DRAGDROPREQ FAR *  LPDRAGDROPREQ;
typedef DRAGDROPREQ NEAR * NPDRAGDROPREQ;

/* Values for wRequestType in DRAGDROPREQ. */
#define DDRT_START              1
#define DDRT_DROPDATA           2
#define DDRT_END                3

/* Responses to a WM_DRAGDROPREQUEST message. */
#define DDRR_UNKNOWNERROR       0x00000000L
#define DDRR_UNKNOWNERROR1      0x00000001L
#define DDRR_OK                 0x00000002L
#define DDRR_BADTYPEERROR       0x00000003L
#define DDRR_MEMERROR           0x00000004L
#define DDRR_FILEERROR          0x00000005L
#define DDRR_INTERNALERROR      0x00000006L
#define DDRR_TOOMANYTYPES       0x00000007L


#ifndef RC_INVOKED

/********************************************************************
 * AppMan (Application Management)
 *
 * Messages, Constants, Structs, &Functions
 ********************************************************************/
/* AppMan Messages */
#define APMN_BASE               WM_USER
#define APMN_ACTION             APMN_BASE + 1

/* Error returns */
#define HHAPMN_ERROK                        0
#define HHAPMN_ERRAPPNOTFOUND               1
#define HHAPMN_ERRAPPALREADYINSTALLED       2
#define HHAPMN_ERROUTOFMEMORY               3
#define HHAPMN_ERRACTIVATEFAIL              4
#define HHAPMN_ERRREGISTEREVENTFAILED       5
#define HHAPMN_ERRUNREGISTEREVENTFAILED     6
#define HHAPMN_ERREVENTEXISTS               7
#define HHAPMN_ERREVENTNOTFOUND             8
#define HHAPMN_ERRNULLPATHNAME              9
#define HHAPMN_ERRINVALIDARGS               10
#define HHAPMN_ERREXECFAILBASE              2000

/* Global Actions */
#define HHAPMN_GLOBAL_REACTIVATE            1

/* Local Actions */
#define HHAPMN_LOCAL_NOARG                  1
#define HHAPMN_LOCAL_OBJECT                 2
#define HHAPMN_LOCAL_EVENTOCCURRED          3
#define HHAPMN_LOCAL_APPBASE                4096

/* Event Flag Fields*/
#define HHAPMN_EVENTFLAG_NOTIFYALWAYS       0x00000001L


/* struct declarations */
typedef struct tagAPPMAN
{
    UINT        uLocalAction;   /* Info describing application invocation */
    LONG        lArg;           /* Long Arg       */
    ENTRYID     eidArg;         /* SOS object arg */
    LPSTR       lpstrArg;       /* C string arg.  */
} APPMAN, * PAPPMAN, FAR * LPAPPMAN;

typedef struct tagAPMNRECT
{
    BOOL        fSizeChanged;
    int         AppLeft;
    int         AppTop;
    int         AppWidth;
    int         AppHeight;
} APMNRECT, * PAPMNRECT, FAR * LPAPMNRECT;

typedef struct tagEVENTDESC
{
    ULONG       ulEventFlags;
    ULONG       ulEventMask;
    LONG        lEventContext;
    ENTRYID     eid;
} EVENTDESC, * PEVENTDESC, FAR * LPEVENTDESC;

/* Function prototypes */
short HHAPI HHAddApp (LPSTR, LPSTR);
short HHAPI HHGetAppArguments (HWND, LPAPPMAN, LPAPMNRECT, LPEVENTDESC);
short HHAPI HHInvokeApp(LPSTR, LPAPPMAN, BOOL);
short HHAPI HHRemoveApp(LPSTR);
VOID  HHAPI HHSetAppRectangle (int, int, int, int);
short HHAPI HHRegisterEvent (LPSTR, LPEVENTDESC);
short HHAPI HHUnregisterEvent (LPSTR, LPEVENTDESC);


#endif /* RC_INVOKED */

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif    /* __cplusplus */

#endif // _INC_HHSYSTEMH
