#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
int main(){
	pid_t pid;
	int res2, x, y;
	scanf("%d %d", &x, &y);
	pid = fork();

	if (pid > 0) { // parent process
		int res1 = 1;
		for(int i = 0; i < y; i++){
			res1 *= x;
		}	
		printf("x ^ y : %d\n", res1);
		
		wait(&res2);
		
		res2 = res2 >> 8;
		printf("final sum : %d\n", res1 + res2);
	}
	else if(pid == 0) { // child process
		sleep(1);
		int res = 0;
		for (int i = x; i <= y; i++){
			res += i;
		}
		printf("x ~ y sum : %d\n", res);
		exit(res);
	}
	else printf("fail to fork\n");

	printf("bye!\n");
}
