/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 06:41:05 by aasselma          #+#    #+#             */
/*   Updated: 2023/08/18 08:51:32 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_args(t_args **args, char *content)
{
	t_args	*newnode;
	t_args	*tmp;

	newnode = malloc(sizeof(t_args));
	newnode->args = ft_strdup(content);
	newnode->next = NULL;
	if (*args == NULL)
		*args = newnode;
	else
	{
		tmp = *args;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = newnode;
	}
}

void	add_files(t_files **files, char *content, char *rdac)
{
	t_files	*newnode;
	t_files	*tmp;

	newnode = malloc(sizeof(t_files));
	newnode->filename = ft_strdup(content);
	newnode->quote = in_qoute(content);
	if (ft_strcmp(rdac, ">") == 0)
		newnode->red_type = OUTPUT;
	else if (ft_strcmp(rdac, "<") == 0)
		newnode->red_type = INPUT;
	else if (ft_strcmp(rdac, ">>") == 0)
		newnode->red_type = APPEND;
	else if (ft_strcmp(rdac, "<<") == 0)
		newnode->red_type = HERDOC;
	newnode->next = NULL;
	if (*files == NULL)
		*files = newnode;
	else
	{
		tmp = *files;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = newnode;
	}
}

void	add_var(t_env **env, char *content, int s_p, int e_p)
{
	t_env	*newnode;

	newnode = malloc(sizeof(t_env));
	newnode->s_p = (s_p - 1);
	newnode->e_p = (e_p);
	newnode->value = ft_strdup(content);
	newnode->next = NULL;
	*env = newnode;
}
