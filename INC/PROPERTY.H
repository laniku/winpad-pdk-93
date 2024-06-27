/*
 *	P R O P E R T Y . H
 *	
 *	Definitions relating to the IMAPIProp interface.
 *
 *               Copyright (c) 1993, Microsoft Corp. All rights reserved.
 */

#ifndef PROPERTY_H
#define PROPERTY_H

#ifdef	__cplusplus
extern "C" {
#endif	

/* Property Types */

#define PT_UNSPECIFIED	((ULONG)  0)	/* (Reserved for interface use) type doesn't matter to caller */
#define PT_NULL			((ULONG)  1)	/* NULL property value */
#define	PT_I2			((ULONG)  2)	/* Signed 16-bit value */
#define PT_LONG			((ULONG)  3)	/* Signed 32-bit value */
#define	PT_R4			((ULONG)  4)	/* 4-byte floating point */
#define PT_DOUBLE		((ULONG)  5)	/* Floating point double */
#define PT_CURRENCY		((ULONG)  6)	/* Signed 64-bit int (decimal w/	4 digits right of decimal pt) */
#define	PT_APPTIME		((ULONG)  7)	/* Application time */
#define PT_ERROR		((ULONG) 10)	/* 32-bit error value */
#define PT_BOOLEAN		((ULONG) 11)	/* 16-bit boolean (non-zero true) */
#define PT_OBJECT		((ULONG) 13)	/* Embedded object in a property */
#define PT_SYSTIME		((ULONG) 256)	/* 64-bit int w/ number of 100ns periods since Jan 1,1601 */
#define PT_STRING8		((ULONG) 257)	/* Null terminated 8-bit character string */
#define PT_BINARY		((ULONG) 258)	/* Uninterpreted (counted byte array) */
#define PT_UNICODE		((ULONG) 263)	/* Null terminated Unicode string */
#define	PT_CLSID		((ULONG) 265)	/* OLE GUID */
#define	PT_LONGLONG		((ULONG) 266)	/* //$Must confirm w. OLE VT_I8 type */

#ifdef WINPAD
#ifndef ARADOR
#define PT_HEADER		((ULONG) 299)	/* A format string */
#define PT_INK			((ULONG) 300)	/* An ink value */
#define PT_BIT			((ULONG) 301)	/* A single bit */
#define	PT_FILE			((ULONG) 302)	/* Handle to file containing property */
#endif
#define EIDNULL	0						/* This value is guaranteed to be an invalid Entry ID */
#define PT_ENTRYID		((ULONG) 40)	/* An Entry ID */
#define PT_DATE			((ULONG) 41)	/* Days since 12/30/1899 in unsigned long format */
#define PT_TIME			((ULONG) 42)	/* Seconds since midnight in unsigned long format */
#endif
/*
 *	The type of a MAPI-defined string property is indirected, so
 *	that it defaults to Unicode string on a Unicode platform and to
 *	String8 on an ANSI or DBCS platform.
 *	
 *	Macros are defined here both for the property type, and for the
 *	field of the property value structure which should be
 *	dereferenced to obtain the string pointer.
 */

#ifdef	UNICODE
#define PT_TSTRING			PT_UNICODE
#define LPSZ				lpszW
#define LPSZMV				lpszWMV
#else
#define PT_TSTRING			PT_STRING8
#define LPSZ				lpszA
#define LPSZMV				lpszAMV
#endif



/* Property Tags   
 *
 * By convention, MAPI never uses 0 or FFFF as a property ID.   
 * Use as null values, initializers, sentinels, or what have you.   
 */

#define PROP_TYPE_MASK			((ULONG)0x0000FFFF)	/* Mask for Property type */
#define PROP_TYPE(ulPropTag)	(((ULONG)(ulPropTag))&PROP_TYPE_MASK)
#define PROP_ID(ulPropTag)		(((ULONG)(ulPropTag))>>16)
#define PROP_TAG(ulPropType,ulPropID)	((((ULONG)(ulPropID))<<16)|((ULONG)(ulPropType)))
#define PROP_ID_NULL			0
#define PROP_ID_INVALID			0xFFFF
#define PR_NULL					PROP_TAG( PT_UNSPECIFIED, PROP_ID_NULL)

/* Multi-valued Property Types */

#define MV_FLAG			0x1000					/* Multi-value flag */
#define	PT_MV_I2		(MV_FLAG|PT_I2)
#define PT_MV_LONG		(MV_FLAG|PT_LONG)
#define	PT_MV_R4		(MV_FLAG|PT_R4)
#define PT_MV_DOUBLE	(MV_FLAG|PT_DOUBLE)
#define PT_MV_CURRENCY	(MV_FLAG|PT_CURRENCY)
#define	PT_MV_APPTIME	(MV_FLAG|PT_APPTIME)
#define PT_MV_SYSTIME	(MV_FLAG|PT_SYSTIME)
#define PT_MV_STRING8	(MV_FLAG|PT_STRING8)
#define PT_MV_BINARY	(MV_FLAG|PT_BINARY)
#define PT_MV_UNICODE	(MV_FLAG|PT_UNICODE)
#define	PT_MV_CLSID		(MV_FLAG|PT_CLSID)
#define PT_MV_LONGLONG	(MV_FLAG|PT_LONGLONG)

#ifdef WINPAD
#define PT_MV_ENTRYID	(MV_FLAG|PT_ENTRYID)

#ifndef ARADOR
/* Common-valued Property Types */

#define CV_FLAG			0x200					/* Common value flag */
#define PT_CV_STRING8	(CV_FLAG|PT_STRING8)
#define PT_CV_BINARY	(CV_FLAG|PT_BINARY)
#define PT_CV_HEADER	(CV_FLAG|PT_HEADER)

/* Property Types stored with the type info */

#define TV_FLAG			0x400					/* Value stored in type info */

#define	PT_TV_I2		(TV_FLAG|PT_I2)
#define PT_TV_LONG		(TV_FLAG|PT_LONG)
#define PT_TV_ENTRYID	(TV_FLAG|PT_ENTRYID)
#define PT_TV_STRING8	(TV_FLAG|PT_STRING8)
#define PT_TV_HEADER	(TV_FLAG|PT_HEADER)
#endif	//!ARADOR
#endif  //WINPAD

/*
 *	Property type reserved bits
 *	
 *	MV_INSTANCE is used as a flag in table operations to request
 *	that a multi-valued property be presented as a single-valued
 *	property appearing in multiple rows.
 *	
 *	PT_ANR is used as a flag in address book table operations to
 *	request ambiguous name resolution on a string.
 */

#define MV_INSTANCE		0x2000
#define MVI_FLAG		(MV_FLAG | MV_INSTANCE)
#define MVI_PROP(tag)	(Assert(PROP_TYPE(tag)&MV_FLAG), \
							(tag) | MV_INSTANCE)

#define PT_ANR			0x4000

/* --------------- */
/* Data Structures */
/* --------------- */

/* Property Tag Array */

#pragma warning (disable: 4200)
typedef struct _SPropTagArray
{
	ULONG	cValues;							
	ULONG	aulPropTag[];
} SPropTagArray, FAR * LPSPropTagArray;
#pragma warning (default: 4200)

/* -------------- */
/* Property Value */
/* -------------- */

typedef struct _SPropValue	SPropValue;

/* standard windows definitions: */
typedef WORD WCHAR;
typedef WCHAR FAR * LPWSTR; 
/* typedef char FAR * LPSTR; */

#ifndef WINPAD
typedef char CURRENCY[8];
#endif

#ifndef	_WINBASE_

typedef struct _FILETIME
{
	DWORD dwLowDateTime;
	DWORD dwHighDateTime;
} FILETIME, FAR * LPFILETIME;

#endif	/* _WINBASE_ */

typedef struct _SBinary
{
	ULONG		cb;
	LPBYTE 		lpb;
} SBinary, FAR *LPSBinary;

typedef	struct _SShortArray
{
	ULONG		cValues;
	short int	FAR *lpi;
} SShortArray;

typedef struct _SGuidArray
{
	ULONG		cValues;
	GUID		FAR *lpguid;
} SGuidArray;

typedef	struct _SRealArray
{
	ULONG		cValues;
	float		FAR *lpflt;
} SRealArray;

typedef struct _SLongArray
{
	ULONG		cValues;
	LONG 		FAR *lpl;
} SLongArray;

#ifndef WINPAD
typedef struct _SLongLongArray
{
	ULONG		cValues;
	LONGLONG	FAR *lpll;
} SLongLongArray;

typedef struct _SDateTimeArray
{
	ULONG		cValues;
	FILETIME	FAR *lpft;
} SDateTimeArray;

typedef struct _SAppTimeArray
{
	ULONG		cValues;
	double		FAR *lpat;
} SAppTimeArray;

typedef struct _SCurrencyArray
{
	ULONG		cValues;
	CURRENCY	FAR *lpcur;
} SCurrencyArray;
#endif // !WINPAD

typedef struct _SBinaryArray
{
	ULONG		cValues;
	SBinary		FAR *lpbin;
} SBinaryArray;

#ifdef WINPAD
typedef struct _SEntryIDArray
{
		ULONG	cValues;
		ENTRYID	far *peid;
} SEntryIDArray;
#endif //WINPAD

typedef struct _SDoubleArray
{
	ULONG		cValues;
	double		FAR *lpdbl;
} SDoubleArray;

typedef struct _SWStringArray
{
	ULONG		cValues;
	LPWSTR		FAR *lpszW;
} SWStringArray;

typedef struct _SLPSTRArray
{
	ULONG		cValues;
	LPSTR		FAR *lpszA;
} SLPSTRArray;


typedef struct _SPropValue
{
	ULONG	ulPropTag;
	ULONG 	dwAlignPad;
	union 	_PV
	{
		short int			i;			/* case PT_I2 */
		LONG				l;			/* case PT_LONG */
		ULONG				ul;			/* alias for PT_LONG */
		float				flt;		/* case PT_R4 */
		double				dbl;		/* case PT_DOUBLE */
		unsigned short int	b;			/* case PT_BOOLEAN */
#ifndef WINPAD
		CURRENCY			cur;		/* case PT_CURRENCY */
		double				at;			/* case PT_APPTIME */
		FILETIME			ft;			/* case PT_SYSTIME */
#endif // !WINPAD
		LPSTR				lpszA;		/* case PT_STRING8 */
		SBinary				bin;		/* case PT_BINARY */
#ifdef WINPAD
		BYTE				bit;		/* case PT_BIT */
		HGLOBAL				hglobal;    /* case PT_INK */
		int					fh;			/* case PT_FILE */
		ENTRYID 			eid;		/* case PT_ENTRYID */
#endif		
		LPWSTR				lpszW;		/* case PT_UNICODE */
#ifndef WINPAD
		LPGUID				lpguid;		/* case PT_CLSID */
		LONGLONG			ll;			/* case PT_LONGLONG */
#endif 	// !WINPAD
		SShortArray			iMV;		/* case PT_MV_I2 */
		SLongArray			lMV;		/* case PT_MV_LONG */
		SRealArray			fltMV;		/* case PT_MV_R4 */
		SDoubleArray		dblMV;		/* case PT_MV_DOUBLE */
#ifndef WINPAD
		SCurrencyArray		curMV;		/* case PT_MV_CURRENCY */
		SAppTimeArray		atMV;		/* case PT_MV_APPTIME */
		SDateTimeArray		dtMV;		/* case PT_MV_SYSTIME */
#endif //!WINPAD
		SBinaryArray		binMV;		/* case PT_MV_BINARY */
#ifdef WINPAD
		SEntryIDArray    	mveid;		/* case PT_MV_ENTRYID */
#endif		
		SLPSTRArray			lpszAMV;	/* case PT_MV_STRING8 */
		SWStringArray		lpszWMV;	/* case PT_MV_UNICODE */
#ifndef WINPAD
		SGuidArray			lpguidMV;	/* case PT_MV_CLSID */
		SLongLongArray		llMV;		/* case PT_MV_LONGLONG */
#endif //!WINPAD
		SCODE				err;		/* case PT_ERROR */
		LONG				x;			/* case PT_NULL, PT_OBJECT (no usable value) */
	} Value;
} FAR * LPSPropValue;


/* --------------------------------------------- */
/* Property Problem and Property Problem Arrays */
/* --------------------------------------------- */

typedef struct _SPropProblem
{
	ULONG	ulIndex;
	ULONG	ulPropTag;
	SCODE	scode;
} SPropProblem;

#pragma warning (disable: 4200)

typedef struct _SPropProblemArray
{
	ULONG			cProblem;
	SPropProblem	aProblem[];
} SPropProblemArray, FAR * LPSPropProblemArray;

#pragma warning (default: 4200)

/* --------------------- */
/* Interface Definitions */
/* --------------------- */

/* Pointers to objects */

typedef IUnknown 	FAR *	LPIUnknown;


/* Dispatch table pointer to function typedefs */

/* ------------------------------ */
/* IMAPIProp interface definition */

/* GetLastError */

/*#define MAPI_UNICODE			((ULONG) 0x8000000) in mapidefs.h */

/* SaveChanges */

#define KEEP_OPEN_READONLY		((ULONG) 0x00000001)
#define KEEP_OPEN_READWRITE		((ULONG) 0x00000002)
#define FORCE_SAVE				((ULONG) 0x00000004)

/* OpenProperty */
/******	MAPI_MODIFY				((ULONG) 0x00000001) in mapidefs.h */
#define	MAPI_CREATE				((ULONG) 0x00000002)

/* CopyTos */

#define MAPI_MOVE				((ULONG) 0x00000001)
#define MAPI_NOREPLACE			((ULONG) 0x00000002)

#ifndef MAPI_DIALOG				/* also defined in mapi.h */
#define MAPI_DIALOG				((ULONG) 0x00000008)
#endif

/* GetIDFromName */
/******	MAPI_CREATE				((ULONG) 0x00000002) in this file */

typedef HRESULT (FAR CDECL GETLASTERROR)(
	LPVOID				lpObject,
	HRESULT				hResult,
	ULONG				ulFlags,
	LPTSTR FAR *		lppszMessage
);
typedef HRESULT (FAR CDECL SAVECHANGES)(
	LPVOID				lpObject,
	ULONG				ulFlags
);
typedef HRESULT (FAR CDECL GETPROPS)(
	LPVOID				lpObject,
	LPSPropTagArray		lpPropTagArray,
	ULONG FAR *			lpcValues,
	LPSPropValue FAR *	lppPropArray
);
typedef HRESULT (FAR CDECL GETPROPLIST)(
	LPVOID				lpObject,
	LPSPropTagArray FAR * lppPropTagArray
);
typedef HRESULT (FAR CDECL OPENPROPERTY)(
	LPVOID				lpObject,
	ULONG				ulPropTag,
	LPIID				lpiid,
	ULONG				ulInterfaceOptions,
	ULONG				ulFlags,
	LPIUnknown FAR *	lppUnk
);
typedef HRESULT (FAR CDECL SETPROPS)(
	LPVOID					lpObject,
	ULONG					cValues,
	LPSPropValue			lpPropArray,
	LPSPropProblemArray FAR * lppProblems
);
typedef HRESULT (FAR CDECL DELETEPROPS)(
	LPVOID					lpObject,
	LPSPropTagArray			lpPropTagArray,
	LPSPropProblemArray FAR * lppProblems
);

typedef HRESULT (FAR CDECL COPYTO)(
	LPVOID					lpObject,
	ULONG					ciidExclude,
	LPIID					rgiidExclude,
	LPSPropTagArray			lpExcludeProps,
	ULONG					ulUIParam,
	LPProgressInfo			lpProgress,
	LPIID					lpInterface,
	LPVOID					lpDestObj,
	ULONG					ulFlags,
	LPSPropProblemArray FAR * lppProblems
);

#ifndef WINPAD
typedef HRESULT (FAR CDECL GETNAMESFROMIDS)(
	LPVOID					lpObject,
	LPSPropTagArray FAR *	lppPropTags,
	ULONG					ulFlags,
	ULONG FAR *				lpcPropNames,
	LPWSTR FAR * FAR *		lpppszPropNames
);
typedef HRESULT (FAR CDECL GETIDSFROMNAMES)(
	LPVOID					lpObject,
	ULONG					cPropNames,
	LPWSTR FAR *			lppszPropNames,
	ULONG					ulFlags,
	LPSPropTagArray FAR *	lppPropTags
);
typedef HRESULT (FAR CDECL RESERVED) (
	LPVOID					lpObject
);
#endif //!WINPAD

#ifdef WINPAD	
#define MAPIPROPMETHODS \
	IUNKNOWNMETHODS \
	GETLASTERROR	FAR * GetLastError; \
	SAVECHANGES		FAR * SaveChanges; \
	GETPROPS		FAR * GetProps; \
	GETPROPLIST		FAR * GetPropList; \
	OPENPROPERTY	FAR * OpenProperty; \
	SETPROPS		FAR * SetProps; \
	DELETEPROPS		FAR * DeleteProps; \
	COPYTO			FAR * CopyTo; 
#else	
#define MAPIPROPMETHODS \
	IUNKNOWNMETHODS \
	GETLASTERROR	FAR * GetLastError; \
	SAVECHANGES		FAR * SaveChanges; \
	GETPROPS		FAR * GetProps; \
	GETPROPLIST		FAR * GetPropList; \
	OPENPROPERTY	FAR * OpenProperty; \
	SETPROPS		FAR * SetProps; \
	DELETEPROPS		FAR * DeleteProps; \	
	COPYTO			FAR * CopyTo; \
	GETNAMESFROMIDS	FAR * GetNamesFromIDs; \
	GETIDSFROMNAMES	FAR * GetIDsFromNames; \
	RESERVED		FAR * reserved6; \
	RESERVED		FAR * reserved5; \
	RESERVED		FAR * reserved4; \
	RESERVED		FAR * reserved3; \
	RESERVED		FAR * reserved2; \
	RESERVED		FAR * reserved1;
#endif //!WINPAD

typedef struct _DTBLMAPIPROP
{
	MAPIPROPMETHODS
} DTBLMAPIPROP, FAR * LPDTBLMAPIPROP;

#ifdef	__cplusplus
}	// extern "C"

class FAR IMAPIProp : public IUnknown 
{
public:
	virtual HRESULT MAPIMETHOD GetLastError(HRESULT hError, ULONG ulFlags, LPSTR FAR * lppszMessage) = 0;
	virtual HRESULT MAPIMETHOD SaveChanges(ULONG ulFlags) = 0;
	virtual HRESULT	MAPIMETHOD GetProps(LPSPropTagArray,ULONG FAR*,LPSPropValue FAR*) = 0;
	virtual HRESULT MAPIMETHOD GetPropList(LPSPropTagArray FAR*) = 0;
	virtual HRESULT MAPIMETHOD OpenProperty(ULONG, LPIID, ULONG, ULONG, LPIUnknown FAR *) = 0;
	virtual HRESULT MAPIMETHOD SetProps(ULONG,LPSPropValue,LPSPropProblemArray FAR*) = 0;
	virtual HRESULT MAPIMETHOD DeleteProps(LPSPropTagArray,LPSPropProblemArray FAR*) = 0;
	virtual HRESULT MAPIMETHOD CopyTo(ULONG,LPIID,LPSPropTagArray lpExcludeProps,ULONG,
	                                  LPProgressInfo,LPIID,LPVOID lpDestObj,ULONG	ulFlags,
	                                  LPSPropProblemArray FAR * lppProblems) = 0;
};                 

#endif


#endif /* PROPERTY_H */
