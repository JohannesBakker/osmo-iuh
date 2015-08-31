/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "HNBAP-IEs"
 * 	found in "../../asn1/hnbap/HNBAP-IEs.asn"
 * 	`asn1c -gen-PER`
 */

#ifndef	_ESN_H_
#define	_ESN_H_


#include <asn_application.h>

/* Including external dependencies */
#include <BIT_STRING.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ESN */
typedef BIT_STRING_t	 ESN_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_ESN;
asn_struct_free_f ESN_free;
asn_struct_print_f ESN_print;
asn_constr_check_f ESN_constraint;
ber_type_decoder_f ESN_decode_ber;
der_type_encoder_f ESN_encode_der;
xer_type_decoder_f ESN_decode_xer;
xer_type_encoder_f ESN_encode_xer;
per_type_decoder_f ESN_decode_uper;
per_type_encoder_f ESN_encode_uper;
per_type_decoder_f ESN_decode_aper;
per_type_encoder_f ESN_encode_aper;

#ifdef __cplusplus
}
#endif

#endif	/* _ESN_H_ */
#include <asn_internal.h>
