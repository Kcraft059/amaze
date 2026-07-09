/**-----------------------------------------------------------------------*
 * Amaze mini-game server
 *
 * Copyright (C) 2026 @kcraft059 - GPL v3
 *-----------------------------------------------------------------------**/

#include "misc/log.h"
#include <stdio.h>
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

int argSetPort(char** argv, int argc);
void sockHandler(struct sock_context* sock_ctx, enum sock_event event);

uint16_t port = ACP_DEFAULT_PORT;
const struct programArgument args[] = {
    {.name = "-p", .description = "set listening port", .func = argSetPort}, // Signify end of array
    {.name = NULL, .description = NULL, .func = NULL},                       // Signify end of array
};

// Global functions

int main(int argc, char** argv) {
  evalArgsContext(argv, argc, args);

  int server_sock_fd, queue_fd;
  struct sock_context* server_sock_ctx;

  queue_fd = initQueue();
  server_sock_fd = initServerSocket(port);
  server_sock_ctx = addSockToQueue(queue_fd, server_sock_fd, T_SERVER_SOCK);
  if (server_sock_ctx == NULL)
    panicErrorf(errno, "Adding server sock to queue");

  handleSockEvents(queue_fd, sockHandler, 40, &(struct timespec){30, 0});

  closeSockCtx(server_sock_ctx);
  close(queue_fd);

  return 0;
}

// Local functions

void sockHandler(struct sock_context* sock_ctx, enum sock_event event) { // WIP
  if (sock_ctx->type != T_SERVER_SOCK)
    return;

  int client_sock_fd;
  while ((client_sock_fd = accept(sock_ctx->fd, NULL, NULL)) != -1) {
    send(client_sock_fd, "Hello !", 8, 0);
    close(client_sock_fd);
  }

  if (errno != EWOULDBLOCK && errno != EAGAIN)
    printErrorf(errno, "Accepting incomming connection");
};

int argSetPort(char** argv, int argc) {
  int val, n, pos;
  if (argc < 1) {
    errno = EINVLPRM; // Check if there's enough params
    return -1;
  }

  n = sscanf(argv[0], "%d%n", &val, &pos);
  if (n != 1 || pos != strlen(argv[0])) {
    errno = EINVLPRM; // Fail if invalid input
    return -1;
  }
  port = val & 0xffff; // Update port with mask

  return 1; // Return number of params used
};
