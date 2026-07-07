/**-----------------------------------------------------------------------*
 * Amaze mini-game server
 *
 * Copyright (C) 2026 @kcraft059 - GPL v3
 *-----------------------------------------------------------------------**/

#include <errno.h>

#include <arpa/inet.h>
#include <sys/socket.h>

#include <acp/acp.h>
#include <misc/log.h>
#include <server/core.h>

int initServerSocket(int port) {
  int server_sock, result;
  server_sock = socket(AF_INET, SOCK_STREAM, 0); // Initiate TCP ipv4 connection

  if (server_sock < 0)
    panicErrorf(errno, "Opening server socket");

  struct sockaddr_in sock_addr = {
      .sin_family = AF_INET,         // Set type to TCP
      .sin_port = htons(port),       // Configure port
      .sin_addr.s_addr = INADDR_ANY, // Configure adress
  };

  result = bind(server_sock, (struct sockaddr*)&sock_addr, sizeof(sock_addr)); // Bind port to adress

  if (result != OK)
    panicErrorf(errno, "Binding server socket to port");

  return server_sock;
}
