/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 15:05:32 by aasselma          #+#    #+#             */
/*   Updated: 2023/07/29 15:21:40 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*p;
	size_t	x;

	x = 0;
	if (!s1 || !s2)
		return (NULL);
	p = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!p)
		return (NULL);
	while (s1[x])
	{
		p[x] = s1[x];
		x++;
	}
	x = 0;
	while (s2[x])
	{
		p[ft_strlen(s1) + x] = s2[x];
		x++;
	}
	p[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	return (p);
}

void	ft_pipe(t_command *cmd, char **paths, int *pipefd, int c_num)
{
	int	i;

	i = 0;
	while(paths[i])
	{
		paths[i] = ft_strjoin(paths[i], cmd->command);
		i++;
	}
	i = 0;
	if (c_num == 1)
		close(pipefd[0]); // Close the read end of the pipe
	else if (c_num == (cmd->cmd_num->cmd_num))
		close(pipefd[1]); // Close the write end of the pipe
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	while(paths[i])
		execv(paths[i++], cmd->arguments);
}