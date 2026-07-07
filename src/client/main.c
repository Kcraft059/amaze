/**-----------------------------------------------------------------------*
 * Amaze mini-game client
 *
 * Copyright (C) 2026 @kcraft059 - GPL v3
 *-----------------------------------------------------------------------**/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <sys/errno.h>
#include <sys/socket.h>

#include <acp/acp.h>
#include <misc/misc.h>

const struct programArgument args[] = {
    {.name = NULL, .description = NULL, .func = NULL}, // Signify end of array
};

int main(int argc, char** argv) {
  err result = OK;

  evalArgsContext(argv, argc, args);

  int client_socket_fd = socket(AF_INET, SOCK_STREAM, 0); // Create new socket
  struct sockaddr_in server_addr = {
      .sin_family = AF_INET,
      .sin_port = htons(ACP_DEFAULT_PORT),
      .sin_addr.s_addr = htonl(INADDR_LOOPBACK),
  };
  result = connect(client_socket_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));

  if (result != 0) panicErrorf(errno, "Connecting to server");

  char buf[32];
  recv(client_socket_fd, buf, 32, 0);
  printf("Message received: %s\n", buf);
  close(client_socket_fd);
  return 0;
}
