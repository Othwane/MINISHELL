/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omajdoub <omajdoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 06:41:05 by aasselma          #+#    #+#             */
/*   Updated: 2023/07/22 01:03:25 by omajdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	add_files(t_files **files, char *content, char *rdac)
{
	t_files	*newnode;
	t_files	*tmp;

	newnode = malloc(sizeof(t_files));
	newnode->filename = ft_strdup(content);
	newnode->redairection = ft_strdup(rdac);
	if (ft_strcmp(rdac, ">") == 0 || ft_strcmp(rdac, ">>") == 0)
		newnode->red_type = OUTPUT;
	else if (ft_strcmp(rdac, "<") == 0)
		newnode->red_type = INPUT;
	else if (ft_strcmp(rdac, "<<") == 0)
		newnode->red_type = HERDOCE;
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

void	add_var(t_env **env, char *content)
{
	t_env	*newnode;
	t_env	*tmp;

	newnode = malloc(sizeof(t_env));
	newnode->value = ft_strdup(content);
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
