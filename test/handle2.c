#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

/*
Problem: question to be asked to user. If they can more than 5 secondes to answer
they will get a hint from the program.
*/

int y = 0;
int x = 5;

void	handle_sigusr1(int sig)
{
	if (y == 0)
		printf("(HINT) You can repete the multiplication\n");
}

int main()
{
	int pid = fork();
	if (pid == -1)
		return 1;

	if (pid == 0)
	{
		//child process
		sleep(5);
		//after 5s, send signal to parent to print something
		kill(getppid(), SIGUSR1); //send custom signal for user used only SIGUSR1//SIGUSR2
	}
	else
	{
		//parent process
		struct sigaction sa = {0};
		sa.sa_flags = SA_RESTART;
		sa.sa_handler = &handle_sigusr1;
		sigaction(SIGUSR1, &sa, NULL);
		printf("what is the result of %d * 5?\n", x = 5);
		scanf("%d", &y);
		if (x * 5 == y)
			printf("right\n");
		else
			printf("Wrong\n");
		wait(NULL);
	}
	return 0;
}
