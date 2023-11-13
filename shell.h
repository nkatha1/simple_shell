#ifndef _SHELL_H
#define _SHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/types.h>

/* Write/read buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define ALIAS_REPLACE_LIMIT 10

/* Command chaining */
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

/* Convert_number() */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/* If using system getline 1 () */
#define USE_GETLINE 0
#define USE_STROK 0

#define HIST_FILE   ".simple_shell_history"
#define HIST_MAX      4096

extern char *environ;

/**
 * struct liststr - The singly linked list.
 * @num: Field number.
 * @str: The string.
 * @next: The next node's pointer.
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - This one contains the pseudo-arguments to pass into a fn,
 *	allowing a prototype that is uniform for struct pointer fn.
 * @arg: Generates string containing arguments from getline.
 * @argv: Strings array that are generated from arg.
 * @path: Current command path's string.
 * @argc: Count argument.
 * @line_number: Error count.
 * @err_num: Error code that is for exit()s.
 * @linecount_flag: This is the input line if on count.
 * @filename: Filename's program.
 * @env: Copy of environ local linked list.
 * @environ: Modified custom copy from LL env of environ.
 * @hist: History's node.
 * @alias: Alias node.
 * @change_env: If environ was changed it is on.
 * @status: The last exec'd command it returns it status.
 * @cmd_buf: If on chaining, adress the pointer to cmd_buf.
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: fd to read the input line.
 * @histcount: Line history number count.
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_number;
	int err_num;
	int linecount_flag;
	char *filename;
	list_t *env;
	list_t *hist;
	list_t *alias;
	char **environ;
	int change_env;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory management */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL}
	{0, 0, 0}

/**
 * struct builtin - The builtin string it contains it and a fn that
 *		is related.
 * @type: Command flag of the builtin.
 * @func: Function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/** sloop.c */
void find_command(info_t *info);
int shel(info_t *info, char **am);
void fork_command(info_t *info);
int check_builtin(info_t *info);

/* pas.c */
char *dup_char(char *path, int s, int p);
int _cmd(info_t *info, char *file_path);
char *path_finder(info_t *info, char *file_path, char *c);

/* plops.c */
int loopsdh(char **);

/*printchar.c */
int putc_fd(int fd, char c);
int puts_fd(int fd, char *string);
int e_putc(char c);
void e_puts(char *string);

/* ring.c */
char *start_with(const char *str1, const char *str2);
int str_len(char *c);
char *str_cat(char *dest, char *source);
int str_cmp(char *str1, char *str2);

/* ring1.c */
void _puts(char *s);
char *str_cpy(char *dest, char *source);
int _putchar(char c);
char *str_dup(const char *s);

/* string.c */
char *strn_cat(char *dest, char *src, size_t n);
char *strn_cpy(char *dest, char *src, size_t n);
char *str_chr(char *c, char s);

/* tok.c */
char **str_tow2(char *s, char t);
char **str_tow(char *s, char *t);

/* reel.c */
void *re_alloc(void *ptr, unsigned int old_s, unsigned int new_s);
char *set_mem(char *m, char f, size_t n);
void ffree(char **sp);

/* freemem.c */
int freemem(void **p);

/* ato.c */
int interact(info_t *);
int _isalpha(int);
int _isdelim(char, char *);
int _atoi(char *);

/* errors.c */
int str_int(char *c);
void print_error(info_t *, char *);
int print_integer(int, int);
char *convert_num(long int, int, int);
void replace_comments(char *);

/* morebuiltin.c */
int my_alias(info_t *info);
int alias_set(info_t *info, char *str);
int alias_unset(info_t *info, char *str);
int print_alias(list_t *node);

/* getline.c */
ssize_t get_form(info_t *info);
int get_line(info_t *info, char **ptr, size_t *n);
ssize_t buff_read(info_t *info, char *buffer, size_t *n);
ssize_t buff_input(info_t *info, char **buffer, size_t *n);

/* infor.c */
void create_info(info_t *info, char **ar);
void free_struct(info_t *info, int n);

/* envir.c */
char *get_env(info_t *info, const char *form);
int my_env(info_t *info);
int my_setenv(info_t *info);
int my_unsetenv(info_t *info);
int create_envlist(info_t *info);

/* atgetenvir.c */
int un_setenv(info_t *info, char *c);
char **_getenviron(info_t *info);
int set_env(info_t *info, char *c, char *v);

/* ithisto.c */
char *get_hist(info_t *info);
int w_history(info_t *info);
int read_hist(info_t *info);
int create_history(info_t *info, char *buffer, int count);
int renum_hist(info_t *info);

/* list.c */
void free_l(list_t **headptr);
size_t print_str_list(const list_t *n);
list_t *add_node(list_t **head, const char *f, int n);
int delete_node(list_t **head, unsigned int index);
list_t *add_endnode(list_t **head, const char *f, int n);

/* more_lists.c */
size_t print_list(const list_t *f);
char **string_list(list_t *head);
ssize_t get_node(const list_t *head, const list_t *node);
size_t listlen(const list_t *f);
list_t *node_start(list_t *node, char *s, char d);

/* varsac.c */
int replace_str(char **former, char *current);
int chain_delim(info_t *info, char *buffer, size_t *n);
int rep_alias(info_t *info);
void checkchain(info_t *info, char *buffer, size_t *n, size_t i, size_t len);
int rep_variables(info_t *info);

int shell_exit(info_t *info);
int chadir(info_t *info);

#endif



