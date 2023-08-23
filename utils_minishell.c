/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 06:04:53 by aasselma          #+#    #+#             */
/*   Updated: 2023/08/23 06:46:59 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_global(char **env)
{
	g_global.env = fill_env(env);
	g_global.export = fill_env(env);
	g_global.exit_s = malloc(1 * sizeof(int));
	*g_global.exit_s = 0;
}

void	intialize_command(t_command **command)
{
	t_command	*cmd;

	cmd = *command;
	cmd->next = NULL;
	cmd->command = NULL;
	cmd->arguments = NULL;
	cmd->files = NULL;
	cmd->args = NULL;
	cmd->infile = 0;
	cmd->outfile = 1;
	cmd->cmd_path = NULL;
}

int	ft_atoi(char *ptr)
{
	int	sign;
	int	res;

	sign = 1;
	res = 0;
	while ((*ptr == '\f') || (*ptr == '\n') || (*ptr == '\r') || (*ptr == '\t')
		|| (*ptr == '\v') || (*ptr == ' '))
		ptr++;
	if ((*ptr == '+') || (*ptr == '-'))
	{
		if (*ptr == '-')
			sign *= -1;
		ptr++;
	}
	while ((*ptr >= '0') && (*ptr <= '9'))
	{
		res *= 10;
		res += (*ptr - 48);
		ptr++;
	}
	return (res * sign);
}
