/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getpath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 16:05:27 by aasselma          #+#    #+#             */
/*   Updated: 2023/08/22 02:17:53 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


char	**getpath(char **envp)
{
	int		i;
	char	**tmpath;

	i = 0;
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
	return (command);
}

char	*checkcmd(char **envp, char **envsplited, char *cmd)
{
	int		i;
	char	*command;

	i = 0;
	if (envp)
		envsplited = getpath(envp);
	while (envsplited && envsplited[i])
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
	envsplited = NULL;
	if (cmd == NULL)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (!access(cmd, F_OK))
			return (cmd);
	}
	command = checkcmd(envp, envsplited, cmd);
	return (command);
}
