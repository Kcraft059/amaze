/**-----------------------------------------------------------------------*
 * Amaze mini-game server
 *
 * Copyright (C) 2026 @kcraft059 - GPL v3
 *-----------------------------------------------------------------------**/

#ifndef _SERVER_CORE_H
#define _SERVER_CORE_H

#include <time.h>

#if !defined(__linux__) && !defined(__APPLE__)
#error "Platform not supported"
#endif

#define MAX_QUEUED_CLIENTS 10

enum sock_type {
  T_SERVER_SOCK = 0,
  T_CLIENT_SOCK
};

enum sock_event {
  SEV_READ = 0,
  SEV_RESET
};

struct sock_context {
  enum sock_type type;
  int fd;
  void* data;
};

typedef void (*event_handler)(struct sock_context* sock_ctx, enum sock_event event);

int initServerSocket(int port);
int initQueue();

struct sock_context* addSockToQueue(int queue_fd, int sock_fd, enum sock_type type);
int closeSockCtx(struct sock_context* sock_ctx);

int handleSockEvents(int queue_fd, event_handler handler, int max_events, struct timespec* timeout);
#endif // _SERVER_CORE_H
