#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <unistd.h>
#include <getopt.h>
#include <libgen.h>

#include "schd.h"

unsigned int debug;

//===========
static struct blob_buf b;
static struct ubus_context *_ctx;

enum {
	SCHD_NAME,
	SCHD_ALLWEEK,	
	SCHD_WEEKDAYS,
	SCHD_ALLDAY,
	SCHD_TIME_FORMAT_24HR,
/*
	SCHD_STAR_TIME_WEEKDAYS,
*/
	SCHD_STAR_TIME_HOUR,
	SCHD_STAR_TIME_MINUTE,
/*
	SCHD_END_TIME_WEEKDAYS,
*/
	SCHD_END_TIME_HOUR,
	SCHD_END_TIME_MINUTE,
	__SCHD_MAX
};
/*ubus call schedule set/add '{name:xxx,allweek:yes,weekdays:"0,1,2,3",allday:yes,24hr:yes,s_hour:0,s_minute:0,e_hour:12,e_minute:0}' */
static const struct blobmsg_policy schd_set_attrs[__SCHD_MAX] = {
	[SCHD_NAME] = { .name = "name", .type = BLOBMSG_TYPE_STRING },
	[SCHD_ALLWEEK] = { .name = "allweek", .type = BLOBMSG_TYPE_BOOL },
	[SCHD_WEEKDAYS] = { .name = "weekdays", .type = BLOBMSG_TYPE_STRING },
	[SCHD_ALLDAY] = { .name = "allday", .type = BLOBMSG_TYPE_BOOL },
	[SCHD_TIME_FORMAT_24HR] = { .name = "24hr", .type = BLOBMSG_TYPE_BOOL },
	[SCHD_STAR_TIME_HOUR] = { .name = "s_hour", .type = BLOBMSG_TYPE_INT32 },
	[SCHD_STAR_TIME_MINUTE] = { .name = "s_minute", .type = BLOBMSG_TYPE_INT32 },
	[SCHD_END_TIME_HOUR] = { .name = "e_hour", .type = BLOBMSG_TYPE_INT32 },
	[SCHD_END_TIME_MINUTE] = { .name = "e_minute", .type = BLOBMSG_TYPE_INT32 },
};

enum {
	SCHD_DEL_ATTR_NAME,
	__SCHD_DEL_ATTR_MAX,
};

static const struct blobmsg_policy schd_del_attrs[__SCHD_DEL_ATTR_MAX] = {
	[SCHD_DEL_ATTR_NAME] = { .name = "name", .type = BLOBMSG_TYPE_STRING },
};

static int schd_handle_set(struct ubus_context *ctx, struct ubus_object *obj,
			struct ubus_request_data *req, const char *method,
			struct blob_attr *msg)
{
	struct blob_attr *tb[__SERVICE_SET_MAX], *cur;
	const char *name;

	/*base on the define of schd_set_attrs parsing the msg and save into tb*/
	blobmsg_parse(schd_set_attrs, __SCHD_MAX, tb, blob_data(msg), blob_len(msg));
	cur = tb[SCHD_NAME];
	if (!cur)
		return UBUS_STATUS_INVALID_ARGUMENT;
	
	name = blobmsg_data(cur);
	
	/*check the schedule exist or not*/
	
	/*create new or update the schedule*/
	
	/*commit uci*/
	
	/*update the crontab*/
}

static const struct ubus_method schd_methods[] = {
	UBUS_METHOD("set", schd_handle_set, schd_set_attrs),
	UBUS_METHOD("add", schd_handle_set, schd_set_attrs),
	UBUS_METHOD_NOARG("list", schd_handle_list),
	UBUS_METHOD("delete", schd_handle_delete, schd_del_attrs),
};

static struct ubus_object_type schd_object_type =
	UBUS_OBJECT_TYPE("schedule", schd_methods);
	
static struct ubus_object schd_object = {
	.name = "schedule",
	.type = &schd_object_type,
	.methods = schd_methods,
	.n_methods = ARRAY_SIZE(schd_methods),
	.subscribe_cb = procd_subscribe_cb,
};

void ubus_init_schd(struct ubus_context *ctx)
{
	int ret;
	_ctx = ctx;
	ret = ubus_add_object(ctx, &schd_object);
	if (ret)
		ERROR("Failed to add object: %s\n", ubus_strerror(ret));
}


//========================
static int usage(const char *prog)
{
	ERROR("Usage: %s [options]\n"
		"Options:\n"
		"\t-s <path>\tPath to ubus socket\n"
		"\t-h <path>\trun as hotplug daemon\n"
		"\t-d <level>\tEnable debug messages\n"
		"\n", prog);
	return 1;
}

int main(int argc, char **argv)
{
	int ch;
	char *dbglvl = getenv("DBGLVL");

	if (dbglvl) {
		debug = atoi(dbglvl);
		unsetenv("DBGLVL");
	}

	while ((ch = getopt(argc, argv, "d:s:h:")) != -1) {
		switch (ch) {
//		case 'h':
//			return hotplug_run(optarg);
		case 's':
			ubus_socket = optarg;
			break;
		case 'd':
			debug = atoi(optarg);
			break;
		default:
			return usage(argv[0]);
		}
	}
	uloop_init();
//	schd_signal();
//	trigger_init();
	if (getpid() != 1)
		schd_connect_ubus();
//	else
//		schd_state_next();
	uloop_run();

	return 0;
}