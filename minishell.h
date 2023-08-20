/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 13:10:14 by aasselma          #+#    #+#             */
/*   Updated: 2023/08/19 23:28:20 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>

#define INPUT 1
#define OUTPUT 2
#define APPEND 4
#define HERDOC 3

typedef struct s_global
{
	char				**env;
	char				**export;
	int					exit_s;
}						t_global;

t_global	global;

typedef struct s_args
{
	char				*args;
	struct s_args		*next;
}						t_args;

typedef struct s_command
{
	char				*command;
	char				**arguments;
	int					infile;
	int					outfile;
	char				*cmd_path;
	t_args				*args;
	struct s_files		*files;
	struct s_command	*next;
}						t_command;

typedef struct s_files
{
	char				*filename;
	int					red_type;
	int					quote;
	struct s_files		*next;
}						t_files;

typedef struct s_env
{
	char				*value;
	int					s_p;
	int					e_p;
	struct s_env		*next;
}						t_env;

typedef struct s_tokens
{
	char				*content;
	int					qoute;
	struct s_tokens		*next;
}						t_tokens;

typedef struct s_env_e
{
	char* key;
	char* value;
	struct s_env_e* next;
} t_env_e;


// -------
void					print_command(t_command *my_list);
void					print_list(t_tokens *my_list);
// -------
void					set_signal();
int						check_brakets(char *str);
void					super_split(t_tokens **my_list, char *str);
int						string_count(char *str);
char					*ft_substr(char const *s, int start, int len);
char					*ft_strdup(const char *s1);
char					**ft_split(char const *s, char c);
int						ft_strncmp(char *s1, char *s2, int n);
char					*ft_strjoin(char *s1, char *s2);
char					*ft_strchr(char *s, int c);
char					*ft_strlcpy(char *dst, const char *src, int len);
char					*ft_strjoin(char *s1, char *s2);
int						ft_strlen(const char *s);
int						check_syntax_error(t_tokens  *token);
int						ft_strcmp(const char *s1, const char *s2);
void					add_args(t_args **args, char *content);
void					add_files(t_files **files, char *content, char *rdac);
int						in_qoute(char *token);
void					add_var(t_env **env, char *content, int	num, int start);
void					free_command(t_command *command);
void					free_resources(t_tokens *token);
void					get_envirement(t_command *token, char **env);
char					*remove_special_char(char *str);
int						check_quote(char *var);
int						get_next_var(char *var);
int						ft_searchfor_var(char *s, t_env **env);
char					*get_value(char **env, char *var);
char					*s_and_r(char *src, char *value, int index, int l);
int						is_redirections(char *token);
int						check_ifvalid(char c);
int						special_strlen(char	*env);
void					remove_quotes(t_command *token);
void					_exec(t_command *command, char	**env);
void					redir_op(t_command *command, char **env);
void					ft_herdoc(int fd, t_command *cmd, char **env);
char					*findpath(char *cmd, char **envp);

// builtin
void					free_env();
char					**fill_env(char **env);
void					env_b(char **export);
void					export_b(t_command *cmd);
char					**add_newenv(char **env, char *new);
void					unsetenv_b(char **args);
int						check_nameof_var(char *var_name);
int						get_pos(char *var);
int						env_len(char **env);
int						echo_b(char **args);
int						pwd_b(void);
int 					cd_b(char** argv);
int						exit_b();
void					exec_builtins(t_command *command);
int						is_builtin(char *arg);
#endif
