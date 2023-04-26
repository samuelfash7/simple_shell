#ifndef SHELL_H
#define SHELL_H
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

int interactive(info_t *info)
int is_delim(char c, char *delim)
int _isalpha(int c)
int _atoi(char *s)
int main(void)


#endif

