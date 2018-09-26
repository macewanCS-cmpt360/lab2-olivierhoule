// SPDX-License-Identifier: GPL-2.0-or-later

/*
 * The value of the variable in the child process is the same value as in the
 * parent process: 100. When both processes change the value, they each have
 * their own "version" of the variable, so when the child changes the value to
 * 200, it remains at 200 for the rest of the process, and when the parent
 * changes it to 300, it stays at 300 for the parent.
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
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
	printf("x value: %d\n", x);
	return 0;
}
