#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGS_LENGTH 10

/**
 * main - Simple Shell
 *
 * Description: Display a prompt and wait for the user to type a command.
 * A command line always ends with a new line.
 * The prompt is displayed again each time a command has been executed.
 * The command lines are simple, no semicolons, no pipes, no redirections
 * or any other advanced features.
 * The command lines are made only of one word. No arguments will be passed
 * to programs.
 * If an executable cannot be found, print an error message and display
 * the prompt again.
 * Handle errors.
 * You have to handle the “end of file” condition (Ctrl+D)
 *
 * Return: 0 on success, otherwise 1
 */
int main(void)
{
	char command[MAX_COMMAND_LENGTH];
	char *args[MAX_ARGS_LENGTH];
	int status, i;

	while (1)
	{
		if (write(STDOUT_FILENO, "$ ", 2) == -1)
		{
			perror("write");
			return (1);
		}

		if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
		{
			if (feof(stdin))
			{
				if (write(STDOUT_FILENO, "\n", 1) == -1)
				{
					perror("write");
					return (1);
				}
				exit(EXIT_SUCCESS);
			}
			else
			{
				perror("fgets");
				return (1);
			}
		}
		char *token = strtok(command, " ");
		i = 0;
		while (token != NULL)
		{
			args[i++] = token;
			token = strtok(NULL, " ");
		}
		args[i] = NULL;
		pid_t pid = fork();

		if (pid < 0)
		{
			perror("fork");
			return (1);
		}

		else if (pid == 0)
		{
			char *path = getcwd(NULL, 0);

			strcat(path, "/");
			strcat(path, args[0]);
			if (access(path, X_OK) != 0)
			{
				perror(args[0]);
				exit(EXIT_FAILURE);
			}

			execve(path, args, NULL);
			perror("execve");
			exit(EXIT_FAILURE);
		}

		else
		{
			waitpid(pid, &status, 0);
		}
	}
	return (0);
}
