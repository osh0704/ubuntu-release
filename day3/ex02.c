#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>

int main(int argc, char *argv[]){
        int fd, nread, cnt, numChar = 0;
        char buffer[1024];

	if(argc < 2) return 0;
        
	if((fd == open(argv[1], O_RDONLY)) == -1){
		printf("file open error\n");
		return 0;
	}
        while((nread = read(fd, buffer, 1024)) > 0){
                
                for(cnt = 0; cnt < nread; cnt++){
			if((buffer[cnt] >= 'a' && buffer[cnt] <= 'Z') ||(buffer[cnt] >= 'A' && buffer[cnt] <= 'Z') )
				numChar++;
		}
        }
	printf("numChar = %d\n", numChar);
        close(fd);
}

