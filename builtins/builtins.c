/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omajdoub <omajdoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 04:22:03 by omajdoub          #+#    #+#             */
/*   Updated: 2023/08/13 16:02:07 by omajdoub         ###   ########.fr       */
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

void	exec_builtins(t_command *command, char **env)
{
	(void)env;

	if(ft_strcmp(command->command, "echo") == 0)
		echo_b(command->arguments);
	else if (ft_strcmp(command->command, "cd") == 0)
		cd_b(command->arguments);
	else if (ft_strcmp(command->command, "pwd") == 0)
		pwd_b();
	// else if (ft_strcmp(args->args, "export") == 0)
	// 	export_b(, env);
	// else if (ft_strcmp(args->args, "unset") == 0)
	// 	unset_b(, env);
	// else if (ft_strcmp(args->args, "env") == 0)
	// 	env_b();
	else if (ft_strcmp(command->command, "exit") == 0)
		exit_b();
}
