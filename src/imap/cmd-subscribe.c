/* Copyright (C) 2002 Timo Sirainen */

#include "common.h"
#include "commands.h"

int _cmd_subscribe_full(struct client_command_context *cmd, int subscribe)
{
        struct mail_storage *storage;
	const char *mailbox;

	/* <mailbox> */
	if (!client_read_string_args(cmd, 1, &mailbox))
		return FALSE;

	if (!client_verify_mailbox_name(cmd, mailbox, subscribe, FALSE))
		return TRUE;

	storage = client_find_storage(cmd, &mailbox);
	if (storage == NULL)
		return TRUE;

	if (mail_storage_set_subscribed(storage, mailbox, subscribe) < 0)
		client_send_storage_error(cmd, storage);
	else {
		client_send_tagline(cmd, subscribe ?
				    "OK Subscribe completed." :
				    "OK Unsubscribe completed.");
	}
	return TRUE;
}

int cmd_subscribe(struct client_command_context *cmd)
{
	return _cmd_subscribe_full(cmd, TRUE);
}
