//---------------------------------------------------------------------------
//		Copyright (C) 1992, Microsoft Corporation
//
// You have a royalty-free right to use, modify, reproduce and distribute
// the Sample Custom Control Files (and/or any modified version) in any way
// you find useful, provided that you agree that Microsoft has no warranty,
// obligation or liability for any Custom Control File.
//---------------------------------------------------------------------------
// PictBlt.h
//---------------------------------------------------------------------------
// Provides the prototypes for PictStretchBlt, and PictFMemDC.
// The macro PictBitBlt is also defined to correspond to the API BitBlt.
//---------------------------------------------------------------------------

BOOL PictFMemDC(HDC hdc);

BOOL PictStretchBlt(HDC hdcDest, int x, int y, int cx, int cy, HDC hdcSrc, int xSrc, int ySrc, int cxSrc, int cySrc, DWORD dwRop);

#define PictBitBlt(hdcDest, x, y, cx, cy, hdcSrc, xSrc, ySrc, dwRop) \
    PictStretchBlt(hdcDest, x, y, cx, cy, hdcSrc, xSrc, ySrc, cx, cy, dwRop)
