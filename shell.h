#ifndef _SHELL_H
#define _SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define WRITE_BUF_SIZE 1024
#define READ_BUFFER_SIZE 1024
#define BUFFER_FLUSH -1

#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define USE_STRTOK 0
#define USE_GETLINE 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;

/**
 * struct liststr - singly linked list
 * @num: Number field
 * @str: String
 * @next: points to next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct data - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: string generated from getline containing arguements
 *@argv: array of strings generated from arg
 *@path: string path for the current command
 *@argc: argument count
 *@line_count: error count
 *@err_num: error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: history node
 *@alias: alias node
 *@env_changed: if environ was changed
 *@status: return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: fd from which to read line input
 *@histcount: history line number count
 */
typedef struct data
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
} data_shell;

#define DATA_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string & related function
 *@type: Builtin command flag
 *@func: function
 */
typedef struct builtin
{
	char *type;
	int (*func)(data_shell *);
} builtin_table;


/* toem_shloop.c */
int hsh(data_shell *, char **);
void find_cmd(data_shell *);
void fork_cmd(data_shell *);
int find_builtin(data_shell *);

/* toem_parser.c */
char *duplc_chars(char *, int, int);
int is_cmd(data_shell *, char *);
char *find_path(data_shell *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* toem_errors.c */
void e_puts(char *);
int e_putchar(char);
int put_fd(char c, int fd);
int puts_fd(char *str, int fd);

/* toem_string.c */
int _strcmp(char *, char *);
int _strlen(char *);
char *_strcat(char *, char *);
char *starts_with(const char *, const char *);

/* toem_string1.c */
char *_strduplc(const char *);
char *_strcpy(char *, char *);
int _putchar(char);
void _puts(char *);

/* toem_exits.c */
char *_strncat(char *, char *, int);
char *_strncpy(char *, char *, int);
char *_strchr(char *, char);

/* toem_tokenizer.c */
char **strtow2(char *, char);
char **strtow(char *, char *);

/* toem_realloc.c */
void ffree(char **);
char *_memset(char *, char, unsigned int);
void *_realloc(void *, unsigned int, unsigned int);

/* toem_memory.c */
int bfree(void **);

/* toem_atoi.c */
int _atoi(char *);
int interactive(data_shell *);
int is_delimeter(char, char *);
int _isalpha(int); 

/* toem_errors1.c */
int _erratoi(char *);
int print_d(int, int);
void print_error(data_shell *, char *);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* toem_builtin.c */
int my_cd(data_shell *);
int my_exit(data_shell *);
int my_help(data_shell *);

/* toem_builtin1.c */
int my_alias(data_shell *);
int my_history(data_shell *);

/*toem_getline.c */
ssize_t get_input(data_shell *);
void sigint_handler(int);
int get_line(data_shell *, char **, size_t *);

/* toem_getinfo.c */
void clear_data(data_shell *);
void free_data(data_shell *, int);
void set_data(data_shell *, char **);

/* toem_environ.c */
char *get_env(data_shell *, const char *);
int my_setenv(data_shell *);
int my_env(data_shell *);
int populate_env_list(data_shell *);
int my_unsetenv(data_shell *);

/* toemget_env.c */
int un_setenv(data_shell *, char *);
char **get_environ(data_shell *);
int _setenv(data_shell *, char *, char *);

/* toem_history.c */
char *get_history_file(data_shell *data);
int read_data_history(data_shell *data);
int write_history(data_shell *data);
int renumber_history(data_shell *data);
int build_history_list(data_shell *data, char *buf, int linecount);

/* toem_lists.c */
list_t *_add_node(list_t **, const char *, int);
list_t *_add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
void free_list(list_t **);
int _delete_node_at_index(list_t **, unsigned int);

/* toem_lists1.c */
char **list_to_strings(list_t *);
size_t list_len(const list_t *);
list_t *_node_starts_with(list_t *, char *, char);
size_t print_list(const list_t *);
ssize_t _get_node_index(list_t *, list_t *);

/* toem_vars.c */
int is_chain(data_shell *, char *, size_t *);
int replace_alias(data_shell *);
int replace_vars(data_shell *);
int replace_string(char **, char *);
void check_chain(data_shell *, char *, size_t *, size_t, size_t);

#endif
