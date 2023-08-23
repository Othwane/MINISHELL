/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_syntax_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 06:51:22 by aasselma          #+#    #+#             */
/*   Updated: 2023/07/25 01:46:15 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_pipes(t_tokens *token)
{
	if (ft_strcmp(token->content, "|") == 0)
		return (1);
	while (token->next)
	{
		if (ft_strcmp(token->content, "|") == 0)
		{
			if (ft_strcmp(token->content, token->next->content) == 0)
				return (1);
		}
		token = token->next;
	}
	if (ft_strcmp(token->content, "|") == 0)
		return (1);
	return (0);
}

int	check_redirections(t_tokens *token)
{
	while (token->next)
	{
		if (ft_strcmp(token->content, ">") == 0 || ft_strcmp(token->content,
				">>") == 0 || ft_strcmp(token->content, "<") == 0
			|| ft_strcmp(token->content, "<<") == 0)
		{
			if (ft_strcmp(token->content, token->next->content) == 0)
				return (1);
			else if (ft_strcmp(token->next->content, "<") == 0)
				return (1);
			else if (ft_strcmp(token->next->content, ">") == 0)
				return (1);
			else if (ft_strcmp(token->next->content, "<<") == 0)
				return (1);
			else if (ft_strcmp(token->next->content, ">>") == 0)
				return (1);
		}
		token = token->next;
	}
	if (token->next == NULL && (ft_strcmp(token->content, ">") == 0
			|| ft_strcmp(token->content, ">>") == 0 || ft_strcmp(token->content,
				"<") == 0 || ft_strcmp(token->content, "<<") == 0))
		return (1);
	return (0);
}

int	check_syntax_error(t_tokens *token)
{
	if (token->next == NULL && (ft_strcmp(token->content, ">") == 0
			|| ft_strcmp(token->content, ">>") == 0 || ft_strcmp(token->content,
				"<") == 0 || ft_strcmp(token->content, "<<") == 0))
		return (1);
	else if (token->next != NULL && (ft_strcmp(token->content, ">") == 0
			|| ft_strcmp(token->content, ">>") == 0 || ft_strcmp(token->content,
				"<") == 0 || ft_strcmp(token->content, "<<") == 0))
	{
		if (token->next != NULL && (ft_strcmp(token->next->content, "|") == 0))
			return (1);
	}
	if (check_redirections(token) == 1)
		return (1);
	if (check_pipes(token))
		return (1);
	return (0);
}
