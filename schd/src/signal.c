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

#include <sys/reboot.h>
#include <sys/types.h>

#include <unistd.h>

#include "schd.h"

static void signal_dummy(int signal, siginfo_t *siginfo, void *data)
{
	ERROR("Got unexpected signal %d\n", signal);
}

struct sigaction sa_dummy = {
	.sa_sigaction = signal_dummy,
	.sa_flags = SA_SIGINFO
};

void schd_signal(void)
{
	signal(SIGPIPE, SIG_IGN);
	if (getpid() != 1)
		return;
	sigaction(SIGTERM, &sa_dummy, NULL);
	sigaction(SIGUSR1, &sa_dummy, NULL);
	sigaction(SIGUSR2, &sa_dummy, NULL);
	sigaction(SIGSEGV, &sa_dummy, NULL);
	sigaction(SIGBUS, &sa_dummy, NULL);
	sigaction(SIGHUP, &sa_dummy, NULL);
	sigaction(SIGKILL, &sa_dummy, NULL);
	sigaction(SIGSTOP, &sa_dummy, NULL);
}
