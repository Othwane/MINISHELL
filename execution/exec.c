#include "../minishell.h"


void	_exec(t_command *command, char** env)
{
	while (command)
	{
		// check for pipes
		if (command->next) {}
		// check redirections
		int child_pid = fork();
		if (!child_pid)
		{
			// dup2 stdin if its not 0
			// dup2 stdout if its not 1
			execve(command->argv[0], command->argv, env);
		}
		// do not wait for each command one by one, execute all of them at once then wait for them all to finish
		wait(&child_pid);
		command = command->next;
	}
	// save the last command exit status, maybe return it
}
