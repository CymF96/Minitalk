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
	if (pid == 0) //this child is created and will exe his process 1st
	{
		while (1)
		{
			printf("Hello from %d, child of %d\n", getpid(), getppid());
			usleep(50000);
		}
	}
	else
	{
		kill(pid, SIGSTOP); // stop child so doesn't start anything before parent authorise
		int time; 
		do // do while loop to ask user how long the child execute his process before stopping
		{
			printf("Time parent %d ask child to wait before executing process: ", getpid());
			scanf("%ds", &time);
			if (time > 0) //avoid error as time = -1 --> sleep is unsigned so - is waiting for MAX_IT seconds!!!
			{
				kill(pid, SIGCONT);
				sleep(time);
				kill(pid, SIGSTOP);
			}
		} while (time > 0);
		kill(pid, SIGKILL);
		wait(NULL);
	}
	return 0;
}
