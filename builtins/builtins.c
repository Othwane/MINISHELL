/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 04:22:03 by omajdoub          #+#    #+#             */
/*   Updated: 2023/08/19 11:14:12 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		is_builtin(char *arg)
{
	if (!ft_strcmp(arg, "echo") || \
		!ft_strcmp(arg, "cd") || \
		!ft_strcmp(arg, "pwd") || \
		!ft_strcmp(arg, "export") || \
		!ft_strcmp(arg, "unset") || \
		!ft_strcmp(arg, "env") || \
		!ft_strcmp(arg, "exit"))
		return (1);
	else
		return (0);
}

void	exec_builtins(t_command *command)
{
	if(ft_strcmp(command->arguments[0], "echo") == 0)
		echo_b(command->arguments);
	else if (ft_strcmp(command->arguments[0], "cd") == 0)
		cd_b(command->arguments);
	else if (ft_strcmp(command->arguments[0], "pwd") == 0)
		pwd_b();
	else if (ft_strcmp(command->arguments[0], "export") == 0)
		export_b(command);
	// else if (ft_strcmp(args->args, "unset") == 0)
	// 	unset_b(, env);
	else if (ft_strcmp(command->arguments[0], "env") == 0)
		env_b("");
	else if (ft_strcmp(command->arguments[0], "exit") == 0)
		exit_b();
}
