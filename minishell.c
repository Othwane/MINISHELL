/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omajdoub <omajdoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 13:10:57 by aasselma          #+#    #+#             */
/*   Updated: 2023/07/25 18:10:18 by omajdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

t_files	*check_firts_token(t_tokens **token)
{
	t_tokens	*node;
	t_files		*file;

	node = *token;
	file = NULL;
	while(node)
	{
		if (is_redirections(node->content))
		{
			add_files(&file, node->next->content, node->content);
			if (node->next->next)
				node = node->next->next;
		}
		else
		{
			*token = node;
			return (file);
		}
	}
	return (NULL);
}

void	parsing(t_tokens *token, t_command **cmd)
{
	t_command	*command;

	command = *cmd;
	command->files = NULL;
	command->args = NULL;
	command->outfile = 1;
	command->infile = 0;
	command->files = check_firts_token(&token);
	command->next = NULL;
	command->cmd_num = malloc(sizeof(t_cmd_nmbr));
	command->arguments = NULL;
	command->command = ft_strdup(token->content);
	// add_command(&command, token->content);
	token = token->next;
	while(token)
	{
		if (ft_strcmp(token->content, "|") == 0)
			break;
		else if (is_redirections(token->content))
		{
			add_files(&command->files, token->next->content, token->content);
			token = token->next;
		}
		else if (is_redirections(token->content) == 0
			|| ft_strcmp(token->content, "|") == 1)
			add_args(&command->args, token->content);
		token = token->next;
	}
	convert_linkedlist(command);
	if (token)
	{
		command->next = malloc(sizeof(t_command));
		command->next->cmd_num = malloc(sizeof(t_cmd_nmbr));
		command->next->cmd_num->cmd_num = command->cmd_num->cmd_num;
		command->next->next = NULL;
		command->next->arguments = NULL;
		command->next->outfile = 1;
		command->next->infile = 0;
		parsing(token->next, &command->next);
	}
}

void	convert_linkedlist(t_command *cmd)
{
	t_args	*args;
	int		len;
	int		i;

	len = 0;
	i = 0;
	args = cmd->args;
	while(args)
	{
		len++;
		args = args->next;
	}
	cmd->arguments = malloc((len + 2) * sizeof(char*));
	while((i - 1) != len)
	{
		if (i == 0)
			cmd->arguments[i] = ft_strdup(cmd->command);
		else
		{
			cmd->arguments[i] = ft_strdup(cmd->args->args);
			cmd->args = cmd->args->next;
		}
		i++;
	}
	cmd->arguments[i] = NULL;
}

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_tokens	*node_head;
	t_command	*command;
	char		*input;

	while (1)
	{
		node_head = NULL;
		command = malloc(sizeof(t_command));
		command->cmd_num = malloc(sizeof(t_cmd_nmbr));
		command->cmd_num->cmd_num = 0;
		input = readline("\033[31m~minishell$> \033[0m");
		if (ft_strlen(input) != 0)
		{
			add_history(input);
			super_split(&node_head ,input);
			// get_envirement(node_head, env);
			if (check_syntax_error(node_head) == 1 || check_brakets(input) == 1)
				printf("minishell~: syntax error near unexpected token\n");
			else
			{
				parsing(node_head, &command);
				_exec(command, env);
			}
			if (command->cmd_num->cmd_num > 0)
			{
				// print_command(command);
				free_command(command);
			}
			else
				free(command);
			free_tokens(node_head);
		}
		free(input);
	}
}
