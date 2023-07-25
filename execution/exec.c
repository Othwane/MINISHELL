#include "../minishell.h"


void	_exec(t_command *command, char** env)
{
		int pipefd[2];
	while (command)
	{
		if (!command->arguments)
			return;
		// check for pipes
		if (command->next)
		{
			pipe(pipefd);
			command->outfile = pipefd[1];
		}
		// check redirections
		int child_pid = fork();
		if (!child_pid)
		{
			// dup2 stdin if its not 0
			if (command->infile != 0)
			{
				dup2(command->infile, 0);
				close(command->infile);
			}
			// dup2 stdout if its not 1
			if (command->outfile != 1)
			{
				dup2(command->outfile, 1);
				close(command->outfile);
			}
			execve(command->command, command->arguments, env);
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
