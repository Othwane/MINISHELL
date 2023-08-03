/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_onecommand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omajdoub <omajdoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 16:05:27 by aasselma          #+#    #+#             */
/*   Updated: 2023/08/03 04:11:36 by omajdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void    ft_execute(t_command *cmd, char **paths)
// {
//     int i;

//     i = 0;
// 	while(paths[i])
// 	{
// 		if ((access(paths[i], F_OK)) != 0 && i == cmd->cmd_num)
//             printf("~minishell$>: %s: command not found\n", cmd->command);
// 		else
// 		    execv(paths[i], cmd->arguments);
//         i++;
// 	}
// }

// void	exec_onecmd(t_command *cmd, char **paths)
// {
// 	int	i;
// 	int	pid;

// 	i = 0;
// 	pid = fork();
//     if (pid == -1)
//         perror("fork : ");
// 	else if (pid == 0)
// 	{
// 		while(paths[i])
// 		{
// 			paths[i] = ft_strjoin(paths[i], cmd->command);
// 			i++;
// 		}
//         ft_execute(cmd, paths);
// 		exit(1);
// 	}
// 	wait(NULL);
// }

char	**getpath(char **envp)
{
	int		i;
	char	**tmpath;

	i = 0;
	if (!envp[i])
		tmpath = ft_split("/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin", ':');
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			tmpath = ft_split(envp[i] + 5, ':');
		i++;
	}
	return (tmpath);
}

char	*joinslash_cmd(char *envsplited, char *cmd)
{
	char	*command;
	char	*slash;

	slash = ft_strjoin(envsplited, "/");
	command = ft_strjoin(slash, cmd);
	free(slash);
	free(envsplited);
	return (command);
}

char	*checkcmd(char **envp, char **envsplited, char *cmd)
{
	int		i;
	char	*command;

	i = 0;
	envsplited = getpath(envp);
	while (envsplited[i])
	{
		command = joinslash_cmd(envsplited[i], cmd);
		if (access(command, F_OK) == 0)
		{
			free(envsplited);
			return (command);
		}
		i++;
		free(command);
	}
	free(envsplited);
	return (0);
}

char	*findpath(char *cmd, char **envp)
{
	int		i;
	char	**envsplited;
	char	*command;

	i = 0;
	if (ft_strchr(cmd, '/'))
	{
		if (!access(cmd, F_OK))
			return (cmd);
	}
	command = checkcmd(envp, envsplited, cmd);
	return (command);
}
