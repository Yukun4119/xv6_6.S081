#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void dealWithPrime(){
	int digit;
	int prime;
	int flag = 0;
	close(p[1]);
	int pid = fork();
	if(pid > 0){
		while(read(p[0], &digit, sizeof(digit)) != 0){
			if(flag == 0){
				printf("%d\n", digit);
				prime = digit;
				flag = 1;
			}
			if(digit % prime != 0){
				write(c2p[1], &digit, sizeof(digit));
			}
		}
	}
	else if(pid == 0){
		dealWithPrime();
	}
	else{
		printf("fork error\n");
	}
}

	int
main(int argc, char *argv[])
{
	if(argc != 1){
		fprintf(2, "usage: primes\n");
		exit(1);
	}
	int p[2];
	pipe(p);

	int pid = fork();
	if (pid > 0){
		// parent process: pass number to child process with pipe
		close(p[0]);
		for(int i = 2; i <= 35; ++i){
			write(p[1], &i, sizeof(i));
		}
		close(p[1]);
	}
	else if(pid == 0){
		// child process: filter and make a change to number recursively
		dealWithPrime();
	}
	else{
		printf("fork error\n");
	}
	exit(0);
}
