#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10

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
    DIR* dir;
    struct dirent* entry;

    if (arg == NULL) {
        dir = opendir(".");
    } else {
        dir = opendir(arg);
    }

    if (dir == NULL) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    closedir(dir);
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
    } else if (strcmp(arguments[0], "exit") == 0) {
        exit(0);
    } else {
        // Execute external command
        pid_t pid = fork();

        if (pid == -1) {
            perror("fork");
            return;
        } else if (pid == 0) {
            // Child process
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

int main() {
    char command[MAX_COMMAND_LENGTH];

    while (1) {
        display_prompt();

        if (fgets(command, sizeof(command), stdin) == NULL) {
            break;
        }

        execute_command(command);
    }

    return 0;
}
