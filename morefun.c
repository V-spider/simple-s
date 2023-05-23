#include "shell.h"
/**
 * add_env_var - Add a new environment variable to the linked list.
 * @head: A pointer to the head of the linked list.
 * @name: The name of the environment variable.
 * @value: The value of the environment variable.
 */
void add_env_var(struct Node **head, const char *name, const char *value)
{
	size_t name_l = _strlen(name);
	size_t value_len = _strlen(value);
	char *new_env_var = malloc(name_l + value_len + 2);
	struct Node *current = *head;

	if (new_env_var == NULL)
	{
		return;
	}

	_memcpy(new_env_var, (void *)name, name_l);
	new_env_var[name_l] = '=';
	_memcpy(new_env_var + name_l + 1, (void *)value, value_len);
	new_env_var[name_l + value_len + 1] = '\0';

	while (current != NULL)
	{
		if (_strncmp(current->str, name, name_l) == 0 && current->str[name_l] == '=')
		{
			free(current->str);
			current->str = new_env_var;
			return;
		}
		current = current->next;
	}

	add_node(head, new_node(new_env_var));
}

/**
 * update_environ - Update the environ variable with the linked list contents.
 * @head: The head of the linked list.
 */
void update_environ(struct Node *head)
{
	size_t count = 0;
	size_t i;
	struct Node *current = head;
	char **new_environ;

	while (current != NULL)
	{
		count++;
		current = current->next;
	}

	new_environ = malloc((count + 1) * sizeof(char *));
	if (new_environ == NULL)
	{
		return;
	}

	current = head;
	for (i = 0; i < count; i++)
	{
		new_environ[i] = current->str;
		current = current->next;
	}
	new_environ[count] = NULL;

	environ = new_environ;
}
