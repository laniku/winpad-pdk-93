/*
 *	PROPTAGS.H
 *	
 *	Property tag definitions for standard properties of MAPI
 *	objects.
 *
 *               Copyright (c) 1993, Microsoft Corp. All rights reserved.
 *	
 *	The following ranges should be used for all property IDs. Note that
 *	property IDs for objects other than messages and recipients should
 *	all fall in the range 0x3000 to 0x3FFF:
 *	
 *	From	To		Kind of property
--------------------------------
 *	0001	0BFF	MAPI_defined envelope property
 *	0C00	0DFF	MAPI_defined per-recipient property
 *	0E00	0FFF	MAPI_defined non-transmittable property
 *	1000	2FFF	MAPI_defined message content property
 *	
 *	3000	3FFF	MAPI_defined property (NOT message or recipient)
 *	
 *	4000	57FF	Transport-defined envelope property
 *	5800	5FFF	Transport-defined per-recipient property
 *	6000	67FF	User-defined non-transmittable property
 *	6800	7BFF	Message class-defined content property
 *	7C00	7FFF	Message class-defined non-transmittable
 *					property
 *	
 *	8000	FFFE	User-defined Name-to-id mapped property
 *	
 *	The 3000-3FFF range is further subdivided as follows:
 *	
 *	From	To		Kind of property
--------------------------------
 *	3000	33FF	Common property such as display name, entry ID
 *	3400	35FF	Message store object
 *	3600	36FF	Folder or AB container
 *	3700	38FF	Attachment
 *	3900	39FF	Address book object
 *	3A00	3BFF	Mail user
 *	3C00	3CFF	Distribution list
 *	3D00	3DFF	Profile section
 *	3E00	3FFF	Status object
 */

// Properties added for WINPAD are from this base.
#ifdef WINPAD
#define SOS_ID_BASE	0x8000
#endif

/*
 *	Message envelope properties
 */

#define PR_ACKNOWLEDGEMENT_MODE						PROP_TAG( PT_LONG,		0x0001)
#define PR_ALTERNATE_RECIPIENT_ALLOWED				PROP_TAG( PT_BOOLEAN,	0x0002)
#define PR_AUTHORIZING_USERS						PROP_TAG( PT_BINARY,	0x0003)
#define PR_AUTO_FORWARD_COMMENT						PROP_TAG( PT_TSTRING,	0x0004)
#define PR_AUTO_FORWARDED							PROP_TAG( PT_BOOLEAN,	0x0005)
#define PR_CONTENT_CONFIDENTIALITY_ALGORITHM_ID		PROP_TAG( PT_BINARY,	0x0006)
#define PR_CONTENT_CORRELATOR						PROP_TAG( PT_BINARY,	0x0007)
#define PR_CONTENT_IDENTIFIER						PROP_TAG( PT_BINARY,	0x0008)	// type?
#define PR_CONTENT_LENGTH							PROP_TAG( PT_LONG,		0x0009)
#define PR_CONTENT_RETURN_REQUESTED					PROP_TAG( PT_BOOLEAN,	0x000A)
#define PR_CONVERSATION_ID							PROP_TAG( PT_BINARY,	0x000B)
#define PR_CONVERSION_EITS							PROP_TAG( PT_BINARY,	0x000C)
#define PR_CONVERSION_WITH_LOSS_PROHIBITED			PROP_TAG( PT_BOOLEAN,	0x000D)
#define PR_CONVERTED_EITS							PROP_TAG( PT_BINARY,	0x000E)
#define PR_DEFERRED_DELIVERY_TIME					PROP_TAG( PT_SYSTIME,	0x000F)
#define PR_DELIVER_TIME								PROP_TAG( PT_SYSTIME,	0x0010)	// dups PR_MESSAGE_DELIVERY_TIME?
#define PR_DISCARD_REASON							PROP_TAG( PT_LONG,		0x0011)
#define PR_DISCLOSURE_OF_RECIPIENTS					PROP_TAG( PT_BOOLEAN,	0x0012)
#define PR_DL_EXPANSION_HISTORY						PROP_TAG( PT_BINARY,	0x0013)
#define PR_DL_EXPANSION_PROHIBITED					PROP_TAG( PT_BOOLEAN,	0x0014)
#define PR_EXPIRY_TIME								PROP_TAG( PT_SYSTIME,	0x0015)
#define PR_IMPLICIT_CONVERSION_PROHIBITED			PROP_TAG( PT_BOOLEAN,	0x0016)
#define PR_IMPORTANCE								PROP_TAG( PT_LONG,		0x0017)
#define PR_IPM_ID									PROP_TAG( PT_BINARY,	0x0018)
#define PR_LATEST_DELIVERY_TIME						PROP_TAG( PT_SYSTIME,	0x0019)
#define PR_MESSAGE_CLASS							PROP_TAG( PT_TSTRING,	0x001A)
#define PR_MESSAGE_DELIVERY_ID						PROP_TAG( PT_BINARY,	0x001B)
#define PR_MESSAGE_ID								PROP_TAG( PT_BINARY,	0x001C)
#define PR_MESSAGE_ORIGIN_AUTHENTICATION_CHECK		PROP_TAG( PT_BINARY,	0x001D)
#define PR_MESSAGE_SECURITY_LABEL					PROP_TAG( PT_BINARY,	0x001E)
#define PR_OBSOLETED_IPMS							PROP_TAG( PT_BINARY,	0x001F)
#define PR_ORIGINALLY_INTENDED_RECIPIENT_NAME		PROP_TAG( PT_BINARY,	0x0020)
#define PR_ORIGINAL_EITS							PROP_TAG( PT_BINARY,	0x0021)
#define PR_ORIGINATOR_CERTIFICATE					PROP_TAG( PT_BINARY,	0x0022)
#define PR_ORIGINATOR_DELIVERY_REPORT_REQUESTED		PROP_TAG( PT_BOOLEAN,	0x0023)
#define PR_ORIGINATOR_RETURN_ADDRESS				PROP_TAG( PT_BINARY,	0x0024)
#define PR_PARENT_ID								PROP_TAG( PT_BINARY,	0x0025)
#define PR_PRIORITY									PROP_TAG( PT_LONG,		0x0026)
#define PR_PROBE_SUBMISSION_AUTHENTICATION_CHECK	PROP_TAG( PT_BINARY,	0x0027)
#define PR_PROOF_OF_SUBMISSION_REQUESTED			PROP_TAG( PT_BOOLEAN,	0x0028)
#define PR_READ_RECEIPT_REQUESTED					PROP_TAG( PT_BOOLEAN,	0x0029)
#define PR_RECEIPT_TIME								PROP_TAG( PT_SYSTIME,	0x002A)
#define PR_RECIPIENT_REASSIGNMENT_PROHIBITED		PROP_TAG( PT_BOOLEAN,	0x002B)
#define PR_REDIRECTION_HISTORY						PROP_TAG( PT_BINARY,	0x002C)
#define PR_RELATED_IPMS								PROP_TAG( PT_BINARY,	0x002D)
#define PR_REPLIED_TO_IPM							PROP_TAG( PT_BINARY,	0x002E)
#define PR_REPLY_RECIPIENTS							PROP_TAG( PT_BINARY,	0x002F)
#define PR_REPLY_TIME								PROP_TAG( PT_SYSTIME,	0x0030)
#define PR_REPORT_TAG								PROP_TAG( PT_BINARY,	0x0031)
#define PR_REPORT_TIME								PROP_TAG( PT_SYSTIME,	0x0032)
#define PR_RETURNED_IPM								PROP_TAG( PT_BOOLEAN,	0x0033)
#define PR_SECURITY									PROP_TAG( PT_LONG,		0x0034)
#define PR_SENDER									PROP_TAG( PT_BINARY,	0x0035)
#define PR_SENSITIVITY								PROP_TAG( PT_LONG,		0x0036)
#define PR_SUBJECT									PROP_TAG( PT_TSTRING,	0x0037)
#define PR_SUBJECT_IPM								PROP_TAG( PT_BINARY,	0x0038)
#define PR_SUBMIT_TIME								PROP_TAG( PT_SYSTIME,	0x0039)
#define PR_THIS_RECIPIENT_NAME						PROP_TAG( PT_BINARY,	0x003B)
#define PR_X400_CONTENT_TYPE						PROP_TAG( PT_BINARY,	0x003C)
#define PR_NORMALIZED_SUBJECT						PROP_TAG( PT_TSTRING,	0x003D)


/*
 *	Message content properties
 */

#define PR_BODY										PROP_TAG( PT_TSTRING,	0x1000)
#define PR_REPORT_TEXT								PROP_TAG( PT_TSTRING,	0x1001)
#define PR_ORIGINATOR_AND_DL_EXPANSION_HISTORY		PROP_TAG( PT_BINARY,	0x1002)
#define PR_REPORTING_DL_NAME						PROP_TAG( PT_BINARY,	0x1003)
#define PR_REPORTING_MTA_CERTIFICATE				PROP_TAG( PT_BINARY,	0x1004)
#define PR_REPORT_ORIGIN_AUTHENTICATION_CHECK		PROP_TAG( PT_BINARY,	0x1005)
#define PR_AUTOFORWARD_COMMENT						PROP_TAG( PT_TSTRING,	0x1006)

//$ The following is a Toy Store/Toy Spooler property, not sure if it belongs. -SM
#define PR_IS_OUTGOING_MESSAGE						PROP_TAG( PT_BOOLEAN,	0x1007)


/*
 *	Message recipient properties
 */

#define PR_CONTENT_INTEGRITY_CHECK					PROP_TAG( PT_BINARY,	0x0C00)
#define PR_EXPLICIT_CONVERSION						PROP_TAG( PT_LONG,		0x0C01)
#define PR_IPM_RETURN_REQUESTED						PROP_TAG( PT_BOOLEAN,	0x0C02)
#define PR_MESSAGE_TOKEN							PROP_TAG( PT_BINARY,	0x0C03)
#define PR_NDR_REASON_CODE							PROP_TAG( PT_LONG,		0x0C04)
#define PR_NON_DELIVERY_DIAG_CODE					PROP_TAG( PT_LONG,		0x0C05)
#define PR_NON_RECEIPT_NOTIFICATION_REQUESTED		PROP_TAG( PT_BOOLEAN,	0x0C06)
#define PR_ORIGINALLY_INTENDED_RECIP				PROP_TAG( PT_BINARY,	0x0C07)
		// dups PR_ORIGINALLY_INTENDED_RECIPIENT_NAME?
#define PR_ORIGINATOR_NON_DELIVERY_REPORT_REQUESTED	PROP_TAG( PT_BOOLEAN,	0x0C08)
#define PR_ORIGINATOR_REQUESTED_ALTERNATE_RECIPIENT	PROP_TAG( PT_BINARY,	0x0C09)
#define PR_PHYSICAL_DELIVERY_BUREAU_FAX_DELIVERY	PROP_TAG( PT_BOOLEAN,	0x0C0A)
#define PR_PHYSICAL_DELIVERY_MODE					PROP_TAG( PT_LONG,		0x0C0B)
#define PR_PHYSICAL_DELIVERY_REPORT_REQUEST			PROP_TAG( PT_LONG,		0x0C0C)
#define PR_PHYSICAL_FORWARDING_ADDRESS				PROP_TAG( PT_BINARY,	0x0C0D)
#define PR_PHYSICAL_FORWARDING_ADDRESS_REQUESTED	PROP_TAG( PT_BOOLEAN,	0x0C0E)
#define PR_PHYSICAL_FORWARDING_PROHIBITED			PROP_TAG( PT_BOOLEAN,	0x0C0F)
#define PR_PHYSICAL_RENDITION_ATTRIBUTES			PROP_TAG( PT_BINARY,	0x0C10)
#define PR_PROOF_OF_DELIVERY						PROP_TAG( PT_BINARY,	0x0C11)
#define PR_PROOF_OF_DELIVERY_REQUESTED				PROP_TAG( PT_BOOLEAN,	0x0C12)
#define PR_RECIPIENT_CERTIFICATE					PROP_TAG( PT_BINARY,	0x0C13)
#define PR_RECIPIENT_NUMBER_FOR_ADVICE				PROP_TAG( PT_TSTRING,	0x0C14)
#define PR_RECIPIENT_TYPE							PROP_TAG( PT_LONG,		0x0C15)
#define PR_REGISTERED_MAIL_TYPE						PROP_TAG( PT_LONG,		0x0C16)
#define PR_REPLY_REQUESTED							PROP_TAG( PT_BOOLEAN,	0x0C17)
#define PR_REQUESTED_DELIVERY_METHOD				PROP_TAG( PT_BINARY,	0x0C18)
#define PR_SENDER_ENTRYID							PROP_TAG( PT_ENTRYID,	0x0C19)
#define PR_SENDER_NAME								PROP_TAG( PT_TSTRING,	0x0C1A)
#define PR_SUPPLEMENTARY_INFO						PROP_TAG( PT_TSTRING,	0x0C1B)	
#define PR_TYPE_OF_MTS_USER							PROP_TAG( PT_LONG,		0x0C1C)


/*
 *	Message non-transmittable properties
 */

#define PR_CAME_IN_AS								PROP_TAG( PT_BINARY,	0x0E00)
#define PR_DELETE_AFTER_SUBMIT						PROP_TAG( PT_BOOLEAN,	0x0E01)
#define PR_DISPLAY_BCC								PROP_TAG( PT_TSTRING,	0x0E02)
#define PR_DISPLAY_CC								PROP_TAG( PT_TSTRING,	0x0E03)
#define PR_DISPLAY_TO								PROP_TAG( PT_TSTRING,	0x0E04)
#define PR_GO_OUT_AS								PROP_TAG( PT_BINARY,	0x0E05)
#define PR_MESSAGE_DELIVERY_TIME					PROP_TAG( PT_SYSTIME,	0x0E06)
#define PR_MESSAGE_FLAGS							PROP_TAG( PT_LONG,		0x0E07)
#define PR_MESSAGE_SIZE								PROP_TAG( PT_LONG,		0x0E08)
#if defined(WINPAD) && !defined(ARADOR)
#define PR_PARENT_ENTRYID							PROP_TAG( PT_TV_ENTRYID,	0x0E09)
#else
#define PR_PARENT_ENTRYID							PROP_TAG( PT_ENTRYID,	0x0E09)
#endif
#define PR_SENTMAIL_ENTRYID							PROP_TAG( PT_ENTRYID,	0x0E0A)
#define PR_UPDATE_PAB								PROP_TAG( PT_BOOLEAN,	0x0E0B)
#define PR_CORRELATE								PROP_TAG( PT_BOOLEAN,	0x0E0C)
#define PR_CORRELATE_MTSID							PROP_TAG( PT_BINARY,	0x0E0D)
#define PR_DISCRETE_VALUES							PROP_TAG( PT_BOOLEAN,	0x0E0E)
#define PR_RESPONSIBILITY							PROP_TAG( PT_BOOLEAN,	0x0E0F)
#if defined(WINPAD) && !defined(ARADOR)
#define PR_PRIVATE									PROP_TAG( PT_BIT,	SOS_ID_BASE + 2)
#endif

/*
 * The following two tags are to be used in the exclude list passed to
 * IMessage::CopyTo when the caller wants either the recipients or attachments
 * of the message to not get copied.  It is also used in the ProblemArray
 * return from IMessage::CopyTo when an error is encountered copying them
 */

#define PR_MESSAGE_RECIPIENT_TABLE					PROP_TAG( PT_OBJECT,	0x0E0C)
#define PR_MESSAGE_ATTACHMENT_TABLE					PROP_TAG( PT_OBJECT,	0x0E0D)

/*
 * The range of non-message and non-recipient property IDs (0x3000 - 0x3FFF) is
 * further broken down into ranges to make assigning new property IDs easier.
 *
 *	From	To		Kind of property
 *	--------------------------------
 *	3000	33FF	MAPI_defined common property
 *	3400	35FF	MAPI_defined message store property
 *	3600	36FF	MAPI_defined Folder or AB Container property
 *	3700	38FF	MAPI_defined attachment property
 *	3900	39FF	MAPI_defined address book property
 *	3A00	3BFF	MAPI_defined mailuser property
 *	3C00	3CFF	MAPI_defined DistList property
 *	3D00	3DFF	MAPI_defined Profile Section property
 *	3E00	3EFF	MAPI_defined Status property
 *	3F00	3FFF	MAPI_defined display table property
 */

/*
 *	Properties common to numerous MAPI objects.
 *	
 *	Those properties that can appear on messages are in the
 *	non-transmittable range for messages. They start at the high
 *	end of that range and work down.
 *	
 *	Properties that never appear on messages are defined in the common
 *	property range (see above).
 */

/*
 * properties that are common to multiple objects (including message objects)
 */
 
#define PR_ENTRYID									PROP_TAG( PT_ENTRYID,	0x0FFF)
#if defined(WINPAD) && !defined(ARADOR)
#define PR_OBJECT_TYPE								PROP_TAG( PT_TV_LONG,		0x0FFE)
#else
#define PR_OBJECT_TYPE								PROP_TAG( PT_LONG,		0x0FFE)
#endif
#define PR_ICON										PROP_TAG( PT_BINARY,	0x0FFD)
#define PR_MINI_ICON								PROP_TAG( PT_BINARY,	0x0FFC)
#define PR_STORE_ENTRYID							PROP_TAG( PT_BINARY,	0x0FFB)
#define PR_STORE_COMPARISON_KEY						PROP_TAG( PT_BINARY,	0x0FFA)
#define PR_COMPARISON_KEY							PROP_TAG( PT_BINARY,	0x0FF9)
#if defined(WINPAD) && !defined(ARADOR)
#define PR_CHANGED									PROP_TAG( PT_BIT,	SOS_ID_BASE + 4)		
#endif

/*
 * properties that are common to multiple objects (NOT including message objects)
 */

#define PR_ROWID									PROP_TAG( PT_LONG,		0x3000)
#define PR_DISPLAY_NAME								PROP_TAG( PT_TSTRING,	0x3001)
#define PR_ADDRTYPE									PROP_TAG( PT_TSTRING,	0x3002)
#define PR_EMAIL_ADDRESS							PROP_TAG( PT_TSTRING,	0x3003)
#define PR_COMMENT									PROP_TAG( PT_TSTRING,	0x3004)
#define PR_DEPTH									PROP_TAG( PT_LONG,		0x3005)
#define PR_PROVIDER_DISPLAY							PROP_TAG( PT_TSTRING,	0x3006)
#define PR_RESOURCE_DISPLAY							PROP_TAG( PT_TSTRING,	0x3007)
#define PR_LAST_MODIFICATION_TIME					PROP_TAG( PT_SYSTIME,	0x3008)
#define PR_RESOURCE_FLAGS							PROP_TAG( PT_LONG,		0x3009)
#define PR_PROVIDER_DLL_NAME						PROP_TAG( PT_TSTRING,	0x300A)

/*
 *	Message store properties
 */

#define PR_DEFAULT_STORE							PROP_TAG( PT_BOOLEAN,	0x3400)
#define PR_ENTRYID_UNIQUE							PROP_TAG( PT_BOOLEAN,	0x3401)
#define PR_READONLY									PROP_TAG( PT_BOOLEAN,	0x3402)
#define PR_SEARCH_OK								PROP_TAG( PT_BOOLEAN,	0x3403)
#define PR_MODIFY_OK								PROP_TAG( PT_BOOLEAN,	0x3404)
#define PR_CREATE_OK								PROP_TAG( PT_BOOLEAN,	0x3405)
#define PR_ATTACH_OK								PROP_TAG( PT_BOOLEAN,	0x3406)
#define PR_OLE_OK									PROP_TAG( PT_BOOLEAN,	0x3407)
#define PR_SUBMIT_OK								PROP_TAG( PT_BOOLEAN,	0x3408)
#define PR_NOTIFY_OK								PROP_TAG( PT_BOOLEAN,	0x3409)
//$ The following are Toy Store properties, I'm not sure they belong here. -SM
#define PR_LOGON_ACCOUNT_NAME						PROP_TAG( PT_TSTRING,	0x340A )
#define PR_LOGON_ACCOUNT_PASSWORD					PROP_TAG( PT_TSTRING,	0x340B )
#define PR_FILENAME_SEQUENCE_NUMBER					PROP_TAG( PT_LONG,		0x340C )
//$ end of Toy Store properties
#define PR_CATEGORIZE_OK							PROP_TAG( PT_BOOLEAN,	0x340D)
#define PR_IPM_SUBTREE_ENTRYID						PROP_TAG( PT_BINARY,	0x340E)
#define PR_IPM_OUTBOX_ENTRYID						PROP_TAG( PT_BINARY,	0x340F)


/*
 *	Folder and AB Container properties
 */

#define PR_CONTAINER_FLAGS							PROP_TAG( PT_LONG,		0x3600)
#define PR_CONTAINER_TYPE							PROP_TAG( PT_LONG,		0x3601)
#if defined(WINPAD) && !defined(ARADOR)
#define PR_FOLDER_TYPE								PROP_TAG( PT_TV_LONG,		0x3601)
#else
#define PR_FOLDER_TYPE								PROP_TAG( PT_LONG,		0x3601)
#endif
#define PR_CONTENT_COUNT							PROP_TAG( PT_LONG,		0x3602)
#define PR_CONTENT_UNREAD							PROP_TAG( PT_LONG,		0x3603)
#define PR_CREATE_TEMPLATES							PROP_TAG( PT_OBJECT,	0x3604)
#define PR_DETAILS_TABLE							PROP_TAG( PT_OBJECT,	0x3605)
#define PR_ICONS									PROP_TAG( PT_OBJECT,	0x3606)
#define PR_SEARCH									PROP_TAG( PT_OBJECT,	0x3607)
#define PR_SEARCH_RESTRICTION						PROP_TAG( PT_BINARY,	0x3608)
#define PR_SELECTABLE								PROP_TAG( PT_BOOLEAN,	0x3609)
#define PR_SUBFOLDERS								PROP_TAG( PT_BOOLEAN,	0x360a)
#define PR_STATUS									PROP_TAG( PT_LONG,		0x360b)


/*
 *	Attachment properties
 */

#define PR_ATTACHMENT_X400_PARAMETERS				PROP_TAG( PT_BINARY,	0x3700)
#define PR_ATTACH_DATA_OBJ							PROP_TAG( PT_OBJECT,	0x3701)	
#define PR_ATTACH_DATA_BIN							PROP_TAG( PT_BINARY,	0x3701)	
#define PR_ATTACH_ENCODING							PROP_TAG( PT_BINARY,	0x3702)
#define PR_ATTACH_EXTENSION							PROP_TAG( PT_TSTRING,	0x3703)
#define PR_ATTACH_FILENAME							PROP_TAG( PT_TSTRING,	0x3704)
#define PR_ATTACH_METHOD							PROP_TAG( PT_LONG,		0x3705)
#define PR_ATTACH_NUM								PROP_TAG( PT_LONG,		0x3706)
#define PR_ATTACH_OBJECT_TYPE						PROP_TAG( PT_LONG,		0x3707)
#define PR_ATTACH_PATHNAME							PROP_TAG( PT_TSTRING,	0x3708)
#define PR_ATTACH_RENDERING							PROP_TAG( PT_BINARY,    0x3709)
#define PR_ATTACH_TAG								PROP_TAG( PT_BINARY,	0x370A)
#define PR_RENDERING_POSITION						PROP_TAG( PT_LONG,		0x370B)

/*
 *  AB Object properties
 */

#define PR_DISPLAY_TYPE								PROP_TAG( PT_LONG,		0x3900)
#define PR_DISPLAY_ICON								PROP_TAG( PT_LONG,		0x3901)

/*
 *	Mail user properties
 */

#define PR_ACCOUNT									PROP_TAG( PT_TSTRING,	0x3A00)
#define PR_ALTERNATE_RECIPIENT						PROP_TAG( PT_BINARY,	0x3A01)
#define PR_CALLBACK_TELEPHONE_NUMBER				PROP_TAG( PT_TSTRING,	0x3A02)
#define PR_CONVERSION_PROHIBITED					PROP_TAG( PT_BOOLEAN,	0x3A03)
#define PR_DISCLOSE_RECIPIENTS						PROP_TAG( PT_BOOLEAN,	0x3A04)
#define PR_GENERATION								PROP_TAG( PT_TSTRING,	0x3A05)
#define PR_GIVEN_NAME								PROP_TAG( PT_TSTRING,	0x3A06)
#define PR_GOVERNMENT_ID_NUMBER						PROP_TAG( PT_TSTRING,	0x3A07)
#define PR_HIDE_FROM_ADDRESS_BOOK					PROP_TAG( PT_BOOLEAN,	0x3A08)
#define PR_HOME_TELEPHONE_NUMBER					PROP_TAG( PT_TSTRING,	0x3A09)
#define PR_INITIALS									PROP_TAG( PT_TSTRING,	0x3A0A)
#define PR_KEYWORD									PROP_TAG( PT_TSTRING,	0x3A0B)
#define PR_LANGUAGE									PROP_TAG( PT_TSTRING,	0x3A0C)
#define PR_LOCATION									PROP_TAG( PT_TSTRING,	0x3A0D)
#define PR_MAIL_PERMISSION							PROP_TAG( PT_BOOLEAN,	0x3A0E)
#define PR_MHS_COMMON_NAME							PROP_TAG( PT_TSTRING,	0x3A0F)
#define PR_ORGANIZATIONAL_ID_NUMBER					PROP_TAG( PT_TSTRING,	0x3A10)
#define PR_SURNAME									PROP_TAG( PT_TSTRING,	0x3A11)


/*
 *	Profile section properties
 */

#define PR_STORE_PROVIDERS							PROP_TAG( PT_BINARY,	0x3D00)
#define PR_AB_PROVIDERS								PROP_TAG( PT_BINARY,	0x3D01)
#define PR_TRANSPORT_PROVIDERS						PROP_TAG( PT_BINARY,	0x3D02)
#define PR_PROFILE_NAMES							PROP_TAG( PT_TSTRING,	0x3D03)
#define PR_DEFAULT_PROFILE							PROP_TAG( PT_TSTRING,	0x3D04)
#define PR_RESOURCE_ENTRYID							PROP_TAG( PT_BINARY,	0x3D05)


/*
 *	Status object properties
 */

#define PR_IDENTITY_DISPLAY							PROP_TAG( PT_TSTRING,	0x3E00)
#define PR_IDENTITY_ENTRYID							PROP_TAG( PT_BINARY,	0x3E01)
#define PR_PROVIDER_ENTRYID							PROP_TAG( PT_BINARY,	0x3E02)
#define PR_RESOURCE_METHODS							PROP_TAG( PT_LONG,		0x3E03)
#define PR_RESOURCE_TYPE							PROP_TAG( PT_LONG,		0x3E04)
#define PR_STATUS_CODE								PROP_TAG( PT_LONG,		0x3E05)
#define PR_STATUS_DLL_NAME							PROP_TAG( PT_TSTRING,	0x3E06)
#define PR_STATUS_DLL_ORDINAL						PROP_TAG( PT_LONG, 	0x3E07)
#define PR_STATUS_SESSION							PROP_TAG( PT_LONG,		0x3E08)
#define PR_STATUS_STRING							PROP_TAG( PT_TSTRING,	0x3E09)
#define PR_X400_DEFERRED_DELIVERY_CANCEL			PROP_TAG( PT_BOOLEAN,	0x3E0A)

/*
 * Display table properties
 */


#define PR_CONTROL_FLAGS							PROP_TAG( PT_LONG,		0x3F00)
#define PR_CONTROL_STRUCTURE						PROP_TAG( PT_BINARY,	0x3F01)
#define PR_CONTROL_TYPE								PROP_TAG( PT_LONG,		0x3F02)
#define PR_DELTAX									PROP_TAG( PT_LONG,		0x3F03)
#define PR_DELTAY									PROP_TAG( PT_LONG,		0x3F04)
#define PR_XPOS										PROP_TAG( PT_LONG,		0x3F05)
#define PR_YPOS										PROP_TAG( PT_LONG,		0x3F06)
