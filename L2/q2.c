/*
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int file = open("output.txt", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);

	if (file < 0) {
		fprintf(stderr, "file open failed\n");
		exit(2);
	}

	int rc = fork();

	if (rc < 0) { // fork failed; exit
		fprintf(stderr, "fork failed\n");
		exit(1);
	} else if (rc == 0) { // child process
		int cbytes = write(file, "This output is from the child\n", 30);
		printf("Child bytes written: %d\n", cbytes);
	} else { // parent process
		int pbytes = write(file, "This output is from the parent\n", 31);
		printf("Parent bytes written: %d\n", pbytes);
	}
	return 0;
}
