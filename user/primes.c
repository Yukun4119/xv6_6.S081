#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int
main(int argc, char *argv[])
{
  if(argc != 1){
    fprintf(2, "usage: primes\n");
    exit(1);
  }
  int number[34];
  int index = -1;
  for(int i = 2 ; i <= 35; ++i){
    number[++index] = i;
  }
  int p[2];
  while(index > -1){
    sleep(1);
    pipe(p);
    int pid = fork();
    if(pid > 0){
      close(p[0]);
      for(int i = 0 ; i <= index; ++i){
        write(p[1], &number[i], sizeof(number[i]));
      }
      close(p[1]);
      wait((int *)0);
      exit(0);
    }
    else if(pid == 0){
      close(p[1]);
      int tmp = 0;
      index = -1;
      int prime = 0;
      while(read(p[0], &tmp, sizeof(tmp)) != 0){
        if(index == -1){
          prime = tmp;
          printf("prime %d\n", prime);
          index++;
        }
        else{
          if(tmp % prime != 0){
            number[index++] = tmp;
          }
        }
      }
      close(p[0]);
    }
    else{
      printf("fork error\n");
      exit(0);
    }
  }
  exit(0);
}
