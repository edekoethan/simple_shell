#ifndef NEW_SHELL_H
#define NEW_SHELL_H

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

/* for read/write buffers */
#define READ_BUF_SIZE 2048
#define WRITE_BUF_SIZE 2048
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

/* for convert_number() */
#define CONVERT_UPPERCASE 1
#define CONVERT_SIGNED 2

/* 1 if using custom getline() */
#define USE_CUSTOM_GETLINE 1
#define USE_STRTOK 0

#define HISTORY_FILE ".new_shell_history"
#define HISTORY_MAX 8192

extern char **environ;

/**

struct linked_string - singly linked list
@num: the number field
@str: a string
@next: points to the next node
*/
typedef struct linked_string
{
int num;
char *str;
struct linked_string *next;
} linked_list_t;
/**

struct arguments - contains pseudo-arguments to pass into a function,

allowing for a unified function pointer struct prototype

@arg: a string generated from getline containing arguments

@argv: an array of strings generated from arg

@path: a string path for the current command

@argc: the argument count

@line_count: the error count

@err_num: the error code for exit()s

@linecount_flag: if on, count this line of input

@fname: the program filename

@env: linked list local copy of environ

@environ: custom modified copy of environ from linked list env

@history: the history node

@alias: the alias node

@env_changed: on if environ was changed

@status: the return status of the last executed command

@cmd_buf: address of pointer to cmd_buf, on if chaining

@cmd_buf_type: CMD_type ||, &&, ;

@readfd: the fd from which to read line input

@histcount: the history line number count
*/
typedef struct arguments
{
char *arg;
char **argv;
char *path;
int argc;
unsigned int line_count;
int err_num;
int linecount_flag;
char *fname;
linked_list_t *env;
linked_list_t *history;
linked_list_t *alias;
char **environ;
int env_changed;
int status;

char *cmd_buf; / pointer to cmd ; chain buffer, for memory management /
int cmd_buf_type; / CMD_type ||, &&, ; */
int readfd;
int histcount;
} info_t;

#define INFO_INIT
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL,
0, 0, 0}

/**

struct builtin_cmd - contains a builtin string and related function
@type: the builtin command flag
@func: the function
*/
typedef struct builtin_cmd
{
char *type;
int (*func)(info_t *);
} builtin_table;
/* new_shell_loop.c */
int new_shell(info_t *, char **);
int find_builtin_command(info_t *);
void find_command(info_t *);
void fork_command(info_t *);

/* new_shell_parser.c */
int is_command(info_t *, char *);
char *duplicate_characters(char *, int, int);
char *find_path(info_t *, char *, char *);

/* shell_loop.c */
int shell_loop(char **);

/* new_shell_errors.c */
void print_error_message(char *);
int print_error_character(char);
int print_to_file_descriptor(char c, int fd);
int print_string_to_file_descriptor(char *str, int fd);

/* new_shell_string.c */
int string_length(char *);
int compare_strings(char *, char *);
char *starts_with_string(const char *, const char *);
char *concatenate_strings(char *, char *);

/* new_shell_string1.c */
char *copy_string(char *, char *);
char *duplicate_string(const char *);
void print_string(char *);
int print_character(char);

/* new_shell_exits.c */
char *copy_string_n(char *, char *, int);
char *concatenate_string_n(char *, char *, int);
char *find_character(char *, char);

/* new_shell_tokenizer.c */
char **tokenize_string(char *, char *);
char **tokenize_string2(char *, char);

/* new_shell_realloc.c */
char *set_memory(char *, char, unsigned int);
void free_memory(char **);
void *reallocate_memory(void *, unsigned int, unsigned int);

/* new_shell_memory.c */
int free_block(void **);

/* new_shell_atoi.c */
int handle_interactive_mode(info_t *);
int is_delimiter(char, char *);
int is_alphabetic(int);
int convert_to_integer(char *);

/* new_shell_errors1.c */
int convert_error_to_integer(char *);
void print_error_message(info_t *, char *);
int print_decimal_number(int, int);
char *convert_number_to_string(long int, int, int);
void remove_comments(char *);

/* new_shell_builtin.c */
int execute_exit_command(info_t *);
int execute_cd_command(info_t *);
int execute_help_command(info_t *);

/* new_shell_builtin1.c */
int execute_history_command(info_t *);
int execute_alias_command(info_t *);

/* new_shell_getline.c */
ssize_t get_input(info_t *);
int custom_getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* new_shell_getinfo.c */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* new_shell_environ.c */
char *get_environment_variable(info_t *, const char *);
int execute_env_command(info_t *);
int execute_setenv_command(info_t *);
int execute_unsetenv_command(info_t *);
int populate_environment_list(info_t *);

/* new_shell_getenv.c */
char **get_environment(info_t *);
int execute_unsetenv(info_t *, char *);
int execute_setenv(info_t *, char *, char *);

/* new_shell_history.c */
char *get_history_file(info_t *info);
int write_history_file(info_t *info);
int read_history_file(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history_list(info_t *info);

/* new_shell_linked_list.c */
linked_list_t *add_node(linked_list_t **, const char *, int);
linked_list_t *add_node_end(linked_list_t **, const char *, int);
size_t print_linked_list_str(const linked_list_t *);
int delete_node_at_index(linked_list_t **, unsigned int);
void free_linked_list(linked_list_t **);

/* new_shell_linked_list1.c */
size_t linked_list_length(const linked_list_t *);
char **linked_list_to_strings(linked_list_t *);
size_t print_linked_list(const linked_list_t *);
linked_list_t *find_node_starts_with(linked_list_t *, char *, char);
ssize_t get_node_index(linked_list_t *, linked_list_t *);

/* new_shell_variables.c */
int is_command_chain(info_t *, char *, size_t *);
void check_command_chain(info_t *, char *, size_t *, size_t, size
size_t);
int replace_alias(info_t *);
int replace_variables(info_t *);
int replace_string_value(char **, char *);

#endif
