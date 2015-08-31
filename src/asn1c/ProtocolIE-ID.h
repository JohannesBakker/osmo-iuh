/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "HNBAP-CommonDataTypes"
 * 	found in "../../asn1/hnbap/HNBAP-CommonDataTypes.asn"
 * 	`asn1c -gen-PER`
 */

#ifndef	_ProtocolIE_ID_H_
#define	_ProtocolIE_ID_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeInteger.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum ProtocolIE_ID {
	ProtocolIE_ID_id_Cause	= 1,
	ProtocolIE_ID_id_CriticalityDiagnostics	= 2,
	ProtocolIE_ID_id_HNB_Identity	= 3,
	ProtocolIE_ID_id_Context_ID	= 4,
	ProtocolIE_ID_id_UE_Identity	= 5,
	ProtocolIE_ID_id_LAC	= 6,
	ProtocolIE_ID_id_RAC	= 7,
	ProtocolIE_ID_id_HNB_Location_Information	= 8,
	ProtocolIE_ID_id_PLMNidentity	= 9,
	ProtocolIE_ID_id_SAC	= 10,
	ProtocolIE_ID_id_CellIdentity	= 11,
	ProtocolIE_ID_id_Registration_Cause	= 12,
	ProtocolIE_ID_id_UE_Capabilities	= 13,
	ProtocolIE_ID_id_RNC_ID	= 14,
	ProtocolIE_ID_id_CSG_ID	= 15,
	ProtocolIE_ID_id_BackoffTimer	= 16,
	ProtocolIE_ID_id_HNB_Internet_Information	= 17,
	ProtocolIE_ID_id_HNB_Cell_Access_Mode	= 18,
	ProtocolIE_ID_id_MuxPortNumber	= 19,
	ProtocolIE_ID_id_Service_Area_For_Broadcast	= 20,
	ProtocolIE_ID_id_CSGMembershipStatus	= 21,
	ProtocolIE_ID_id_RABList	= 22,
	ProtocolIE_ID_id_HNBConfigInfo	= 23,
	ProtocolIE_ID_id_AccessResult	= 25,
	ProtocolIE_ID_id_Update_cause	= 26,
	ProtocolIE_ID_id_NeighbourInfoList	= 27,
	ProtocolIE_ID_id_NeighbourInfoRequestList	= 28,
	ProtocolIE_ID_id_Iurh_Signalling_TNL_Address	= 29,
	ProtocolIE_ID_id_PSC	= 30,
	ProtocolIE_ID_id_HNB_Cell_Identifier	= 31,
	ProtocolIE_ID_id_Tunnel_Information	= 41,
	ProtocolIE_ID_id_CELL_FACHMobilitySupport	= 42,
	ProtocolIE_ID_id_S_RNTIPrefix	= 43,
	ProtocolIE_ID_id_URAIdentity	= 44,
	ProtocolIE_ID_id_NeighbourIdentity	= 45,
	ProtocolIE_ID_id_HNBCapacity	= 46,
	ProtocolIE_ID_id_NeighbourCellIdentityList	= 47,
	ProtocolIE_ID_id_AdditionalNeighbourInfoList	= 48,
	ProtocolIE_ID_id_U_RNTI	= 49,
	ProtocolIE_ID_id_UnknownU_RNTIIndication	= 50,
	ProtocolIE_ID_id_HNB_GWResponse	= 51,
	ProtocolIE_ID_id_URAIdentityList	= 52
} e_ProtocolIE_ID;

/* ProtocolIE-ID */
typedef long	 ProtocolIE_ID_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_ProtocolIE_ID;
asn_struct_free_f ProtocolIE_ID_free;
asn_struct_print_f ProtocolIE_ID_print;
asn_constr_check_f ProtocolIE_ID_constraint;
ber_type_decoder_f ProtocolIE_ID_decode_ber;
der_type_encoder_f ProtocolIE_ID_encode_der;
xer_type_decoder_f ProtocolIE_ID_decode_xer;
xer_type_encoder_f ProtocolIE_ID_encode_xer;
per_type_decoder_f ProtocolIE_ID_decode_uper;
per_type_encoder_f ProtocolIE_ID_encode_uper;
per_type_decoder_f ProtocolIE_ID_decode_aper;
per_type_encoder_f ProtocolIE_ID_encode_aper;

#ifdef __cplusplus
}
#endif

#endif	/* _ProtocolIE_ID_H_ */
#include <asn_internal.h>
