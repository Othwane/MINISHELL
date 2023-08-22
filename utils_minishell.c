/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 06:04:53 by aasselma          #+#    #+#             */
/*   Updated: 2023/08/22 06:47:51 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    init_global(char **env)
{
    global.env = fill_env(env);
	global.export = fill_env(env);
	global.exit_s = malloc(1 * sizeof(int));
	*global.exit_s = 0;
	// global.fdin = dup(0);
	// global.fdout = dup(1);
}

void    intialize_command(t_command **command)
{
    t_command   *cmd;

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