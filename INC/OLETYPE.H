/*****************************************************************************
*
* oletype.h -  This file defines some OLE types required by the SOS API
*
*               Version 1.0
*
*               Copyright (c) 1993, Microsoft Corp. All rights reserved.
*
******************************************************************************
*
*
\****************************************************************************/

#ifndef OLETYPE_H
#define OLETYPE_H 1
typedef unsigned long ULONG;
typedef unsigned short WCHAR;
typedef char __int64[8];
typedef ULONG LHANDLE;
typedef LHANDLE FAR *LPLHANDLE;
/*
 * GUID and IID
 * A Global Unique IDentifier (GUID) is a 16-byte value which uniquely identifies something.
 */
/*
typedef struct GUID
{
	BYTE bits[16];
} GUID, far * LPGUID;
*/
/*
 * An Interface IDentifier (IID) is a GUID which identifies a particular interface to an object:
 */
//typedef GUID IID, far * LPIID;

//typedef unsigned long	HRESULT;

//typedef unsigned long	SCODE;

// #define FAILED(code) ((SCODE)(code) & 0x80000000)
#define FAILED(code) (!!(code))

#endif // OLETYPE_H
