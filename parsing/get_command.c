/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 06:41:05 by aasselma          #+#    #+#             */
/*   Updated: 2023/07/29 16:47:21 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_command(t_command **command, char *content)
{
	t_command	*cmd;

	cmd = *command;
	if (cmd->cmd_num == 0)
	{
		cmd->cmd_num++;
		cmd->command = ft_strdup(content);
		cmd->next = NULL;
	}
	else
	{
		cmd->command = ft_strdup(content);
		cmd->next = NULL;
	}
}

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

void	add_var(t_env **env, char *content, int	num)
{
	t_env	*newnode;
	t_env	*tmp;

	newnode = malloc(sizeof(t_env));
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
