/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 06:06:33 by aasselma          #+#    #+#             */
/*   Updated: 2023/08/23 06:34:42 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_files	*check_firts_token(t_tokens **token)
{
	t_tokens	*node;
	t_files		*file;

	node = *token;
	file = NULL;
	if (is_redirections(node->content))
	{
		add_files(&file, node->next->content, node->content);
		if (node->next->next)
			*token = node->next->next;
		else
			*token = NULL;
		return (file);
	}
	return (NULL);
}

void	ft_check_redi(t_command *command, t_tokens **node)
{
	t_tokens	*token;

	token = *node;
	if (token)
	{
		if ((is_redirections(token->content) == 0)
			&& (ft_strcmp(token->content, "|") != 0))
		{
			command->command = ft_strdup(token->content);
			*node = token->next;
		}
	}
}

void	parsing(t_tokens *token, t_command **cmd)
{
	t_command	*command;

	command = *cmd;
	command->files = check_firts_token(&token);
	ft_check_redi(*cmd, &token);
	while (token)
	{
		if (ft_strcmp(token->content, "|") == 0)
			break ;
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
		intialize_command(&command->next);
		parsing(token->next, &command->next);
	}
}
