/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 19:16:11 by aasselma          #+#    #+#             */
/*   Updated: 2023/08/23 07:12:46 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_nameof_var(char *var_name)
{
	int	i;

	i = 0;
	while (var_name[i])
	{
		if (i == 0 && ((var_name[i] >= '0' && var_name[i] <= '9')
				|| var_name[i] == '='))
			return (1);
		if (!(var_name[i] >= '0' && var_name[i] <= '9') && !(var_name[i] >= 65
				&& var_name[i] <= 90) && !(var_name[i] >= 97
				&& var_name[i] <= 122) && !((var_name[i] == '_')
				|| (var_name[i] == '=')))
			return (1);
		if (var_name[i] == '=')
			break ;
		i++;
	}
	return (0);
}

int	check_ifexist(char *var)
{
	char	*env_var;
	int		i;
	int		p;

	i = 0;
	while (g_global.export[i])
	{
		p = get_pos(g_global.export[i]);
		env_var = ft_strlcpy("", g_global.export[i], p);
		if (!ft_strcmp(env_var, var))
		{
			free(env_var);
			return (1);
		}
		free(env_var);
		i++;
	}
	return (0);
}

int	ft_check_value(char *env_var, char *env_val, char *value, int index)
{
	if (ft_strcmp(env_val, value) != 0)
	{
		free(g_global.export[index]);
		g_global.export[index] = ft_strjoin(ft_strdup(env_var), value);
		free(env_val);
		free(env_var);
		return (1);
	}
	else
	{
		free(env_val);
		free(env_var);
		return (0);
	}
}

int	ft_var_checker(char *v_n, char *value, int index)
{
	char	*env_var;
	char	*env_val;
	int		len;
	int		p;

	while (g_global.export[index])
	{
		p = get_pos(g_global.export[index]);
		len = ft_strlen(g_global.export[index]) - (p);
		env_var = ft_strlcpy("", g_global.export[index], p);
		env_val = ft_strlcpy("", &g_global.export[index][p], len);
		if (ft_strcmp(env_var, v_n) == 0)
		{
			if (ft_check_value(env_var, env_val, value, index) == 1)
				return (1);
			else
				return (0);
		}
		index++;
		free(env_val);
		free(env_var);
	}
	return (3);
}
