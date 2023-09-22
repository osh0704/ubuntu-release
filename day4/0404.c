#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, char **argv)
{
	char *filename = "b.txt";

	if(access(argv[1], F_OK) == -1)
	{
		fprintf(stderr, " not file %s\n", filename);
	      	exit(1);	
	}

	printf("file exists\n", filename);
}
