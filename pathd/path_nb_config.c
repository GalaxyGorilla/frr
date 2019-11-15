/*
 * Copyright (C) 2019  NetDEF, Inc.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; see the file COPYING; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include <zebra.h>

#include "northbound.h"
#include "libfrr.h"

#include "pathd/pathd.h"
#include "pathd/path_nb.h"

/*
 * XPath: /frr-pathd:pathd/segment-list
 */
int pathd_te_segment_list_create(enum nb_event event, const struct lyd_node *dnode,
			  union nb_resource *resource)
{
	return NB_OK;
}

int pathd_te_segment_list_destroy(enum nb_event event, const struct lyd_node *dnode)
{
	return NB_OK;
}

/*
 * XPath: /frr-pathd:pathd/segment-list/label
 */
int pathd_te_segment_list_label_create(enum nb_event event, const struct lyd_node *dnode,
			  union nb_resource *resource)
{
	return NB_OK;
}

int pathd_te_segment_list_label_destroy(enum nb_event event, const struct lyd_node *dnode)
{
	return NB_OK;
}

int pathd_te_segment_list_label_move(enum nb_event event,
					   const struct lyd_node *dnode)
{
	return NB_OK;
}

/*
 * XPath: /frr-pathd:pathd/sr-policy
 */
int pathd_te_sr_policy_create(enum nb_event event, const struct lyd_node *dnode,
			  union nb_resource *resource)
{
	return NB_OK;
}

int pathd_te_sr_policy_destroy(enum nb_event event, const struct lyd_node *dnode)
{
	return NB_OK;
}

/*
 * XPath: /frr-pathd:pathd/sr-policy/color
 */
int pathd_te_sr_policy_color_modify(enum nb_event event,
					  const struct lyd_node *dnode,
					  union nb_resource *resource)
{
	return NB_OK;
}

int pathd_te_sr_policy_color_destroy(enum nb_event event, const struct lyd_node *dnode)
{
	return NB_OK;
}

/*
 * XPath: /frr-pathd:pathd/sr-policy/endpoint
 */
int pathd_te_sr_policy_endpoint_modify(enum nb_event event,
					  const struct lyd_node *dnode,
					  union nb_resource *resource)
{
	return NB_OK;
}

int pathd_te_sr_policy_endpoint_destroy(enum nb_event event, const struct lyd_node *dnode)
{
	return NB_OK;
}

/*
 * XPath: /frr-pathd:pathd/sr-policy/binding-sid
 */
int pathd_te_sr_policy_binding_sid_modify(enum nb_event event,
					  const struct lyd_node *dnode,
					  union nb_resource *resource)
{
	return NB_OK;
}

int pathd_te_sr_policy_binding_sid_destroy(enum nb_event event, const struct lyd_node *dnode)
{
	return NB_OK;
}

/*
 * XPath: /frr-pathd:pathd/sr-policy/candidate-path
 */
int pathd_te_sr_policy_candidate_path_create(enum nb_event event, const struct lyd_node *dnode,
			  union nb_resource *resource)
{
	return NB_OK;
}

int pathd_te_sr_policy_candidate_path_destroy(enum nb_event event, const struct lyd_node *dnode)
{
	return NB_OK;
}

/*
 * XPath: /frr-pathd:pathd/sr-policy/candidate-path/protocol-origin
 */
int pathd_te_sr_policy_candidate_path_protocol_origin_modify(enum nb_event event,
					  const struct lyd_node *dnode,
					  union nb_resource *resource)
{
	return NB_OK;
}

int pathd_te_sr_policy_candidate_path_protocol_origin_destroy(enum nb_event event, const struct lyd_node *dnode)
{
	return NB_OK;
}

/*
 * XPath: /frr-pathd:pathd/sr-policy/candidate-path/originator
 */
int pathd_te_sr_policy_candidate_path_originator_modify(enum nb_event event,
					  const struct lyd_node *dnode,
					  union nb_resource *resource)
{
	return NB_OK;
}

int pathd_te_sr_policy_candidate_path_originator_destroy(enum nb_event event, const struct lyd_node *dnode)
{
	return NB_OK;
}

/*
 * XPath: /frr-pathd:pathd/sr-policy/candidate-path/dynamic-flag
 */
int pathd_te_sr_policy_candidate_path_dynamic_flag_modify(enum nb_event event,
					  const struct lyd_node *dnode,
					  union nb_resource *resource)
{
	return NB_OK;
}

int pathd_te_sr_policy_candidate_path_dynamic_flag_destroy(enum nb_event event, const struct lyd_node *dnode)
{
	return NB_OK;
}

/*
 * XPath: /frr-pathd:pathd/sr-policy/candidate-path/segment-list-name
 */
int pathd_te_sr_policy_candidate_path_segment_list_name_modify(enum nb_event event,
					  const struct lyd_node *dnode,
					  union nb_resource *resource)
{
	return NB_OK;
}

int pathd_te_sr_policy_candidate_path_segment_list_name_destroy(enum nb_event event, const struct lyd_node *dnode)
{
	return NB_OK;
}

/*
 * XPath: /frr-pathd:pathd/mpls/lsp
 */
int pathd_mpls_lsp_create(enum nb_event event, const struct lyd_node *dnode,
			  union nb_resource *resource)
{
	struct te_path *path;
	mpls_label_t input_label;

	if (event != NB_EV_APPLY)
		return NB_OK;

	input_label = yang_dnode_get_uint32(dnode, "./input-label");

	path = te_path_add(input_label);
	nb_running_set_entry(dnode, path);

	return NB_OK;
}

int pathd_mpls_lsp_destroy(enum nb_event event, const struct lyd_node *dnode)
{
	struct te_path *path;

	if (event != NB_EV_APPLY)
		return NB_OK;

	path = nb_running_unset_entry(dnode);
	te_path_del(path);

	return NB_OK;
}

void pathd_mpls_lsp_apply_finish(const struct lyd_node *dnode)
{
	struct te_path *path;

	path = nb_running_get_entry(dnode, NULL, true);
	te_path_install_zebra(path);
}

/*
 * XPath: /frr-pathd:pathd/mpls/lsp/nhlfe
 */
int pathd_mpls_lsp_nhlfe_create(enum nb_event event,
				const struct lyd_node *dnode,
				union nb_resource *resource)
{
	struct te_path *path;
	struct te_path_nhlfe *nhlfe;
	struct ipaddr nexthop;

	if (event != NB_EV_APPLY)
		return NB_OK;

	path = nb_running_get_entry(dnode, NULL, true);
	yang_dnode_get_ip(&nexthop, dnode, "./nexthop");

	nhlfe = te_path_nhlfe_add(path, &nexthop);
	nb_running_set_entry(dnode, nhlfe);

	return NB_OK;
}

int pathd_mpls_lsp_nhlfe_destroy(enum nb_event event,
				 const struct lyd_node *dnode)
{
	struct te_path_nhlfe *nhlfe;

	if (event != NB_EV_APPLY)
		return NB_OK;

	nhlfe = nb_running_unset_entry(dnode);
	te_path_nhlfe_del(nhlfe);

	return NB_OK;
}

/*
 * XPath: /frr-pathd:pathd/mpls/lsp/nhlfe/interface
 */
int pathd_mpls_lsp_nhlfe_interface_modify(enum nb_event event,
					  const struct lyd_node *dnode,
					  union nb_resource *resource)
{
	struct te_path_nhlfe *nhlfe;
	const char *ifname;

	if (event != NB_EV_APPLY)
		return NB_OK;

	nhlfe = nb_running_get_entry(dnode, NULL, true);
	ifname = yang_dnode_get_string(dnode, NULL);
	strlcpy(nhlfe->ifname, ifname, sizeof(nhlfe->ifname));

	return NB_OK;
}

/*
 * XPath: /frr-pathd:pathd/mpls/lsp/nhlfe/labels/label
 */
int pathd_mpls_lsp_nhlfe_labels_label_create(enum nb_event event,
					     const struct lyd_node *dnode,
					     union nb_resource *resource)
{
	struct te_path_nhlfe *nhlfe;
	mpls_label_t label;

	if (event != NB_EV_APPLY)
		return NB_OK;

	nhlfe = nb_running_get_entry(dnode, NULL, true);
	label = yang_dnode_get_uint32(dnode, NULL);
	nhlfe->labels[nhlfe->label_num++] = label;

	return NB_OK;
}

int pathd_mpls_lsp_nhlfe_labels_label_destroy(enum nb_event event,
					      const struct lyd_node *dnode)
{
#if 0
	struct te_path_nhlfe *nhlfe;
	mpls_label_t label;

	if (event != NB_EV_APPLY)
		return NB_OK;

	nhlfe = nb_running_get_entry(dnode, NULL, true);
	label = yang_dnode_get_uint32(dnode, NULL);
#endif
	/* TODO: implement me. */
	return NB_OK;
}

int pathd_mpls_lsp_nhlfe_labels_label_move(enum nb_event event,
					   const struct lyd_node *dnode)
{
#if 0
	struct te_path_nhlfe *nhlfe;
	mpls_label_t label;

	if (event != NB_EV_APPLY)
		return NB_OK;

	nhlfe = nb_running_get_entry(dnode, NULL, true);
	label = yang_dnode_get_uint32(dnode, NULL);
#endif
	/* TODO: implement me. */
	return NB_OK;
}

/*
 * XPath: /frr-pathd:pathd/mpls/lsp/nhlfe/preference
 */
int pathd_mpls_lsp_nhlfe_preference_modify(enum nb_event event,
					   const struct lyd_node *dnode,
					   union nb_resource *resource)
{
	struct te_path_nhlfe *nhlfe;
	uint32_t pref;

	if (event != NB_EV_APPLY)
		return NB_OK;

	nhlfe = nb_running_get_entry(dnode, NULL, true);
	pref = yang_dnode_get_uint32(dnode, NULL);
	nhlfe->pref = pref;

	return NB_OK;
}
