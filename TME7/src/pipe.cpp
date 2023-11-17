#include <cstring>
#include <unistd.h>
#include <cstdlib>

using namespace std;

int main(int argc, char ** argv){

    int fd[2];
    pipe(fd);
    
    char ** argv1 = (char **) malloc (sizeof(char*)*(argc-1));
    char ** argv2 = (char **) malloc (sizeof(char*)*(argc-1));

    for (int sz = 0; sz < argc - 1; ++sz){
        argv1[sz] = argv2[sz] = NULL;
    }


    int i = 1;
    while (strcmp("|", argv[i])!=0){
        argv1[i-1] = strdup(argv[i]);
        ++i;
    }

    argv1[++i] = NULL;

    int j = 0;
    while (argv[i]!= NULL){
        argv2[j] = strdup(argv[i]);
        ++i;
        ++j;
    }

    argv2[++i] = NULL;
  
    if (fork()==0){
        close(fd[0]);
        dup2(fd[1],1 );
        execv(argv1[0], argv1);
    }
    else if (fork()==0){
        close(fd[1]);
        dup2(fd[0],0);
        execv(argv2[0], argv2);
    }


    for (int sz = 0; sz < argc - 1; ++sz){
        if (argv1[sz] == NULL) break;
        free(argv1[sz]);
    } 

    for (int sz = 0; sz < argc - 1; ++sz){
        if (argv2[sz] == NULL) break;
        free(argv2[sz]);
    } 

    free(argv1);
    free(argv2);
    
    return 0;
}