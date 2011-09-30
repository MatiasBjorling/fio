#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <getopt.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/poll.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <signal.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "fio.h"

static int net_port = 8765;

int exit_backend = 0;

static int accept_loop(int listen_sk)
{
	struct sockaddr addr;
	unsigned int len = sizeof(addr);
	struct pollfd pfd;
	int ret, sk, flags;

	flags = fcntl(listen_sk, F_GETFL);
	flags |= O_NONBLOCK;
	fcntl(listen_sk, F_SETFL, flags);
again:
	pfd.fd = listen_sk;
	pfd.events = POLLIN;
	do {
		ret = poll(&pfd, 1, 100);
		if (ret < 0) {
			if (errno == EINTR)
				break;
			perror("poll");
			goto out;
		} else if (!ret)
			continue;

		if (pfd.revents & POLLIN)
			break;
	} while (!exit_backend);

	if (exit_backend)
		goto out;

	sk = accept(listen_sk, &addr, &len);
	if (sk < 0) {
		log_err("fio: accept failed\n");
		return -1;
	}

	/* read forever */
	while (!exit_backend) {
		char buf[131072];

		ret = recv(sk, buf, 4096, 0);
		if (ret > 0) {
			if (!strncmp("FIO_QUIT", buf, 8)) {
				exit_backend = 1;
				break;
			}
			parse_jobs_ini(buf, 1, 0);
			exec_run();
			reset_fio_state();
			break;
		} else if (!ret)
			break;
		if (errno == EAGAIN || errno == EINTR)
			continue;
		break;
	}

	close(sk);

	if (!exit_backend)
		goto again;

out:
	return 0;
}

int fio_server(void)
{
	struct sockaddr_in saddr_in;
	struct sockaddr addr;
	unsigned int len;
	int sk, opt;

	sk = socket(AF_INET, SOCK_STREAM, 0);
	if (sk < 0) {
		log_err("fio: socket\n");
		return -1;
	}

	opt = 1;
	if (setsockopt(sk, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
		log_err("fio: setsockopt\n");
		return -1;
	}
#ifdef SO_REUSEPORT
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt)) < 0) {
		td_verror(td, errno, "setsockopt");
		return 1;
	}
#endif

	saddr_in.sin_family = AF_INET;
	saddr_in.sin_addr.s_addr = htonl(INADDR_ANY);
	saddr_in.sin_port = htons(net_port);

	if (bind(sk, (struct sockaddr *) &saddr_in, sizeof(saddr_in)) < 0) {
		perror("bind");
		log_err("fio: bind\n");
		return -1;
	}

	if (listen(sk, 1) < 0) {
		log_err("fio: listen\n");
		return -1;
	}

	len = sizeof(addr);
	if (getsockname(sk, &addr, &len) < 0) {
		log_err("fio: getsockname");
		return -1;
	}

	return accept_loop(sk);
}
