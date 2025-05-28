#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int ac, char **av)
{
	int fd[2];
	// read -- fd[0];
	// write -- fd[1];
	if (pipe(fd) == -1)
		printf("an error ocurred with opening a pipe\n");
	int id = fork();
	if (id == -1)
		return 4;
	if (id == 0)
	{
		close(fd[0]);
		int x;
		printf("Input number: ");
		scanf("%d", &x);
		if (write(fd[1], &x, sizeof(int)) == -1)
		{
			printf("Error ocurred while writing\n");
			return 2;
		}
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		int y;
		if (read(fd[0], &y, sizeof(int)) == -1)
		{
			printf("Error ocurred while writing\n");
			return 3;
		}
		close(fd[0]);
		printf("Got from child process %d\n", y);
	}
	return 0;
}
