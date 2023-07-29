/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_onecommand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 16:05:27 by aasselma          #+#    #+#             */
/*   Updated: 2023/07/29 18:47:06 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    ft_execute(t_command *cmd, char **paths)
{
    int i;

    i = 0;
	while(paths[i])
	{
		if ((access(paths[i], F_OK)) != 0 && i == cmd->cmd_num)
            printf("~minishell$>: %s: command not found\n", cmd->command);
		else
		    execv(paths[i], cmd->arguments);
        i++;
	}
}

void	exec_onecmd(t_command *cmd, char **paths)
{
	int	i;
	int	pid;

	i = 0;
	pid = fork();
    if (pid == -1)
        perror("fork : ");
	else if (pid == 0)
	{		
		while(paths[i])
		{
			paths[i] = ft_strjoin(paths[i], cmd->command);
			i++;
		}
        ft_execute(cmd, paths);
		exit(1);
	}
	wait(NULL);
}
