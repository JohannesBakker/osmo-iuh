/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "HNBAP-IEs"
 * 	found in "../../asn1/hnbap/HNBAP-IEs.asn"
 * 	`asn1c -gen-PER`
 */

#ifndef	_NeighbourCellIdentityList_H_
#define	_NeighbourCellIdentityList_H_


#include <asn_application.h>

/* Including external dependencies */
#include <asn_SEQUENCE_OF.h>
#include <constr_SEQUENCE_OF.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct NeighbourIdentity;

/* NeighbourCellIdentityList */
typedef struct NeighbourCellIdentityList {
	A_SEQUENCE_OF(struct NeighbourIdentity) list;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} NeighbourCellIdentityList_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_NeighbourCellIdentityList;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "NeighbourIdentity.h"

#endif	/* _NeighbourCellIdentityList_H_ */
#include <asn_internal.h>
