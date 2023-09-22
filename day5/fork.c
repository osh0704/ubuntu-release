#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>

pid_t fork(void);

int main(){
	pid_t pid;
	int i = 1;

	pid = fork();

	if(pid > 0) { // parent process 
		printf("%d\n", i++);
	}

	else if(pid == 0) { // child process
		printf("%d\n", i--);
	}
	else printf("fork fail\n");
}


