/* Test HNB */

/* (C) 2015 by Daniel Willmann <dwillmann@sysmocom.de>
 * (C) 2015 by Sysmocom s.f.m.c. GmbH
 * All Rights Reserved
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <errno.h>
#include <signal.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/sctp.h>
#include <arpa/inet.h>

#include <osmocom/core/application.h>
#include <osmocom/core/talloc.h>
#include <osmocom/core/select.h>
#include <osmocom/core/logging.h>
#include <osmocom/core/socket.h>
#include <osmocom/core/msgb.h>
#include <osmocom/core/write_queue.h>
#include <osmocom/netif/stream.h>

#include <osmocom/vty/telnet_interface.h>
#include <osmocom/vty/logging.h>
#include <osmocom/vty/command.h>

#include "hnb-test.h"
#include "hnbap_common.h"
#include "hnbap_ies_defs.h"
#include "rua_helper.h"
#include "asn1helpers.h"
#include "iu_helpers.h"

#include "ranap_msg_factory.h"

static void *tall_hnb_ctx;
void *talloc_asn1_ctx;

struct hnb_test g_hnb_test = {
	.gw_port = IUH_DEFAULT_SCTP_PORT,
};

struct msgb *rua_new_udt(struct msgb *inmsg);


static int hnb_test_ue_de_register_tx(struct hnb_test *hnb_test)
{
	struct msgb *msg;
	int rc, imsi_len;
	uint32_t ctx_id;

	UEDe_Register_t dereg;
	UEDe_RegisterIEs_t dereg_ies;
	memset(&dereg_ies, 0, sizeof(dereg_ies));

	asn1_u24_to_bitstring(&dereg_ies.context_ID, &ctx_id, hnb_test->ctx_id);
	dereg_ies.cause.present = Cause_PR_radioNetwork;
	dereg_ies.cause.choice.radioNetwork = CauseRadioNetwork_connection_with_UE_lost;

	memset(&dereg, 0, sizeof(dereg));
	rc = hnbap_encode_uede_registeries(&dereg, &dereg_ies);

	msg = hnbap_generate_initiating_message(ProcedureCode_id_UEDe_Register,
						Criticality_ignore,
						&asn_DEF_UEDe_Register,
						&dereg);

	ASN_STRUCT_FREE_CONTENTS_ONLY(asn_DEF_UEDe_Register, &dereg);

	msgb_sctp_ppid(msg) = IUH_PPI_HNBAP;

	return osmo_wqueue_enqueue(&hnb_test->wqueue, msg);
}

static int hnb_test_ue_register_tx(struct hnb_test *hnb_test, const char *imsi_str)
{
	struct msgb *msg;
	int rc, imsi_len;

	char imsi_buf[16];

	UERegisterRequest_t request_out;
	UERegisterRequestIEs_t request;
	memset(&request, 0, sizeof(request));

	request.uE_Identity.present = UE_Identity_PR_iMSI;

	imsi_len = encode_iu_imsi(imsi_buf, sizeof(imsi_buf), imsi_str);
	OCTET_STRING_fromBuf(&request.uE_Identity.choice.iMSI, imsi_buf, imsi_len);

	request.registration_Cause = Registration_Cause_normal;
	request.uE_Capabilities.access_stratum_release_indicator = Access_stratum_release_indicator_rel_6;
	request.uE_Capabilities.csg_capability = CSG_Capability_not_csg_capable;

	memset(&request_out, 0, sizeof(request_out));
	rc = hnbap_encode_ueregisterrequesties(&request_out, &request);

	msg = hnbap_generate_initiating_message(ProcedureCode_id_UERegister,
						Criticality_reject,
						&asn_DEF_UERegisterRequest,
						&request_out);

	ASN_STRUCT_FREE_CONTENTS_ONLY(asn_DEF_UERegisterRequest, &request_out);

	msgb_sctp_ppid(msg) = IUH_PPI_HNBAP;

	return osmo_wqueue_enqueue(&hnb_test->wqueue, msg);
}

static int hnb_test_rx_hnb_register_acc(struct hnb_test *hnb, ANY_t *in)
{
	int rc;
	HNBRegisterAcceptIEs_t accept;

	rc = hnbap_decode_hnbregisteraccepties(&accept, in);
	if (rc < 0) {
	}

	hnb->rnc_id = accept.rnc_id;
	printf("HNB Register accept with RNC ID %u\n", hnb->rnc_id);

	return 0;
}

static int hnb_test_rx_ue_register_acc(struct hnb_test *hnb, ANY_t *in)
{
	int rc;
	uint32_t ctx_id;
	UERegisterAcceptIEs_t accept;
	char imsi[16];

	rc = hnbap_decode_ueregisteraccepties(&accept, in);
	if (rc < 0) {
		return rc;
	}

	if (accept.uE_Identity.present != UE_Identity_PR_iMSI) {
		printf("Wrong type in UE register accept\n");
		return -1;
	}

	ctx_id = asn1bitstr_to_u24(&accept.context_ID);

	decode_iu_bcd(imsi, sizeof(imsi), accept.uE_Identity.choice.iMSI.buf,
			accept.uE_Identity.choice.iMSI.size);
	printf("UE Register accept for IMSI %s, context %u\n", imsi, ctx_id);

	hnb->ctx_id = ctx_id;

	return 0;
}

int hnb_test_hnbap_rx(struct hnb_test *hnb, struct msgb *msg)
{
	HNBAP_PDU_t _pdu, *pdu = &_pdu;
	asn_dec_rval_t dec_ret;
	int rc;

	memset(pdu, 0, sizeof(*pdu));
	dec_ret = aper_decode(NULL, &asn_DEF_HNBAP_PDU, (void **) &pdu,
			      msg->data, msgb_length(msg), 0, 0);
	if (dec_ret.code != RC_OK) {
		LOGP(DMAIN, LOGL_ERROR, "Error in ASN.1 decode\n");
		return rc;
	}

	if (pdu->present != HNBAP_PDU_PR_successfulOutcome) {
		printf("Unexpected HNBAP message received\n");
	}

	switch (pdu->choice.successfulOutcome.procedureCode) {
	case ProcedureCode_id_HNBRegister:
		/* Get HNB id and send UE Register request */
		rc = hnb_test_rx_hnb_register_acc(hnb, &pdu->choice.successfulOutcome.value);
		break;
	case ProcedureCode_id_UERegister:
		rc = hnb_test_rx_ue_register_acc(hnb, &pdu->choice.successfulOutcome.value);
		break;
	default:
		break;
	}

	return rc;
}

static int hnb_read_cb(struct osmo_fd *fd)
{
	struct hnb_test *hnb_test = fd->data;
	struct sctp_sndrcvinfo sinfo;
	struct msgb *msg = msgb_alloc(IUH_MSGB_SIZE, "Iuh rx");
	int flags = 0;
	int rc;

	if (!msg)
		return -ENOMEM;

	rc = sctp_recvmsg(fd->fd, msgb_data(msg), msgb_tailroom(msg),
			  NULL, NULL, &sinfo, &flags);
	if (rc < 0) {
		LOGP(DMAIN, LOGL_ERROR, "Error during sctp_recvmsg()\n");
		/* FIXME: clean up after disappeared HNB */
		close(fd->fd);
		osmo_fd_unregister(fd);
		return rc;
	} else if (rc == 0) {
		LOGP(DMAIN, LOGL_INFO, "Connection to HNB closed\n");
		close(fd->fd);
		osmo_fd_unregister(fd);
		fd->fd = -1;

		return -1;
	} else {
		msgb_put(msg, rc);
	}

	if (flags & MSG_NOTIFICATION) {
		LOGP(DMAIN, LOGL_DEBUG, "Ignoring SCTP notification\n");
		msgb_free(msg);
		return 0;
	}

	sinfo.sinfo_ppid = ntohl(sinfo.sinfo_ppid);

	switch (sinfo.sinfo_ppid) {
	case IUH_PPI_HNBAP:
		printf("HNBAP mesage received\n");
		rc = hnb_test_hnbap_rx(hnb_test, msg);
		break;
	case IUH_PPI_RUA:
		printf("RUA mesage received\n");
//		rc = hnbgw_rua_rx(hnb, msg);
		break;
	case IUH_PPI_SABP:
	case IUH_PPI_RNA:
	case IUH_PPI_PUA:
		LOGP(DMAIN, LOGL_ERROR, "Unimplemented SCTP PPID=%u received\n",
		     sinfo.sinfo_ppid);
		rc = 0;
		break;
	default:
		LOGP(DMAIN, LOGL_ERROR, "Unknown SCTP PPID=%u received\n",
		     sinfo.sinfo_ppid);
		rc = 0;
		break;
	}

	msgb_free(msg);
	return rc;
}

static int hnb_write_cb(struct osmo_fd *fd, struct msgb *msg)
{
	struct hnb_test *ctx = fd->data;
	struct sctp_sndrcvinfo sinfo = {
		.sinfo_ppid = htonl(msgb_sctp_ppid(msg)),
		.sinfo_stream = 0,
	};
	int rc;

	rc = sctp_send(fd->fd, msgb_data(msg), msgb_length(msg),
			&sinfo, 0);
	/* we don't need to msgb_free(), write_queue does this for us */
	return rc;
}

static void hnb_send_register_req(struct hnb_test *hnb_test)
{
	HNBRegisterRequest_t request_out;
	struct msgb *msg;
	int rc;
	uint16_t lac, sac;
	uint8_t rac;
	uint32_t cid;
	uint8_t plmn[] = {0x09, 0xf1, 0x99};
	char identity[50] = "ATestHNB@";

	HNBRegisterRequestIEs_t request;
	memset(&request, 0, sizeof(request));

	lac = 0xc0fe;
	sac = 0xabab;
	rac = 0x42;
	cid = 0xadceaab;

	asn1_u16_to_str(&request.lac, &lac, lac);
	asn1_u16_to_str(&request.sac, &sac, sac);
	asn1_u8_to_str(&request.rac, &rac, rac);
	asn1_u28_to_bitstring(&request.cellIdentity, &cid, cid);

	request.hnB_Identity.hNB_Identity_Info.buf = identity;
	request.hnB_Identity.hNB_Identity_Info.size = strlen(identity);

	request.plmNidentity.buf = plmn;
	request.plmNidentity.size = 3;



	memset(&request_out, 0, sizeof(request_out));
	rc = hnbap_encode_hnbregisterrequesties(&request_out, &request);
	if (rc < 0) {
		printf("Could not encode HNB register request IEs\n");
	}

	msg = hnbap_generate_initiating_message(ProcedureCode_id_HNBRegister,
						Criticality_reject,
						&asn_DEF_HNBRegisterRequest,
						&request_out);


	msgb_sctp_ppid(msg) = IUH_PPI_HNBAP;

	osmo_wqueue_enqueue(&hnb_test->wqueue, msg);
}

static void hnb_send_deregister_req(struct hnb_test *hnb_test)
{
	struct msgb *msg;
	int rc;

	HNBDe_RegisterIEs_t request;
	memset(&request, 0, sizeof(request));

	request.cause.present = Cause_PR_misc;
	request.cause.choice.misc = CauseMisc_o_and_m_intervention;

	HNBDe_Register_t request_out;
	memset(&request_out, 0, sizeof(request_out));
	rc = hnbap_encode_hnbde_registeries(&request_out, &request);
	if (rc < 0) {
		printf("Could not encode HNB deregister request IEs\n");
	}

	msg = hnbap_generate_initiating_message(ProcedureCode_id_HNBDe_Register,
						Criticality_reject,
						&asn_DEF_HNBDe_Register,
						&request_out);

	msgb_sctp_ppid(msg) = IUH_PPI_HNBAP;

	osmo_wqueue_enqueue(&hnb_test->wqueue, msg);
}


static const struct log_info_cat log_cat[] = {
	[DMAIN] = {
		.name = "DMAIN", .loglevel = LOGL_INFO, .enabled = 1,
		.color = "",
		.description = "Main program",
	},
	[DHNBAP] = {
		.name = "DHNBAP", .loglevel = LOGL_DEBUG, .enabled = 1,
		.color = "",
		.description = "Home Node B Application Part",
	},
};

static const struct log_info hnb_test_log_info = {
	.cat = log_cat,
	.num_cat = ARRAY_SIZE(log_cat),
};

static struct vty_app_info vty_info = {
	.name		= "OsmoHNB-Test",
	.version	= "0",
};

static int sctp_sock_init(int fd)
{
	struct sctp_event_subscribe event;
	int rc;

	/* subscribe for all events */
	memset((uint8_t *)&event, 1, sizeof(event));
	rc = setsockopt(fd, IPPROTO_SCTP, SCTP_EVENTS,
			&event, sizeof(event));

	return rc;
}

#define HNBAP_STR	"HNBAP related commands\n"
#define HNB_STR		"HomeNodeB commands\n"
#define UE_STR		"User Equipment commands\n"
#define RANAP_STR	"RANAP related commands\n"
#define CSPS_STR	"Circuit Switched\n" "Packet Switched\n"

DEFUN(hnb_register, hnb_register_cmd,
	"hnbap hnb register", HNBAP_STR HNB_STR "Send HNB-REGISTER REQUEST")
{
	hnb_send_register_req(&g_hnb_test);

	return CMD_SUCCESS;
}

DEFUN(hnb_deregister, hnb_deregister_cmd,
	"hnbap hnb deregister", HNBAP_STR HNB_STR "Send HNB-DEREGISTER REQUEST")
{
	hnb_send_deregister_req(&g_hnb_test);

	return CMD_SUCCESS;
}

DEFUN(ue_register, ue_register_cmd,
	"hnbap ue register IMSI", HNBAP_STR UE_STR "Send UE-REGISTER REQUEST")
{
	hnb_test_ue_register_tx(&g_hnb_test, argv[0]);

	return CMD_SUCCESS;
}

DEFUN(asn_dbg, asn_dbg_cmd,
	"asn-debug (1|0)", "Enable or disabel libasn1c debugging")
{
	asn_debug = atoi(argv[0]);

	return CMD_SUCCESS;
}

DEFUN(ranap_reset, ranap_reset_cmd,
	"ranap reset (cs|ps)", RANAP_STR "Send RANAP RESET\n" CSPS_STR)
{
	int is_ps = 0;
	struct msgb *msg, *rua;

	RANAP_Cause_t cause = {
		.present = RANAP_Cause_PR_transmissionNetwork,
		.choice.transmissionNetwork = RANAP_CauseTransmissionNetwork_signalling_transport_resource_failure,
	};

	if (!strcmp(argv[0], "ps"))
		is_ps = 1;

	msg = ranap_new_msg_reset(is_ps, &cause);
	rua = rua_new_udt(msg);
	//msgb_free(msg);
	osmo_wqueue_enqueue(&g_hnb_test.wqueue, rua);

	return CMD_SUCCESS;
}


enum my_vty_nodes {
	CHAN_NODE = _LAST_OSMOVTY_NODE,
};

static struct cmd_node chan_node = {
	CHAN_NODE,
	"%s(chan)> ",
	1,
};


struct hnbtest_chan {
	int is_ps;
	uint32_t conn_id;
	char *imsi;
};

static struct msgb *gen_initue_lu(int is_ps, uint32_t conn_id, const char *imsi)
{
	uint8_t lu[] = { 0x05, 0x08, 0x70, 0x62, 0xf2, 0x30, 0xff, 0xf3, 0x57,
		/*	 len-  IMSI------------------------------------------ */
			 0x08, 0x29, 0x26, 0x24, 0x10, 0x32, 0x54, 0x76, 0x98,
			 0x33, 0x03, 0x57, 0x18 , 0xb2 };
	uint8_t plmn_id[] = { 0x09, 0x01, 0x99 };
	RANAP_GlobalRNC_ID_t rnc_id = {
		.rNC_ID = 23,
		.pLMNidentity.buf = plmn_id,
		.pLMNidentity.size = sizeof(plmn_id),
	};
	struct msgb *msg;

	/* FIXME: patch imsi */

	return ranap_new_msg_initial_ue(is_ps, conn_id, &rnc_id, lu, sizeof(lu));
}

DEFUN(chan, chan_cmd,
	"channel (cs|ps) lu imsi IMSI",
	"Open a new Signalling Connection\n"
	"To Circuit-Switched CN\n"
	"To Packet-Switched CN\n"
	"Performing a Location Update\n"
	)
{
	struct hnbtest_chan *chan;
	struct msgb *msg, *rua;

	chan = talloc_zero(tall_hnb_ctx, struct hnbtest_chan);
	if (!strcmp(argv[0], "ps"))
		chan->is_ps = 1;
	chan->imsi = talloc_strdup(chan, argv[1]);
	chan->conn_id = 42;

	msg = gen_initue_lu(chan->is_ps, chan->conn_id, chan->imsi);
	rua = rua_new_conn(chan->is_ps, chan->conn_id, msg);

	osmo_wqueue_enqueue(&g_hnb_test.wqueue, rua);

	vty->index = chan;
	vty->node = CHAN_NODE;

	return CMD_SUCCESS;
}

static void hnbtest_vty_init(void)
{
	install_element_ve(&asn_dbg_cmd);
	install_element_ve(&hnb_register_cmd);
	install_element_ve(&hnb_deregister_cmd);
	install_element_ve(&ue_register_cmd);
	install_element_ve(&ranap_reset_cmd);
	install_element_ve(&chan_cmd);

	install_node(&chan_node, NULL);
	vty_install_default(CHAN_NODE);
}

static void handle_options(int argc, char **argv)
{
	while (1) {
		int idx = 0, c;
		static const struct option long_options[] = {
			{ "ues", 1, 0, 'u' },
			{ 0, 0, 0, 0 },
		};

		c = getopt_long(argc, argv, "u:", long_options, &idx);

		if (c == -1)
			break;

		switch (c) {
		case 'u':
			g_hnb_test.ues = atoi(optarg);
			break;
		}
	}
}

int main(int argc, char **argv)
{
	int rc;

	tall_hnb_ctx = talloc_named_const(NULL, 0, "hnb_context");
	talloc_asn1_ctx = talloc_named_const(NULL, 0, "asn1_context");

	rc = osmo_init_logging(&hnb_test_log_info);
	if (rc < 0)
		exit(1);

	vty_init(&vty_info);
	hnbtest_vty_init();

	rc = telnet_init(NULL, NULL, 2324);
	if (rc < 0) {
		perror("Error binding VTY port");
		exit(1);
	}

	handle_options(argc, argv);

	osmo_wqueue_init(&g_hnb_test.wqueue, 16);
	g_hnb_test.wqueue.bfd.data = &g_hnb_test;
	g_hnb_test.wqueue.read_cb = hnb_read_cb;
	g_hnb_test.wqueue.write_cb = hnb_write_cb;

	rc = osmo_sock_init_ofd(&g_hnb_test.wqueue.bfd, AF_INET, SOCK_STREAM,
			   IPPROTO_SCTP, "127.0.0.1",
			   g_hnb_test.gw_port, OSMO_SOCK_F_CONNECT);
	if (rc < 0) {
		perror("Error connecting to Iuh port");
		exit(1);
	}
	sctp_sock_init(g_hnb_test.wqueue.bfd.fd);

#if 0
	/* some hard-coded message generation.  Doesn't make sense from
	 * a protocol point of view but enables to look at the encoded
	 * results in wireshark for manual verification */
	{
		struct msgb *msg, *rua;
		const uint8_t nas[] = { 0, 1, 2, 3 };
		const uint8_t ik[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };

		msg = ranap_new_msg_dt(0, nas, sizeof(nas));
		rua = rua_new_udt(msg);
		osmo_wqueue_enqueue(&g_hnb_test.wqueue, rua);

		msg = ranap_new_msg_sec_mod_cmd(ik, ik);
		rua = rua_new_udt(msg);
		osmo_wqueue_enqueue(&g_hnb_test.wqueue, rua);

		msg = ranap_new_msg_iu_rel_cmd()
		rua = rua_new_udt(msg);
		osmo_wqueue_enqueue(&g_hnb_test.wqueue, rua);

		msg = ranap_new_msg_paging_cmd("901990123456789", NULL, 0, 0);
		rua = rua_new_udt(msg);
		osmo_wqueue_enqueue(&g_hnb_test.wqueue, rua);

		msg = ranap_new_msg_rab_assign_voice(1, 0x01020304, 0x1020);
		rua = rua_new_udt(msg);
		osmo_wqueue_enqueue(&g_hnb_test.wqueue, rua);

		msg = ranap_new_msg_rab_assign_data(2, 0x01020304, 0x11223344);
		rua = rua_new_udt(msg);
		osmo_wqueue_enqueue(&g_hnb_test.wqueue, rua);
	}
#endif

	while (1) {
		rc = osmo_select_main(0);
		if (rc < 0)
			exit(3);
	}

	/* not reached */
	exit(0);
}
