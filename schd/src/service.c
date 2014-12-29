/*
 * Copyright (C) 2013 Felix Fietkau <nbd@openwrt.org>
 * Copyright (C) 2013 John Crispin <blogic@openwrt.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 2.1
 * as published by the Free Software Foundation
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <libubox/blobmsg_json.h>
#include <libubox/avl-cmp.h>

#include "schd.h"

#include "service.h"
static struct ubus_context *ctx;

enum {
	SERVICE_ATTR_NAME,
	__SERVICE_ATTR_MAX,
};

static const struct blobmsg_policy service_attrs[__SERVICE_ATTR_MAX] = {
	[SERVICE_ATTR_NAME] = { "name", BLOBMSG_TYPE_STRING },
};

static int
service_handle_list(struct ubus_context *ctx, struct ubus_object *obj,
		    struct ubus_request_data *req, const char *method,
		    struct blob_attr *msg)
{
	struct blob_attr *tb[__SERVICE_ATTR_MAX];
	int verbose = 0;

	blobmsg_parse(service_attrs, __SERVICE_ATTR_MAX, tb, blob_data(msg), blob_len(msg));

	if (tb[SERVICE_ATTR_NAME] && blobmsg_get_bool(tb[SERVICE_ATTR_NAME]))
		verbose = 1;

//	blob_buf_init(&b, 0);

//	ubus_send_reply(ctx, req, b.head);

	return 0;
}

static struct ubus_method main_object_methods[] = {
	UBUS_METHOD("schedule_apply", service_handle_list, service_attrs),
};

static struct ubus_object_type main_object_type =
	UBUS_OBJECT_TYPE("schedule", main_object_methods);

static struct ubus_object main_object = {
	.name = "schedule",
	.type = &main_object_type,
	.methods = main_object_methods,
	.n_methods = ARRAY_SIZE(main_object_methods),
};


void ubus_init_service(struct ubus_context *_ctx)
{
	ctx = _ctx;
	ubus_add_object(ctx, &main_object);
}


