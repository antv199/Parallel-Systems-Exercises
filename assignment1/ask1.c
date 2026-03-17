#include <stdio.h>
#include <unistd.h>

int main()
{
	pid_t chid1 = fork();
	pid_t chid2 = fork();
	printf("hello from process %d\n", getpid());
}