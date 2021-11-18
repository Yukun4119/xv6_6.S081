
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    if(argc != 1){
        fprintf(2, "usage: pingpong\n");
        exit(1);
    }
	int pid = fork();
	if (pid > 0){
		pid = wait((int* )0);
		printf("%d: received pong\n",getpid());
	}
	else if(pid == 0){
		printf("%d: received ping\n",getpid());
		exit(0);
	}
	else{
		printf("fork error\n");
	}

    exit(0);
}
