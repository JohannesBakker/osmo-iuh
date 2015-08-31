/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "HNBAP-IEs"
 * 	found in "../../asn1/hnbap/HNBAP-IEs.asn"
 * 	`asn1c -gen-PER`
 */

#include "NeighbourInfoRequestItem.h"

static asn_TYPE_member_t asn_MBR_NeighbourInfoRequestItem_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct NeighbourInfoRequestItem, hnb_RNL_Identity),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_HNB_RNL_Identity,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"hnb-RNL-Identity"
		},
	{ ATF_POINTER, 1, offsetof(struct NeighbourInfoRequestItem, iE_Extensions),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_IE_Extensions,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"iE-Extensions"
		},
};
static const int asn_MAP_NeighbourInfoRequestItem_oms_1[] = { 1 };
static const ber_tlv_tag_t asn_DEF_NeighbourInfoRequestItem_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_NeighbourInfoRequestItem_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* hnb-RNL-Identity */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* iE-Extensions */
};
static asn_SEQUENCE_specifics_t asn_SPC_NeighbourInfoRequestItem_specs_1 = {
	sizeof(struct NeighbourInfoRequestItem),
	offsetof(struct NeighbourInfoRequestItem, _asn_ctx),
	asn_MAP_NeighbourInfoRequestItem_tag2el_1,
	2,	/* Count of tags in the map */
	asn_MAP_NeighbourInfoRequestItem_oms_1,	/* Optional members */
	1, 0,	/* Root/Additions */
	1,	/* Start extensions */
	3	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_NeighbourInfoRequestItem = {
	"NeighbourInfoRequestItem",
	"NeighbourInfoRequestItem",
	SEQUENCE_free,
	SEQUENCE_print,
	SEQUENCE_constraint,
	SEQUENCE_decode_ber,
	SEQUENCE_encode_der,
	SEQUENCE_decode_xer,
	SEQUENCE_encode_xer,
	SEQUENCE_decode_uper,
	SEQUENCE_encode_uper,
	SEQUENCE_decode_aper,
	SEQUENCE_encode_aper,
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_NeighbourInfoRequestItem_tags_1,
	sizeof(asn_DEF_NeighbourInfoRequestItem_tags_1)
		/sizeof(asn_DEF_NeighbourInfoRequestItem_tags_1[0]), /* 1 */
	asn_DEF_NeighbourInfoRequestItem_tags_1,	/* Same as above */
	sizeof(asn_DEF_NeighbourInfoRequestItem_tags_1)
		/sizeof(asn_DEF_NeighbourInfoRequestItem_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_NeighbourInfoRequestItem_1,
	2,	/* Elements count */
	&asn_SPC_NeighbourInfoRequestItem_specs_1	/* Additional specs */
};

