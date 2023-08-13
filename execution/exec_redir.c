/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omajdoub <omajdoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 04:40:49 by omajdoub          #+#    #+#             */
/*   Updated: 2023/08/12 04:44:27 by omajdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	input_redir(t_command *command)
{
	int infile_fd;

	infile_fd = open(command->files->filename, O_RDONLY);
	if (infile_fd < 0)
	{
		perror("Error opening input file");
		exit(EXIT_FAILURE);
	}
	dup2(infile_fd, 0);
	close(infile_fd);
}

void	output_redir(t_command *command)
{
	int outfile_fd;

	outfile_fd = open(command->files->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd < 0)
	{
		perror("Error opening output file");
		exit(EXIT_FAILURE);
	}
	dup2(outfile_fd, 1);
	close(outfile_fd);
}

void	append_redir(t_command *command)
{
	int outfile_fd;

	outfile_fd = open(command->files->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (outfile_fd < 0)
	{
		perror("Error opening output file");
		exit(EXIT_FAILURE);
	}
	dup2(outfile_fd, 1);
	close(outfile_fd);
}

void	herdoc_redir(t_command *command)
{
	int outfile_fd;

	outfile_fd = open(command->files->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (outfile_fd < 0)
	{
		perror("Error opening output file");
		exit(EXIT_FAILURE);
	}
	my_herdoc(outfile_fd, command->files->filename);
	dup2(outfile_fd, 1);
	close(outfile_fd);
}

void	redir_op(t_command *command)
{
	while (command->files)
	{
		if (command->files->red_type == INPUT)
			input_redir(command);
		else if (command->files->red_type == OUTPUT)
			output_redir(command);
		else if (command->files->red_type == APPEND)
			append_redir(command);
		else if (command->files->red_type == HERDOC)
			herdoc_redir(command);
		command->files = command->files->next;
	}
}
