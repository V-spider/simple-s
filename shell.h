#ifndef SHELL_H
#define SHELL_H

/* Headers */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <stddef.h>
#include <sys/wait.h>
#include <signal.h>

/* Macros */
#define BUFFER_SIZE 1024
#define MAX_ARGS 1024
#define MAX_NUM_Aliases 100
#define UNUSED  __attribute__((unused))

static char *cmd __attribute__((unused));
extern char **environ UNUSED;

/* Function Prototypes */
char *_getline(void);
char *read_command(void);
void hash_handler(char *buff);
int _strcmp(const char *str1, const char *str2);
int _strlen(const char *str);
int _strncpy(char *dest, char *src, int size);
void *_memcpy(void *dest, void *src, size_t n);
void *_realloc(void *ptr, size_t size);
char *which(char *command);
char *_strtok(char *str, char const *delim);
char *_getenv(char *str);
int _strncmp(const char *str1, const char *str2, size_t len);
int _strcpy(char *dest, char *src);
char *_strcat(char *dest, const char *src);
char *_strdup(char *s);
void remove_trailing_and_leading_spaces(char *str);
void tokenize(char *command, char *argv[MAX_ARGS]);
int num_args(char *argv[]);
void _exec(char **_argum, char *av);
void _1exit(char *status __attribute__((unused)));
int _atoi(const char *str);
int cd(char *path);
int process_command(char **argv);
/**
* struct alias_s - alias structure
* @name: name of alias
* @alias_cmd: command of alias
*/
typedef struct alias_s
{
	char *name;
	char *alias_cmd;
} alias_t;

int alias_command(char *argv[MAX_ARGS], int num_arg);

/**
* struct Node - singly linked list
* @str: string - (malloc'ed string)
* @next: points to the next node
*/
struct Node
{
	char *str;
	struct Node *next;
};

static struct Node *new_node(char *str) UNUSED;
/**
 * new_node - Creates a new node for a linked list
 * @str: String value to be stored in the new node
 * Return: Pointer to the newly created node
 */
static struct Node *new_node(char *str)
{
	struct Node *node = malloc(sizeof(struct Node));

	if (node == NULL)
		return (NULL);

	node->str = str;
	node->next = NULL;
	return (node);
}

static void add_node(struct Node **head, struct Node *node) UNUSED;
/**
 * add_node - Adds a node to the end of a linked list
 * @head: Pointer to the head of the linked list
 * @node: Node to be added to the linked list
 */
static void add_node(struct Node **head, struct Node *node)
{
	if (*head == NULL)
		*head = node;
	else
	{
		struct Node *current = *head;

		while (current->next != NULL)
			current = current->next;
		current->next = node;
	}
}

void print_list(struct Node *head);
void free_list(struct Node *head);
int _env(void);
int _unsetenv(const char *name);
int _setenv(const char *name, const char *value);
void add_env_var(struct Node **head, const char *name, const char *value);
void update_environ(struct Node *head);
void handle_segfault(int signo __attribute__((unused)));
void handle_sigint(int signo __attribute__((unused)));
void alias_name(alias_t alias);
void remwspaces(char *s);
int wspace(char s);
#endif /* SHELL_H */
