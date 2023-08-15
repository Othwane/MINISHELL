/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 06:41:05 by aasselma          #+#    #+#             */
/*   Updated: 2023/08/13 06:49:49 by aasselma         ###   ########.fr       */
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
		while(tmp->next)
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

void	add_var(t_env **env, char *content, int	num, int start)
{
	t_env	*newnode;
	t_env	*tmp;

	newnode = malloc(sizeof(t_env));
	newnode->index = (start - 1);
	if (num > 0)
		newnode->value = ft_strdup(content);
	else
		newnode->value = NULL;
	newnode->next = NULL;
	if (*env == NULL)
		*env = newnode;
	else
	{
		tmp = *env;
		while(tmp->next)
			tmp = tmp->next;
		tmp->next = newnode;
	}
}
