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
int pathd_te_segment_list_create(struct nb_cb_create_args *args);
int pathd_te_segment_list_destroy(struct nb_cb_destroy_args *args);
int pathd_te_segment_list_label_move(struct nb_cb_move_args *args);
int pathd_te_segment_list_label_create(struct nb_cb_create_args *args);
int pathd_te_segment_list_label_destroy(struct nb_cb_destroy_args *args);
int pathd_te_sr_policy_create(struct nb_cb_create_args *args);
int pathd_te_sr_policy_destroy(struct nb_cb_destroy_args *args);
int pathd_te_sr_policy_color_modify(struct nb_cb_modify_args *args);
int pathd_te_sr_policy_color_destroy(struct nb_cb_destroy_args *args);
int pathd_te_sr_policy_endpoint_modify(struct nb_cb_modify_args *args);
int pathd_te_sr_policy_endpoint_destroy(struct nb_cb_destroy_args *args);
int pathd_te_sr_policy_binding_sid_modify(struct nb_cb_modify_args *args);
int pathd_te_sr_policy_binding_sid_destroy(struct nb_cb_destroy_args *args);
int pathd_te_sr_policy_candidate_path_create(struct nb_cb_create_args *args);
int pathd_te_sr_policy_candidate_path_destroy(struct nb_cb_destroy_args *args);
int pathd_te_sr_policy_candidate_path_protocol_origin_modify(
	struct nb_cb_modify_args *args);
int pathd_te_sr_policy_candidate_path_protocol_origin_destroy(
	struct nb_cb_destroy_args *args);
int pathd_te_sr_policy_candidate_path_originator_modify(
	struct nb_cb_modify_args *args);
int pathd_te_sr_policy_candidate_path_originator_destroy(
	struct nb_cb_destroy_args *args);
int pathd_te_sr_policy_candidate_path_dynamic_flag_modify(
	struct nb_cb_modify_args *args);
int pathd_te_sr_policy_candidate_path_dynamic_flag_destroy(
	struct nb_cb_destroy_args *args);
int pathd_te_sr_policy_candidate_path_segment_list_name_modify(
	struct nb_cb_modify_args *args);
int pathd_te_sr_policy_candidate_path_segment_list_name_destroy(
	struct nb_cb_destroy_args *args);

/* Optional 'apply_finish' callbacks. */

/* Optional 'cli_show' callbacks. */

#endif /* _FRR_PATH_NB_H_ */