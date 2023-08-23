/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omajdoub <omajdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 21:57:48 by aasselma          #+#    #+#             */
/*   Updated: 2023/08/23 05:59:48 by omajdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_command(t_command *cmd, char **env)
{
	int	child_pid;

	child_pid = fork();
	if (child_pid == 0)
	{
		set_signal();
		prep_pipe(cmd);
		if (redir_op(cmd, env) > 0)
			exit(*global.exit_s);
		cmd->cmd_path = findpath(cmd->arguments[0], env);
		if (cmd->arguments[0] != NULL)
		{
			if ((access(cmd->cmd_path, F_OK)))
			{
				display_error("minishell: : command not found\n",
					cmd->arguments[0], ':');
				*global.exit_s = 127;
			}
			else
				execve(cmd->cmd_path, cmd->arguments, env);
		}
		exit(*global.exit_s);
	}
}

void	nonbuiltin_command(t_command *command, char **env)
{
	{
		if (command->arguments[0] && (command->arguments[0][0] == '.' \
				&& command->arguments[0][1] == '/'))
		{
			if (access(command->arguments[0], F_OK))
			{
				write(2, "minishell : No such file or directory\n", 39);
				*global.exit_s = 127;
			}
			else if (access(command->arguments[0], X_OK))
			{
				write(2, "minishell : Permission denied\n", 30);
				*global.exit_s = 126;
			}
			else
				exec_command(command, env);
		}
		else
			exec_command(command, env);
	}
}

void	builtins_command(t_command *command, int pipefd[2], int built_fork)
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
}

void	_exec(t_command *command, char **env)
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
		builtins_command(command, pipefd, built_fork);
		if (is_builtin(command->command) && !built_fork)
		{
			exec_builtins(command);
			command = command->next;
			continue ;
		}
		else
			nonbuiltin_command(command, env);
		inf_outf(command, pipefd);
		command = command->next;
	}
	while (wait(&status) > 0)
		*global.exit_s = status >> 8;
	remove_herdoc_file(files);
}

void	inf_outf(t_command *command, int pipefd[2])
{
	if (command->outfile != 1)
		close(command->outfile);
	if (command->next)
		command->next->infile = pipefd[0];
	if (command->infile != 0)
		close(command->infile);
}
