#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, int **argv)
{
	char *filename = "test.txt";

	if(access(argv[1], R_OK) == -1)
	{
		fprintf(stderr, "User cannot read file %s\n", filename);
	      	exit(1);	
	}

	printf("%s readable, proceeding \n", filename);
}
