#include "wish.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

const char *bin = "/usr/bin";
token buffer[1024];

int main(int argc, char **argv) {

  char *input = NULL;
  size_t len = 0;
  int nread = 0;
  FILE *stream = stdin;
  char *path = malloc(strlen(bin) + 1);
  path = strncpy(path, bin, strlen(bin) + 1);
  printf("%s \n", path);

  if (argc > 1) {
    stream = fopen(argv[1], "r");
    if (stream == NULL) {
      printf("cannot find %s", argv[1]);
      exit(1);
    }
  }

  printf("wish> ");

  while (true) {
    if ((nread = getline(&input, &len, stdin) != -1)) {
      int size = lexer(buffer, input);
      for (int i = 0; i < size; ++i)
        printf("%s ", buffer[i].str);

      printf("wish> ");
    }
  }

  free(path);
  return 0;
}
