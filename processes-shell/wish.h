typedef struct token {
  struct token *left;
  struct token *right;
  int size;
  char *str;
} token;

typedef struct ptree {
  token *root;
  token tokens;
  int size;
} ptree;

ptree *parser(token *input, int size);

token tokenise(int id, char *args, token *left, token *right);

int lexer(token *dest, char *input);

void executor(ptree *p, char *path);
