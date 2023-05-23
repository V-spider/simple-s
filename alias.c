#include "shell.h"

/**
 * alias_command - alias command
 * @argv: argument
 * @num_arg: number of arguments
 *
 * Return: 0 if successful
 */

int alias_command(char *argv[MAX_ARGS], int num_arg __attribute__((unused)))
{
	int i = 0;
	int num_aliases = 4;
	alias_t aliases[MAX_NUM_Aliases] = {
		{"l", "ls -CF"}, {"la", "ls -A"}, {"ll", "ls -alF"},
		{"ls", "ls --color=auto"}, {NULL, NULL}
	};
	if (_strcmp(argv[0], "alias") != 0 && num_arg > 2)
		return (0);
	if (_strcmp(argv[0], "alias") == 0 && num_arg == 1)
	{
		while (aliases[i].name != NULL)
		{
			alias_name(aliases[i]);
			i++;
		}
		return (1);
	}
	if (argv[1] != NULL)
	{
		if (_strcmp(argv[0], "alias") == 0)
		{
			int i;

			for (i = 0; i < num_aliases; i++)
			{
				if (_strcmp(argv[1], aliases[i].name) == 0)
				{
					alias_name(aliases[i]);
					return (1);
				}
			}
		}
		else
		{
			return (0);
		}
	}
		return (0);
}

/**
 * alias_name - prints alias details.
 * @alias: alias input
 */

void alias_name(alias_t alias)
{
	write(1, "alias ", 7);
	write(1, alias.name, _strlen(alias.name));
	write(1, "='", 2);
	write(1, alias.alias_cmd, _strlen(alias.alias_cmd));
	write(1, "'", 1);
	write(1, "\n", 1);
}
