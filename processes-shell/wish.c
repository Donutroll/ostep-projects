#include "wish.h"
#include <string.h>

ptree *parser(token *input, int size) { return NULL; }

int lexer(token *dest, char *input) {
  char *str = NULL;
  int size = 0;
  while ((str = strsep(&input, " ")) != NULL) {
    if (strcmp(str, "\0") == 0)
      continue;
    else {
      dest[size] = (token){NULL, NULL, strlen(str), str};
      ++size;
    }
  }

  return size;
}

void executor(ptree *p, char *path) { return; }
