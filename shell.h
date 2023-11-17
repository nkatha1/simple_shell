#ifndef SHELL_H
#define SHELL_H

extern char **environ;

#define BUFSIZE 1024
#define DELIM "\t\r\n\a"
#define PRINTER(c) (write(STDOUT_FILENO, c, _strlen(c)))

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <limits.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

/**
 * builtin - struct
 * @command: pointer to string
 * @func: function to execute
 */
typedef struct builtin
{
	char *command;
	int (*func)(char **, int);
} bul_t;

int main(int, char **);
int strn_cmp(const char *, const char *, size_t);
char *str_chr(char *, char);
char *_itoa(unsigned int);
char *str_dup(char *);
void _puts(char *);
int intlen(int);
int is_alpha(int);
int _atoi(char *);
int _putchar(char);
int str_len(char *);
int str_cmp(char *, char *);
void array_rev(char *, int);
char *str_cpy(char *, char *);
char *str_cat(char *, char *);
int un_setenv(char *);
int set_env(char *, char *);
char *str_tok(char *, const char *);
char *strn_cpy(char *, char *, int);
unsigned int check_delim(char, const char *);

void *fill_array(void *, int, unsigned int);
void free_env(char **);
void free_all(char **, char *);
void *re_alloc(void *ptr, unsigned int, unsigned int);
char *mem_cpy(char *, char *, unsigned int);
void *_calloc(unsigned int);

void pre_error(char **, int, char **);
void print_error(char *, int, char **);
void print_number_in(int);
void print_number(unsigned int);

void treat_file(char *, int, FILE *, char **);
int check_cmd(char **, char *, int, char **);
void exit_bul_for_file(char **, char *, FILE *);
void read_file(char *, char **);
int handle_builtin(char **, int);
char *build(char *, char *);
void create_env(char **);
int check_builtin(char **);
char **parsecmd(char *);
char *get_env(char *);
int pathcmd(char **);

char *get_line(void);
void signal_to_handle(int);
void prompt(void);

int print_echo(char **);
void exit_bul(char **, char *, char **, int);
int echo_bul(char **, int);
int dis_help(char **, int);
int ch_dir(char **, int);
int dis_env(char **, int);
int history_dis(char **, int);
int history(char *);
void hash_handle(char *);

#endif
