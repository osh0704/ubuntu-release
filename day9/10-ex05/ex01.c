#include<signal.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int num = 0;
int flag = 1;

int main(){
	static struct sigaction act;

	void int_handle(int);

	act.sa_handler = int_handle;
	sigfillset(&(act.sa_mask));
	sigaction(SIGINT, &act, NULL);

	while(flag){
		printf("i'm sleepy..\n");
		sleep(1);
		if(num >= 3)
			exit(0);
	}
}

void int_handle(int signum){
//	printf("SI.GINT : %d\n", signum);
//	printf("int_handle called %d times\n", ++num);

	char buf[] = "exit\n";
	itn fd = open("a.txt", O_CREAT | O_EXCL, 0644);
	write(fd, buf, strlen(buf));

	close(fd);
	flag = 0;
}
