/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omajdoub <omajdoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 13:10:14 by aasselma          #+#    #+#             */
/*   Updated: 2023/07/17 23:15:36 by omajdoub         ###   ########.fr       */
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
	int	cmd_num;
}		t_cmd_nmbr;

typedef struct s_command
{
	char				*command;
	t_cmd_nmbr			*cmd_num;
	t_args				*args;
	struct s_files		*files;
	struct s_command	*next;
}						t_command;

typedef struct s_files
{
	char			*filename;
	// char* left_redir_file;
	// char* right_redir_file;
	char			*redairection;
	int				red_type;
	struct s_files	*next;
}					t_files;

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
size_t					ft_strlen(const char *s);
int						check_syntax_error(t_tokens  *token);
int						ft_strcmp(const char *s1, const char *s2);
void					add_command(t_command **command, char *content);
void					add_args(t_args **args, char *content);
void					add_files(t_files **files, char *content, char *rdac);
void					print_command(t_command *my_list);
void					print_list(t_tokens *my_list);
void					free_command(t_command *command);
void					get_envirement(t_tokens *token);

#endif
