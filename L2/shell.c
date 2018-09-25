#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(void)
{
	while (1) {
		char *cmdline;
		char *token = NULL;
		int i, rc, bg;
		char *args[10];

		cmdline = calloc(1, 1024);
		i = 0;

		printf("prompt> ");
		fgets(cmdline, 1024, stdin);
		//fprintf(stderr, "[debug] cmdline = *%s*\n", cmdline);

		token = strtok(cmdline, "\n ");
		while (token != NULL) {
			printf("%s %d\n", token, i);
			args[i++] = strdup(token);
			token = strtok(NULL, "\n ");
		}
		args[i] = NULL;
		bg = 0;

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
			if (!bg) {
				wait(NULL);
			}
		}

		free(cmdline);
	}
}
