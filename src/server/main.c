/**-----------------------------------------------------------------------*
 * Amaze mini-game server
 *
 * Copyright (C) 2026 @kcraft059 - GPL v3
 *-----------------------------------------------------------------------**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
  error_code err;

  err = evalArgsContext(argv, args);
  if (err != OK) exit(err);

  int server_sock_fd = socket(AF_INET, SOCK_STREAM, 0);

  if (server_sock_fd < 0) {
    perror("Opening socket");
    exit(errno);
  }

  struct sockaddr_in sock_addr = {
      .sin_family = AF_INET,
      .sin_port = htons(ACP_DEFAULT_PORT),
      .sin_addr.s_addr = INADDR_ANY,
  };

  if (bind(server_sock_fd, (struct sockaddr*)&sock_addr, sizeof(sock_addr)) != 0) {
    perror("Binding socket");
    exit(errno);
  }

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
