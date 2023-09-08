#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>

int main(){
	int fildes;
	char pathname[] = "temp.txt";

	if((fildes = open(pathname, O_CREAT | O_RDWR | O_EXCL, 0644)) == -1 ){
		printf("file open error!\n");
		exit(1);
	}

	cloose(filedes);

}
