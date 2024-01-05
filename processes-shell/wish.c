
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define MAXBUF 1024


//char **getargv(char *input, char **argv, int *argc, int start) {

    //int i = start;
    //int sz = 0;
    //for (; input[i] != '\0' && input[i] != ' ' && input[i] != '\n'; ++i) {
        //printf("%c", input[i]);
    //}
    
    //switch (input[i])
    //{
    //case '\0':
        //argv = calloc(*argc, sizeof(char*)); 
        //return argv;
        //break;
    //case ' ':
    //case '\n':
        //(*argc)++;
        //argv = getargv(input, argv, argc, i + 1);
        //break;
    //default:
        //printf("something went wrong!!!");
        //break;
    //}

    //printf("%d %d %d \n", i, *argc, start);
    //if ( (i-start) > 0) {
        //input[i] = '\0';
        //argv[*argc - 1] = (char *)(input + start);
        //printf("%p \n", (void *)input);
        //printf("%p \n", (void *)(input + start));
        //printf("%d %d %s \n",*argc, start, argv[*argc - 1]);
    //}

    //return argv;

//}  
char *newPath(char **argv, int argc) {

    int size = 0;   
    for (int i = 1; argv[i] != NULL; ++i)
        size += strlen(argv[i]) + 1;
    
    char *path = malloc(size + 1);
    path[0] = '\0';
    for (int i = 1; argv[i] != NULL; ++i) {
        strcat(path, argv[i]);
        strcat(path, ":");
    }
    printf("%s", path);

    return path;

}

char **getargs(char *input, int *sz) {
    int argc = 1;
    int i = 0;
    for (; input[i] != '\0'; ++i) {
        if (isspace(input[i]) > 0 ) {
            input[i] = '\0';
            if (isspace(input[i + 1]) == 0 && input[i + 1] != '\0') {
            argc++;
            }
        }
    }

    char **argv = calloc(argc + 1, sizeof(char *));
    int n = 0;
    bool w = false;
    for (int j = 0; n < argc && j < i; ++j) {
       if (input[j] != '\0' && w == false) {
           w = true;
           argv[n] = input + j;
           n++;
       }
       else if ( input[j] == '\0' && input[j + 1]  != '\0')
            w = false; 
    }

    *sz = argc;
    argv[argc] = NULL;
    return argv;
}

int main(int argc, char **argv) {

    printf("%d \n", getpid());
    char *input = NULL;
    size_t len = 0;
    int nread = 0;
    FILE *stream = stdin;
    const char *bin = "/usr/bin";
    char *path = malloc(strlen(bin) + 1);
    path = strncpy(path, bin, strlen(bin) + 1);
    printf("%s \n", path); 
    if(argc > 1) {
        stream = fopen(argv[1], "r");
        if (stream == NULL) {
            printf("cannot find %s", argv[1]);    
            exit(1);
        }
    }
    
   printf("wish> ");

   while(true) { 
    if ((nread = getline(&input, &len, stdin) != -1)) {
    
    int pid = fork();
        
    if (pid == 0) {
        printf("path: %s", path);
        int exargc = 0;
        char **exargv = getargs(input, &exargc);
        char *expath = malloc( strlen(path) + 1 + strlen(exargv[0]) + 1);
        char *ex = exargv[0];
        expath = strcpy(expath, path);
        expath = strcat(expath, "/");
        expath = strcat(expath, exargv[0]);
        exargv[0] = expath;
        
        if (strcmp(ex, "cd") == 0)
            chdir(exargv[1]);
        else if (strcmp(ex, "exit") == 0)
            exit(0);
        else if (strcmp(ex, "path") == 0) {
            free(path);
            path = newPath(exargv, exargc);
        } 
        else if (access(expath, X_OK) == -1) {
            printf("error! %s", expath);
            exit(1);
        }
        else {
            printf("executing %s \n", expath);
            execv(expath, exargv);
        }
    }
    else if (pid == -1) {
        printf("failed to create child!");
    }
    else if (pid > 0){
        int chstat = -1;
        if (wait(&chstat) == -1) {
            printf("error!");
            exit(1);
        }
    }
    printf("wish> ");
    }
   }    
    
    free(path);
    return 0;
}
