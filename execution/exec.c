/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omajdoub <omajdoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 21:57:48 by aasselma          #+#    #+#             */
/*   Updated: 2023/08/13 06:28:27 by omajdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	my_herdoc(int fd, char *filename)
{
	char	*input;
	char	*newinput;
	char	*args[3];
	int		pid;

	while(1)
	{
		input = readline(">");
		if (ft_strlen(input) != 0)
		{
			if (ft_strcmp(input, filename) == 0)
			{
				pid = fork();
				if (pid == 0)
				{
					args[0] = "rm";
					args[1] = filename;
					args[2] = NULL;
					execv("/bin/rm", args);
					exit(0);
				}
				wait(0);
				break;
			}
			newinput = ft_strjoin(input, "\n");
			write(fd, &newinput, ft_strlen(newinput));
			free(newinput);
		}
		free(input);
	}
	return (0);
}

void	child_proc(t_command *command, char **env)
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
	redir_op(command);
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


void _exec(t_command *command, char** env)
{
	int child_pid;
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
		if (is_builtin(command->command))
		{
			exec_builtins(command, env);
			command = command->next;
			continue;
		}
		child_pid = fork();
		if (!child_pid)
			child_proc(command, env);
		if (command->outfile != 1)
			close(command->outfile);
		if (command->next)
			command->next->infile = pipefd[0];
		if (command->infile != 0)
			close(command->infile);
		command = command->next;
	}
	while (wait(NULL) > 0);
}
	// save the last command exit status, maybe return it
