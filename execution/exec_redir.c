/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omajdoub <omajdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 04:40:49 by omajdoub          #+#    #+#             */
/*   Updated: 2023/08/23 05:39:43 by omajdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	input_redir(t_command *command)
{
	int	infile_fd;

	infile_fd = open(command->files->filename, O_RDONLY);
	if (infile_fd < 0)
	{
		write(2, "minishell: No such file or directory\n", 37);
		*global.exit_s = 1;
		return (*global.exit_s);
	}
	dup2(infile_fd, 0);
	close(infile_fd);
	return (0);
}

int	output_redir(t_command *command)
{
	int	outfile_fd;

	outfile_fd = open(command->files->filename, O_WRONLY | O_CREAT | O_TRUNC, \
		0644);
	if (outfile_fd < 0)
	{
		write(2, "minishell: No such file or directory\n", 37);
		*global.exit_s = 1;
		return (*global.exit_s);
	}
	dup2(outfile_fd, 1);
	close(outfile_fd);
	return (0);
}

int	append_redir(t_command *command)
{
	int	outfile_fd;

	outfile_fd = open(command->files->filename, O_WRONLY | O_CREAT | O_APPEND, \
		0644);
	if (outfile_fd < 0)
	{
		write(2, "minishell: No such file or directory\n", 37);
		*global.exit_s = 1;
		return (*global.exit_s);
	}
	dup2(outfile_fd, 1);
	close(outfile_fd);
	return (0);
}

void	herdoc_redir(t_command *command, char **env)
{
	int	fd[2];

	pipe(fd);
	ft_herdoc(fd[1], command, env);
	dup2(fd[0], 0);
	close(fd[1]);
	close(fd[0]);
}

int	redir_op(t_command *command, char **env)
{
	while (command->files)
	{
		if (command->files->red_type == INPUT)
			*global.exit_s = input_redir(command);
		else if (command->files->red_type == OUTPUT)
			*global.exit_s = output_redir(command);
		else if (command->files->red_type == APPEND)
			*global.exit_s = append_redir(command);
		else if (command->files->red_type == HERDOC)
			herdoc_redir(command, env);
		if (*global.exit_s == 1)
			return (*global.exit_s);
		command->files = command->files->next;
	}
	return (0);
}
