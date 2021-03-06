// SPDX-License-Identifier: GPL-2.0-or-later
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(void)
{
	char *cmdline;
	char *token = NULL;
	int i, rc, bg;
	char *args[10];
	int *status;

	while (1) {
		cmdline = calloc(1, 1024);
		i = 0;
		bg = 0;

		printf("prompt> ");
		fgets(cmdline, 1024, stdin);
		//fprintf(stderr, "[debug] cmdline = *%s*\n", cmdline);

		token = strtok(cmdline, "\n ");

		free(cmdline);
		while (token != NULL) {
			//printf("%s\n", token);
			args[i++] = strdup(token);
			token = strtok(NULL, "\n ");
		}
		args[i] = NULL;

		// If last argument is &, don't wait and get rid of argument
		if (strcmp(args[i-1], "&") == 0) {
			args[i-1] = NULL;
			bg = 1;
		}
		rc = fork();

		if (rc < 0) { // fork failed; exit
			fprintf(stderr, "fork failed\n");
			exit(1);
		} else if (rc == 0) { // child
			execvp(args[0], args);
		} else { // parent
			if (!bg)
				waitpid(rc, &status, 0);
		}
	}
	return 0;
}
