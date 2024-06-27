/*
 *	T A B L E . H
 *	
 *	Definitions relating to the IMAPITable interface.
 *
 *               Copyright (c) 1993, Microsoft Corp. All rights reserved.
 *
 */

#ifndef TABLE_H
#define TABLE_H

#ifdef __cplusplus
extern "C" {
#endif

/* Table status */

#define TBLSTAT_COMPLETE			((ULONG) 0)
#define TBLSTAT_QCHANGED			((ULONG) 7)
#define TBLSTAT_SORTING				((ULONG) 9)
#define TBLSTAT_SORT_ERROR			((ULONG) 10)
#define TBLSTAT_SETTING_COLS		((ULONG) 11)
#define TBLSTAT_SETCOL_ERROR		((ULONG) 13)
#define TBLSTAT_RESTRICTING			((ULONG) 14)
#define TBLSTAT_RESTRICT_ERROR		((ULONG) 15)


/* Table Type */

#define TBLTYPE_SNAPSHOT			((ULONG) 0)
#define TBLTYPE_KEYSET				((ULONG) 1)
#define TBLTYPE_DYNAMIC				((ULONG) 2)


/* Sort order */

/* bit 0: set if descending, clear if ascending */

#define TABLE_SORT_ASCEND		((ULONG) 0x00000000)
#define TABLE_SORT_DESCEND		((ULONG) 0x00000001)


/* Data structures */

#pragma warning (disable: 4200)

typedef struct _SRow
{
	ULONG			cValues;	/* Count of property values */
	LPSPropValue	lpProps;	/* Property value array */
} SRow, FAR * LPSRow;

typedef struct _SRowSet
{
	ULONG			cRows;		/* Count of rows */
	SRow			aRow[];		/* Array of rows */
} SRowSet, FAR * LPSRowSet;

typedef struct _SSortOrder
{
	ULONG	ulPropTag;			/* Column to sort on */
	ULONG	ulOrder;			/* Ascending or descending */
} SSortOrder, FAR * LPSSortOrder;

typedef struct _SSortOrderSet
{
	ULONG	  		cSorts;		/* Number of sort columns */
	SSortOrder		aSort[];	/* The sort orders */
} SSortOrderSet, FAR * LPSSortOrderSet;


#pragma warning (default: 4200)

typedef ULONG 		BOOKMARK;

#define BOOKMARK_BEGINNING	((BOOKMARK) 0)		/* Before first row */
#define BOOKMARK_CURRENT	((BOOKMARK) 1)		/* Before current row */
#define BOOKMARK_END		((BOOKMARK) 2)		/* After last row */

/* Fuzzy Level */

#define FL_EXACT		((ULONG) 0)
#define FL_RANGE		((ULONG) 1)

/* Restrictions */

typedef struct _SRestriction	FAR * LPSRestriction;

/* Restriction types */

#define RES_AND				((ULONG) 0x00000000)
#define RES_OR				((ULONG) 0x00000001)
#define RES_NOT				((ULONG) 0x00000002)	
#define RES_CONTENT			((ULONG) 0x00000003)
#define RES_PROPERTY		((ULONG) 0x00000004)
#define RES_COMPAREPROPS	((ULONG) 0x00000005)
#define RES_BITMASK			((ULONG) 0x00000006)
#define RES_SIZE			((ULONG) 0x00000007)
#define RES_EXIST			((ULONG) 0x00000008)
#define RES_SUBRESTRICTION	((ULONG) 0x00000009)


/* Relational operators. These apply to all property comparison restrictions. */

#define RELOP_LT		((ULONG) 0)		/* < */
#define RELOP_LE		((ULONG) 1)		/* <= */
#define RELOP_GT		((ULONG) 2)		/* > */
#define RELOP_GE		((ULONG) 3)		/* >= */
#define RELOP_EQ		((ULONG) 4)		/* == */
#define RELOP_NE		((ULONG) 5)		/* != */
#define RELOP_RE		((ULONG) 6)		/* LIKE (Regular expression) */

/* Bitmask operators, for RES_BITMASK only. */

#define BMR_EQZ		((ULONG) 0)		/* ==0 */
#define BMR_NEZ		((ULONG) 1)		/* !=0 */

/* Subobject identifiers, for RES_SUBRESTRICTION only. */

#define SUBOBJ_RECIP	((ULONG) 1)		/* message recipient table */
#define SUBOBJ_ATTACH	((ULONG) 2)		/* message attachment table */

typedef struct _SAndRestriction
{
	ULONG			cRes;
	LPSRestriction 	lpRes;
} SAndRestriction;

typedef struct _SOrRestriction
{
	ULONG			cRes;
	LPSRestriction 	lpRes;
} SOrRestriction;

typedef struct _SNotRestriction
{
	LPSRestriction 	lpRes;
} SNotRestriction;

typedef struct _SContentRestriction
{
	ULONG			ulFuzzyLevel;
	ULONG			ulPropTag;
	SPropValue		prop;
} SContentRestriction;

typedef struct _SBitMaskRestriction
{
	ULONG			relBMR;
	ULONG			ulPropTag;
	ULONG			ulMask;
} SBitMaskRestriction;

typedef struct _SPropertyRestriction
{
	ULONG			relop;				
	ULONG			ulPropTag;
	SPropValue		prop;			
} SPropertyRestriction;

typedef struct _SComparePropsRestriction
{
	ULONG			relop;
	ULONG			ulPropTag1;
	ULONG			ulPropTag2;
} SComparePropsRestriction;

typedef struct _SSizeRestriction
{
	ULONG			relop;
	ULONG			ulPropTag;
	ULONG			cb;
} SSizeRestriction;

typedef struct _SExistRestriction
{
	ULONG			ulPropTag;
} SExistRestriction;

typedef struct _SSubRestriction
{
	ULONG			ulSubObject;
	LPSRestriction	lpRes;
} SSubRestriction;

typedef struct _SRestriction
{
	ULONG	rt;			/* Restriction type */
	union
	{
		SAndRestriction				resAnd;
		SOrRestriction				resOr;
		SNotRestriction				resNot;
		SContentRestriction			resContent;
		SPropertyRestriction		resProperty;
		SComparePropsRestriction	resCompareProps;
		SBitMaskRestriction			resBitMask;
		SSizeRestriction			resSize;
		SExistRestriction			resExist;
		SSubRestriction				resSub;
	} res;
} SRestriction;


/* Pointer to objects */
/* //$ Is this typedef needed? */
/* //$ typedef struct _IMAPITable FAR * LPTABLE; */


/* Flags of the methods of IMAPITable */

/* QueryColumn */

#define TBL_ALL_COLUMNS		((ULONG) 0x00000001)

/* Table wait flag */

#define TBL_NOWAIT			((ULONG) 0x00000001)

/* FindRow */

#define DIR_BACKWARD		((ULONG) 0x00000001)

/* Table cursor states */

#define TBL_NOADVANCE		((ULONG) 0x00000001)

#ifndef	__cplusplus
/* Dispatch table pointer to function typedefs */

typedef HRESULT (CDECL GETSTATUS)(
	LPMAPITABLE			lpTable,
	ULONG FAR *			lpulTableStatus,
	ULONG FAR *			lpulTableType
);
typedef HRESULT (CDECL SETCOLUMNS)(
	LPMAPITABLE			lpTable,
	LPSPropTagArray		lpPropTagArray,
	ULONG				ulFlags
);
typedef HRESULT (CDECL QUERYCOLUMNS)(
	LPMAPITABLE				lpTable,
	ULONG					ulFlags,
	LPSPropTagArray FAR *	lpPropTagArray
);
typedef HRESULT (CDECL GETROWCOUNT)(
	LPMAPITABLE			lpTable,
	ULONG				ulFlags,
	ULONG FAR *			lpulCount
);
typedef HRESULT (CDECL SEEKROW)(
	LPMAPITABLE			lpTable,
	BOOKMARK			bkOrigin,
	LONG				lRowCount,
	LONG FAR *			lplRowsSought
);
typedef HRESULT (CDECL SEEKROWAPPROX)(
	LPMAPITABLE			lpTable,
	ULONG				ulNumerator,
	ULONG				ulDenominator
);
typedef HRESULT (CDECL QUERYPOSITION)(
	LPMAPITABLE			lpTable,
	ULONG FAR *			lpulRow,
	ULONG FAR *			lpulNumerator,
	ULONG FAR *			lpulDenominator
);
typedef HRESULT (CDECL FINDROW)(
	LPMAPITABLE			lpTable,
	LPSRestriction		lpRestriction,
	BOOKMARK			bkOrigin,
	ULONG				ulFlags
);
typedef HRESULT (CDECL RESTRICT)(
	LPMAPITABLE			lpTable,
	LPSRestriction		lpRestriction,
	ULONG				ulFlags
);
typedef HRESULT (CDECL CREATEBOOKMARK)(
	LPMAPITABLE			lpTable,
	BOOKMARK FAR *		lpbkPosition
);
typedef HRESULT (CDECL FREEBOOKMARK)(
	LPMAPITABLE			lpTable,
	BOOKMARK			bkPosition
);
typedef HRESULT (CDECL SORTTABLE)(
	LPMAPITABLE			lpTable,
	LPSSortOrderSet		lpSortCriteria,
	ULONG				ulFlags
);
typedef HRESULT (CDECL QUERYSORTORDER)(
	LPMAPITABLE				lpTable,
	LPSSortOrderSet FAR *	lppSortCriteria
);
typedef HRESULT (CDECL QUERYROWS)(
	LPMAPITABLE			lpTable,
	ULONG				ulRowCount,
	ULONG				ulFlags,
	LPSRowSet FAR *		lppRows
);
typedef HRESULT (CDECL ABORT)(
	LPMAPITABLE			lpTable
);
				

#ifdef WINPAD
#define MAPITABLEMETHODS \
	IUNKNOWNMETHODS \
	GETSTATUS			FAR * GetStatus;\
	SETCOLUMNS			FAR * SetColumns;\
	QUERYCOLUMNS		FAR * QueryColumns;\
	GETROWCOUNT			FAR * GetRowCount;\
	SEEKROW				FAR * SeekRow;\
	SEEKROWAPPROX		FAR * SeekRowApprox;\
	QUERYPOSITION		FAR * QueryPosition;\
	FINDROW				FAR * FindRow;\
	RESTRICT			FAR * Restrict;\
	CREATEBOOKMARK		FAR * CreateBookmark;\
	FREEBOOKMARK		FAR * FreeBookmark;\
	SORTTABLE			FAR * SortTable;\
	QUERYSORTORDER		FAR * QuerySortOrder;\
	QUERYROWS			FAR * QueryRows;\
	ABORT				FAR * Abort;
#else //WINPAD	
#define MAPITABLEMETHODS \
	IUNKNOWNMETHODS \
	GETLASTERROR		FAR * GetLastError;\
	GETSTATUS			FAR * GetStatus;\
	SETCOLUMNS			FAR * SetColumns;\
	QUERYCOLUMNS		FAR * QueryColumns;\
	GETROWCOUNT			FAR * GetRowCount;\
	SEEKROW				FAR * SeekRow;\
	SEEKROWAPPROX		FAR * SeekRowApprox;\
	QUERYPOSITION		FAR * QueryPosition;\
	FINDROW				FAR * FindRow;\
	RESTRICT			FAR * Restrict;\
	CREATEBOOKMARK		FAR * CreateBookmark;\
	FREEBOOKMARK		FAR * FreeBookmark;\
	SORTTABLE			FAR * SortTable;\
	QUERYSORTORDER		FAR * QuerySortOrder;\
	QUERYROWS			FAR * QueryRows;\
	ABORT				FAR * Abort;
#endif //!WINPAD


/* Dispatch table */

typedef struct _DTBLMAPITABLE
{
	MAPITABLEMETHODS
} DTBLMAPITABLE, FAR * LPDTBLMAPITABLE;
#endif // !__cplusplus

#ifdef	__cplusplus
class FAR IMAPITable : public IUnknown
{
public:
	virtual HRESULT	MAPIMETHOD GetStatus(ULONG FAR * lpulTableStatus,ULONG FAR * lpulTableType) = 0;
	virtual HRESULT MAPIMETHOD SetColumns(LPSPropTagArray lpPropTagArray,ULONG	ulFlags) = 0;
	virtual HRESULT MAPIMETHOD QueryColumns(ULONG ulFlags,LPSPropTagArray FAR * lpPropTagArray) = 0;
	virtual HRESULT MAPIMETHOD GetRowCount(ULONG ulFlags,ULONG FAR * lpulCount) = 0;
	virtual HRESULT MAPIMETHOD SeekRow(BOOKMARK bkOrigin,LONG lRowCount,LONG FAR * lplRowsSought) = 0;
	virtual HRESULT MAPIMETHOD SeekRowApprox(ULONG ulNumerator,ULONG ulDenominator) = 0;
	virtual HRESULT MAPIMETHOD QueryPosition(ULONG FAR * lpulRow,ULONG FAR * lpulNumerator,ULONG FAR * lpulDenominator) = 0;
	virtual HRESULT MAPIMETHOD FindRow(LPSRestriction lpRestriction,BOOKMARK bkOrigin,ULONG ulFlags) = 0;
	virtual HRESULT MAPIMETHOD Restrict(LPSRestriction lpRestriction,ULONG ulFlags) = 0;
	virtual HRESULT MAPIMETHOD CreateBookmark(BOOKMARK FAR * lpbkPosition) = 0;
	virtual HRESULT MAPIMETHOD FreeBookmark(BOOKMARK bkPosition) = 0;
	virtual HRESULT MAPIMETHOD SortTable(LPSSortOrderSet lpSortCriteria,ULONG ulFlags) = 0;
	virtual HRESULT MAPIMETHOD QuerySortOrder(LPSSortOrderSet FAR * lppSortCriteria) = 0;
	virtual HRESULT MAPIMETHOD QueryRows(ULONG ulRowCount,ULONG ulFlags,LPSRowSet FAR * lppRows) = 0;
	virtual HRESULT MAPIMETHOD Abort() = 0;
};	
#endif				

#ifdef	__cplusplus
}		/*	extern "C" */
#endif	

#endif /* TABLE_H */
