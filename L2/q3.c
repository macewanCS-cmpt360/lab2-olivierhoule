/* SPDX-License-Identifier: GPL-2.0-or-later
 *
 * This will print "hello" and then "goodbye", but it technically isn't
 * guaranteed to be in this order. If the child takes more than 1 second to
 * print hello, the parent will end up printing first. Using wait() is the
 * ideal way to ensure the print order.
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
		printf("hello\n");
	} else { // parent process
		sleep(1);
		printf("goodbye\n");
	}
	return 0;
}
