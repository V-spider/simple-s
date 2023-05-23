#include "shell.h"

/**
 * _getenv - getenv()
 * @str: string
 * Return: path
 */
char *_getenv(char *str)
{
	int i = 0;
	int len = _strlen(str);

	while (environ[i] != NULL)
	{
		if (_strncmp(environ[i], str, len) == 0 && environ[i][len] == '=')
		{
			return (&(environ[i][len + 1]));
		}
		i++;
	}
	return (NULL);
}
