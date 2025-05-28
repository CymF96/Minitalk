#include <stdio.h> 
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

int main(int ac, char **av)
{
	int arr[5];
	srand(time(NULL));
	int fd = open("sum", O_RDONLY);
	if (fd == -1)
	{
		printf("Error reading file\n");
		return 1;
	}
	for (int i = 0; i < 5; i++){
		if (read(fd, &arr[i], sizeof(int)) == -1)
			return 2;
		printf("received  %d\n", arr[i]);
	}

	close (fd);
	return 0;

}

