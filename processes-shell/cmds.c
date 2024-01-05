#include <stdio.h>

int main(int argc, char **argv) {
    FILE *file = fopen("cat.txt", "r");

    if (file == NULL) {
        printf("file not found!!");
        return 1;
    }
    
    char s[256];
    while (fgets(s, 256, file) != NULL)
        printf("%s", s);

    return 0;
}