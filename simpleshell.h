#ifndef SIMPLESHELL_H
#define SIMPLESHELL_H

/* Function Prototypes */

/* Task 0: Betty would be proud */
void betty_check(char *file);

/* Task 1: Simple shell 0.1 */
void prompt_loop(void);

/* Task 2: Simple shell 0.2 */
char **split_input(char *input);

/* Task 3: Simple shell 0.3 */
char *find_command(char *command, char **paths);
int execute_command(char **args, char **env);

/* Task 4: Simple shell 0.4 */
int built_in_exit(void);
int built_in_env(char **env);

/* Task 5: Simple shell 1.0 */
void handle_signal(int signal);
int check_built_in(char **args, char **env);
char *get_env_value(char *var, char **env);

/* Helper Functions */
void free_args(char **args);
void free_env(char **env);

#endif /* SIMPLESHELL_H */
