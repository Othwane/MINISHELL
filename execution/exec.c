/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 21:57:48 by aasselma          #+#    #+#             */
/*   Updated: 2023/08/20 03:47:42 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_herdoc_file(t_files *file)
{
	while (file)
	{
		if (file->red_type == HERDOC)
			unlink(file->filename);
		file = file->next;
	}
}

void _exec(t_command *command, char **env)
{
	t_files	*files;
	int pipefd[2];

	files = command->files;	
	while (command)
	{
		if (!command->arguments)
			return ;
		if (command->next)
		{
			pipe(pipefd);
			command->outfile = pipefd[1];
		}
		if (is_builtin(command->command))
		{
			exec_builtins(command);
			command = command->next;
		}
		else
		{
		signal(SIGINT, SIG_IGN);
		int child_pid = fork();
		if (child_pid == 0)
		{
			set_signal();
			if (command->infile != 0)
			{
				dup2(command->infile, 0);
				close(command->infile);
			}
			if (command->outfile != 1)
			{
				dup2(command->outfile, 1);
				close(command->outfile);
			}
			redir_op(command, env);
			command->cmd_path = findpath(command->command, env);
			if (command->command != NULL)
			{
				if ((access(command->cmd_path, F_OK)))
					write(2, "~minishell$> :command not found.\n", 33);
				else
					execve(command->cmd_path, command->arguments, env);
			}
			exit(1);
		}
		}
		if (command->outfile != 1)
			close(command->outfile);
		if (command->next)
			command->next->infile = pipefd[0];
		if (command->infile != 0)
			close(command->infile);
		// do not wait for each command one by one, execute all of them at once then wait for them all to finish
		// wait(&child_pid);
		command = command->next;
	}
	while(wait(NULL) > 0);
	remove_herdoc_file(files);
}
	// save the last command exit status, maybe return it
