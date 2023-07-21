#include "../minishell.h"


void	_exec(t_command *command)
{
	while (command)
	{
		// execute command node
		command = command->next;
	}

}
