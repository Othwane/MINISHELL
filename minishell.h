/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 13:10:14 by aasselma          #+#    #+#             */
/*   Updated: 2023/08/08 01:26:11 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>

#define INPUT 1
#define OUTPUT 2
#define HERDOCE 3
#define APPEND 4

typedef struct s_args
{
	char				*args;
	struct s_args		*next;
}						t_args;

typedef struct cmd_nmbr
{
	int					cmd_num;
}						t_cmd_nmbr;

typedef struct s_command
{
	char				*command;
	char				**arguments;
	int					cmd_num;
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
	struct s_files		*next;
}						t_files;

typedef struct s_env
{
	char				*value;
	int					index;
	struct s_env		*next;
}						t_env;

typedef struct s_tokens
{
	char				*content;
	int					qoute;
	struct s_tokens		*next;
}						t_tokens;

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
void					add_command(t_command **command, char *content);
void					add_args(t_args **args, char *content);
void					add_files(t_files **files, char *content, char *rdac);
int						in_qoute(char *token);
void					add_var(t_env **env, char *content, int	num, int start);
void					print_command(t_command *my_list);
void					free_command(t_command *command);
void					print_list(t_tokens *my_list);
void					free_tokens(t_tokens *token);
void					get_envirement(t_tokens *token, char **env);
int						is_redirections(char *token);
int						check_ifvalid(char c);
int						special_strlen(char	*env);
char					*search_and_replace(char *src, char *value, int index);
void					remove_quotes(t_tokens *token);
void					_exec(t_command *command, char** env);
char					*findpath(char *cmd, char **envp);

#endif
