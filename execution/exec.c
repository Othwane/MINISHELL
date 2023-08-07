/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omajdoub <omajdoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 21:57:48 by aasselma          #+#    #+#             */
/*   Updated: 2023/08/07 13:39:52 by omajdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <fcntl.h>

void _exec(t_command *command, char** env)
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
			while (command->files)
			{
            	// Input Redirection: <
				if (command->files->red_type == INPUT)
				{
					int infile_fd = open(command->files->filename, O_RDONLY);
					if (infile_fd < 0)
					{
						perror("Error opening input file");
						exit(EXIT_FAILURE);
					}
					dup2(infile_fd, 0);
					close(infile_fd);
				}
				// Output Redirection: >
				if (command->files->red_type == OUTPUT)
				{
					int outfile_fd = open(command->files->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
					if (outfile_fd < 0)
					{
						perror("Error opening output file");
						exit(EXIT_FAILURE);
					}
					dup2(outfile_fd, 1);
					close(outfile_fd);
				}
				// Append Redirection: >>
				if (command->files->red_type == APPEND)
				{
					int outfile_fd = open(command->files->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
					if (outfile_fd < 0)
					{
						perror("Error opening output file");
						exit(EXIT_FAILURE);
					}
					dup2(outfile_fd, 1);
					close(outfile_fd);
				}
				command->files = command->files->next;
			}
            command->cmd_path = findpath(command->command, env);
            if ((access(command->cmd_path, F_OK)))
                write(2, "command not found.\n", 20);
            else
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
}
	// save the last command exit status, maybe return it
