/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_b.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 23:13:35 by omajdoub          #+#    #+#             */
/*   Updated: 2023/08/19 13:15:40 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_nameof_var(char *var_name)
{
	int	i;

	i = 0;
	while (var_name[i])
	{
		if (i == 0 && (var_name[i] >= '0' && var_name[i] <= '9'))
			return (1);
		if (!(var_name[i] >= '0' && var_name[i] <= '9')
				&& !(var_name[i] >= 65 && var_name[i] <= 90)
				&& !(var_name[i] >= 97 && var_name[i] <= 122)
				&& !((var_name[i] == '_') || (var_name[i] == '=')))
				return (1);
		i++;
	}
	return (0);
}

void	export_b(t_command *cmd)
{
	int	i;

	i = 1;
	while (cmd->arguments[i])
	{
		if (check_nameof_var(cmd->arguments[i]))
		{
			write(2, "~minishell$>: export: `", 23);
			write(2, cmd->arguments[i], ft_strlen(cmd->arguments[i]));
			write(2, "': not a valid identifier\n", 26);
			global.exit_s = EXIT_FAILURE;
			i++;
		}
		else
		{
			global.env = add_newenv(global.env, cmd->arguments[i]);
			i++;
		}
	}
	if (cmd->arguments[1] == NULL)
		env_b("declare -x ");
}
