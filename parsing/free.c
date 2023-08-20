/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 22:34:27 by aasselma          #+#    #+#             */
/*   Updated: 2023/08/19 16:06:10 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_command(t_command *my_list)
{
	t_command	*node_head;
	t_files		*file_head;
	int			i;

	node_head = my_list;
	while(node_head)
	{
		i = 1;
		printf("Command %s \n", node_head->command);
		while(node_head->arguments[i])
			printf("	Args %s \n", node_head->arguments[i++]);
		file_head = node_head->files;
		while(file_head)
		{
			printf("			File name %s \n", file_head->filename);
			printf("			qoute %d \n", file_head->quote);
			file_head = file_head->next;
		}
		printf("\n------------\n");
		node_head = node_head->next;
	}
}


void	free_command(t_command *command)
{
	void		*tmp;
	t_command	*cmd;
	int			i;

	while (command)
	{
		i = 0;
		while (command->files)
		{
			free(command->files->filename);
			tmp = command->files;
			command->files = command->files->next;
			free(tmp);
		}
		if (command->arguments)
		{
			while(command->arguments[i])
				free(command->arguments[i++]);
			free(command->arguments);
		}
		cmd = command;
		command = command->next;
		free(cmd->command);
		free(cmd);
	}
}

void	free_resources(t_tokens *token)
{
	t_tokens	*tmp;
	while(token)
	{
		tmp = token;
		token = token->next;
		free(tmp->content);
		free(tmp);
	}
}

void	free_env(void)
{
	int	i;

	i = 0;
	while (global.env[i])
		free(global.env[i++]);
	free(global.env);
	i = 0;
	while (global.export[i])
		free(global.export[i++]);
	free(global.export);
}
