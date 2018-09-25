/*
 * When printf is called, nothing is output to the shell because stdout is
 * closed.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	int rc = fork();

	if (rc < 0) { // fork failed; exit
		fprintf(stderr, "fork failed\n");
		exit(1);
	} else if (rc == 0) { // child process
		close(STDOUT_FILENO);
		printf("hello\n");
	} else { // parent process
		wait(NULL);
	}
	return 0;
}
