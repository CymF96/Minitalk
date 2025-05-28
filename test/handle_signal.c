#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

void	handle_sigtstp(int sig)
{
	printf("stop not allowed\n");
}

void	handle_sigcont(int sig)
{
	printf("Input number: ");
	fflush(stdout);
}

int main()
{
	struct sigaction sa;
	sa.sa_handler = &handle_sigcont;
	sa.sa_flags = SA_RESTART;
	sigaction (SIGCONT, &sa, NULL);

	//signal(SIGSTP, &handle_sigtstp);
	//for protability reason, sigation() is better and strongly recommanded by man

	int x;

	printf("Input number: ");
	scanf("%d", &x);
	printf("Result of %d * 5 = %d\n", x, x * 5);

	return 0;
}
