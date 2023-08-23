/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 21:57:48 by aasselma          #+#    #+#             */
/*   Updated: 2023/08/23 08:07:55 by aasselma         ###   ########.fr       */
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
			exit(*g_global.exit_s);
		cmd->cmd_path = findpath(cmd->arguments[0], env);
		if (cmd->arguments[0] != NULL)
		{
			if ((access(cmd->cmd_path, F_OK)))
			{
				display_error("minishell: : command not found\n",
					cmd->arguments[0], ':');
				*g_global.exit_s = 127;
			}
			else
				execve(cmd->cmd_path, cmd->arguments, env);
		}
		exit(*g_global.exit_s);
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
				*g_global.exit_s = 127;
			}
			else if (access(command->arguments[0], X_OK))
			{
				write(2, "minishell : Permission denied\n", 30);
				*g_global.exit_s = 126;
			}
			else
				exec_command(command, env);
		}
		else
			exec_command(command, env);
	}
}

void	builtins_command(t_command *command, int *pipefd, int *built_fork)
{
	if (!command->arguments)
		return ;
	if (command->next)
	{
		pipe(pipefd);
		command->outfile = pipefd[1];
	}
	if (is_builtin(command->arguments[0]) && command->next)
		*built_fork = 1;
}

void	inf_outf(t_command *command, int *pipefd)
{
	if (command->outfile != 1)
		close(command->outfile);
	if (command->next)
		command->next->infile = pipefd[0];
	if (command->infile != 0)
		close(command->infile);
}

void	_exec(t_command *command, char **env, int built_fork)
{
	t_files	*files;
	int		*pipefd;
	int		status;

	files = command->files;
	pipefd = malloc(sizeof(int) * 2);
	signal(SIGINT, SIG_IGN);
	while (command)
	{
		builtins_command(command, pipefd, &built_fork);
		if (is_builtin(command->arguments[0]) && !built_fork)
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
		*g_global.exit_s = status >> 8;
	free(pipefd);
	remove_herdoc_file(files);
}
