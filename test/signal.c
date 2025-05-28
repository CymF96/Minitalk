#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

int main(int ac, char **av)
{
	int pid = fork();
	if (pid == -1)
		return 1;
	if (pid == 0)
	{
		while (1)
		{
			printf("Hello\n");
			usleep(50000);
		}
	}
	else
	{
		sleep(1);
		kill(pid,SIGKILL);
		wait(NULL);
	}
	return 0;
}
