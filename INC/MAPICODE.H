/*
 *	M A P I C O D E . H
 *	
 *	Status Codes returned by MAPI routines
 *
 *               Copyright (c) 1993, Microsoft Corp. All rights reserved.
 */


#ifdef	__cplusplus
extern "C" {
#endif	

#ifndef GetSCode
#define GetSCode( hResult )  				((SCODE) (hResult))
#endif

#ifndef ReportResult
#define ReportResult( l1, scode, l2, l3)	((HRESULT) (scode))
#endif

#ifndef MakeResult
#define MakeResult(_s)	ReportResult(0,_s,0,0)
#endif

/*
 *	Simple MAPI error codes. These are duplicated in MAPI.H.
 *	We want to support mixed use of SMAPI and extended MAPI calls,
 *	so we will avoid defining duplicate values for these errors
 *	unless constrained to do so by the OS.
 */
#ifndef __SIMPLE_MAPI_CODES_DEFINED
#define __SIMPLE_MAPI_CODES_DEFINED

#ifndef SUCCESS_SUCCESS
#define SUCCESS_SUCCESS                 0
#endif
#define MAPI_USER_ABORT                 1
#define MAPI_E_USER_ABORT               MAPI_USER_ABORT
#define MAPI_E_FAILURE                  2
#define MAPI_E_LOGON_FAILURE            3
#define MAPI_E_LOGIN_FAILURE            MAPI_E_LOGON_FAILURE
#define MAPI_E_DISK_FULL                4
#define MAPI_E_INSUFFICIENT_MEMORY      5
#define MAPI_E_ACCESS_DENIED            6
#define MAPI_E_TOO_MANY_SESSIONS        8
#define MAPI_E_TOO_MANY_FILES           9
#define MAPI_E_TOO_MANY_RECIPIENTS      10
#define MAPI_E_ATTACHMENT_NOT_FOUND     11
#define MAPI_E_ATTACHMENT_OPEN_FAILURE  12
#define MAPI_E_ATTACHMENT_WRITE_FAILURE 13
#define MAPI_E_UNKNOWN_RECIPIENT        14
#define MAPI_E_BAD_RECIPTYPE            15
#define MAPI_E_NO_MESSAGES              16
#define MAPI_E_INVALID_MESSAGE          17
#define MAPI_E_TEXT_TOO_LARGE           18
#define MAPI_E_INVALID_SESSION          19
#define MAPI_E_TYPE_NOT_SUPPORTED       20
#define MAPI_E_AMBIGUOUS_RECIPIENT      21
#define MAPI_E_AMBIG_RECIP              MAPI_E_AMBIGUOUS_RECIPIENT
#define MAPI_E_MESSAGE_IN_USE           22
#define MAPI_E_NETWORK_FAILURE          23
#define MAPI_E_INVALID_EDITFIELDS       24
#define MAPI_E_INVALID_RECIPS           25
#define MAPI_E_NOT_SUPPORTED            26

#endif	/* __SIMPLE_MAPI_CODES_DEFINED */

/* Arbitrary. We will eventually need to change this. */
/* Start MAPI errors at 0x0400, and go no higher */
/* than 0xFF00. */

#define MAPI_E_NOT_INITIALIZED			((SCODE) (0x0400)) /* MAPI */
#define MAPI_E_NO_MORE		  			((SCODE) (0x0401)) /* MAPI */
#define MAPI_E_ZERO_ALLOCATION			((SCODE) (0x0402)) /* MAPI */
#define MAPI_E_BAD_BUFFER	  			((SCODE) (0x0403)) /* MAPI */
#define	MAPI_E_NOT_IMPLEMENTED			((SCODE) (0x0404)) /* MAPI */

#define MAPI_W_CHECK_STATUS				((SCODE) (0x0405)) /* TABLE */
#define MAPI_W_POSITION_CHANGED			((SCODE) (0x0406)) /* TABLE */
#define MAPI_W_APPROX_COUNT				((SCODE) (0x0407)) /* TABLE */

#define MAPI_E_BUSY						((SCODE) (0x0408)) /* TABLE,XPORT */
#define MAPI_E_INSUFFICIENT_RESOURCES	((SCODE) (0x0409)) /* TABLE */
#define MAPI_E_UNABLE_TO_COMPLETE		((SCODE) (0x040A)) /* TABLE */
#define MAPI_E_BAD_SORT_CRITERIA		((SCODE) (0x040B)) /* TABLE */
#define MAPI_E_TABLE_EMPTY				((SCODE) (0x040C)) /* TABLE */
#define MAPI_E_TABLE_TOO_BIG			((SCODE) (0x040D)) /* TABLE */
#define MAPI_E_UNKNOWN_SORT_ORDER		((SCODE) (0x040E)) /* TABLE */
#define MAPI_E_NOT_FOUND				((SCODE) (0x040F)) /* TABLE */

#define MAPI_E_OUT_OF_SPACE				((SCODE) (0x0410)) /* STREAM */
#define MAPI_E_INVALID_FUNCTION			((SCODE) (0x0412)) /* STREAM */
#define MAPI_E_WRITE_LOCKED				((SCODE) (0x0414)) /* STREAM */
#define MAPI_E_NOT_READY				((SCODE) (0x0415)) /* STREAM */
#define MAPI_E_CRC_ERROR				((SCODE) (0x0416)) /* STREAM */
#define MAPI_E_SECTOR_NOT_FOUND			((SCODE) (0x0417)) /* STREAM */
#define MAPI_E_WRITE_FAULT				((SCODE) (0x0418)) /* STREAM */
#define MAPI_E_READ_FAULT				((SCODE) (0x0419)) /* STREAM */
#define MAPI_E_GENERAL_FAILURE			((SCODE) (0x041A)) /* STREAM */
#define MAPI_E_SHARING_VIOLATION		((SCODE) (0x041B)) /* STREAM */
#define MAPI_E_LOCK_VIOLATION			((SCODE) (0x041C)) /* STREAM */
#define MAPI_E_SHARE_BUF_OVFL			((SCODE) (0x041D)) /* STREAM */
#define MAPI_E_HANDLE_EOF				((SCODE) (0x041E)) /* STREAM */
#define MAPI_E_HANDLE_DISK_FULL			((SCODE) (0x041F)) /* STREAM */
#define MAPI_E_END_OF_STREAM			((SCODE) (0x0420)) /* STREAM */

#define MAPI_W_ALMOST_FULL				((SCODE) (0x0421)) /* STREAM */

#define	MAPI_E_NETWORK					((SCODE) (0x0422)) /* XPORT */
#define MAPI_E_WAIT						((SCODE) (0x0423)) /* XPORT */
#define MAPI_E_CANCEL					((SCODE) (0x0424)) /* XPORT */
#define MAPI_E_NOT_ME					((SCODE) (0x0425)) /* XPORT */

#define MAPI_W_CANCEL_MESSAGE			((SCODE) (0x0426)) /* XPORT */
#define MAPI_E_VERSION					((SCODE) (0x0427)) /* XPORT, others? */

#define MAPI_E_ACTIVE					((SCODE) (0x0429)) /* XPORT */

#define MAPI_E_PROPERTY_NOT_FOUND		((SCODE) (0x0430)) /* PROPERTY */
#define MAPI_W_ERRORS_RETURNED			((SCODE) (0x0431)) /* PROPERTY */
#define MAPI_E_CALL_FAILED				((SCODE) (0x0432)) /* PROPERTY */
#define MAPI_E_MODIFY_FAILURE			((SCODE) (0x0433)) /* PROPERTY */
#define MAPI_E_BAD_VALUE				((SCODE) (0x0434)) /* PROPERTY */
#define MAPI_E_NO_PROPERTIES			((SCODE) (0x0435)) /* PROPERTY */

#define MAPI_E_INTERFACE_NOT_SUPPORTED	((SCODE) (0x0436)) /* UNKNOWN  */
#define MAPI_E_INVALID_PARAMETER		((SCODE) (0x0437)) /* XPORT    */
#define MAPI_E_INVALID_OBJECT			((SCODE) (0x0438)) /* MAPI     */

#define MAPI_E_BAD_CREDENTIALS			((SCODE) (0x0439)) /* TOY STORE */
#define MAPI_E_COPY_FAILURE				((SCODE) (0x043A)) /* TOY STORE */
#define MAPI_E_CREATE_FAILURE			((SCODE) (0x043B)) /* TOY STORE */
#define MAPI_E_INVALID_ENTRYID			((SCODE) (0x043C)) /* TOY STORE */
#define MAPI_E_CORRUPT_STORE			((SCODE) (0x043D)) /* TOY STORE */
#define MAPI_E_UI_FAILURE				((SCODE) (0x043E)) /* TOY STORE */
#define MAPI_E_NOT_IN_QUEUE				((SCODE) (0x043F)) /* TOY STORE */
#define MAPI_E_UNABLE_TO_ABORT			((SCODE) (0x0440)) /* TABLE, TOY STORE */


#define MAPI_E_END_OF_TABLE				((SCODE) (0x0441)) /* TABLE (Raid 179) */
#define MAPI_E_INVALID_BOOKMARK			((SCODE) (0x0442)) /* TABLE (Raid 251) */
#define MAPI_E_ACTIVATE_COLUMN			((SCODE) (0x0443)) /* TABLE (Raid 156) */
#define MAPI_E_TOO_COMPLEX				((SCODE) (0x0444)) /* TABLE (Raid 155) */

#define MAPI_E_ENDOFSESSION				((SCODE) (0x0445)) /* MAPI (Raid 9) */
#define MAPI_E_OBJECT_CHANGED			((SCODE) (0x0446)) /* PROPERTY (Raid 197) */
#define MAPI_E_OBJECT_DELETED			((SCODE) (0x0447)) /* PROPERTY (Raid 197) */
#define MAPI_E_NO_SUPPRESS				((SCODE) (0x0448)) /* MAPI (Raid 209) */
#define MAPI_E_UNKNOWN_FLAGS			((SCODE) (0x0449)) /* MAPI (Raid 323) */
#define MAPI_E_SECURITY_VIOLATION		((SCODE) (0x044A)) /* STREAM (Raid 159) */
#define MAPI_E_ADDREF_FAILED			((SCODE) (0x044B)) /* MAPI (Raid 274) */

/* Define new errors before this line using the next sequentially */
/* higher number. Eventually, we will probably rearrange the errors */
/* into categories, so if you want to, please comment the category of */
/* the error you add. Example categories are: MAPI, LMS, AB, PAB, SPOOL, */
/* XPORT. If you need other categories, invent them. If you have */
/* additional questions about adding errors to this file, please let me */
/* know. Thanks -- billm 9/3/92 */

#define MAPI_E_SYSTEM_ERROR		((SCODE) (0x0FF00)) /* MAPI */

/* Internal error codes used by common utilities and other components */
/* which do not report their errors across the API. */

#define	MAPI_E_BAD_PARAMETER			((SCODE) (0x1000)) /* FLV/IBF */
#define MAPI_E_FID_NOT_FOUND			((SCODE) (0x1001)) /* FLV/IBF */


#ifdef	__cplusplus
}		/*	extern "C" */
#endif
