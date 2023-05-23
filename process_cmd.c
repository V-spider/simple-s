#include "shell.h"

/**
 * process_command - Process the command and execute corresponding actions.
 * @argv: Array of strings where argv[0] is the command.
 *
 * Return: 0 on success, 1 if the command was unsuccessful.
 */
int process_command(char **argv)
{
	int num_arg = num_args(argv);

	if (_strcmp(argv[0], "cd") == 0)
	{
		if (num_arg >= 1)
		{
			cd(argv[1]);
			return (0);
		}
	}
	if (_strcmp(argv[0], "env") == 0)
	{
		_env();
		return (0);
	}
	if (_strcmp(argv[0], "setenv") == 0)
	{
		if (num_arg == 3)
		{
			_setenv(argv[1], argv[2]);
			return (0);
		}
	}
	if (_strcmp(argv[0], "unsetenv") == 0)
	{
		if (num_arg == 2)
		{
			_unsetenv(argv[1]);
			return (0);
		}
	}
	if (alias_command(argv, num_arg))
	{
		return (0);
	}
	return (1);
}
