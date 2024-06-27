/*
 *	M A P I X . H
 *	
 *	Declarations of the C-style implementations of extended MAPI objects.
 *
 *               Copyright (c) 1993, Microsoft Corp. All rights reserved.
 *
 */

#ifndef MAPIX_H
#define MAPIX_H

#ifdef	__cplusplus
extern "C" {
#endif	

/* ------------------------------------------------------ */
/* data structures common among MAPI objects in this file */

/* ------------------- */
/* Event Notifications */

/*
 *	Event types. The event types can be combined in a bitmask for
 *	filtering. Each one has a parameter structure associated with
 *	it:
 *	
 *		fnevCriticalError		ERROR_NOTIFICAION
 *		fnevNewMail				NEWMAIL_NOTIFICATION
 *		fnevObjectCreated		OBJECT_NOTOFICATION
 *		fnevObjectDeleted		OBJECT_NOTOFICATION
 *		fnevObjectModified		OBJECT_NOTOFICATION
 *		fnevObjectCopied		OBJECT_NOTOFICATION
 *		fnevSearchComplete		OBJECT_NOTOFICATION
 *	
 *		fnevExtended			EXTENDED_NOTIFICATION
 */

#define fnevCriticalError		((ULONG) 0x00000001)
#define fnevNewMail				((ULONG) 0x00000002)
#define fnevObjectCreated		((ULONG) 0x00000004)
#define fnevObjectDeleted		((ULONG) 0x00000008)
#define fnevObjectModified		((ULONG) 0x00000010)
#define fnevObjectMoved			((ULONG) 0x00000020)
#define fnevObjectCopied		((ULONG) 0x00000040)
#define fnevSearchComplete		((ULONG) 0x00000080)
#define fnevTableModified		((ULONG) 0x00000100)
#define fnevExtended			((ULONG) 0x80000000)

/* Flags for TABLE_NOTIFICATION */

#define TABLE_INVALID	((ULONG) 0x00000001)

/* Event Structures */

typedef struct _ERROR_NOTIFICATION
{
	ULONG		cbEntryID;
	LPENTRYID	lpEntryID;
	SCODE		scode;
	ULONG		ulFlags;	/* bottom bit 1==>string8, 0==>UNICODE */
	LPTSTR		lpszError;	/* error string (UNICODE or string8) */
} ERROR_NOTIFICATION;

typedef struct _NEWMAIL_NOTIFICATION
{
	ULONG		cbEntryID;
	LPENTRYID	lpEntryID;			/* identifies the new message */
	ULONG		cbParentID;
	LPENTRYID	lpParentID;			/* identifies the folder it lives in */
	ULONG		ulFlags;			/* bottom bit 0==>string8, 1==>UNICODE */
	LPTSTR		lpszMessageClass;	/* error string (UNICODE or string8)*/
	ULONG		ulMessageFlags;		/* copy of PR_MESSAGE_FLAGS */
} NEWMAIL_NOTIFICATION;

typedef struct _OBJECT_NOTIFICATION
{
	ULONG				cbEntryID;
	LPENTRYID			lpEntryID;		/* EntryID of object */
	ULONG				ulObjType;		/* Type of object */
	ULONG				cbParentID;
	LPENTRYID			lpParentID;		/* EntryID of parent object */
	ULONG				cbOldID;
	LPENTRYID			lpOldID;		/* EntryID of old object */
	ULONG				cbOldParentID;
	LPENTRYID			lpOldParentID;	/* EntryID of old parent */
	LPSPropTagArray		lpPropTagArray;
} OBJECT_NOTIFICATION;

typedef struct _TABLE_NOTIFICATION
{
	ULONG				ulFlags;
} TABLE_NOTIFICATION;

typedef struct _EXTENDED_NOTIFICATION
{
	ULONG		ulEvent;					/* extended event code */
	ULONG		cb;							/* size of event parameters */
	LPBYTE		pbEventParameters;			/* event parameters */
} EXTENDED_NOTIFICATION;

typedef struct _NOTIFICATION
{
	ULONG	ulEventType;		/* notification type, i.e. fnevSomething */
	union
	{
		ERROR_NOTIFICATION			err;
		NEWMAIL_NOTIFICATION		newmail;
		OBJECT_NOTIFICATION			obj;
		TABLE_NOTIFICATION			table;
		EXTENDED_NOTIFICATION		ext;
	} info;
} NOTIFICATION, FAR * LPNOTIFICATION;


/* ------------------------------------------------------ */
/* shared with simple mapi */

typedef ULONG       FLAGS;

/* MAPILogon() flags.       */

#define MAPI_LOGON_UI           0x00000001  /* Display logon UI             */
#define MAPI_NEW_SESSION        0x00000002  /* Don't use shared session     */
#define MAPI_FORCE_DOWNLOAD     0x00001000  /* Get new mail before return   */
#define MAPI_ALLOW_OTHERS       0x00000008  /* Make this a shared session   */
#define MAPI_EXPLICIT_PROFILE   0x00000010  /* Don't use default profile    */
#define MAPI_EXTENDED           0x00000020  /* Extended MAPI Logon          */

#define MAPI_SIMPLE_DEFAULT (MAPI_LOGON_UI | MAPI_FORCE_DOWNLOAD | MAPI_ALLOW_OTHERS)
#define MAPI_SIMPLE_EXPLICIT (MAPI_NEW_SESSION | MAPI_FORCE_DOWNLOAD | MAPI_EXPLICIT_PROFILE)

/* MAPILogoff() flags.      */

#define MAPI_LOGOFF_SHARED      0x00000001  /* Close all shared sessions    */
#define MAPI_LOGOFF_UI          0x00000002  /* It's OK to present UI        */


/* MAPI base functions */
/* MAPIFreeBuffer must match the prototype in mapi.h (the */
/* simple mapi header file). */

SCODE CDECL _export MAPIAllocateBuffer( ULONG ulSize, LPVOID FAR * lppv );

SCODE CDECL _export MAPIAllocateMore( ULONG ulSize, LPVOID lpv, LPVOID FAR * lppv );

ULONG FAR PASCAL _export MAPIFreeBuffer( LPVOID lpvMemory );


/*
 * MAPI Object Definitions.
 * These now follow the order and format in the MAPI Client Spec:
 *		any data structures and flags specific to the object
 *		function pointer typedefs
 *		dispatch table
 */


/* --------------------------------- */
/* IMAPISession interface definition */

#ifdef __cplusplus
class IMAPISession;
#else
typedef struct _DTBLMAPISESSION		FAR * IMAPISession;
#endif

typedef IMAPISession	FAR * LPMAPISESSION;
/* Flags for OpenEntry and others */

/*#define MAPI_MODIFY				((ULONG) 0x00000001) */

/* IMAPISession method prototypes */

typedef HRESULT (CDECL LOGOFF)(
	LPMAPISESSION lpSession,
	ULONG ulUIParam,
	ULONG ulFlags,
	ULONG ulReserved);

#ifndef WINPAD
typedef HRESULT (CDECL OPENMSGSTORE)(
	LPMAPISESSION lpSession,
	ULONG ulUIParam,
	LPVOID lpvReserved,
	ULONG cbEntryID,
	LPENTRYID lpEntryID,
	LPIID lpInterface,
	ULONG ulFlags,
	LPMDB FAR *lppMDB);

typedef HRESULT (CDECL OPENADDRESSBOOK)(
	LPMAPISESSION lpSession,
	ULONG ulUIParam,
	LPIID lpInterface,
	ULONG ulFlags,
	LPADRBOOK FAR *lppAdrBook);

typedef HRESULT (CDECL OPENPROFILESECTION)(
	LPMAPISESSION lpSession,
	LPMAPIUID lpUID,
	LPIID lpInterface,
	ULONG ulFlags,
	LPPROFSECT FAR *lppProfSect);

typedef HRESULT (CDECL MESSAGEOPTIONS)(
	LPMAPISESSION lpSession,
	ULONG ulUIParam,
	ULONG ulFlags,
	LPTSTR lpszAdrType,
	LPMESSAGE lpMessage);

typedef HRESULT (CDECL QUERYDEFAULTMESSAGEOPT)(
	LPMAPISESSION lpSession,
	LPTSTR lpszAdrType,
	ULONG ulFlags,
	ULONG FAR *lpcValues,
	LPSPropValue FAR *lppOptions);

typedef HRESULT (CDECL ENUMADRTYPES)(
	LPMAPISESSION lpSession,
	ULONG ulFlags,
	ULONG FAR *lpcAdrTypes,
	LPTSTR FAR * lppszAdrTypes);

typedef HRESULT (CDECL QUERYIDENTITY)(
	LPMAPISESSION lpSession,
	ULONG FAR *lpcbEntryID,
	LPENTRYID FAR *lppEntryID);

typedef HRESULT (CDECL LOGOFF)(
	LPMAPISESSION lpSession,
	ULONG ulUIParam,
	ULONG ulFlags,
	ULONG ulReserved);
#endif //!WINPAD

typedef struct _DTBLMAPISESSION
{
	IUNKNOWNMETHODS
#ifndef WINPAD	
	GETLASTERROR FAR *			GetLastError;
	STDGETTABLE FAR *			GetMsgStoresTable;
	OPENMSGSTORE FAR *			OpenMsgStore;
	OPENADDRESSBOOK FAR *		OpenAddressBook;
	OPENPROFILESECTION FAR *	OpenProfileSection;
	STDGETTABLE FAR *			GetStatusTable;
#endif //!WINPAD	
	STDOPENENTRY FAR *			OpenEntry;
#ifndef WINPAD	
	STDCOMPAREENTRYIDS FAR *	CompareEntryIDs;
#endif	
	STDREGISTERNOTIFICATION FAR *RegisterNotification;
#ifndef WINPAD	
	MESSAGEOPTIONS FAR *		MessageOptions;
	QUERYDEFAULTMESSAGEOPT FAR *QueryDefaultMessageOpt;
	ENUMADRTYPES FAR *			EnumAdrTypes;
	QUERYIDENTITY FAR *			QueryIdentity;
#endif //!WINPAD	
	LOGOFF FAR *				Logoff;
} DTBLMAPISESSION, FAR *LPDTBLMAPISESSION;

#ifdef __cplusplus
class IMAPISession : public IUnknown
{
public:
	virtual HRESULT MAPIMETHOD OpenEntry(ULONG cbEntryID,LPENTRYID lpEntryID,LPIID lpInterface,ULONG ulFlags,ULONG FAR * lpulObjType,LPMAPIPROP FAR * lppMAPIPropEntry) = 0;
	virtual HRESULT MAPIMETHOD RegisterNotification(ULONG	cbEntryID,LPENTRYID	lpEntryID,ULONG	ulEventMask,FARPROC	lpfCallbackFunc,LPVOID lpvCallbackContext,LPNOTIFOBJ FAR * lppNotify) = 0;
	virtual HRESULT MAPIMETHOD Logoff(ULONG ulUIParam,ULONG ulFlags,ULONG ulReserved) = 0;
};
#endif

#ifndef WINPAD
/* ------------------------------ */
/* IAddrBook interface definition */

/*
 * Prototype for the client function hooked to an optional button on
 * the address book dialog
 */

typedef SCODE (CDECL FAR * LPFNBUTTON)(
	ULONG				ulUIParam,
	LPVOID				lpvContext,
	ULONG				cbEntryID,
	LPENTRYID			lpSelection,
	ULONG				ulFlags
);

/* Parameters for the address book dialog */

typedef struct _ADRPARM
{
	ULONG			ulReserved;
	LPVOID			lpvReserved;
	ULONG			ulFlags;	
	ULONG			ulModality;
	LPDISMISS		lpfnDismiss;
	LPTSTR			lpszCaption;
	ULONG			cDestFields;
	ULONG			nDestFieldFocus;
	LPTSTR FAR *	lppszAbrvTitles;
	LPTSTR FAR *	lppszDestTitles;
	LPSRestriction	lpContRestriction;
	LPSRestriction	lpHierRestriction;
	LPFNBUTTON		lpfButtonCallback;
	LPVOID			lpvContext;
	LPTSTR			lpszButtonText;
} ADRPARM, FAR * LPADRPARM;


typedef HRESULT (CDECL CREATEONEOFF)(
	LPADRBOOK		lpAdrBook,
	LPTSTR			lpszName,
	LPTSTR			lpszAdrType,
	LPTSTR			lpszAddress,
	ULONG			ulFlags,
	ULONG FAR *		lpcbEntryID,
	LPENTRYID FAR *	lppEntryID
);
typedef HRESULT (CDECL RESOLVENAME)(
	LPADRBOOK		lpAdrBook,
	ULONG			ulUIParam,
	LPTSTR			lpszPartialName,
	ULONG			ulFlags,
	LPTSTR FAR *	lppszDisplayName,
	ULONG FAR *		lpcbEntryID,
	LPENTRYID FAR *	lppEntryID,
	LPTSTR FAR *	lppszAdrType
);
typedef HRESULT (CDECL ADDRESS)(
	LPADRBOOK		lpAdrBook,
	ULONG FAR *		lpulUIParam,
	LPADRPARM		lpAdrParms,
	ULONG			ulFlags,
	LPADRLIST FAR *	lppAdrList
);
typedef HRESULT (CDECL DETAILS)(
	LPADRBOOK		lpAdrBook,
	ULONG FAR *		lpulUIParam,
	ULONG			ulModality,
	LPDISMISS		lpfnDismiss,
	ULONG			cbEntryID,
	LPENTRYID 		lpEntryID,
	LPFNBUTTON		lpfButtonCallback,
	LPVOID			lpvContext,
	LPTSTR			lpszButtonText,
	ULONG			ulFlags
);
typedef HRESULT (CDECL RECIPOPTIONS)(
	LPADRBOOK		lpAdrBook,
	ULONG			ulUIParam,
	ULONG			ulFlags,
	LPADRENTRY FAR *lppRecip
);

typedef HRESULT (CDECL GETPAB)(
	LPADRBOOK		lpAdrBook,
	ULONG FAR *		lpcbEntryID,
	LPENTRYID FAR *	lppEntryID
);

typedef HRESULT (CDECL SETPAB)(
	LPADRBOOK			lpAdrBook,
	ULONG				cbEntryID,
	LPENTRYID 			lpEntryID
);

typedef HRESULT (CDECL GETDEFAULTDIR)(
	LPADRBOOK			lpAdrBook,
	ULONG FAR *			lpcbEntryID,
	LPENTRYID FAR *		lppEntryID
);

typedef HRESULT (CDECL SETDEFAULTDIR)(
	LPADRBOOK			lpAdrBook,
	ULONG				cbEntryID,
	LPENTRYID 			lpEntryID
);

typedef HRESULT (CDECL QUERYDEFAULTRECIPOPT)(
	LPADRBOOK			lpAdrBook,
	LPTSTR				lpszAdrType,
	ULONG				ulFlags,
	ULONG FAR *			lpcValues,
	LPSPropValue FAR *	lppOptions);
	
typedef struct _DTBLADDRBOOK
{
	MAPIPROPMETHODS
	STDOPENENTRY		* OpenEntry;
	STDCOMPAREENTRYIDS	* CompareEntryIDs;
	STDREGISTERNOTIFICATION	* RegisterNotification;
	CREATEONEOFF		* CreateOneOff;
	RESOLVENAME			* ResolveName;
	ADDRESS				* Address;
	DETAILS				* Details;
	RECIPOPTIONS		* RecipOptions;
	GETPAB				* GetPAB;
	SETPAB				* SetPAB;
	GETDEFAULTDIR		* GetDefaultDir;
	SETDEFAULTDIR		* SetDefaultDir;
} DTBLADDRBOOK, FAR * LPDTBLADDRBOOK;

#endif
#ifdef	__cplusplus
}		/*	extern "C" */
#endif	

#endif /* MAPIX_H */
