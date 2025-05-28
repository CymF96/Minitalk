#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int ac, char **av)
{
	int id = fork();
	int n;
	if (id == 0)
		n = 1;
	else 
		n = 6;
	if (id != 0)
		wait(NULL);
	for (int i = n; i < n + 5; i++){
		printf("%d from id: %d\n", i, id);
		fflush(stdout);
	}
	
	return 0;
}
