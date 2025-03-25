#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0
#define PORT 8181

int main() {
  int s, c;
  socklen_t addr_len;
  struct sockaddr_in srv, cli;
  char buff[256];
  char *data;

  addr_len = 0;

  memset(&srv, 0, sizeof(srv));
  memset(&cli, 0, sizeof(cli));
  s = socket(AF_INET, SOCK_STREAM, 0);

  if (s < 0) {
    printf("socker failed\n");
    return EXIT_FAILURE;
  }

  srv.sin_family = AF_INET;
  srv.sin_addr.s_addr = 0;
  srv.sin_port = htons(PORT);

  if (bind(s, (struct sockaddr *)&srv, sizeof(srv))) {
    printf("bind()\n");
    close(s);
    return EXIT_FAILURE;
  }

  if (listen(s, 5)) {
    printf("listen() failed\n");
    close(s);
    return EXIT_FAILURE;
  }
  printf("Listening on 0.0.0.0:%d \n", PORT);

  c = accept(s, (struct sockaddr *)&srv, &addr_len);

  if (c < 0) {
    printf("accept() failed\n");
    return EXIT_FAILURE;
  }

  printf("Client connected.\n");

  data = "http v1.0\n";
  read(c, buff, 255);
  write(c, data, strlen(data));

  close(c);
  close(s);

  return EXIT_SUCCESS;
}
