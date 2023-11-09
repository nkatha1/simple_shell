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
}list_t;

/**
 * struct passinfo - This one contains the pseudo-arguments to pass into a fn,
 * 			allowing a prototype that is uniform for struct pointer fn.
 * @arg: Generates string containing arguments from getline.
 * @argv: Strings array that are generated from arg.
 * @path: Current command path's string.
 * @argc: Count argument.
 * @line_count: Error count.
 * @err_num: Error code that is for exit()s.
 * @linecount_flag: This is the input line if on count.
 * @fname: Filename's program.
 * @env: Copy of environ local linked list.
 * @environ: Modified custom copy from LL env of environ.
 * @history: History's node.
 * @alias: Alias node.
 * @env_changed: If environ was changed it is on.
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
}info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL}
	{0, 0, 0}

/**
 * struct builtin - The builtin string it contains it and a fn that
 * 			is related.
 * @type: Command flag of the builtin.
 * @func: Function
 */
typedef struct builtin 
{
	char *type;
	int (*func)(info_t *);
}builtin_table;


/** t_sloop.c */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* t_pas.c */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/*lops.c */
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

/* t_reel.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int );

/* t_meme.c */
int bfree(void **);

/* t_ato.c */
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

/* t_list.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* t_list1.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* t_varsac.c */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

int shell_exit(info_t *info);
int chadir(info_t *info); 

#endif



