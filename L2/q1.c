#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	int x = 100;
	int rc = fork();

	if (rc < 0) { // fork failed; exit
		fprintf(stderr, "fork failed\n");
		exit(1);
	} else if (rc == 0) { // child process
		printf("Child x before change: %d\n", x);
		x = 200;
		printf("Child x after change: %d\n", x);
	} else { // parent process
		printf("Parent x before change: %d\n", x);
		x = 300;
		printf("Parent x after change: %d\n", x);
	}
	return 0;
}
