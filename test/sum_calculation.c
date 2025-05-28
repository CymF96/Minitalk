#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int ac, char **av)
{
	int arr[] = {1,2,3,6,8,45};
	int arrSize = sizeof(arr)/sizeof(int);
	int fd[2];
	int start, end;
	if (pipe(fd) == -1)
	{
		printf("Error generating the pipe\n");
		return 3; 
	}
	int id = fork();
	if (id == -1)
	{
		printf("Error generating the fork\n");
		return 4;
	}
	if (id == 0)
	{
		start = 0;
		end = start + arrSize / 2;
	}
	else
	{
		start = arrSize / 2;
		end = arrSize;
	}
	int sum = 0;
	for (int i = start; i < end; i++){
		sum += arr[i];
	}
	printf("Calculated partial sum: %d from id: %d\n", sum, getpid());
	if (id == 0)
	{
		close(fd[0]);
		write(fd[1], &sum, sizeof(sum));
		close(fd[1]);
	}
	else
	{
		int sumOfChild;
		close(fd[1]);
		read(fd[0], &sumOfChild, sizeof(sumOfChild));
		close(fd[0]);

		int totalSum = sum + sumOfChild; 
		printf("Total sum: %d, from id: %d\n", totalSum, getpid());
		wait(NULL);
	}
	return 0;
}
