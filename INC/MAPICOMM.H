/*
 *	M A P I C O M M . H
 *	
 *	Definitions used by MAPI clients and service providers.
 *
 *               Copyright (c) 1993, Microsoft Corp. All rights reserved.
 *
 */

#ifndef MAPICOMM_H
#define MAPICOMM_H

#ifdef	__cplusplus
extern "C" {
#endif	

/*
 *	ENTRYID, ENTRYLIST structures
 */

#ifndef WINPAD
#pragma warning (disable: 4200)
typedef struct
{
	BYTE	abFlags[4];
	BYTE	ab[];
} ENTRYID, FAR *LPENTRYID;
#pragma warning (disable: 4200)
#endif //WINPAD

/* Bit definitions for abFlags[0] of ENTRYID */

#define MAPI_PERMANENT			0x80
#define MAPI_NOTRECIP			0x40
#define MAPI_THISSESSION		0x20
#define MAPI_NOW				0x10
#define MAPI_NOTRESERVED		0x08

typedef SBinaryArray ENTRYLIST, FAR *LPENTRYLIST;

/*
 *	Common prototypes used in multiple objects.
 *	
 *		OpenEntry				opens an object in a container
 *		CompareEntryIDs			checks two entry IDs for equality
 *		RegisterNotification	registers a callback function for
 *								events such as changes to an object
 *		GetTable				opens a table associated with an
 *								object
 */

/*
 *	Flags to CompareEntryIDs.
 *	Note: this flag is for internal use noly.
 */

#define MAPI_STOREEID			((ULONG)0x00000001)


typedef HRESULT (FAR CDECL STDOPENENTRY)(
	LPVOID				lpObject,
	ULONG				cbEntryID,
	LPENTRYID			lpEntryID,
	LPIID				lpInterface,
	ULONG				ulFlags,
	ULONG FAR *			lpulObjType,
	LPMAPIPROP FAR *	lppMAPIPropEntry);

typedef HRESULT (FAR CDECL STDCOMPAREENTRYIDS)(
	LPVOID				lpObject,
	ULONG				cbEntryID1,
	LPENTRYID			lpEntryID1,
	ULONG				cbEntryID2,
	LPENTRYID			lpEntryID2,
	ULONG				ulFlags,
	ULONG FAR *			lpulResult);

typedef HRESULT (FAR CDECL STDREGISTERNOTIFICATION)(
	LPVOID				lpObject,
	ULONG				cbEntryID,
	LPENTRYID			lpEntryID,
	ULONG				ulEventMask,
	FARPROC				lpfCallbackFunc,
	LPVOID				lpvCallbackContext,
	LPNOTIFOBJ FAR *	lppNotify);

typedef HRESULT (FAR CDECL STDGETTABLE)(
	LPVOID				lpObject,
	ULONG				ulFlags,
	LPMAPITABLE FAR *	lppTable);

/* ------------------------------------- */
/* Typedefs for MAPI allocation routines */
/* Note: FreeBuffer is ULONG PASCAL to match MAPIFreeBuffer, */
/* which is ULONG PASCAL because it is part of simple MAPI. */

typedef SCODE (FAR CDECL ALLOCATEBUFFER)(
	ULONG			cbSize,
	LPVOID FAR *	lppBuffer
);

typedef SCODE (FAR CDECL ALLOCATEMORE)(
	ULONG			cbSize,
	LPVOID			lpObject,
	LPVOID FAR *	lppBuffer
);

typedef ULONG (FAR PASCAL FREEBUFFER)(
	LPVOID			lpBuffer
);

typedef ALLOCATEBUFFER FAR *LPALLOCATEBUFFER;
typedef ALLOCATEMORE FAR *LPALLOCATEMORE;
typedef FREEBUFFER FAR *LPFREEBUFFER;

#ifndef WINPAD
/* --------------------------------- */
/* IMAPIProfile interface definition */

typedef struct _DTBLPROFSECT
{
	MAPIPROPMETHODS
} DTBLPROFSECT, FAR * LPDTBLPROFSECT;

/* -------------------------------- */
/* IMAPIStatus interface definition */

/* Values for PR_RESOURCE_TYPE, _METHODS, _FLAGS */

#define MAPI_STORE_PROVIDER		((ULONG) 33)	/* Message Store */
#define MAPI_AB					((ULONG) 34)	/* Address Book */
#define MAPI_AB_PROVIDER		((ULONG) 35)	/* Address Book Provider */
#define MAPI_TRANSPORT_PROVIDER	((ULONG) 36)	/* Transport Provider */
#define MAPI_SPOOLER			((ULONG) 37)	/* Message Spooler */
#define MAPI_PROFILE_PROVIDER	((ULONG) 38)	/* Profile Provider */
#define MAPI_SUBSYSTEM			((ULONG) 39)	/* Overall Subsystem Status */

#define STATUS_VALIDATE_STATE	((ULONG) 0x00000001)
#define STATUS_SETTINGS_DIALOG	((ULONG) 0x00000002)
#define STATUS_CHANGE_PASSWORD	((ULONG) 0x00000004)
#define STATUS_FLUSH_QUEUES		((ULONG) 0x00000008)

#define STATUS_DEFAULT_OUTBOUND	((ULONG) 0x00000001)
#define STATUS_DEFAULT_STORE	((ULONG) 0x00000002)
#define STATUS_PRIMARY_IDENTITY	((ULONG) 0x00000004)

/*
 * PR_STATUS_CODE bit. Low 16 bits for common values; High 16 bits
 * for provider type-specific values. (DCR 304)
 */

#define	STATUS_AVAILABLE		((ULONG) 0x00000001)
#define STATUS_OFFLINE			((ULONG) 0x00000002)
#define STATUS_FAILURE			((ULONG) 0x00000004)

/* Transport values of PR_STATUS_CODE */

#define STATUS_INBOUND_ENABLED	((ULONG) 0x00010000)
#define STATUS_INBOUND_ACTIVE	((ULONG) 0x00020000)
#define STATUS_INBOUND_FLUSH	((ULONG) 0x00040000)
#define STATUS_OUTBOUND_ENABLED	((ULONG) 0x00100000)
#define STATUS_OUTBOUND_ACTIVE	((ULONG) 0x00200000)
#define STATUS_OUTBOUND_FLUSH	((ULONG) 0x00400000)

typedef struct
{
	ULONG			cbEntryID;
	LPENTRYID		lpEntryID;
	ULONG			cValues;
	LPSPropValue	lpPropVals;
} STATUS_OBJECT_NOTIFICATION;

/* ValidateStatus flags */

#define SUPPRESS_UI		((ULONG) 0x00000001)

/* SettingsDialog flags */

#define UI_READONLY		((ULONG) 0x00000001)

/* FlushQueues flags */

#define FLUSH_UPLOAD		((ULONG) 0x00000002)
#define FLUSH_DOWNLOAD		((ULONG) 0x00000004)
#define FLUSH_FORCE			((ULONG) 0x00000008)
#define FLUSH_NO_UI			((ULONG) 0x00000010)

typedef HRESULT (FAR CDECL VALIDATESTATUS)(
	LPMAPISTATUS	lpProvider,
	ULONG			ulUIParam,
	ULONG			ulFlags
);

typedef HRESULT (FAR CDECL SETTINGSDIALOG)(
	LPMAPISTATUS	lpProvider,
	ULONG			ulUIParam,
	ULONG			ulFlags
);

typedef HRESULT (FAR CDECL CHANGEPASSWORD)(
	LPMAPISTATUS	lpProvider,
	LPTSTR			lpOldPass,
	LPTSTR			lpNewPass,
	ULONG			ulFlags
);

typedef HRESULT (FAR CDECL FLUSHQUEUES)(
	LPMAPISTATUS	lpProvider,
	ULONG			ulUIParam,
	ULONG			cbTargetTransport,
	LPENTRYID		lpTargetTransport,
	ULONG			ulFlags
);

typedef struct _DTBLSTATUS
{
	MAPIPROPMETHODS
	VALIDATESTATUS		FAR * ValidateStatus;
	SETTINGSDIALOG		FAR * SettingsDialog;
	CHANGEPASSWORD		FAR * ChangePassword;
	FLUSHQUEUES			FAR * FlushQueues;
} DTBLSTATUS, FAR * LPDTBLSTATUS;

/* ------------------------------ */
/* ADRENTRY, ADRLISTCOMP, ADRLIST */

/* ulRecipFlags */

#define RECIP_ADD		((ULONG) 0x00000001)
#define RECIP_MODIFY	((ULONG) 0x00000002)
#define RECIP_REMOVE	((ULONG) 0x00000004)

typedef struct _ADRENTRY	
{
	ULONG			ulRecipFlags;		
	ULONG			cValues;
	LPSPropValue	rgPropVals;
} ADRENTRY, FAR * LPADRENTRY;

#pragma warning (disable: 4200)

typedef struct _ADRLISTCOMP
{
	ULONG			ulRecipType;
	ULONG			cEntries;
	ADRENTRY		aEntries[];
} ADRLISTCOMP, FAR * LPADRLISTCOMP;

typedef struct _ADRLIST
{
	ULONG			cLists;
	LPADRLISTCOMP	Lists[];
} ADRLIST, FAR * LPADRLIST;

#pragma warning (default: 4200)
#endif //!WINPAD


/* ----------------------------------- */
/* IMAPIContainer interface definition */

/* Flags for GetContentsTable */

#define MAPI_CATEGORIZE			((ULONG) 0x00000001)

#define MAPICONTMETHODS \
	MAPIPROPMETHODS \
	STDGETTABLE		FAR * GetContentsTable; \
	STDGETTABLE		FAR * GetHierarchyTable; \
	STDOPENENTRY	FAR * OpenEntry;


typedef struct _DTBLMAPICONTAINER
{
	MAPICONTMETHODS
} DTBLMAPICONTAINER, FAR * LPDTBLMAPICONTAINER;

#ifdef __cplusplus
class FAR IMAPIContainer : public IMAPIProp
{
public:
	virtual	HRESULT	MAPIMETHOD GetContentsTable(ULONG ulFlags,LPMAPITABLE FAR * lppTable) const = 0;
	virtual HRESULT MAPIMETHOD GetHierarchyTable(ULONG ulFlags,LPMAPITABLE FAR * lppTable) const = 0;	
	virtual HRESULT MAPIMETHOD OpenEntry(ULONG	cbEntryID,LPENTRYID	lpEntryID,LPIID	lpInterface,
	                                     ULONG ulFlags,ULONG FAR * lpulObjType,
	                                     LPMAPIPROP FAR * lppMAPIPropEntry) const = 0;	
};
#endif

/* --------------------------------- */
/* IABContainer interface definition */

/*
 *	IABContainer PR_CONTAINER_FLAGS values
 *	If AB_NOT_MODIFIABLE and AB_UNSURE are both set, we'll go ahead and
 *	try to modify the contents but we won't expect it to work.
 *	If neither bit is set, it implies that the user definitely has the
 *	privilege of modifying the contents table.
 */

#define AB_RECIPIENTS			((ULONG) 0x00000001)
#define AB_SUBCONTAINERS		((ULONG) 0x00000002)
#define AB_NOT_MODIFIABLE		((ULONG) 0x00000004)
#define AB_UNSURE				((ULONG) 0x0000000C)
	

typedef struct _DTBLABCONTAINER
{
	MAPICONTMETHODS
} DTBLABCONTAINER, FAR * LPDTBLABCONTAINER;


/* -------------------------------- */
/* IABMailUser interface definition */

typedef struct _DTBLMAILUSER
{
	MAPIPROPMETHODS
} DTBLMAILUSER, FAR * LPDTBLMAILUSER;


/* -------------------------------- */
/* IABDistList interface definition */

typedef struct _DTBLDISTLIST
{
	MAPICONTMETHODS
} DTBLDISTLIST, FAR * LPDTBLDISTLIST;


/* ---------------------------- */
/* IFolder interface definition */

/* IFolder folder type (enum) */

#define FOLDER_ROOT				((ULONG) 0x00000000)
#define FOLDER_GENERIC			((ULONG) 0x00000001)
#define FOLDER_SEARCH			((ULONG) 0x00000002)

/* CopyMessages */

#define MESSAGE_MOVE			((ULONG) 0x00000001)
#define MESSAGE_DIALOG			((ULONG) 0x00000002)

/* CopyFolder */

#define FOLDER_MOVE				((ULONG) 0x00000001)
#define FOLDER_DIALOG			((ULONG) 0x00000002)
#define COPY_SUBFOLDERS			((ULONG) 0x00000004)

/* GetHierarchyTable */

#define CONVENIENT_DEPTH		((ULONG) 0x00000001)

/* DeleteFolder */

#define DEL_CONTENTS			((ULONG) 0x00000001)
#define DEL_RECURSIVE			((ULONG) 0x00000002)

/* SetSearchCriteria, GetSearchCriteria */

#define STOP_SEARCH				((ULONG) 0x00000001)
#define CONTINUOUS_SEARCH		((ULONG) 0x00000002)
#define PERMANENT_SEARCH		((ULONG) 0x00000004)
#define RECURSIVE_SEARCH		((ULONG) 0x00000008)
#define FOREGROUND_SEARCH		((ULONG) 0x00000010)

/* GetMessageStatus */

#define MSGSTATUS_HIGHLIGHTED	((ULONG) 0x00000001)
#define MSGSTATUS_TAGGED		((ULONG) 0x00000002)
#define MSGSTATUS_HIDDEN		((ULONG) 0x00000004)
#define MSGSTATUS_DELMARKED		((ULONG) 0x00000008)
#define MSGSTATUS_RESEND		((ULONG) 0x00000010)

/* SaveContentsSort */

/*#define MAPI_CATEGORIZE		((ULONG) 0x00000001) */
#define RECURSIVE_SORT			((ULONG) 0x00000002)

/* PR_STATUS property */

#define FLDSTATUS_HIGHLIGHTED	((ULONG) 0x00000001)
#define FLDSTATUS_TAGGED		((ULONG) 0x00000002)
#define FLDSTATUS_HIDDEN		((ULONG) 0x00000004)
#define FLDSTATUS_DELMARKED		((ULONG) 0x00000008)


typedef HRESULT (FAR CDECL CREATEMESSAGE)(
	LPFOLDER		lpFolder,
	LPIID			lpInterface,
	ULONG			ulFlags,
	LPMESSAGE FAR *	lppMessage
);
typedef HRESULT (FAR CDECL COPYMESSAGES)(
	LPFOLDER		lpFolder,
	LPENTRYLIST		lpMsgList,
	LPFOLDER		lpDestFolder,
	ULONG			ulUIParam,
	LPProgressInfo	lpProgress,
	ULONG			ulFlags,
	ULONG FAR *		lpulErrorIndex
);
typedef HRESULT (FAR CDECL DELETEMESSAGES)(
	LPFOLDER		lpFolder,
	ULONG			ulUIParam,
	LPProgressInfo	lpProgress,
	LPENTRYLIST		lpMsgList,
	ULONG			ulFlags,
	ULONG FAR *		lpulErrorIndex
);
typedef HRESULT (FAR CDECL CREATEFOLDER)(
	LPFOLDER		lpFolder,
	ULONG			ulFolderType,
	LPTSTR			lpszFolderName,
	LPTSTR			lpszFolderComment,
	LPIID			lpInterface,
	ULONG			ulFlags,
	LPFOLDER FAR *	lppFolder
);
typedef HRESULT (FAR CDECL COPYFOLDER)(
	LPFOLDER		lpFolder,
	LPFOLDER		lpDestFolder,
	LPTSTR			lpszNewFolderName,
	ULONG			ulUIParam,
	LPProgressInfo	lpProgress,
	ULONG			ulFlags
);
typedef HRESULT (FAR CDECL DELETEFOLDER)(
	LPFOLDER		lpFolder,
	ULONG			ulUIParam,
	LPProgressInfo	lpProgress,
	ULONG			cbEntryID,
	LPENTRYID		lpEntryID,
	ULONG			ulFlags
);
typedef HRESULT (FAR CDECL SETSEARCHCRITERIA)(
	LPFOLDER		lpFolder,
	LPSRestriction	lpRestriction,
	LPENTRYLIST		lpFolderList,
	ULONG			ulSearchFlags
);
typedef HRESULT (FAR CDECL GETSEARCHCRITERIA)(
	LPFOLDER			lpFolder,
	LPSRestriction FAR *lppRestriction,
	LPENTRYLIST FAR *	lppFolderList,
	ULONG FAR *			lpulSearchState
);
typedef HRESULT (FAR CDECL GETMESSAGESTATUS)(
	LPFOLDER		lpFolder,
	ULONG			cbEntryID,
	LPENTRYID		lpEntryID,
	ULONG			ulFlags,
	ULONG FAR *		lpulMessageStatus
);
typedef HRESULT (FAR CDECL SETMESSAGESTATUS)(
	LPFOLDER		lpFolder,
	ULONG			cbEntryID,
	LPENTRYID		lpEntryID,
	ULONG			ulNewStatus,
	ULONG			ulNewStatusMask,
	ULONG FAR *		lpulOldStatus
);
typedef HRESULT (CDECL SAVECONTENTSSORT)(
	LPFOLDER		lpFolder,
	LPSSortOrderSet	lpSortCriteria,
	ULONG			ulFlags);

typedef struct _DTBLFOLDER
{
	MAPICONTMETHODS
	CREATEMESSAGE		FAR * CreateMessage;
	COPYMESSAGES		FAR * CopyMessages;
	DELETEMESSAGES		FAR * DeleteMessages;
	CREATEFOLDER		FAR * CreateFolder;
	COPYFOLDER			FAR * CopyFolder;
	DELETEFOLDER		FAR * DeleteFolder;
	SETSEARCHCRITERIA	FAR * SetSearchCriteria;
	GETSEARCHCRITERIA	FAR * GetSearchCriteria;
	GETMESSAGESTATUS	FAR * GetMessageStatus;
	SETMESSAGESTATUS	FAR * SetMessageStatus;
	SAVECONTENTSSORT	FAR * SaveContentsSort;
} DTBLFOLDER, FAR * LPDTBLFOLDER;

#ifdef __cplusplus
class FAR IFolder : public IMAPIContainer
{
public:
	virtual	HRESULT	MAPIMETHOD CreateMessage(LPIID lpiid,ULONG ulFlags,LPMESSAGE FAR * lppMessage) = 0;
	virtual HRESULT MAPIMETHOD CopyMessages(LPENTRYLIST lpMsgList,LPFOLDER lpDestFloder,ULONG ulUIParam,LPProgressInfo	lpProgress,ULONG ulFlags,ULONG FAR * lpulErrorIndex) = 0;
	virtual HRESULT MAPIMETHOD DeleteMessages(ULONG ulUIParam,LPProgressInfo lpProgress,LPENTRYLIST lpMsgList,ULONG ulFlags,ULONG FAR *lpulErrorIndex) = 0;
	virtual HRESULT MAPIMETHOD CreateFolder(ULONG ulFolderType,LPTSTR lpszFolderName,LPTSTR lpszFolderComment,LPIID lpInterface,ULONG ulFlags,LPFOLDER FAR * lppFolder) = 0;
	virtual HRESULT MAPIMETHOD CopyFolder(LPFOLDER lpDestFolder,LPTSTR lpszNewFolderName,ULONG ulUIParam,LPProgressInfo lpProgress,ULONG ulFlags) = 0;
	virtual HRESULT MAPIMETHOD DeleteFolder(ULONG ulUIParam,LPProgressInfo lpProgress,ULONG cbEntryID,ENTRYID FAR * lpEntryID,ULONG ulFlags) = 0;
	virtual HRESULT MAPIMETHOD SetSearchCriteria(LPSRestriction lpRestriction,LPENTRYLIST lpFolderList,ULONG ulSearchFlags) = 0;
	virtual HRESULT MAPIMETHOD GetSearchCriteria(LPSRestriction FAR *lppRestriction,LPENTRYLIST FAR *	lppFolderList,ULONG FAR * lpulSearchState) = 0;
	virtual HRESULT MAPIMETHOD GetMessageStatus(ULONG cbEntryID,ENTRYID FAR * lpEntryID,ULONG ulFlags,ULONG FAR * lpulMessageStatus) = 0;
	virtual HRESULT MAPIMETHOD SetMessageStatus(ULONG cbEntryID,ENTRYID FAR * lpEntryID,ULONG ulNewStatus,ULONG ulNewStatusMask,ULONG FAR * lpulOldStatus) = 0;
	virtual HRESULT MAPIMETHOD SaveContentsSort(LPSSortOrderSet lpSortCriteria,ULONG ulFlags) = 0;
};
#endif // __cplusplus

#ifndef WINPAD
/* ------------------------------ */
/* IMsgStore interface definition */


/* StoreLogoff() */

#define	LOGOFF_NO_WAIT		((ULONG) 0x00000001)
#define	LOGOFF_ORDERLY		((ULONG) 0x00000002)
#define	LOGOFF_PURGE		((ULONG) 0x00000004)
#define LOGOFF_ABORT		((ULONG) 0x00000008)
#define LOGOFF_QUIET		((ULONG) 0x00000010)

#define LOGOFF_COMPLETE		((ULONG) 0x00010000)
#define	LOGOFF_INBOUND		((ULONG) 0x00020000)
#define LOGOFF_OUTBOUND		((ULONG) 0x00040000)
#define LOGOFF_OUTBOUND_QUEUE ((ULONG) 0x0008000)


typedef HRESULT (FAR CDECL SETRECEIVEFOLDER)(
	LPMDB		lpMDB,
	LPTSTR		lpszMessageClass,
	ULONG		ulFlags,
	ULONG		cbEntryID,
	LPENTRYID	lpEntryID
);
typedef HRESULT (FAR CDECL GETRECEIVEFOLDER)(
	LPMDB		lpMDB,
	LPTSTR		lpszMessageClass,
	ULONG		ulFlags,
	ULONG FAR *	lpcbEntryID,
	LPENTRYID FAR *lppEntryID,
	LPTSTR FAR *lppszExplicitClass
);

typedef HRESULT (FAR CDECL MDBGETOUTGOINGQUEUE)(
	LPVOID			lpObject,
	ULONG			ulFlags,
	ULONG			ulEventMask,
	FARPROC			lpfCallbackFunc,
	LPVOID			lpvCallbackContext,
	LPNOTIFOBJ FAR *lppNotify,
	LPMAPITABLE FAR *lppTable);

typedef HRESULT (FAR CDECL MDBLOCKMSG)(
	LPMDB		lpMDB,
	ULONG		ulFlags,
	ULONG		cbEntryID,
	LPENTRYID	lpEntryID
);

typedef HRESULT (FAR CDECL MDBFINISHEDMSG)(
	LPMDB		lpMDB,
	ULONG		ulFlags,
	ULONG		cbEntryID,
	LPENTRYID	lpEntryID
);

typedef HRESULT (FAR CDECL STORELOGOFF)(
	LPMDB		lpMDB,
	ULONG FAR *	lpulFlags
);


typedef struct _DTBLMSGSTORE
{
	MAPIPROPMETHODS
	STDOPENENTRY			FAR * OpenEntry;
	STDCOMPAREENTRYIDS		FAR * CompareEntryIDs;
	STDREGISTERNOTIFICATION	FAR * RegisterNotification;
	SETRECEIVEFOLDER		FAR * SetReceiveFolder;
	GETRECEIVEFOLDER		FAR * GetReceiveFolder;
	MDBGETOUTGOINGQUEUE		FAR * MDBGetOutgoingQueue;
	MDBLOCKMSG				FAR * MDBLockMsg;
	MDBFINISHEDMSG			FAR * MDBFinishedMsg;
	STORELOGOFF				FAR * StoreLogoff;
} DTBLMSGSTORE, FAR * LPDTBLMSGSTORE;

#endif //!WINPAD

/* ----------------------------- */
/* IMessage interface definition */

/* SubmitMessage */

#define FORCE_SUBMIT			((ULONG) 0x00000001)

/* GetMessageFlags */

#define MSGFLAG_READ			((ULONG) 0x00000001)
#define MSGFLAG_UNMODIFIED		((ULONG) 0x00000002)
#define MSGFLAG_SUBMIT			((ULONG) 0x00000004)
#define MSGFLAG_UNSENT			((ULONG) 0x00000008)
#define MSGFLAG_HASATTACH		((ULONG) 0x00000010)

/* ModifyRecipients */

#define MESSAGE_REPLACE			((ULONG) 0x00000001)

/* SetReadFlag */

#define SUPPRESS_RECEIPT		((ULONG) 0x00000001)

/* PR_SECURITY values */
#define SECURITY_SIGNED			((ULONG) 0x00000001)
#define SECURITY_ENCRYPTED		((ULONG) 0x00000002)

#ifdef WINPAD
typedef struct _DTBLMESSAGE
{
	MAPIPROPMETHODS
} DTBLMESSAGE, FAR * LPDTBLMESSAGE;

#else
typedef HRESULT (FAR CDECL OPENATTACH)(
	LPMESSAGE		lpMessage,
	ULONG			ulAttachmentNum,
	LPIID			lpInterface,
	ULONG			ulFlags,
	LPATTACH FAR *	lppAttach
);
typedef HRESULT (FAR CDECL CREATEATTACH)(
	LPMESSAGE		lpMessage,
	LPIID			lpInterface,
	ULONG			ulFlags,
	ULONG FAR *		lpulAttachmentNum,
	LPATTACH FAR *	lppAttach
);
typedef HRESULT (FAR CDECL DELETEATTACH)(
	LPMESSAGE		lpMessage,
	ULONG			ulUIParam,
	LPProgressInfo	lpProgress,
	ULONG			ulAttachmentNum,
	ULONG			ulFlags
);
typedef HRESULT (FAR CDECL MODIFYRECIPIENTS)(
	LPMESSAGE		lpMessage,
	ULONG			ulFlags,
	LPADRLIST		lpMods
);
typedef HRESULT (FAR CDECL SUBMITMESSAGE)(
	LPMESSAGE		lpMessage,
	ULONG			ulFlags
);
typedef HRESULT (FAR CDECL ABORTSUBMIT)(
	LPMESSAGE		lpMessage,
	ULONG			ulFlags
);
typedef HRESULT (FAR CDECL SETREADFLAG)(
	LPMESSAGE		lpMessage,
	ULONG			ulFlags
);

typedef struct _DTBLMESSAGE
{
	MAPIPROPMETHODS
	STDGETTABLE			FAR * GetAttachmentTable;
	OPENATTACH			FAR * OpenAttach;
	CREATEATTACH		FAR * CreateAttach;
	DELETEATTACH		FAR * DeleteAttach;
	STDGETTABLE			FAR * GetRecipientTable;
	MODIFYRECIPIENTS	FAR * ModifyRecipients;
	SUBMITMESSAGE		FAR * SubmitMessage;
	ABORTSUBMIT			FAR * AbortSubmit;
	SETREADFLAG			FAR * SetReadFlag;
} DTBLMESSAGE, FAR * LPDTBLMESSAGE;


/* ---------------------------- */
/* IAttach interface definition */

/* IAttach attachment methods: PR_ATACH_METHOD values */

#define NO_ATTACHMENT			((ULONG) 0x00000000)
#define ATTACH_BY_VALUE			((ULONG) 0x00000001)
#define ATTACH_BY_REFERENCE		((ULONG) 0x00000002)
#define ATTACH_BY_REF_RESOLVE	((ULONG) 0x00000003)
#define ATTACH_BY_REF_ONLY		((ULONG) 0x00000004)
#define ATTACH_EMBEDDED_MSG		((ULONG) 0x00000005)
#define ATTACH_OLE				((ULONG) 0x00000006)


typedef struct _DTBLATTACH
{
	MAPIPROPMETHODS
} DTBLATTACH, FAR * LPDTBLATTACH;


/* --------------------------------- */
/* Address Book interface definition */


/* ADRPARM ulFlags */

#define ADDRESS_ONE				((ULONG) 0x00000002)


typedef void (FAR CDECL DISMISSMODELESS)( ULONG ulUIParam );
typedef DISMISSMODELESS FAR * LPDISMISS;


/* ------------ */
/* Random flags */

/* Flags for OpenMessageStore */

#define MDB_NO_DIALOG			((ULONG) 0x00000001)
#define MDB_SELECT_STORE		((ULONG) 0x00000002)
#define MDB_WRITE				((ULONG) 0x00000004)

/* Flag for deferred error */
#define MAPI_DEFERRED_ERRORS	((ULONG) 0x00000008)

/* Flags for OpenAddressBook */

#define AB_NO_DIALOG			((ULONG) 0x00000001)

#endif //!WINPAD
#ifdef	__cplusplus
}		/*	extern "C" */
#endif	

#endif /* MAPICOMM_H */
