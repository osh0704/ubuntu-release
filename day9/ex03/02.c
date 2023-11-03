#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

extern char **environ;

int main(){
	printf("MYDATA=%s\n", getenv("MYDATA"));
	while(*environ)
		printf("%s\n", *environ++);
}
