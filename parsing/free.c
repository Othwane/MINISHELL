/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omajdoub <omajdoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 22:34:27 by aasselma          #+#    #+#             */
/*   Updated: 2023/07/22 00:53:10 by omajdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_command(t_command *my_list)
{
	t_command	*node_head;
	int			i;
	t_files		*file_head;

	i = 1;
	node_head = my_list;
	while(node_head)
	{
		printf("Command %s \n", node_head->argv[0]);
		while(node_head->argv[i])
		{
			printf("Args %s \n", node_head->argv[i]);
			i++;
		}
		i = 1;
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
	int			i;

	i = 0;
	while (command)
	{
		while (command->argv[i])
		{
			free(command->argv[i]);
			i++;
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
