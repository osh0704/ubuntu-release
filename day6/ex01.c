#include<unistd.h>

int main(){
	execlp("ls", "ls", "-l", "linux2/", (char *)0);
}
