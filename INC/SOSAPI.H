/*****************************************************************************
*
* sosapi.h -  Include this file to get all the public definitions associated
*             with the small object store.
*
*               Version 1.0
*
*               Copyright (c) 1993, Microsoft Corp. All rights reserved.
*
******************************************************************************
*
*
\****************************************************************************/

#ifndef SOSAPI_H
#define SOSAPI_H 1

#define WINPAD 1
#define MAPIAPI CDECL _loadds __export
#define MAPIMETHOD CDECL _loadds
typedef LPSTR	LPTSTR;

#include "oletype.h"
#include "mapidefs.h"
#include "mapicode.h"
#include "property.h"
#include "table.h"
#include "mapicomm.h"
#include "mapi.h"
#include "mapix.h"
#include "proptags.h"

// Object store Error codes
#define SOS_ERROR_BASE	0xC1230000
#define SOS_E_FILE_OPEN_FAILED	SOS_ERROR_BASE 


#ifdef __cplusplus
// This is a smart pointer to a SOS managed memory object
#define DEFMAPIPTR(x) \
class FAR MAPIPTR##x								   \
{					                                   \
public:                                                \
	x FAR *	p;		                                   \
	MAPIPTR##x() {p = NULL;};				           \
	MAPIPTR##x(x FAR * px) {p = px;};				   \
	~MAPIPTR##x() {if(p) MAPIFreeBuffer(p);};	       \
	x FAR * operator ->() {return p;};	               \
	x FAR * FAR * operator &() {return &p;};           \
}                                                      
#endif

#endif // SOSAPI_H
