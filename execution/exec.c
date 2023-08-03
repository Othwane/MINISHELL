/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omajdoub <omajdoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 21:57:48 by aasselma          #+#    #+#             */
/*   Updated: 2023/08/03 13:42:26 by omajdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	_exec(t_command *command, char** env)
{
	int pipefd[2];
	while (command)
	{
		if (!command->arguments)
			return;
		if (command->next)
		{
			pipe(pipefd);
			command->outfile = pipefd[1];
		}
		int child_pid = fork();
		if (!child_pid)
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
			command->cmd_path = findpath(command->command, env);
			execve(command->cmd_path, command->arguments, env);
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
	while (wait(NULL) > 0);
	// save the last command exit status, maybe return it
}
