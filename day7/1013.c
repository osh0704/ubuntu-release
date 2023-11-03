#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<stdio.h>

int main()
{
	pid_t pid[100];

	for(int i = 0 ; i < 5; i++){
		pid[i] = fork();
		if(pid[i] == 0) break;
	}
		
	if(n == 5){
	       	for(int i = 0 ; i < 5; i++){
			waitpid(pid[i], &status, 0);
			printf("child %d - exit(%d)\n", pid[i], status);
		}
	}

	else if(n < 5){
		exit(1);
	}
	else printf("fail to fork\n");
	
	
}
