/**-----------------------------------------------------------------------*
 * Amaze mini-game server
 *
 * Copyright (C) 2026 @kcraft059 - GPL v3
 *-----------------------------------------------------------------------**/

#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#ifdef __linux__
#include <sys/epoll.h>
#elif defined(__APPLE__)
#include <sys/event.h>
#endif

#include <arpa/inet.h>
#include <sys/socket.h>

#include <acp/acp.h>
#include <misc/log.h>
#include <server/core.h>

// Local function declarations

int addReadSockQueue(int queue_fd, struct sock_context* sock_ctx);

// Global function definition

int initServerSocket(int port) {
  int server_sock, socket_flags, result;
  server_sock = socket(AF_INET, SOCK_STREAM, 0); // Initiate TCP ipv4 connection

  if (server_sock == -1)
    panicErrorf(errno, "Opening server TCP socket");

  struct sockaddr_in sock_addr = {
      .sin_family = AF_INET,         // Set type to TCP
      .sin_port = htons(port),       // Configure port
      .sin_addr.s_addr = INADDR_ANY, // Configure adress
  };

  socket_flags = fcntl(server_sock, F_GETFL);

  if (socket_flags == -1)
    panicErrorf(errno, "Getting server socket flags");

  socket_flags |= O_NONBLOCK; // Set server socket to non-blocking
  result = fcntl(server_sock, F_SETFL, socket_flags);

  if (socket_flags == -1)
    panicErrorf(errno, "Setting server socket flags");

  result = bind(server_sock, (struct sockaddr*)&sock_addr, sizeof(sock_addr)); // Bind port to adress

  if (result != OK)
    panicErrorf(errno, "Binding server socket to port %d", port);

  result = listen(server_sock, MAX_QUEUED_CLIENTS); // Set sock to passive listening with MAX_QUEUED_CLIENTS

  if (result != OK)
    panicErrorf(errno, "Listening on socket");

  return server_sock;
}

int initQueue() {
  int queue_fd;

#ifdef __linux__
#error "Not implemented yet"
#elif defined(__APPLE__)
  queue_fd = kqueue(); // Init a kqeue instance
  if (queue_fd == -1)
    panicErrorf(errno, "Creating kqueue");
#endif

  return queue_fd;
}

struct sock_context* addSockToQueue(int queue_fd, int sock_fd, enum sock_type type) { // Needs to live in memory, should be allocated
  struct sock_context* sock_ctx = malloc(sizeof(struct sock_context));
  sock_ctx->type = type;
  sock_ctx->fd = sock_fd;

  switch (sock_ctx->type) {
  case T_SERVER_SOCK:
  case T_CLIENT_SOCK:
    return addReadSockQueue(queue_fd, sock_ctx) != -1 ? sock_ctx : NULL;
  }
};

int closeSockCtx(struct sock_context* sock_ctx) {
  if (close(sock_ctx->fd) == -1) return -1;
  free(sock_ctx);
  return 0;
};

int handleSockEvents(int queue_fd, event_handler handler, int max_events, struct timespec* timeout) {
#ifdef __linux__
#error "Not implemented yet"
#elif defined(__APPLE__)
  struct kevent events[max_events];
  int n = kevent(queue_fd, NULL, 0, events, max_events, timeout); // Fetch max number of events

  if (n == -1) // If error during poll
    return -1;

  for (n = n - 1; n >= 0; --n)
    handler(events[n].udata, events[n].flags & EV_EOF ? SEV_RESET : SEV_READ);

#endif
  return 0;
};

// Local function definiton

int addReadSockQueue(int queue_fd, struct sock_context* sock_ctx) {
#ifdef __linux__
#error "Not implemented yet"
#elif defined(__APPLE__)
  // Add server_sock to the queue
  int result = kevent(queue_fd, &(struct kevent){
                                    .flags = EV_ADD, // Will contain EV_EOF on sock close
                                    .ident = sock_ctx->fd,
                                    .filter = EVFILT_READ,
                                    .udata = sock_ctx,
                                },
                      1, NULL, 0, NULL);

  return result != -1 ? 0 : -1;
#endif
}
