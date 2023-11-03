#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<stdio.h>

int main()
{
	pid_t pid1, pid2;
	int status, x, y;
	scanf("%d %d", &x, &y);
	pid1 = pid2 = -1;

	pid1 = fork();
	if(pid1 > 0) pid2 = fork();

	if(pid1 > 0 && pid2 > 0){ // parent process
		int p_res = 1, c1_res, c2_res;
		for(int i = 0; i < y; i++){
			p_res *= x; 
		}	
		printf("x ^ y : %d\n", p_res);
		
		waitpid(pid1, &c1_res, 0);
		waitpid(pid2, &c2_res, 0);
		
		c1_res = c1_res >> 8;
		c2_res = c2_res >> 8;

		printf("final res : %d\n", c2_res - c1_res - p_res); 
	}

	else if(pid1 == 0 && pid2 == -1){
		sleep(1);
		int res = 0;
		for(int i = x; i <= y; i++) {
			res += i;
		}
		printf("x ~ y sum : %d\n", res);

		exit(res);
	}
	else if(pid1 > 0 && pid2 == 0){
		sleep(2);
		int res = 1;
		for(int i = x; i <= y; i++){
			res *= i;
		}
		printf("x ~ y mul : %d\n", res);

		exit(res);
	}
	else printf("fail to fork\n");
}
