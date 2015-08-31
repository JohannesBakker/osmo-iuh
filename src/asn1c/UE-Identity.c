/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "HNBAP-IEs"
 * 	found in "../../asn1/hnbap/HNBAP-IEs.asn"
 * 	`asn1c -gen-PER`
 */

#include "UE-Identity.h"

static asn_per_constraints_t asn_PER_type_UE_Identity_constr_1 GCC_NOTUSED = {
	{ APC_CONSTRAINED | APC_EXTENSIBLE,  3,  3,  0l,  7l }	/* (0..7,...) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_TYPE_member_t asn_MBR_UE_Identity_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct UE_Identity, choice.iMSI),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_IMSI,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"iMSI"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct UE_Identity, choice.tMSILAI),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_TMSILAI,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"tMSILAI"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct UE_Identity, choice.pTMSIRAI),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_PTMSIRAI,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"pTMSIRAI"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct UE_Identity, choice.iMEI),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_IMEI,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"iMEI"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct UE_Identity, choice.eSN),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ESN,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"eSN"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct UE_Identity, choice.iMSIDS41),
		(ASN_TAG_CLASS_CONTEXT | (5 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_IMSIDS41,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"iMSIDS41"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct UE_Identity, choice.iMSIESN),
		(ASN_TAG_CLASS_CONTEXT | (6 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_IMSIESN,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"iMSIESN"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct UE_Identity, choice.tMSIDS41),
		(ASN_TAG_CLASS_CONTEXT | (7 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_TMSIDS41,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"tMSIDS41"
		},
};
static const asn_TYPE_tag2member_t asn_MAP_UE_Identity_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* iMSI */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* tMSILAI */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* pTMSIRAI */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 }, /* iMEI */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 4, 0, 0 }, /* eSN */
    { (ASN_TAG_CLASS_CONTEXT | (5 << 2)), 5, 0, 0 }, /* iMSIDS41 */
    { (ASN_TAG_CLASS_CONTEXT | (6 << 2)), 6, 0, 0 }, /* iMSIESN */
    { (ASN_TAG_CLASS_CONTEXT | (7 << 2)), 7, 0, 0 } /* tMSIDS41 */
};
static asn_CHOICE_specifics_t asn_SPC_UE_Identity_specs_1 = {
	sizeof(struct UE_Identity),
	offsetof(struct UE_Identity, _asn_ctx),
	offsetof(struct UE_Identity, present),
	sizeof(((struct UE_Identity *)0)->present),
	asn_MAP_UE_Identity_tag2el_1,
	8,	/* Count of tags in the map */
	0,
	8	/* Extensions start */
};
asn_TYPE_descriptor_t asn_DEF_UE_Identity = {
	"UE-Identity",
	"UE-Identity",
	CHOICE_free,
	CHOICE_print,
	CHOICE_constraint,
	CHOICE_decode_ber,
	CHOICE_encode_der,
	CHOICE_decode_xer,
	CHOICE_encode_xer,
	CHOICE_decode_uper,
	CHOICE_encode_uper,
	CHOICE_decode_aper,
	CHOICE_encode_aper,
	CHOICE_outmost_tag,
	0,	/* No effective tags (pointer) */
	0,	/* No effective tags (count) */
	0,	/* No tags (pointer) */
	0,	/* No tags (count) */
	&asn_PER_type_UE_Identity_constr_1,
	asn_MBR_UE_Identity_1,
	8,	/* Elements count */
	&asn_SPC_UE_Identity_specs_1	/* Additional specs */
};

