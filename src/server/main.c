/**-----------------------------------------------------------------------*
 * Amaze mini-game server
 *
 * Copyright (C) 2026 @kcraft059 - GPL v3
 *-----------------------------------------------------------------------**/

#include "misc/log.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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
  int server_sock_fd;

  evalArgsContext(argv, argc, args);

  server_sock_fd = initServerSocket(port);

  listen(server_sock_fd, 4); // Listen to socket with max of 4 queued connections

  struct sockaddr_in client_addr;
  socklen_t client_addr_len = sizeof(client_addr);
  int client_sock_fd = accept(server_sock_fd, (struct sockaddr*)&client_addr, &client_addr_len);

  char* message = "Hello client !";

  send(client_sock_fd, message, strlen(message) + 1, 0);
  printf("Message sent.\n");

  close(client_sock_fd);
  close(server_sock_fd);
  return 0;
}

// Local functions

err argSetPort(char** argv, int* argc) {
  int val, pos;
  if (*argc < 1) return EINVLPRM; // Check if there's enough params

  int n = sscanf(argv[0], "%d%n", &val, &pos);
  if (n != 1 || pos != strlen(argv[0])) return EINVLPRM; // Fail if invalid input
  port = val & 0xffff; // Update port with mask

  *argc = 1; // Set number of params used
  return OK;
};
