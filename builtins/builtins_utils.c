/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 19:16:11 by aasselma          #+#    #+#             */
/*   Updated: 2023/08/23 01:09:11 by aasselma         ###   ########.fr       */
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
	return (i);
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
		if (var_name[i] == '=')
			break ;
		i++;
	}
	return (0);
}

int	check_ifexist(char *var)
{
	int	i;
	
	i = 0;
	while (global.export[i])
	{
		if (!ft_strcmp(global.export[i], var))
			return (1);
		i++;
	}
	return (0);
}
int	ft_var_checker(char *v_n, char *value, int index)
{
	char	*env_var;
	char	*env_val;
	int		len;
	int		p;

	while(global.export[index])
	{
		p = get_pos(global.export[index]);
		len = ft_strlen(global.export[index]) - (p);
		env_var = ft_strlcpy("", global.export[index], p);
		env_val = ft_strlcpy("", &global.export[index][p], len);
		if (ft_strcmp(env_var, v_n) == 0)
		{
			if (ft_strcmp(env_val, value) != 0)
			{
				free(global.export[index]);
				global.export[index]  = ft_strjoin(ft_strdup(env_var), value);
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
		index++;
		free(env_val);
		free(env_var);
	}
	return (3);
}
