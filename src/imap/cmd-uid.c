/* Copyright (C) 2002 Timo Sirainen */

#include "common.h"
#include "commands.h"

int cmd_uid(struct client_command_context *cmd)
{
	const char *cmd_name;

	/* UID <command> <args> */
	cmd_name = imap_parser_read_word(cmd->client->parser);
	if (cmd_name == NULL)
		return FALSE;

	cmd->func = command_find(t_strconcat("UID ", cmd_name, NULL));

	if (cmd->func != NULL) {
		cmd->uid = TRUE;
		return cmd->func(cmd);
	} else {
		client_send_tagline(cmd, t_strconcat(
			"BAD Unknown UID command ", cmd_name, NULL));
		return TRUE;
	}
}
