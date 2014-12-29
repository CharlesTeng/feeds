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

#ifndef __SCHD_H
#define __SCHD_H

#include <libubox/uloop.h>
#include <libubox/utils.h>
#include <libubus.h>

#include <stdio.h>
#include <syslog.h>

#include "log.h"

#define __init __attribute__((constructor))

extern char *ubus_socket;

void schd_connect_ubus(void);
void schd_reconnect_ubus(int reconnect);
void ubus_init_service(struct ubus_context *ctx);
void ubus_init_system(struct ubus_context *ctx);

void schd_signal(void);


#endif
