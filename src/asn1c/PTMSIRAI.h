/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "HNBAP-IEs"
 * 	found in "../../asn1/hnbap/HNBAP-IEs.asn"
 * 	`asn1c -gen-PER`
 */

#ifndef	_PTMSIRAI_H_
#define	_PTMSIRAI_H_


#include <asn_application.h>

/* Including external dependencies */
#include "PTMSI.h"
#include "RAI.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* PTMSIRAI */
typedef struct PTMSIRAI {
	PTMSI_t	 pTMSI;
	RAI_t	 rAI;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} PTMSIRAI_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_PTMSIRAI;

#ifdef __cplusplus
}
#endif

#endif	/* _PTMSIRAI_H_ */
#include <asn_internal.h>
