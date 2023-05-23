#include "shell.h"

/**
* remove_trailing_and_leading_spaces - remove trailing spaces from a string
* @str: string to remove trailing spaces from
*/
void remove_trailing_and_leading_spaces(char *str)
{
	size_t len = _strlen(str);
	size_t start = 0;
	size_t i;

	/* Remove trailing spaces */
	if (len > 0)
	{
		while (len > 0 && str[len - 1] == ' ')
			len--;
		str[len] = '\0';
	}

	/* Find the starting position after removing trailing spaces */
	while (str[start] == ' ')
		start++;

	/* Shift the string to remove leading spaces */
	if (start > 0)
	{
		i = 0;
		while (str[start + i] != '\0')
		{
			str[i] = str[start + i];
			i++;
		}
		str[i] = '\0';
	}
}

/**
* tokenize - tokenize a string into an array of tokens
* @command: string to tokenize
* @argv: array to store tokens
*/

void tokenize(char *command, char *argv[MAX_ARGS])
{
	char *token;
	int i = 0;

	token = _strtok(command, " ");
	while (token != NULL)
	{
		argv[i++] = token;
		token = _strtok(NULL, " ");
	}
	argv[i] = NULL;
}

/**
* num_args - count the number of arguments in an array of arguments
* @argv: array of arguments
*
* Return: number of arguments in argv
*/
int num_args(char *argv[])
{
	int i = 0;

	while (argv[i] != NULL)
		i++;
	return (i);
}

/**
* _atoi - convert a string to an integer
* @str: string to convert
*
* Return: integer value of str
*/
int _atoi(const char *str)
{
	int i, n = 0;
	int sign = 1;

	for (i = 0; str[i] != '\0'; i++)
		if (str[i] == '-')
			sign = -1;
		else if (str[i] >= '0' && str[i] <= '9')
			n = n * 10 + (str[i] - '0');
		else
			break;

	return (n * sign);
}

/**
* _1exit - exit with a status code
* @status: status code to exit with
*/
void _1exit(char *status __attribute__((unused)))
{
	int i;

	if (status)
	{
		i  = _atoi(status);
		exit(i);
	}
	exit(0);
}
