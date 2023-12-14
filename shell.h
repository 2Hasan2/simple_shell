#ifndef SHELL_H
#define SHELL_H
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>

/* Global variables */
#define PROMPT "$ "
#define TITLE_PATH "PATH"
#define TITLE_DIR "PWD"
#define SEP_SLASH "/"
#define SEP_EQUAL "="
#define SEP_TPOIN ":"
#define SEP_ESPAC " \t\r\n\a"
#define TITLE_FILE "_"


/* Error MSG*/
#define ERROR_MSG "Error"
#define ERROR_NOTFOUND "not found"
#define ERROR_EXIT "Illegal number"
#define ERROR_ALLOCATION "Error on allocation"
#define ERROR_NOT_FILE_DIR "No such file or directory"
#define ERROR_OLDPWD "cd: OLDPWD not set"
#define ERROR_HOME "cd: HOME not set"
#define ERROR_PWD "cd: can't cd to "


/**
 * struct built_command - struct built-in
 * @command: command
 * @fun: fun
 */
typedef struct built_command
{
	char *command;
	int (*fun)(char *, char **, char *, char **, int, int);
} built;

/* Interactive mode */
void LOOP(char **environ, char *arg);
int arguments(char *s, char *file, char **environ, int count, int out);
int check_input(char *str, ssize_t length);

/* no-Interactive mode */
void non_interactive(char **environ, char *file);
int args_non_interactive(char *file, char **environ, char *s, int out);
int check_input_non_interactive(char *str, ssize_t length);

/* get commands */
int getCommand(char *s, char **args, char *file, char **env, int num, int out);

/* Built-in commands */
int (*built_in_command(char *str))(char *, char **, char *, char **, int, int);
int EXIT(char *s, char **arg, char *file, char **environ, int count, int out);
int ENV(char *s, char **av, char *fl, char **env, int count, int out);
int CD(char *s, char **arg, char *file, char **environ, int count, int out);

/* CD commands */
int change_to_home(char **arg, char *file, char **environ, int count);
int change_to_oldpwd(char **arg, char *file, char **environ, int count);
int change_to_directory(char **arg, char *file, int count);


/* Exe commands */
int exe_command(char **arg, char *file, char **environ, int count);
int get_path(char **arg, char *file, char **environ, int count);
char *check_exe(char *path, char *command);
char *Get_Env(char **environ, char *path);

/* Strings functions */
int _strcmp(char *str1, char *str2);
char *_strcpy(char *new, char *old);
int _strlen(char *string);
void _strcat(char *new, char *old);

/* Numbers functions */
int is_digit(char c);
int convert_to_integer(char *s);

/* Memory functions */
void *reallocate_mem(void *ptr, unsigned int old_size, unsigned int new_size);
void copy_memory(char *dest, char *src, unsigned int n);

/* out put functions */
void tap(int number);
void _putchar(char *c);
void print_num(int number);
void print_err(char *file, char *arg, int count, char *message);
void print_errex(char *file, char **arg, int count, char *message);


/* custom_getline function*/
ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream);
char *custom_strtok(char *str, const char *delim);


#endif
