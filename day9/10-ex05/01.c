#include<signal.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>

int num = 0;

int main(){
	static struct sigaction act;

	void int_handle(int);

	act.sa_handler = int_handle;
	sigfillset(&(act.sa_mask));
	sigaction(SIGINT, &act, NULL);

}

void int_handle(int signum){
	//printf("SIGINT : %d\n", signum);
	//printf("int_handle called %d times\n", ++num);
	
	char buf[1024] = "exit";
	int fd;

	fd = open("a.txt", O_CREAT | O_EXCL, 0644);
	write(fd, buf, 1024);

	
}
