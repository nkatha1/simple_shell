#ifndef _SHELL_H
#define _SHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <limits.h>
#include <fcntl.h>

/* write/read buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* chaining command */
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

/* convert_number() */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/* using system getline 1() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE ".simple_shell_hist"
#define HIST_MAX 4096

extern char **environ;


/**
 * struct liststr - The linked list that is singly.
 * @num: The field num.
 * @str: The string.
 * @next: The next nodes pointer.
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - Has the uniform prototype that is allowed by the pseudo
 *                   arguments.
 *@arg: The generated string from getline and contains an argument in it.
 *@argv: Strings got from arg.
 *@path: The current command paths string.
 *@argc: The count argument.
 *@line_count: The count error.
 *@err_num: The exit()s code error.
 *@linecount_flag: The line of input if on count.
 *@fname: The filenames program.
 *@env: environ local copy linked list.
 *@environ: Local copy custom modoified from LL environ.
 *@history:The nodes history.
 *@alias: The nodes alias.
 *@env_changed: If environ is changed then its on.
 *@status: The last exec'd command status return.
 *@cmd_buf: Pointer adress if on chaining of the cmd_buf.
 *@cmd_buf_type: CMD_type , &&, ; ,||
 *@readfd: The read line input where the fd is found.
 *@histcount: Count number line history.
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}


/**
* struct builtin - contains a builtin string and related function
* @type: The flag command builtin.
* @func: Function.
*/
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/* t_shlop.c */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* t_pars.c */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* loops.c */
int loophsh(char **);

/* t_err.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* t_str.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* t_str1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* t_exit.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* t_token.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* t_real.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* t_mem.c */
int bfree(void **);

/* t_at.c */
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* t_err.c */
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* t_built.c */
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

/* t_built1.c */
int _myhistory(info_t *);
int _myalias(info_t *);

/* t_get.c */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* t_infoget.c */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* t_env.c */
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

/* t_genvi.c */
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* t_hist.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

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

/* t_vars.c */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);


#endif






