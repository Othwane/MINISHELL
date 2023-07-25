/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omajdoub <omajdoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 13:10:14 by aasselma          #+#    #+#             */
/*   Updated: 2023/07/25 18:20:02 by omajdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <string.h>

#define INPUT 1
#define OUTPUT 2
#define HERDOCE 3

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
	int 				infile;
	int					outfile;
	char				*command;
	char				**arguments;
	t_cmd_nmbr			*cmd_num;
	t_args				*args;
	struct s_files		*files;
	struct s_command	*next;
}						t_command;

typedef struct s_files
{
	char				*filename;
	char				*redairection;
	int					red_type;
	struct s_files		*next;
}						t_files;

typedef struct s_env
{
	char				*value;
	struct s_env		*next;
}   					t_env;

typedef struct s_tokens
{
	char				*content;
	struct s_tokens		*next;
}   					t_tokens;

int						check_brakets(char *str);
void					super_split(t_tokens **my_list, char *str);
int						string_count(char *str);
char					*ft_substr(char const *s, int start, int len);
char					*ft_strdup(const char *s1);
char					*ft_strlcpy(char *dst, const char *src, int len);
int					ft_strlen(const char *s);
int						check_syntax_error(t_tokens  *token);
int						ft_strcmp(const char *s1, const char *s2);
void					add_command(t_command **command, char *content);
void					add_args(t_args **args, char *content);
void					add_files(t_files **files, char *content, char *rdac);
void					add_var(t_env **env, char *content, int	num);
void					print_command(t_command *my_list);
void					free_command(t_command *command);
void					print_list(t_tokens *my_list);
void					free_tokens(t_tokens *token);
void					get_envirement(t_tokens *token, char **env);
int						is_redirections(char *token);
int						check_ifvalid(char c);
int						special_strlen(char	*env);
char					*search_and_replace(char *src, char *value);
void					convert_linkedlist(t_command *cmd);
void					_exec(t_command *command, char** env);
#endif
