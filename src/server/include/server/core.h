/**-----------------------------------------------------------------------*
 * Amaze mini-game server
 *
 * Copyright (C) 2026 @kcraft059 - GPL v3
 *-----------------------------------------------------------------------**/

#ifndef _SERVER_CORE_H
#define _SERVER_CORE_H

#if !defined(__linux__) && !defined(__APPLE__)
#error "Platform not supported"
#endif

#define MAX_QUEUED_CLIENTS 10

int initServerSocket(int port);
int initQueue();

void addServerSockQueue(int queue_fd, int server_sock_fd);
void handleQueue();

#endif // _SERVER_CORE_H
