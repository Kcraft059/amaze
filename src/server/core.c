/**-----------------------------------------------------------------------*
 * Amaze mini-game server
 *
 * Copyright (C) 2026 @kcraft059 - GPL v3
 *-----------------------------------------------------------------------**/

#include <errno.h>
#include <fcntl.h>
#include <sys/fcntl.h>
#include <time.h>

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
    panicErrorf(errno, "Getting server socket flags");

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

void addServerSockQueue(int queue_fd, int server_sock_fd) {
#ifdef __linux__
#error "Not implemented yet"
#elif defined(__APPLE__)
  struct kevent changes[1] = {{
      .flags = EV_ADD,
      .ident = server_sock_fd,
      .filter = EVFILT_READ, /* Sockets	which  have  previously	been passed to
                               listen(2) return	when there is an incoming con-
                               nection pending.	 data contains the size	of the
                               listen backlog. */
  }};

  int result = kevent(queue_fd, changes, 1, NULL, 0, NULL); // Add server_sock to the queue
  if (result == -1)
    panicErrorf(errno, "Adding server socket to queue");
  printLogf("Added to queue_fd");
#endif
}
