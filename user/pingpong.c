
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
	// create pipe
	// since pipe is single direction, we need two pipes
	int p2c[2];
	int c2p[2];
	char msg[4];
	pipe(p2c);
	pipe(c2p);

	int pid = fork();
	if (pid > 0){
		close(p2c[0]);
		close(c2p[1]);
		write(p2c[1], "ping", 4);
		read(c2p[0], msg, 4);
		printf("%d: received %s\n",getpid(), msg);
		close(c2p[0]);
		close(p2c[1]);
		//pid = wait((int* )0);
	}
	else if(pid == 0){
		close(p2c[1]);
		close(c2p[0]);
		read(p2c[0], msg, 4);
		printf("%d: received %s\n",getpid(), msg);
		write(c2p[1], "pong", 4);
		close(c2p[1]);
		close(p2c[0]);
		exit(0);
	}
	else{
		printf("fork error\n");
	}

    exit(0);
}
