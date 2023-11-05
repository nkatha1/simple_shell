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
 * @histcount: Line gistory number count.
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

/*t_err.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* t_ring.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* t_ring1.c */
char *_strcpy(char *);
char *strdup(const char *);
void _puts(char *);
int _putchar(char);

/* t_exi.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* t_tok.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

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

/* t_erro1.c */
int _erratoi(char *c);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* t_builta.c */
int _myhistory(info_t *);
int _myalias(info_t *);

/* t_getl.c */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* t_infoget.c */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* t_envir.c */
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

/* t_getenvir.c */
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* t_histo.c */
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

/* t_varsac.c */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

int shell_exit(info_t *info);
int chadir(info_t *info); 

#endif



