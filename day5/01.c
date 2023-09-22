#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main(){
	pid_t pid;
	int n;
	scanf("%d", &n);

	pid = fork();

	if(pid > 0){
		printf("1~%d sum : %d\n",n ,n * (n + 1)/2);
	}
	else if(pid == 0){
		int mul = 1;
		for(int i = 2; i<= n; i++) 
			mul *= i;
		printf("1~%d mul : %d\n", n , mul);
	}
	else printf("fork fail\n");
}
