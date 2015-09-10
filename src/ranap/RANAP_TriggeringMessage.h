/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "RANAP-CommonDataTypes"
 * 	found in "../../asn1/ranap/RANAP-CommonDataTypes.asn"
 */

#ifndef	_RANAP_TriggeringMessage_H_
#define	_RANAP_TriggeringMessage_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum RANAP_TriggeringMessage {
	RANAP_TriggeringMessage_initiating_message	= 0,
	RANAP_TriggeringMessage_successful_outcome	= 1,
	RANAP_TriggeringMessage_unsuccessfull_outcome	= 2,
	RANAP_TriggeringMessage_outcome	= 3
} e_RANAP_TriggeringMessage;

/* RANAP_TriggeringMessage */
typedef long	 RANAP_TriggeringMessage_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_RANAP_TriggeringMessage;
asn_struct_free_f RANAP_TriggeringMessage_free;
asn_struct_print_f RANAP_TriggeringMessage_print;
asn_constr_check_f RANAP_TriggeringMessage_constraint;
ber_type_decoder_f RANAP_TriggeringMessage_decode_ber;
der_type_encoder_f RANAP_TriggeringMessage_encode_der;
xer_type_decoder_f RANAP_TriggeringMessage_decode_xer;
xer_type_encoder_f RANAP_TriggeringMessage_encode_xer;
per_type_decoder_f RANAP_TriggeringMessage_decode_uper;
per_type_encoder_f RANAP_TriggeringMessage_encode_uper;
per_type_decoder_f RANAP_TriggeringMessage_decode_aper;
per_type_encoder_f RANAP_TriggeringMessage_encode_aper;

#ifdef __cplusplus
}
#endif

#endif	/* _RANAP_TriggeringMessage_H_ */
#include <asn_internal.h>