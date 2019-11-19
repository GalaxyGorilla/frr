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

#ifndef _FRR_PATHD_H_
#define _FRR_PATHD_H_

#include "lib/mpls.h"
#include "lib/ipaddr.h"
#include "lib/typesafe.h"

PREDECL_RBTREE_UNIQ(tree_te_path)
PREDECL_RBTREE_UNIQ(tree_te_path_nhlfe)

/* TE path NHLFE. */
struct te_path_nhlfe {
    /* RB-tree entry. */
    struct tree_te_path_nhlfe_item entry;

    /* Nexthop address. */
    struct ipaddr nexthop;

    /* Nexthop interface. */
    char ifname[INTERFACE_NAMSIZ];

    /* Nexthop labels. */
    uint8_t label_num;
    mpls_label_t labels[MPLS_MAX_LABELS];

    /* Administrative preference. */
    uint32_t pref;

    /* Back pointer to TE path. */
    struct te_path *path;
};

/* TE path. */
struct te_path {
    /* RB-tree entry. */
    struct tree_te_path_item entry;

    /* MPLS LSP input label. */
    mpls_label_t input_label;

    /* List of NHLFEs. */
    struct tree_te_path_nhlfe_head nhlfes;
};

struct te_segment_list {
    RB_ENTRY(te_segment_list) entry;

    /* Name of the Segment List. */
    char *name;

    /* Nexthop labels. */
    uint8_t label_num;
    mpls_label_t *labels;
};
RB_HEAD(te_segment_list_instance_head, te_segment_list);
RB_PROTOTYPE(te_segment_list_instance_head, te_segment_list, entry, te_segment_list_instance_compare)

struct te_candidate_path {
    /* Administrative preference. */
    uint32_t preference;

    /* The associated Segment List. */
    char *segment_list_name;
};

struct te_sr_policy {
    RB_ENTRY(te_sr_policy) entry;

    /* Name */
    char *name;

    /* Binding SID */
    mpls_label_t binding_sid;

    /* Color */
    uint32_t color;

    /* Endpoint */
    struct ipaddr *endpoint;

    /* Candidate Paths */
    uint8_t candidate_path_num;
    struct te_candidate_path *candidate_paths;
};
RB_HEAD(te_sr_policy_instance_head, te_sr_policy);
RB_PROTOTYPE(te_sr_policy_instance_head, te_sr_policy, entry, te_sr_policy_instance_compare)

extern struct zebra_privs_t pathd_privs;
extern struct tree_te_path_head te_paths;

/* Prototypes. */
struct te_path *te_path_add(mpls_label_t input_label);
void te_path_del(struct te_path *path);
struct te_path *te_path_find(mpls_label_t input_label);
struct te_path_nhlfe *te_path_nhlfe_add(struct te_path *path,
                    struct ipaddr *nexthop);
void te_path_nhlfe_del(struct te_path_nhlfe *nhlfe);
struct te_path_nhlfe *te_path_nhlfe_find(struct te_path *path,
                     struct ipaddr *nexthop);
void te_path_install_zebra(struct te_path *path);
void te_path_uninstall_zebra(struct te_path *path);
void path_zebra_init(struct thread_master *master);
void path_cli_init(void);

struct te_segment_list *te_segment_list_create(char *name);
void te_segment_list_label_add(struct te_segment_list *te_segment_list, mpls_label_t label);
void te_segment_list_del(struct te_segment_list *te_segment_list);
struct te_sr_policy *te_sr_policy_create(char *name);
void te_sr_policy_del(struct te_sr_policy *te_sr_policy);
void te_sr_policy_color_add(struct te_sr_policy *te_sr_policy, uint32_t color);
void te_sr_policy_endpoint_add(struct te_sr_policy *te_sr_policy, struct ipaddr *endpoint);
void te_sr_policy_binding_sid_add(struct te_sr_policy *te_sr_policy, mpls_label_t binding_sid);
void te_sr_policy_candidate_path_add(struct te_sr_policy *te_sr_policy, uint32_t preference);
void te_sr_policy_candidate_path_segment_list_name_add(struct te_sr_policy *te_sr_policy, char *segment_list_name);

/* Generate rb-trees. */
int te_path_nhlfe_compare(const struct te_path_nhlfe *a,
              const struct te_path_nhlfe *b);
DECLARE_RBTREE_UNIQ(tree_te_path_nhlfe, struct te_path_nhlfe, entry,
            te_path_nhlfe_compare)
int te_path_compare(const struct te_path *a, const struct te_path *b);
DECLARE_RBTREE_UNIQ(tree_te_path, struct te_path, entry, te_path_compare)
#endif /* _FRR_PATHD_H_ */
