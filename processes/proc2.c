#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/wait.h> 

void child_process() {
	int time;
	
	srand( getpid() );
	time = rand() % 5 + 1;
	printf("PID = %i PPID = %i SLEEP = %i\n", getpid(), getppid(), time);
	sleep( time );
	printf("PID = %i PPID = %i\n", getpid(), getppid());
	exit(0);
}

int main(int argc, char* argv[]) {
	int i, num, pid, result;
	
	if (argc != 2) {
		printf("usage: %s number_of_childs\n", argv[0]);
		return -1;
	}
	
	num = atoi(argv[1]);
	if (num < 1) {
		printf("%s: number_of_childs must be a positive number greater than 0\n", argv[0]);
		return -1;
	}
	
	for (i = 0; i < num; i++) {
		printf("PID = %i PPID = %i - i am going to create another process\n", getpid(), getppid());
		if ( (pid = fork()) < 0 ) {
			perror(argv[0]);
			exit(-1);
		} else if (pid == 0) {
			child_process();
		} else {
			//do nothing
		}
	}
	
	int rid;
	while (i > 0) {
		rid = wait(&result);
		printf("The process %i has ended\n", rid);
		i--;
	} 
	return 0;
}
