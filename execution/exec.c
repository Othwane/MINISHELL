/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 21:57:48 by aasselma          #+#    #+#             */
/*   Updated: 2023/08/22 08:23:04 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    remove_herdoc_file(t_files *file)
{
	while (file)
	{
		if (file->red_type == HERDOC)
			unlink(file->filename);
		file = file->next;
	}
}

int    shouldfork(char* command)
{
	if (!ft_strcmp(command, "env"))
		return(1);
	return(0);
}

void    prep_pipe(t_command* command)
{
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
}

void    exec_command(t_command* command, char** env)
{
	int child_pid;

	child_pid = fork();
	if (child_pid == 0)
	{
		set_signal();
		prep_pipe(command);
		if (redir_op(command, env) > 0)
			exit(*global.exit_s);
		command->cmd_path = findpath(command->command, env);
		if (command->command != NULL)
		{
			if ((access(command->cmd_path, F_OK)))
			{
				write(2, "minishell :command not found\n", 30);
				*global.exit_s = 127;
			}
			else
				execve(command->cmd_path, command->arguments, env);
		}
		exit(*global.exit_s);
	}
}
void _exec(t_command *command, char **env)
{
	t_files	*files;
	int		pipefd[2];
	int		built_fork;
	int		status;

	files = command->files;    
	built_fork = 0;
	signal(SIGINT, SIG_IGN);
	while (command)
	{
		if (!command->arguments)
			return ;
		if (command->next)
		{
			pipe(pipefd);
			command->outfile = pipefd[1];
		}
		if (is_builtin(command->command) && command->next)
			built_fork += 1;
		if (is_builtin(command->command) && !built_fork)
		{
			exec_builtins(command);
			command = command->next;
			continue ;
		}
		else
		{
			if ((command->arguments[0][0] == '.' && command->arguments[0][1] == '/'))
			{
				if(access(command->arguments[0], F_OK))
				{
					write(2, "minishell : No such file or directory\n", 39);
					*global.exit_s = 127;
					exit(*global.exit_s);            
				}
				else if(access(command->arguments[0], X_OK))
				{
					write(2, "minishell : Permission denied\n", 30);
					*global.exit_s = 126;
					exit(*global.exit_s);            
				}
				else
					exec_command(command, env);
			}
			else
				exec_command(command, env);
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
	// dup2(global.fdin, 0);
	// dup2(global.fdout, 1);
	while(wait(&status) > 0)
		*global.exit_s = status >> 8;
	remove_herdoc_file(files);
}