#ifndef _SHELL_H
#define _SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>

/* convert_num */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/* chain commands */
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

/* Write/read buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define ALIAS_REPLACE_LIMIT 10

#define HIST_FILE  ".simple_shell_history"
#define HIST_MAX   4096

/* getline */
#define USE_GETLINE 0
#define USE_STROK 0

extern char **environ;

/**
 * liststr - struct
 * @str: pointer to string
 * @num: integer
 * @next: pointer to next node
 */
typedef struct liststr
{
	char *str;
	int num;
	struct liststr *next;
} list_t;

/**
 * passinfo - struct
 * @arg: Generates string containing arguments from getline.
 * @argv: Strings array that are generated from arg.
 * @path: Current command path's string.
 * @filename: name of program
 * @environ: custom copy of environment variables
 * @argc: Count argument.
 * @change_env: change environment
 * @err_num: Error code that is for exit()s.
 * @linecount_flag: This is the input line if on count.
 * @status: exit status
 * @line_number: Error count
 * @env: Copy of environ local linked list.
 * @hist: history node
 * @alias: alias node
 * @cmd_buf: If on chaining, adress the pointer to cmd_buf.
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @histcount: line history count
 * @readfd: fd to read the input line
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	char *filename;
	char **environ;
	int argc;
	int change_env;
	int err_num;
	int linecount_flag;
	int status;
	unsigned int line_number;
	list_t *env;
	list_t *hist;
	list_t *alias;

	char **cmd_buf;
	int cmd_buf_type;
	int histcount;
	int readfd;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 0, 0, 0, NULL, NULL, NULL, NULL}, \
	{NULL, 0, 0}

/** 
 * builtin - struct
 * @type: command flag
 * @func: function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *info);
} builtin_table;

/** atgetenvir.c */
int un_setenv(info_t *info, char *c);
char **_getenviron(info_t *info);
int set_env(info_t *info, char *c, char *v);

/** envir.c */
char *get_env(info_t *info, const char *form);
int my_env(info_t *info);
int my_setenv(info_t *info);
int my_unsetenv(info_t *info);
int create_envlist(info_t *info);

/** errors.c */
int print_integer(int fd, int n);
void print_error(info_t *info, char *str);
char *convert_num(long int n, int base, int flags);
void replace_comments(char *c);
int str_int(char *c);

/** freemem.c */
int freemem(void **p);

/** func_builtin.c */
int chadir(info_t *info);
int shell_exit(info_t *info);

/** getline.c */
ssize_t get_form(info_t *info);
int get_line(info_t *info, char **ptr, size_t *n);
ssize_t buff_read(info_t *info, char *buffer, size_t *n);
ssize_t buff_input(info_t *info, char **buffer, size_t *n);

/** infor.c */
void create_info(info_t *info, char **ar);
void free_struct(info_t *info, int n);

/** isattty.c */
int interact(info_t *info);
int _atoi(char *c);
int _isalpha(int n);
int _isdelim(char c, char *delim);

/** ithisto.c */
int renum_hist(info_t *info);
int read_hist(info_t *info);
int w_history(info_t *info);
char *get_hist(info_t *info);
int create_history(info_t *info, char *buffer, int count);

/** list.c */
void free_l(list_t **headptr);
size_t print_str_list(const list_t *n);
list_t *add_node(list_t **head, const char *str, int n);
int delete_node(list_t **head, unsigned int index);
list_t *add_endnode(list_t **head, const char *str, int n);

/** main.c */
int main(int a, char **b);

/** more_builtin.c */
int my_alias(info_t *info);
int alias_set(info_t *info, char *str);
int alias_unset(info_t *info, char *str);
int print_alias(list_t *node);

/** more_lists.c */
size_t print_list(const list_t *f);
char **string_list(list_t *head);
ssize_t get_node(const list_t *head, const list_t *node);
size_t listlen(const list_t *f);
list_t *node_start(list_t *node, char *s, char d);

/** pas.c */
char *dup_char(const char *path, int s, int p);
int _cmd(info_t *info, char *file_path);
char *path_finder(info_t *info, char *file_path, char *c);

/** printchar.c */
int putc_fd(int fd, char c);
int puts_fd(int fd, char *string);
int e_putc(char c);
void e_puts(char *string);

/** reel.c */
void *re_alloc(void *ptr, unsigned int old_s, unsigned int new_s);
char *set_mem(char *m, char f, size_t n);
void ffree(char **sp);

/* ring.c */
char *start_with(const char *str1, const char *str2);
int str_len(char *c);
char *str_cat(char *dest, const char *source);
int str_cmp(char *str1, char *str2);

/* ring1.c */
void _puts(char *s);
char *str_cpy(char *dest, char *source);
int _putchar(char c);
char *str_dup(const char *s);

/** sloop.c */
void find_command(info_t *info);
int shel(info_t *info, char **am);
void fork_command(info_t *info);
int check_builtin(info_t *info);

/** strings.c */
char *strn_cat(char *dest, char *src, size_t n);
char *strn_cpy(char *dest, char *src, size_t n);
char *str_chr(char *c, char s);

/* tok.c */
char **str_tow2(char *s, char t);
char **str_tow(char *s, char *t);

/* varsac.c */
int replace_str(char **former, char *current);
int chain_delim(info_t *info, char *buffer, size_t *n);
int rep_alias(info_t *info);
void checkchain(info_t *info, char *buffer, size_t *n, size_t i, size_t len);
int rep_variables(info_t *info);

#endif
