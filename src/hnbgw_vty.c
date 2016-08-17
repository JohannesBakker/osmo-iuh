/* HNB-GW interface to quagga VTY */

/* (C) 2016 by sysmocom s.f.m.c. GmbH <info@sysmocom.de>
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

#include <osmocom/vty/command.h>

#include "hnbgw.h"
#include "context_map.h"

static void *tall_hnb_ctx = NULL;
static struct hnb_gw *g_hnb_gw = NULL;

static void vty_dump_hnb_info(struct vty *vty, struct hnb_context *hnb)
{
	struct hnbgw_context_map *map;

	vty_out(vty, "HNB \"%s\" MCC %u MNC %u LAC %u RAC %u SAC %u CID %u%s", hnb->identity_info,
			hnb->id.mcc, hnb->id.mnc, hnb->id.lac, hnb->id.rac, hnb->id.sac, hnb->id.cid,
			VTY_NEWLINE);
	vty_out(vty, "   HNBAP ID %u RUA ID %u%s", hnb->hnbap_stream, hnb->rua_stream, VTY_NEWLINE);

	llist_for_each_entry(map, &hnb->map_list, hnb_list) {
		vty_out(vty, " Map %u->%u (RUA->SUA) cnlink=%p state=%u%s", map->rua_ctx_id, map->scu_conn_id,
			map->cn_link, map->state, VTY_NEWLINE);

	}
}

static void vty_dump_ue_info(struct vty *vty, struct ue_context *ue)
{
	vty_out(vty, "UE IMSI \"%s\" context ID %u%s", ue->imsi, ue->context_id, VTY_NEWLINE);
}

DEFUN(show_hnb, show_hnb_cmd, "show hnb all", SHOW_STR "Display information about a HNB")
{
	struct hnb_context *hnb;

	llist_for_each_entry(hnb, &g_hnb_gw->hnb_list, list) {
		vty_dump_hnb_info(vty, hnb);
	}

	return CMD_SUCCESS;
}

DEFUN(show_ue, show_ue_cmd, "show ue all", SHOW_STR "Display information about a UE")
{
	struct ue_context *ue;

	llist_for_each_entry(ue, &g_hnb_gw->ue_list, list) {
		vty_dump_ue_info(vty, ue);
	}

	return CMD_SUCCESS;
}

DEFUN(show_talloc, show_talloc_cmd, "show talloc", SHOW_STR "Display talloc info")
{
	talloc_report_full(tall_hnb_ctx, stderr);
	talloc_report_full(talloc_asn1_ctx, stderr);

	return CMD_SUCCESS;
}

void hnbgw_vty_init(struct hnb_gw *gw, void *tall_ctx)
{
	g_hnb_gw = gw;
	tall_hnb_ctx = tall_ctx;
	install_element_ve(&show_hnb_cmd);
	install_element_ve(&show_ue_cmd);
	install_element_ve(&show_talloc_cmd);
}
