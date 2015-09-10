/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "RANAP-IEs"
 * 	found in "../../asn1/ranap/RANAP-IEs.asn"
 */

#ifndef	_RANAP_ListOfInterfacesToTrace_H_
#define	_RANAP_ListOfInterfacesToTrace_H_


#include <asn_application.h>

/* Including external dependencies */
#include "RANAP_InterfacesToTraceItem.h"
#include <asn_SEQUENCE_OF.h>
#include <constr_SEQUENCE_OF.h>

#ifdef __cplusplus
extern "C" {
#endif

/* RANAP_ListOfInterfacesToTrace */
typedef struct RANAP_ListOfInterfacesToTrace {
	A_SEQUENCE_OF(RANAP_InterfacesToTraceItem_t) list;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} RANAP_ListOfInterfacesToTrace_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_RANAP_ListOfInterfacesToTrace;

#ifdef __cplusplus
}
#endif

#endif	/* _RANAP_ListOfInterfacesToTrace_H_ */
#include <asn_internal.h>