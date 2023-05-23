#include "shell.h"

/**
 * main - Entry point of the program.
 * @ac: The number of command-line arguments.
 * @av: An array of command-line arguments.
 *
 * Return: 0 on success.
 */
int main(int ac __attribute__((unused)), char **av __attribute__((unused)))
{
	/*static char *cmd = NULL;*/
	char *__attribute__ ((unused)) cmd1;
	char *argv[MAX_ARGS];

	char *__attribute__ ((unused)) full_path;
	int __attribute__ ((unused)) num_arg;
	signal(SIGSEGV, handle_segfault);

	do {
		if (isatty(STDIN_FILENO))
			write(1, "$ ", 2);
		cmd = read_command();
		if (cmd == NULL)
			exit(EXIT_SUCCESS);
		if (cmd[0] == '\0' || (_strcmp(cmd, "\n") == 0))
			continue;

		remwspaces(cmd);
		tokenize(cmd, argv);
		if (cmd[0] == '\0')
			continue;
		if (_strcmp(argv[0], "exit") == 0)
		{
			free(cmd);
			_1exit(argv[1]);
		}

		if (process_command(argv) == 0)
		{
			free(cmd);
			continue;
		}
		else
			_exec(argv, av[0]);

		free(cmd);
		cmd = NULL;
	} while (1);

	return (0);
}

/**
 * wspace - check character space or tab
 * @s: character to be checked
 *
 * Return: 1 if successful or 0 if not.
 */

int wspace(char s)
{
	if (s == ' ' || s == '\t')
		return (1);

	return (0);
}

/**
 * remwspaces - remove white spaces
 * @s: string to be checked
 */

void remwspaces(char *s)
{
	int length = _strlen(s);
	int i = 0, j = length - 1, k;
	int l, count, m;

	if (s == NULL)
		return;

	while (i < length && wspace(s[i]))
	{
		i++;
	}
	while (j >= i && wspace(s[j]))
	{
		j--;
	}
	k = 0;
	while (i <= j)
	{
		s[k++] = s[i++];
	}
	s[k] = '\0';
	l = 0;
	count = 0;
	for (m = 0; m <= j; m++)
	{
		if (s[m] != ' ')
		{
			s[l++] = s[m];
			count = 0;
		}
		else if (count == 0)
		{
			s[l++] = s[m];
			count++;
		}
	}
	s[l] = '\0';
}

/**
 * read_command - Read user input from stdin.
 *
 * Return: Pointer to the input command string.
 */
char *read_command(void)
{
	char *cmd1 = _getline();

	signal(SIGINT, handle_sigint);
	return (cmd1);
}

/**
 * handle_sigint - Signal handler for SIGINT (Ctrl+C).
 * @signo: The signal number.
 */
void handle_sigint(int signo __attribute__((unused)))
{
	write(1, "\n", 1);
	if (cmd != NULL)
	{
		free(cmd);
		cmd = NULL;
	}
	exit(0);
}
