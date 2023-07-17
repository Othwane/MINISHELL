/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omajdoub <omajdoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 13:10:57 by aasselma          #+#    #+#             */
/*   Updated: 2023/07/18 00:00:07 by omajdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

int	is_redirections(char *token)
{
	if (ft_strcmp(token, ">") == 0 || ft_strcmp(token, ">>") == 0
		|| ft_strcmp(token, "<") == 0 || ft_strcmp(token, "<<") == 0)
		return (1);
	return (0);
}

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

void	parcing(t_tokens *token, t_command **cmd)
{
	t_command	*command;

	command = *cmd;
	command->files = NULL;
	command->args = NULL;
	command->files = check_firts_token(&token);
	add_command(&command, token->content);
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
	if (token)
	{
		command->next = malloc(sizeof(t_command));
		command->next->cmd_num = malloc(sizeof(t_cmd_nmbr));
		command->next->cmd_num->cmd_num = command->cmd_num->cmd_num;
		parcing(token->next, &command->next);
	}
}

int main()
{
	t_tokens	*node_head;
	t_command	*command;
	t_command	*tmp;
	char		*input;

	node_head = NULL;
	while (1)
	{
		command = malloc(sizeof(t_command));
		command->cmd_num = malloc(sizeof(t_cmd_nmbr));
		command->cmd_num->cmd_num = 0;
		tmp = command;
		input = readline("\033[31m~minishell$> \033[0m");
		if (check_brakets(input))
				printf("minishell~: syntax error near unexpected token1\n");
		else if (ft_strlen(input) != 0)
		{
			add_history(input);
			super_split(&node_head ,input);
			if (check_syntax_error(node_head) == 1)
			{
				printf("minishell~: syntax error near unexpected token2\n");
				continue;
			}
			else
			{
				// get_envirement(node_head);
				parcing(node_head, &command);
			}
			// exec();
			print_command(command);
			while(node_head)
			{
				free(node_head->content);
				free(node_head);
				node_head = node_head->next;
			}
		}
		free(input);
	}
	return 0;
}
