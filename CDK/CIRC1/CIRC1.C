//---------------------------------------------------------------------------
//		Copyright (C) 1991-92, Microsoft Corporation
//
// You have a royalty-free right to use, modify, reproduce and distribute
// the Sample Custom Control Files (and/or any modified version) in any way
// you find useful, provided that you agree that Microsoft has no warranty,
// obligation or liability for any Custom Control File.
//---------------------------------------------------------------------------
// Circ1.c
//---------------------------------------------------------------------------
// Contains control procedure for CIRC1 control
//---------------------------------------------------------------------------

#include <windows.h>
#include <vbapi.h>
#include "circ1.h"

//---------------------------------------------------------------------------
// Global Variables
//---------------------------------------------------------------------------
HANDLE hmodDLL;


//---------------------------------------------------------------------------
// Circle Control Procedure
//---------------------------------------------------------------------------
LONG FAR PASCAL _export CircleCtlProc
(
    HCTL   hctl,
    HWND   hwnd,
    USHORT msg,
    USHORT wp,
    LONG   lp
)
{
    return VBDefControlProc(hctl, hwnd, msg, wp, lp);
}


//---------------------------------------------------------------------------
// Initialize library. This routine is called when the first client loads
// the DLL.
//---------------------------------------------------------------------------
int FAR PASCAL LibMain
(
    HANDLE hModule,
    WORD   wDataSeg,
    WORD   cbHeapSize,
    LPSTR  lpszCmdLine
)
{
    // Avoid warnings on unused (but required) formal parameters
    wDataSeg	= wDataSeg;
    cbHeapSize	= cbHeapSize;
    lpszCmdLine = lpszCmdLine;

    hmodDLL = hModule;

    return 1;
}


//---------------------------------------------------------------------------
// Register custom control. This routine is called by VB when the custom
// control DLL is loaded for use.
//---------------------------------------------------------------------------
BOOL FAR PASCAL _export VBINITCC
(
    USHORT usVersion,
    BOOL   fRuntime
)
{
    // Avoid warnings on unused (but required) formal parameters
    fRuntime  = fRuntime;
    usVersion = usVersion;

    // Register control(s)
    return VBRegisterModel(hmodDLL, &modelCircle);
}


//---------------------------------------------------------------------------
// WEP
//---------------------------------------------------------------------------
// C7 and QCWIN provide default a WEP:
//---------------------------------------------------------------------------
#if (_MSC_VER < 610)

int FAR PASCAL WEP(int fSystemExit);

//---------------------------------------------------------------------------
// For Windows 3.0 it is recommended that the WEP function reside in a
// FIXED code segment and be exported as RESIDENTNAME.  This is
// accomplished using the alloc_text pragma below and the related EXPORTS
// and SEGMENTS directives in the .DEF file.
//
// Read the comments section documenting the WEP function in the Windows
// 3.1 SDK "Programmers Reference, Volume 2: Functions" before placing
// any additional code in the WEP routine for a Windows 3.0 DLL.
//---------------------------------------------------------------------------
#pragma alloc_text(WEP_TEXT,WEP)

//---------------------------------------------------------------------------
// Performs cleanup tasks when the DLL is unloaded.  WEP() is
// called automatically by Windows when the DLL is unloaded (no
// remaining tasks still have the DLL loaded).	It is strongly
// recommended that a DLL have a WEP() function, even if it does
// nothing but returns success (1), as in this example.
//---------------------------------------------------------------------------
int FAR PASCAL WEP
(
    int fSystemExit
)
{
    // Avoid warnings on unused (but required) formal parameters
    fSystemExit = fSystemExit;

    return 1;
}
#endif // C6

//---------------------------------------------------------------------------
