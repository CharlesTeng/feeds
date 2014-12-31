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
#include <uci.h>

static struct ubus_context *ctx;
static struct blob_buf b;


static int
service_handle_list(struct ubus_context *ctx, struct ubus_object *obj,
		    struct ubus_request_data *req, const char *method,
		    struct blob_attr *msg)
{
	static struct uci_context *uctx;
	struct uci_ptr ptr;
	int ret = 0;

//  list the config/schedule 
	blob_buf_init(&b, 0);
	uctx = uci_alloc_context();
	if (uci_lookup_ptr(uctx, &ptr, "schedule", true) != UCI_OK) {
		ret = 1;
	}
	if(ret == 0){
		//uci_export(uctx, stdout, ptr.p, true);
		//-->uci_export_package(package, stream, header);
		struct uci_package *p = ptr.p;
		struct uci_element *s, *o, *i;
		void *c;
		
		uci_foreach_element(&p->sections, s) {	
			struct uci_section *sec = uci_to_section(s);
			c = blobmsg_open_table(&b, sec->type);	
			uci_foreach_element(&sec->options, o) {
				struct uci_option *opt = uci_to_option(o);
				switch(opt->type) {
				case UCI_TYPE_STRING:
					blobmsg_add_string(&b, opt->e.name, opt->v.string);
					break;
				case UCI_TYPE_LIST:
					uci_foreach_element(&opt->v.list, i) {
				// not support		
					}
					break;
				default:
				//	fprintf(stream, "\t# unknown type for option '%s'\n", uci_escape(ctx, opt->e.name));
					break;
				}
			}
			blobmsg_close_table(&b, c);
		}
	}
	ubus_send_reply(ctx, req, b.head);
	uci_free_context(uctx);
	return ret;
}

static struct ubus_method main_object_methods[] = {
	UBUS_METHOD_NOARG("list", service_handle_list),
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


