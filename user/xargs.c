#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

#define MAXLINE 1024

int
main(int argc, char *argv[])
{
    char line[MAXLINE];
    char* para[MAXARG];
    char* cmd = argv[1];
    int paraIdx = 0;
    for(int i = 1; i < argc; ++i){
      para[paraIdx++] = argv[i];
    }
    int n = read(0, line, MAXLINE);
    int pid = fork();
    if(pid > 0){  // parent process
      wait((int*) 0);
    }
    else{
      char* curArg = (char*) malloc(sizeof(line));
      int index = 0;
      for(int i =0 ; i < n; ++i){
        if(line[i] == ' ' || line[i] == '\n'){
          curArg[index] = 0;
          para[paraIdx++] = curArg;
          curArg =  (char*) malloc(sizeof(line));
          index = 0;
        }
        else{
          curArg[index++] = line[i];
        }
      }
      curArg[index] = 0;
      para[paraIdx] = 0;
      exec(cmd, para);
    }
    exit(0);
}

