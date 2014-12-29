#include <sys/resource.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include "schd.h"

char *ubus_socket = NULL;
static struct ubus_context *ctx;
static struct uloop_timeout ubus_timer;


static void
ubus_reconnect_cb(struct uloop_timeout *timeout)
{
	if (!ubus_reconnect(ctx, ubus_socket))
		ubus_add_uloop(ctx);
	else
		uloop_timeout_set(timeout, 2000);
}

static void
ubus_disconnect_cb(struct ubus_context *ctx)
{
	ubus_timer.cb = ubus_reconnect_cb;
	uloop_timeout_set(&ubus_timer, 2000);
}

static void
ubus_connect_cb(struct uloop_timeout *timeout)
{
	ctx = ubus_connect(ubus_socket);

	if (!ctx) {
		DEBUG(4, "Connection to ubus failed\n");
		uloop_timeout_set(&ubus_timer, 1000);
		return;
	}

	ctx->connection_lost = ubus_disconnect_cb;
	ubus_init_service(ctx);
//	ubus_init_system(ctx);
//	watch_ubus(ctx);

	DEBUG(2, "Connected to ubus, id=%08x\n", ctx->local_id);
	ubus_add_uloop(ctx);
}

void
schd_connect_ubus(void)
{
	ubus_timer.cb = ubus_connect_cb;
	uloop_timeout_set(&ubus_timer, 1000);
}
