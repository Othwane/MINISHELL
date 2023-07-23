/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 22:34:27 by aasselma          #+#    #+#             */
/*   Updated: 2023/07/20 01:24:11 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_command(t_command *my_list)
{
	t_command	*node_head;
	t_args		*arg_head;
	t_files		*file_head;

	node_head = my_list;
	while(node_head)
	{
		printf("Command %s \n", node_head->command);
		arg_head = node_head->args;
		while(arg_head)
		{
			printf("Args %s \n", arg_head->args);
			arg_head = arg_head->next;
		}
		file_head = node_head->files;
		while(file_head)
		{
			printf("red %s \n", file_head->redairection);
			printf("File name %s \n", file_head->filename);
			file_head = file_head->next;
		}
		printf("\n------------\n");
		node_head = node_head->next;
	}
}

void	print_list(t_tokens *my_list)
{
	t_tokens	*node_head;
	
	node_head = my_list;
	while(node_head)
	{
		printf("%s ", node_head->content);
		node_head = node_head->next;
	}
	printf("\n");
}

void	free_command(t_command *command)
{
	void		*tmp;
	t_command	*cmd;
	
	while (command)
	{
		while (command->args)
		{
			free(command->args->args);
			tmp	= command->args;
			command->args = command->args->next;
			free(tmp);
		}
		while (command->files)
		{
			free(command->files->filename);
			free(command->files->redairection);
			tmp = command->files;
			command->files = command->files->next;
			free(tmp);
		}
		cmd = command;
		command = command->next;
		free(cmd->command);
		free(cmd);
	}
}

void	free_tokens(t_tokens *token)
{
	while(token)
	{
		free(token->content);
		free(token);
		token = token->next;
	}
}
