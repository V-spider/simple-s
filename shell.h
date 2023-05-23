#ifndef SHELL_H
#define SHELL_H

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGUMENTS 64
#define MAX_BUFFER_SIZE 1024

extern int verbose_mode;

void display_prompt();
void execute_cd(char* arg);
void execute_ls(char* arg);
void execute_pwd();
void execute_cat(char* filename);
void execute_command(char* command);
void run_shell();

#endif  /* SHELL_H */
