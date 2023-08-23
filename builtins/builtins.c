/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 04:22:03 by omajdoub          #+#    #+#             */
/*   Updated: 2023/08/23 06:49:15 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(char *arg)
{
	if (!ft_strcmp(arg, "echo") || !ft_strcmp(arg, "cd") || !ft_strcmp(arg,
			"pwd") || !ft_strcmp(arg, "export") || !ft_strcmp(arg, "unset")
		|| !ft_strcmp(arg, "env") || !ft_strcmp(arg, "exit"))
		return (1);
	else
		return (0);
}

int	check_var_n(char *var_name)
{
	int	i;

	i = 0;
	while (var_name[i])
	{
		if (i == 0 && ((var_name[i] >= '0' && var_name[i] <= '9')))
			return (1);
		if (!(var_name[i] >= '0' && var_name[i] <= '9') && !(var_name[i] >= 65
				&& var_name[i] <= 90) && !(var_name[i] >= 97
				&& var_name[i] <= 122) && !((var_name[i] == '_')))
			return (1);
		i++;
	}
	return (0);
}

void	unset_b(char **ar)
{
	int	i;

	i = 1;
	while (ar[i])
	{
		if (ar[i] && check_var_n(ar[i]))
		{
			display_error("minishell: export: `': not a valid identifier\n",
				ar[i], 96);
			i++;
		}
		else
			unsetenv_b(ar[i++]);
	}
}

void	exec_builtins(t_command *command)
{
	if (ft_strcmp(command->arguments[0], "echo") == 0)
		*g_global.exit_s = echo_b(command->arguments);
	else if (ft_strcmp(command->arguments[0], "cd") == 0)
		*g_global.exit_s = cd_b(command->arguments);
	else if (ft_strcmp(command->arguments[0], "pwd") == 0)
		*g_global.exit_s = pwd_b();
	else if (ft_strcmp(command->arguments[0], "export") == 0)
		export_b(command);
	else if (ft_strcmp(command->arguments[0], "unset") == 0)
		unset_b(command->arguments);
	else if (ft_strcmp(command->arguments[0], "env") == 0)
		env_b(NULL);
	else if (ft_strcmp(command->arguments[0], "exit") == 0)
		exit_b(command, 1);
}
