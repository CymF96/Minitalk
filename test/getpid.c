#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main(int ac, char **av)
{
	int id1 = fork();
	int id2 = fork();
	if (id1 == 0)
	{
		if (id2 == 0)
			printf("We are process y, our current id is: %d and our parent id is: %d\n", getpid(), getppid());
		else
			printf("We are process x, our current id is: %d and our parent id is: %d\n", getpid(), getppid());
	}
	else
	{
		if (id2 == 0)
			printf("We are process z, our current id is: %d and our parent id is: %d\n", getpid(), getppid());
		else
			printf("We are the parent process, our current id is: %d and our parent id is: %d\n", getpid(), getppid());
	}
	while (wait(NULL) != -1 || errno != ECHILD);
		printf("Waiting for child %d to finish\n", getpid());
/*
	printf("current id: %d, parent ID: %d\n", getpid(), getppid());
	int res = wait(NULL);
	if (res == -1)
		printf("NO children to wait for\n");
	else
		printf("%d finished execution\n", res);		
*/	return 0;
}
