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

#include "log.h"
#include "command.h"
#include "mpls.h"
#include "northbound_cli.h"

#include "pathd/pathd.h"
#include "pathd/path_nb.h"
#ifndef VTYSH_EXTRACT_PL
#include "pathd/path_cli_clippy.c"
#endif

/*
 * XPath: /frr-pathd:pathd/segment-list
 */
DEFPY_NOSH (te_path_segment_list,
       te_path_segment_list_cmd,
       "segment-list WORD$name",
       "Segment List\n"
       "Segment List Name\n")
{
	char xpath[XPATH_MAXLEN];
	int ret;

	snprintf(xpath, sizeof(xpath), "/frr-pathd:pathd/segment-list[name='%s']", name);
	nb_cli_enqueue_change(vty, xpath, NB_OP_CREATE, NULL);

	ret = nb_cli_apply_changes(vty, NULL);
	if (ret == CMD_SUCCESS)
		VTY_PUSH_XPATH(TE_PATH_NODE, xpath);

	return ret;
}

DEFPY (no_te_path_segment_list,
       no_te_path_segment_list_cmd,
       "no segment-list WORD$name",
       NO_STR
       "Segment List\n"
       "Segment List Name\n")
{
	char xpath[XPATH_MAXLEN];

	snprintf(xpath, sizeof(xpath), "/frr-pathd:pathd/segment-list[name='%s']", name);
	nb_cli_enqueue_change(vty, xpath, NB_OP_DESTROY, NULL);

	return nb_cli_apply_changes(vty, NULL);
}

/*
 * XPath: /frr-pathd:pathd/segment-list/label
 */
DEFPY (te_path_segment_list_label,
       te_path_segment_list_label_cmd,
       "mpls label (16-1048575)$label",
       "MPLS or IP Label\n"
       "Label\n"
       "Label Value\n")
{
	char xpath[XPATH_MAXLEN];

	snprintf(xpath, sizeof(xpath), "./label");
	nb_cli_enqueue_change(vty, xpath, NB_OP_CREATE, label_str);

	return nb_cli_apply_changes(vty, NULL);
}

/*
 * XPath: /frr-pathd:pathd/sr-policy
 */
DEFPY_NOSH (te_path_sr_policy,
       te_path_sr_policy_cmd,
       "sr-policy WORD$name",
       "Segment Routing Policy\n"
       "SR Policy name\n")
{
	char xpath[XPATH_MAXLEN];
	int ret;

	snprintf(xpath, sizeof(xpath), "/frr-pathd:pathd/sr-policy[name='%s']", name);
	nb_cli_enqueue_change(vty, xpath, NB_OP_CREATE, NULL);

	ret = nb_cli_apply_changes(vty, NULL);
	if (ret == CMD_SUCCESS)
		VTY_PUSH_XPATH(TE_PATH_NODE, xpath);

	return ret;
}

DEFPY (no_te_path_sr_policy,
       no_te_path_sr_policy_cmd,
       "no sr-policy WORD$name",
       NO_STR
       "Segment Routing Policy\n"
       "SR Policy name\n")
{
	char xpath[XPATH_MAXLEN];

	snprintf(xpath, sizeof(xpath), "/frr-pathd:pathd/sr-policy[name='%s']", name);
	nb_cli_enqueue_change(vty, xpath, NB_OP_DESTROY, NULL);

	return nb_cli_apply_changes(vty, NULL);
}

/*
 * XPath: /frr-pathd:pathd/sr-policy/color
 */
DEFPY (te_path_sr_policy_color,
       te_path_sr_policy_color_cmd,
       "color (0-4294967295)$num",
       "Segment Routing Policy Color\n"
       "SR Policy color\n")
{
	char xpath[XPATH_MAXLEN];

	snprintf(xpath, sizeof(xpath), "./color");
	nb_cli_enqueue_change(vty, xpath, NB_OP_CREATE, num_str);

	return nb_cli_apply_changes(vty, NULL);
}

/*
 * XPath: /frr-pathd:pathd/sr-policy/endpoint
 */
DEFPY (te_path_sr_policy_endpoint,
       te_path_sr_policy_endpoint_cmd,
       "endpoint A.B.C.D$endpoint",
       "Segment Routing Policy Endpoint\n"
       "SR Policy endpoint IP\n")
{
	char xpath[XPATH_MAXLEN];

	snprintf(xpath, sizeof(xpath), "./endpoint");
	nb_cli_enqueue_change(vty, xpath, NB_OP_CREATE, endpoint_str);

	return nb_cli_apply_changes(vty, NULL);
}

/*
 * XPath: /frr-pathd:pathd/sr-policy/binding-sid
 */
DEFPY (te_path_sr_policy_binding_sid,
       te_path_sr_policy_binding_sid_cmd,
       "binding-sid (0-1048575)$label",
       "Segment Routing Policy Binding-SID\n"
       "SR Policy Binding-SID label\n")
{
	char xpath[XPATH_MAXLEN];

	snprintf(xpath, sizeof(xpath), "./binding-sid");
	nb_cli_enqueue_change(vty, xpath, NB_OP_CREATE, label_str);

	return nb_cli_apply_changes(vty, NULL);
}

/*
 * XPath: /frr-pathd:pathd/sr-policy/candidate-path
 */
DEFPY (te_path_sr_policy_candidate_path,
       te_path_sr_policy_candidate_path_cmd,
       "candidate-path\
        preference (0-4294967295)$preference\
        explicit segment-list WORD$list_name",
       "Segment Routing Policy Candidate Path\n"
       "Segment Routing Policy Candidate Path Preference\n"
       "Administrative Preference\n"
       "'explicit' or 'dynamic' Path\n"
       "List of SIDs\n"
       "Name of the Segment List\n")
{
	char xpath[XPATH_MAXLEN];

	snprintf(xpath, sizeof(xpath), "./candidate-path[preference='%s']", preference_str);
	nb_cli_enqueue_change(vty, xpath, NB_OP_CREATE, preference_str);

	snprintf(xpath, sizeof(xpath), "./candidate-path[preference='%s']/protocol-origin", preference_str);
	nb_cli_enqueue_change(vty, xpath, NB_OP_CREATE, "config");

	snprintf(xpath, sizeof(xpath), "./candidate-path[preference='%s']/originator", preference_str);
	nb_cli_enqueue_change(vty, xpath, NB_OP_CREATE, "127.0.0.1");

	snprintf(xpath, sizeof(xpath), "./candidate-path[preference='%s']/dynamic-flag", preference_str);
	nb_cli_enqueue_change(vty, xpath, NB_OP_CREATE, "false");

	snprintf(xpath, sizeof(xpath), "./candidate-path[preference='%s']/segment-list-name", preference_str);
	nb_cli_enqueue_change(vty, xpath, NB_OP_CREATE, list_name);

	return nb_cli_apply_changes(vty, NULL);
}

DEFPY (no_te_path_sr_policy_candidate_path,
       no_te_path_sr_policy_candidate_path_cmd,
       "no candidate-path\
        preference (0-4294967295)$preference",
       NO_STR
       "Segment Routing Policy Candidate Path\n"
       "Segment Routing Policy Candidate Path Preference\n"
       "Administrative Preference\n")
{
	char xpath[XPATH_MAXLEN];

	snprintf(xpath, sizeof(xpath), "./candidate-path[preference='%s']", preference_str);
	nb_cli_enqueue_change(vty, xpath, NB_OP_DESTROY, NULL);

	return nb_cli_apply_changes(vty, NULL);
}

/*
 * XPath: /frr-pathd:pathd/mpls/lsp
 */
DEFPY_NOSH (te_path_mpls,
       te_path_mpls_cmd,
       "te-path mpls input (16-1048575)$input_label",
       "Establish a traffic-engineered path\n"
       "Multiprotocol Label Switching LSP\n"
       "Incoming MPLS label\n"
       "MPLS label value\n")
{
	char xpath[XPATH_MAXLEN];
	int ret;

	snprintf(xpath, sizeof(xpath),
		 "/frr-pathd:pathd/mpls/lsp[input-label='%s']",
		 input_label_str);
	nb_cli_enqueue_change(vty, xpath, NB_OP_CREATE, NULL);

	ret = nb_cli_apply_changes(vty, NULL);
	if (ret == CMD_SUCCESS)
		VTY_PUSH_XPATH(TE_PATH_NODE, xpath);

	return ret;
}

DEFPY (no_te_path_mpls,
       no_te_path_mpls_cmd,
       "no te-path mpls input (16-1048575)$input_label",
       NO_STR
       "Establish a traffic-engineered path\n"
       "Multiprotocol Label Switching LSP\n"
       "Incoming MPLS label\n"
       "MPLS label value\n")
{
	char xpath[XPATH_MAXLEN];

	snprintf(xpath, sizeof(xpath),
		 "/frr-pathd:pathd/mpls/lsp[input-label='%s']",
		 input_label_str);
	nb_cli_enqueue_change(vty, xpath, NB_OP_DESTROY, NULL);

	return nb_cli_apply_changes(vty, NULL);
}

void cli_show_te_path_mpls(struct vty *vty, struct lyd_node *dnode,
			   bool show_defaults)
{
	vty_out(vty, "!\n");
	vty_out(vty, "te-path mpls input %s\n",
		yang_dnode_get_string(dnode, "./input-label"));
}

/*
 * XPath: /frr-pathd:pathd/mpls/lsp/nhlfe
 */
DEFPY (te_path_mpls_nhlfe,
       te_path_mpls_nhlfe_cmd,
       "nexthop <A.B.C.D|X:X::X:X>$nexthop\
	 interface IFNAME$interface\
	 label WORD$label\
	 [preference (0-4294967295)$preference]",
       "Nexthop address\n"
       "IPv4 nexthop address\n"
       "IPv6 nexthop address\n"
       "Nexthop interface\n"
       "Interface name\n"
       "Outgoing MPLS label(s)\n"
       "One or more labels in the range (16-1048575) separated by '/'\n"
       "Administrative preference\n"
       "Administrative preference value\n")
{
	mpls_label_t labels[MPLS_MAX_LABELS];
	uint8_t num_labels = 0;
	int ret;

	/* Parse outgoing label(s). */
	ret = mpls_str2label(label, &num_labels, labels);
	if (ret < 0) {
		switch (ret) {
		case -1:
			vty_out(vty, "%% Malformed label(s)\n");
			break;
		case -2:
			vty_out(vty,
				"%% Cannot use reserved label(s) (%u-%u)\n",
				MPLS_LABEL_RESERVED_MIN,
				MPLS_LABEL_RESERVED_MAX);
			break;
		case -3:
			vty_out(vty, "%% Too many labels. Enter %u or fewer\n",
				MPLS_MAX_LABELS);
			break;
		}
		return CMD_WARNING_CONFIG_FAILED;
	}

	nb_cli_enqueue_change(vty, ".", NB_OP_CREATE, NULL);
	nb_cli_enqueue_change(vty, "./interface", NB_OP_MODIFY, interface);

	/* Delete all outgoing labels first. */
	nb_cli_enqueue_change(vty, "./labels", NB_OP_DESTROY, NULL);
	/* Add newly configured outgoing label(s). */
	for (uint8_t i = 0; i < num_labels; i++) {
		char label_str[MPLS_MAX_LABELS][BUFSIZ];

		snprintf(label_str[i], sizeof(label_str[i]), "%u", labels[i]);
		nb_cli_enqueue_change(vty, "./labels/label", NB_OP_CREATE,
				      label_str[i]);
	}
	if (preference_str)
		nb_cli_enqueue_change(vty, "./preference", NB_OP_MODIFY,
				      preference_str);

	return nb_cli_apply_changes(vty, "./nhlfe[nexthop='%s']", nexthop_str);
}

DEFPY (no_te_path_mpls_nhlfe,
       no_te_path_mpls_nhlfe_cmd,
       "no nexthop <A.B.C.D|X:X::X:X>$nexthop\
	 [interface IFNAME\
	 label WORD\
	 [preference (0-4294967295)]]",
       NO_STR
       "Nexthop address\n"
       "IPv4 nexthop address\n"
       "IPv6 nexthop address\n"
       "Nexthop interface\n"
       "Interface name\n"
       "Outgoing MPLS label(s)\n"
       "One or more labels in the range (16-1048575) separated by '/'\n"
       "Administrative preference\n"
       "Administrative preference value\n")
{
	nb_cli_enqueue_change(vty, ".", NB_OP_DESTROY, NULL);

	return nb_cli_apply_changes(vty, "./nhlfe[nexthop='%s']", nexthop_str);
}

struct cli_show_nhlfe_label_args {
	struct vty *vty;
	bool first;
};

static int cli_show_nhlfe_label(const struct lyd_node *dnode, void *arg)
{
	struct cli_show_nhlfe_label_args *args = arg;
	struct vty *vty = args->vty;
	bool *first = &args->first;

	if (!*first)
		vty_out(vty, "/");
	*first = false;
	vty_out(vty, "%s", yang_dnode_get_string(dnode, NULL));

	return YANG_ITER_CONTINUE;
}

void cli_show_te_path_mpls_nhlfe(struct vty *vty, struct lyd_node *dnode,
				 bool show_defaults)
{
	struct cli_show_nhlfe_label_args args;

	args.vty = vty;
	args.first = true;

	vty_out(vty, " nexthop %s interface %s label ",
		yang_dnode_get_string(dnode, "./nexthop"),
		yang_dnode_get_string(dnode, "./interface"));
	yang_dnode_iterate(cli_show_nhlfe_label, &args, dnode,
			   "./labels/label");
	if (show_defaults || !yang_dnode_is_default(dnode, "./preference"))
		vty_out(vty, " preference %s",
			yang_dnode_get_string(dnode, "./preference"));
	vty_out(vty, "\n");
}

/* TE path node structure. */
static struct cmd_node te_path_node = {TE_PATH_NODE, "%s(config-te)# ", 1};

static int config_write_paths(struct vty *vty)
{
	struct lyd_node *dnode;

	dnode = yang_dnode_get(running_config->dnode, "/frr-pathd:pathd");
	assert(dnode);
	nb_cli_show_dnode_cmds(vty, dnode, false);

	return 1;
}

void path_cli_init(void)
{
	install_node(&te_path_node, config_write_paths);
	install_default(TE_PATH_NODE);

	install_element(CONFIG_NODE, &te_path_segment_list_cmd);
	install_element(CONFIG_NODE, &no_te_path_segment_list_cmd);
	install_element(TE_PATH_NODE, &te_path_segment_list_label_cmd);
	install_element(CONFIG_NODE, &te_path_sr_policy_cmd);
	install_element(CONFIG_NODE, &no_te_path_sr_policy_cmd);
	install_element(TE_PATH_NODE, &te_path_sr_policy_color_cmd);
	install_element(TE_PATH_NODE, &te_path_sr_policy_endpoint_cmd);
	install_element(TE_PATH_NODE, &te_path_sr_policy_binding_sid_cmd);
	install_element(TE_PATH_NODE, &te_path_sr_policy_candidate_path_cmd);
	install_element(TE_PATH_NODE, &no_te_path_sr_policy_candidate_path_cmd);

	install_element(CONFIG_NODE, &te_path_mpls_cmd);
	install_element(CONFIG_NODE, &no_te_path_mpls_cmd);
	install_element(TE_PATH_NODE, &te_path_mpls_nhlfe_cmd);
	install_element(TE_PATH_NODE, &no_te_path_mpls_nhlfe_cmd);
}
