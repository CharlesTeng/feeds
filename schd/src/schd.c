#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <unistd.h>
#include <getopt.h>
#include <libgen.h>

#include "schd.h"
unsigned int debug;
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
	schd_signal();
//	trigger_init();
	if (getpid() != 1)
		schd_connect_ubus();
//	else
//		schd_state_next();
	uloop_run();

	return 0;
}