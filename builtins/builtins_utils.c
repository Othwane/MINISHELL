/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 19:16:11 by aasselma          #+#    #+#             */
/*   Updated: 2023/08/20 03:45:11 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_pos(char *var)
{
	int	i;
	
	i = 0;
	while (var[i])
	{
		if (var[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

int	env_len(char **env)
{
	int	i;
	
	i = 0;
	while (env[i])
		i++;
	return (i);
}
int	check_nameof_var(char *var_name)
{
	int	i;

	i = 0;
	while (var_name[i])
	{
		if (i == 0 && ((var_name[i] >= '0' && var_name[i] <= '9')
			|| var_name[i] == '='))
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

// int	check_ifexist()
// {
	
// }