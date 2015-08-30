#pragma once

#include <osmocom/core/select.h>
#include <osmocom/core/linuxlist.h>

#define DEBUG
#include <osmocom/core/logging.h>

enum {
	DMAIN,
};


/* 25.467 Section 7.1 */
#define IUH_DEFAULT_SCTP_PORT	29169
#define RNA_DEFAULT_SCTP_PORT	25471

#define IUH_PPI_RUA		19
#define IUH_PPI_HNBAP		20
#define IUH_PPI_SABP		31
#define IUH_PPI_RNA		42
#define IUH_PPI_PUA		55

#define IUH_MSGB_SIZE	2048

struct umts_cell_id {
	uint16_t mcc;	/*!< Mobile Country Code */
	uint16_t mnc;	/*!< Mobile Network Code */
	uint16_t lac;	/*!< Locaton Area Code */
	uint16_t rac;	/*!< Routing Area Code */
	uint16_t sac;	/*!< Service Area Code */
	uint32_t cid;	/*!< Cell ID */
};

struct hnb_gw;

struct hnb_context {
	/*! Entry in HNB-global list of HNB */
	struct llist_head list;
	/*! HNB-GW we are part of */
	struct hnb_gw *gw;
	/*! SCTP socket for Iuh to this specific HNB */
	struct osmo_fd socket;
	/*! copied from HNB-Identity-Info IE */
	char identity_info[256];
	/*! copied from Cell Identity IE */
	struct umts_cell_id id;
};

struct ue_context {
	/*! Entry in the HNB-global list of UE */
	struct llist_head list;
	/*! Unique Context ID for this UE */
	uint32_t context_id;
	/*! UE is serviced via this HNB */
	struct hnb_context *hnb;
};

struct hnb_gw {
	struct {
		/*! SCTP port for Iuh listening */
		uint16_t iuh_listen_port;
		/*! The UDP port where we receive multiplexed CS user
		 * plane traffic from HNBs */
		uint16_t iuh_cs_mux_port;
		uint16_t rnc_id;
	} config;
	/*! SCTP listen socket for incoming connections */
	struct osmo_fd listen_fd;
	struct llist_head hnb_list;
};

extern struct hnb_gw g_hnb_gw;