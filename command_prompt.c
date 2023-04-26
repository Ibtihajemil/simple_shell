#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define BUFFER_SIZE 1024
int main(void)
{
	char *buffer;
	size_t bufsize = BUFFER_SIZE;
	ssize_t nread;
	char *args[2], *path = "/bin/", *command;

	buffer = (char *)malloc(bufsize * sizeof(char));
	if (buffer == NULL)
	{
		perror("Unable to allocate buffer");
		exit(1);
	}

	while (1)
	{
		printf("$ ");
		nread = getline(&buffer, &bufsize, stdin);
		if (nread == -1)
		{
			break;
		}
		command = buffer;
		command[nread - 1] = '0';
		args[0] = command;
		args[1] = NULL;
		pid_t pid = fork();

		if (pid == -1)
		{
			perror("Unable to fork");
			exit(1);
		}
		if (pid == 0)
		{
		execve(strcat(path, command), args, NULL);
			perror("Unable to execute command");
			exit(1);
		}
		else
		{
			wait(NULL);
		}
	}
	free(buffer);
	return (0);
}
