#include "shell.h"

/**
 * print_list - Print the contents of the linked list.
 * @head: The head of the linked list.
 */
void print_list(struct Node *head)
{
	while (head != NULL)
	{
		write(STDOUT_FILENO, head->str, _strlen(head->str));
		write(STDOUT_FILENO, "\n", 1);
		head = head->next;
	}
}

/**
 * free_list - Free up memory allocated for each node in the linked list.
 * @head: The head of the linked list.
 */
void free_list(struct Node *head)
{
	struct Node *temp;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp);
	}
}

/**
 * _env - Print the environment variables.
 *
 * Return: Always 0.
 */
int _env(void)
{
	char **env;
	struct Node *head = NULL;

	for (env = environ; *env != NULL; env++)
	{
		add_node(&head, new_node(*env));
	}

	print_list(head);

	free_list(head);
	return (0);
}

/**
 * _setenv - Set an environment variable.
 * @name: The name of the environment variable.
 * @value: The value to be set.
 *
 * Return: Always 0.
 */
int _setenv(const char *name, const char *value)
{
	char **env;
	struct Node *head = NULL;
	/*extern char **environ;*/

	for (env = environ; *env != NULL; env++)
	{
		add_node(&head, new_node(*env));
	}

	add_env_var(&head, name, value);

	update_environ(head);

	free_list(head);
	return (0);
}

/**
 * _unsetenv - Delete an environment variable.
 * @name: The name of the environment variable to be deleted.
 *
 * Return: 0 on success, -1 on failure.
 */
int _unsetenv(const char *name)
{
	char **e;
	char **env;
	size_t len = _strlen(name);

	for (env = environ; *env != NULL; env++)
	{
		if (_strncmp(*env, name, len) == 0 && (*env)[len] == '=')
		{
			for (e = env; *e != NULL; e++)
			{
				*e = *(e + 1);
			}
			return (0);
		}
	}

	return (-1);
}
