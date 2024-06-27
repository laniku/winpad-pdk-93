/*
 *	M A P I D E F S . H
 *	
 *	Base definitions that MAPI objects and the objects that they
 *	derive from (table, stream, property, unknown) have in common.
 */

#ifndef MAPIDEFS_H
#define MAPIDEFS_H

/* CDECL defines to be nothing in windef.h unless you define DOSWIN32. */
/* It's much easier for us to have the definition here. */

#ifdef CDECL
#undef CDECL
#endif
#define CDECL __cdecl

/*
 *	This flag is used in many different MAPI calls to signify that
 *	the object opened by the call should be modifiable.
 */

#define MAPI_MODIFY				((ULONG) 0x00000001)

/*
 *	The MAPI_UNICODE flag is used in many different MAPI calls to signify
 *	that strings passed through the interface are in Unicode (a 16-bit
 *	character set). The default is an 8-bit character set.
 *	
 *	The value fMapiUnicode can be used as the 'normal' value for
 *	that bit, given the application's default character set.
 */

#define MAPI_UNICODE			((ULONG) 0x80000000)

#ifdef UNICODE
#define fMapiUnicode			MAPI_UNICODE
#else
#define fMapiUnicode			0
#endif

/* Simple data types */

/*
 *	The next three definitions match those OLE 2.0 uses (in scode.h)
 *		SCODE		16 bits of error code information in a long
 *		HRESULT		handle to a result code (and eventually other
 *					information)
 *		hrSuccess	Special handle to no-error result
 */
typedef long			SCODE;
typedef SCODE			HRESULT;
#define hrSuccess		((HRESULT) 0)

/* 64-bit unsigned integer */
/*	Modified 2/3/93 by DanaB to match system/OLE's ULARGE_INTEGER */
typedef struct _LONGLONG
{
	ULONG ulLow;
	ULONG ulHigh;
} LONGLONG;

/* Simple MAPI opaque handle */
#ifndef __LHANDLE
#define __LHANDLE
typedef unsigned long       LHANDLE, FAR * LPLHANDLE;
#endif

/* Byte-order-independent version of GUID (world-unique identifier) */
typedef struct _MAPIUID
{
	BYTE ab[16];
} MAPIUID, FAR * LPMAPIUID;

#ifndef GUID_DEFINED
#define GUID_DEFINED

/* This is the same definition as OLE 2.0 uses (in compobj.h). */
/* This is also defined in rpcdce.h (by windows). That's why there's */
/* a ifndef around the definition. */
typedef struct _GUID
{
	unsigned long  Data1;
	unsigned short Data2;
	unsigned short Data3;
	unsigned char  Data4[8];
} GUID;

#endif /* defined (GUID_DEFINED) */

#ifndef LPGUID						/* Currently defined in OLE2 compobj.h */
typedef GUID FAR *	LPGUID;
#endif

#ifndef DEFINE_GUID

#ifndef EXTERN_C
#ifdef __cplusplus
    #define EXTERN_C    extern "C"
#else
    #define EXTERN_C    extern
#endif
#endif	/* EXTERN_C */


#define DEFINE_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
	EXTERN_C const GUID CDECL FAR name

#endif	/* DEFINE_GUID */

/*
 *	WARNING!!! This macro is only used to define the external 
 *	declarations of MAPI IID guids.  The real definition is
 *	in $(MAPI)\src\common\mapiguid.c
 */
#define DEFINE_MAPIGUID(name, l, w1, w2) \
	DEFINE_GUID(name, l, w1, w2, 0,0,0,0,0,0,0,0)

/*
 *	Progress dialog request structure and callback function.
 */

typedef SCODE (CDECL PROGRESSPROC)(
	LPVOID		lpvContext,
	ULONG		ulValue,
	ULONG		ulCount,
	ULONG		ulTotal);
typedef PROGRESSPROC FAR *LPPROGRESSPROC;

#define MAPI_TOP_LEVEL		((ULONG) 0x00000001)	/* ulProgressFlags */

typedef struct
{
	LPPROGRESSPROC	lpProgressProc;
	LPVOID			lpvProgressContext;
	ULONG			ulProgressFlags;
	ULONG			ulMin;
	ULONG			ulMax;
} ProgressInfo, FAR *LPProgressInfo;

#ifdef WINPAD
typedef WORD ENTRYID, FAR * LPENTRYID;
#endif
/*
 *	Pointer types for MAPI-defined objects.
 *	These are all forward declarations. The dispatch tables
 *	themselves, which include all the object methods, are defined
 *	in the other MAPI headers.
 */
#ifndef __cplusplus

#ifndef LPUNKNOWN
typedef struct _DTBLUNKNOWN			FAR * IUnknown;
#endif
#ifndef WINPAD
typedef struct _DTBLMSGSTORE		FAR * IMsgStore;
#endif
typedef struct _DTBLFOLDER			FAR * IFolder;
typedef struct _DTBLMESSAGE			FAR * IMessage;
#ifndef WINPAD
typedef struct _DTBLATTACH			FAR * IAttach;
typedef struct _DTBLADDRBOOK		FAR * IAddrBook;
typedef struct _DTBLABCONTAINER		FAR * IABContainer;
typedef struct _DTBLMAILUSER		FAR * IMailUser;
typedef struct _DTBLDISTLIST		FAR * IDistList;
typedef struct _DTBLMAPISTATUS		FAR * IMAPIStatus;
#endif //!WINPAD
typedef struct _DTBLNOTIFICATION	FAR * INotifObj;
#ifndef WINPAD
typedef struct _DTBLSTREAM			FAR * IMAPIStream;
#endif
typedef struct _DTBLMAPITABLE		FAR * IMAPITable;
#ifndef WINPAD
typedef struct _DTBLPROFSECT		FAR * IProfSect;
#endif
typedef struct _DTBLMAPIPROP		FAR * IMAPIProp;
typedef struct _DTBLMAPICONTAINER	FAR * IMAPIContainer;

#else

#ifndef LPUNKNOWN
class IUnknown;
#endif
#ifndef WINPAD
class FAR IMsgStore;
#endif
class FAR IFolder;
class FAR IMessage;
#ifndef WINPAD
class FAR IAttach;
class FAR IAddrBook;
class FAR IABContainer;
class FAR IMailUser;
class FAR IDistList;
class FAR IMAPIStatus;
#endif //!WINPAD
class FAR INotifObj;
#ifndef WINPAD
class FAR IMAPIStream;
#endif
class FAR IMAPITable;
#ifndef WINPAD
class FAR IProfSect;
#endif
class FAR IMAPIProp;
class FAR IMAPIContainer;

#endif //!__cplusplus

typedef IMAPIProp		FAR * LPMAPIPROP;
typedef IMAPIContainer	FAR * LPMAPICONTAINER;
#ifndef WINPAD
typedef IMsgStore		FAR * LPMDB;
#endif
typedef IFolder			FAR * LPFOLDER;
typedef IMessage		FAR * LPMESSAGE;
#ifndef WINPAD
typedef IAttach			FAR * LPATTACH;
typedef IAddrBook		FAR * LPADRBOOK;
typedef IABContainer	FAR * LPABCONT;
typedef IMailUser		FAR * LPMAILUSER;
typedef IDistList		FAR * LPDISTLIST;
typedef IProfSect		FAR * LPPROFSECT;
typedef IMAPIStatus		FAR * LPMAPISTATUS;
#endif //!WINPAD
typedef INotifObj		FAR * LPNOTIFOBJ;
#ifndef WINPAD
typedef IMAPIStream		FAR * LPMAPISTREAM;
#endif
typedef IMAPITable		FAR * LPMAPITABLE;


/* Object type */

#define MAPI_STORE		((ULONG) 0x00000001)	/* Message Store */
#define MAPI_ADDRBOOK	((ULONG) 0x00000002)	/* Address Book */
#define MAPI_FOLDER		((ULONG) 0x00000003)	/* Folder */
#define MAPI_ABCONT		((ULONG) 0x00000004)	/* Address Book Container */
#define MAPI_MESSAGE	((ULONG) 0x00000005)	/* Message */
#define MAPI_MAILUSER	((ULONG) 0x00000006)	/* Individual Recipient */
#define MAPI_ATTACH		((ULONG) 0x00000007)	/* Attachment */
#define MAPI_DISTLIST	((ULONG) 0x00000008)	/* Distribution List Recipient */
#define MAPI_PROFSECT	((ULONG) 0x00000009)	/* Profile Section */
#define MAPI_STATUS		((ULONG) 0x0000000A)	/* Status Object */
#define MAPI_SESSION	((ULONG) 0x0000000B)	/* Session */

/* Interface identifier. Also defined in OLE2 compobj.h. */

#ifndef LPIID
typedef GUID IID, FAR * LPIID;
#endif


/* ----------------------------- */
/* IUnknown interface definition */

typedef SCODE	(FAR CDECL QUERYINTERFACE)(
	LPVOID		lpObject,
	LPIID		lpiid,
	LPVOID FAR *	lppNewObj
);
typedef ULONG	(FAR CDECL ADDREF)(
	LPVOID		lpObject
);
typedef ULONG	(FAR CDECL RELEASE)(
	LPVOID		lpObject
);

#define IUNKNOWNMETHODS \
	QUERYINTERFACE		FAR * QueryInterface; \
	ADDREF				FAR * AddRef; \
	RELEASE				FAR * Release;

typedef struct _DTBLUNKNOWN
{
	IUNKNOWNMETHODS
} DTBLUNKNOWN, FAR * LPDTBLUNKNOWN;

#ifdef __cplusplus
class FAR IUnknown {
public:
    virtual HRESULT QueryInterface(LPIID, LPVOID FAR*) = 0;
    virtual DWORD AddRef() = 0;
    virtual DWORD Release() = 0;
};

class FAR INotifObj : public IUnknown {
public:
	virtual HRESULT ChangeEvMask(LPNOTIFOBJ lpNotifObj, ULONG ulEventMask, ULONG ulFlags) = 0;
};
#endif // __cplusplus

/*  ulModality */
#define DIALOG_MODAL			((ULONG) 0x00000000)
#define DIALOG_MDI				((ULONG) 0x00000001)
#define DIALOG_SDI				((ULONG) 0x00000002)


#endif /* MAPIDEFS_H */
