#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"

int verbose_mode = 0; // Global flag for verbose mode

void display_prompt() {
    char* username = getenv("USER");
    char* current_dir = getcwd(NULL, 0);

    printf("%s@%s$ ", username, current_dir);

    free(current_dir);
}

void execute_cd(char* arg) {
    if (arg == NULL) {
        fprintf(stderr, "cd: missing directory\n");
    } else {
        if (chdir(arg) != 0) {
            perror("cd");
        }
    }
}

void execute_ls(char* arg) {
    char* ls_args[] = { "/bin/ls", "-l", arg, NULL };

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        return;
    } else if (pid == 0) {
        // Child process
        if (execve("/bin/ls", ls_args, NULL) == -1) {
            perror("execve");
            exit(1);
        }
    } else {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
    }
}

void execute_pwd() {
    char* current_dir = getcwd(NULL, 0);
    printf("%s\n", current_dir);
    free(current_dir);
}

void execute_cat(char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("fopen");
        return;
    }

    char buffer[MAX_BUFFER_SIZE];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }

    fclose(file);
}

void execute_command(char* command) {
    char* arguments[MAX_ARGUMENTS];
    int arg_count = 0;

    char* token = strtok(command, " \n");
    while (token != NULL && arg_count < MAX_ARGUMENTS - 1) {
        arguments[arg_count] = token;
        token = strtok(NULL, " \n");
        arg_count++;
    }
    arguments[arg_count] = NULL;

    if (arg_count == 0) {
        return;  // Empty command, prompt again
    }

    if (strcmp(arguments[0], "cd") == 0) {
        execute_cd(arguments[1]);
    } else if (strcmp(arguments[0], "ls") == 0) {
        execute_ls(arguments[1]);
    } else if (strcmp(arguments[0], "pwd") == 0) {
        execute_pwd();
    } else if (strcmp(arguments[0], "cat") == 0) {
        execute_cat(arguments[1]);
    } else if (strcmp(arguments[0], "exit") == 0) {
        exit(0);
    } else if (strcmp(arguments[0], "-v") == 0) {
        verbose_mode = 1; // Enable verbose mode
    } else {
        // Execute external command
        pid_t pid = fork();

        if (pid == -1) {
            perror("fork");
            return;
        } else if (pid == 0) {
            // Child process
            if (verbose_mode) {
                printf("Executing external command: %s", arguments[0]);
                for (int i = 1; arguments[i] != NULL; i++) {
                    printf(" %s", arguments[i]);
                }
                printf("\n");
            }

            execvp(arguments[0], arguments);

            // execvp returns only if an error occurs
            perror("execvp");
            exit(1);
        } else {
            // Parent process
            int status;
            waitpid(pid, &status, 0);
        }
    }
}

void run_shell() {
    char command[MAX_COMMAND_LENGTH];

    while (1) {
        system("clear"); // Clear the shell prompt

        display_prompt();

        if (fgets(command, sizeof(command), stdin) == NULL) {
            break;
        }

        execute_command(command);
    }
}

int main() {
    run_shell();
    return 0;
}
