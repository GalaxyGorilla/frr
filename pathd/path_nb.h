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

#ifndef _FRR_PATH_NB_H_
#define _FRR_PATH_NB_H_

extern const struct frr_yang_module_info frr_pathd_info;

/* Mandatory callbacks. */
int pathd_te_segment_list_create(enum nb_event event, const struct lyd_node *dnode,
			  union nb_resource *resource);
int pathd_te_segment_list_destroy(enum nb_event event, const struct lyd_node *dnode);
int pathd_te_segment_list_label_move(enum nb_event event,
					   const struct lyd_node *dnode);
int pathd_te_segment_list_label_create(enum nb_event event, const struct lyd_node *dnode,
			  union nb_resource *resource);
int pathd_te_segment_list_label_destroy(enum nb_event event, const struct lyd_node *dnode);
int pathd_te_sr_policy_create(enum nb_event event, const struct lyd_node *dnode,
			  union nb_resource *resource);
int pathd_te_sr_policy_destroy(enum nb_event event, const struct lyd_node *dnode);
int pathd_te_sr_policy_color_modify(enum nb_event event,
					  const struct lyd_node *dnode,
					  union nb_resource *resource);
int pathd_te_sr_policy_color_destroy(enum nb_event event, const struct lyd_node *dnode);
int pathd_te_sr_policy_endpoint_modify(enum nb_event event,
					  const struct lyd_node *dnode,
					  union nb_resource *resource);
int pathd_te_sr_policy_endpoint_destroy(enum nb_event event, const struct lyd_node *dnode);
int pathd_te_sr_policy_binding_sid_modify(enum nb_event event,
					  const struct lyd_node *dnode,
					  union nb_resource *resource);
int pathd_te_sr_policy_binding_sid_destroy(enum nb_event event, const struct lyd_node *dnode);
int pathd_te_sr_policy_candidate_path_create(enum nb_event event, const struct lyd_node *dnode,
			  union nb_resource *resource);
int pathd_te_sr_policy_candidate_path_destroy(enum nb_event event, const struct lyd_node *dnode);
int pathd_te_sr_policy_candidate_path_protocol_origin_modify(enum nb_event event,
					  const struct lyd_node *dnode,
					  union nb_resource *resource);
int pathd_te_sr_policy_candidate_path_protocol_origin_destroy(enum nb_event event, const struct lyd_node *dnode);
int pathd_te_sr_policy_candidate_path_originator_modify(enum nb_event event,
					  const struct lyd_node *dnode,
					  union nb_resource *resource);
int pathd_te_sr_policy_candidate_path_originator_destroy(enum nb_event event, const struct lyd_node *dnode);
int pathd_te_sr_policy_candidate_path_dynamic_flag_modify(enum nb_event event,
					  const struct lyd_node *dnode,
					  union nb_resource *resource);
int pathd_te_sr_policy_candidate_path_dynamic_flag_destroy(enum nb_event event, const struct lyd_node *dnode);
int pathd_te_sr_policy_candidate_path_segment_list_name_modify(enum nb_event event,
					  const struct lyd_node *dnode,
					  union nb_resource *resource);
int pathd_te_sr_policy_candidate_path_segment_list_name_destroy(enum nb_event event, const struct lyd_node *dnode);
int pathd_mpls_lsp_create(enum nb_event event, const struct lyd_node *dnode,
			  union nb_resource *resource);
int pathd_mpls_lsp_destroy(enum nb_event event, const struct lyd_node *dnode);
int pathd_mpls_lsp_nhlfe_create(enum nb_event event,
				const struct lyd_node *dnode,
				union nb_resource *resource);
int pathd_mpls_lsp_nhlfe_destroy(enum nb_event event,
				 const struct lyd_node *dnode);
int pathd_mpls_lsp_nhlfe_interface_modify(enum nb_event event,
					  const struct lyd_node *dnode,
					  union nb_resource *resource);
int pathd_mpls_lsp_nhlfe_labels_label_create(enum nb_event event,
					     const struct lyd_node *dnode,
					     union nb_resource *resource);
int pathd_mpls_lsp_nhlfe_labels_label_destroy(enum nb_event event,
					      const struct lyd_node *dnode);
int pathd_mpls_lsp_nhlfe_labels_label_move(enum nb_event event,
					   const struct lyd_node *dnode);
int pathd_mpls_lsp_nhlfe_preference_modify(enum nb_event event,
					   const struct lyd_node *dnode,
					   union nb_resource *resource);

/* Optional 'apply_finish' callbacks. */
void pathd_mpls_lsp_apply_finish(const struct lyd_node *dnode);

/* Optional 'cli_show' callbacks. */
void cli_show_te_path_mpls(struct vty *vty, struct lyd_node *dnode,
			   bool show_defaults);
void cli_show_te_path_mpls_nhlfe(struct vty *vty, struct lyd_node *dnode,
				 bool show_defaults);

#endif /* _FRR_PATH_NB_H_ */
