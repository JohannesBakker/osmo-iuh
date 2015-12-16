/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "RANAP-IEs"
 * 	found in "../../asn1/ranap/RANAP-IEs.asn"
 */

#ifndef	_RANAP_MessageStructure_H_
#define	_RANAP_MessageStructure_H_


#include <asn_application.h>

/* Including external dependencies */
#include <asn_SEQUENCE_OF.h>
#include "RANAP_ProtocolIE-ID.h"
#include "RANAP_RepetitionNumber1.h"
#include "RANAP_IE-Extensions.h"
#include <constr_SEQUENCE.h>
#include <constr_SEQUENCE_OF.h>

#ifdef __cplusplus
extern "C" {
#endif

/* RANAP_MessageStructure */
typedef struct RANAP_MessageStructure {
	A_SEQUENCE_OF(struct MemberL {
		RANAP_ProtocolIE_ID_t	 iE_ID;
		RANAP_RepetitionNumber1_t	*repetitionNumber	/* OPTIONAL */;
		RANAP_IE_Extensions_t	*iE_Extensions	/* OPTIONAL */;
		/*
		 * This type is extensible,
		 * possible extensions are below.
		 */
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} ) list;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} RANAP_MessageStructure_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_RANAP_MessageStructure;

#ifdef __cplusplus
}
#endif

#endif	/* _RANAP_MessageStructure_H_ */
#include <asn_internal.h>
