/**-----------------------------------------------------------------------*
 * Amaze mini-game server
 *
 * Copyright (C) 2026 @kcraft059 - GPL v3
 *-----------------------------------------------------------------------**/

#include "misc/log.h"
#include <_stdio.h>
#include <_time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#ifdef __linux__
#include <sys/epoll.h>
#elif defined(__APPLE__)
#include <sys/event.h>
#endif

#include <arpa/inet.h>
#include <sys/errno.h>
#include <sys/socket.h>

#include <acp/acp.h>
#include <misc/misc.h>
#include <server/core.h>

// Local declarations

err argSetPort(char** argv, int* argc);

uint16_t port = ACP_DEFAULT_PORT;
const struct programArgument args[] = {
    {.name = "-p", .description = "set listening port", .func = argSetPort}, // Signify end of array
    {.name = NULL, .description = NULL, .func = NULL},                       // Signify end of array
};

// Global functions

int main(int argc, char** argv) {
  evalArgsContext(argv, argc, args);

  int server_sock_fd, queue_fd;
  server_sock_fd = initServerSocket(port);
  queue_fd = initQueue();
  addServerSockQueue(queue_fd, server_sock_fd);

	printLogf("Starting to wait");
  nanosleep(&(struct timespec){30, 0}, NULL);
	printLogf("Accepting clients");

#ifdef __linux__
#error "Not implemented yet"
#elif defined(__APPLE__)
  struct kevent events[10];

  int n = kevent(queue_fd, NULL, 0, events, 10, &(struct timespec){30, 0});

  printLogf("Number of events returned: %d", n);

  for (n = n - 1; n >= 0; n--) {
    int client_sock_fd;

    while ((client_sock_fd = accept(events[n].ident, NULL, NULL)) != -1) {
      send(client_sock_fd, "Gloup !", 8, 0);
      close(client_sock_fd);
    };

    if (errno != EWOULDBLOCK && errno != EAGAIN)
      panicErrorf(errno, "Accept error");
  }
#endif

  return 0;
}

// Local functions

err argSetPort(char** argv, int* argc) {
  int val, n, pos;
  if (*argc < 1) return EINVLPRM; // Check if there's enough params

  n = sscanf(argv[0], "%d%n", &val, &pos);
  if (n != 1 || pos != strlen(argv[0])) return EINVLPRM; // Fail if invalid input
  port = val & 0xffff;                                   // Update port with mask

  *argc = 1; // Set number of params used
  return OK;
};
