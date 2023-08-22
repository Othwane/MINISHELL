/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 23:13:37 by omajdoub          #+#    #+#             */
/*   Updated: 2023/08/22 00:13:31 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	newlen(char *varname)
{
	char	*env_name;
	int i;
	int len;

	i = 0;
	len = env_len(global.env);
	while (global.env[i])
	{
		env_name = ft_strlcpy("", global.env[i], get_pos(global.env[i]));
		if (ft_strcmp(varname, env_name) == 0)
			len--;
		free(env_name);
		i++;
	}
	return (len);
}

int	is_exist_var(char *varname, char *env_name)
{
	int i;

	i = 0;
	while (global.env[i])
	{
		if (ft_strcmp(varname, env_name) == 0)
			return (1);
		i++;
	}
	return (0);
}

void    unsetenv_b(char *arg)
{
	char	**newenv;
	char	*env_name;
	int		i;
	int		j;

	i = 0;
	j = 0;
	newenv = malloc((newlen(arg) + 1) * sizeof(char*));
	while (global.env[i])
	{
		if (arg && check_nameof_var(arg))
			display_error("minishell: export: `': not a valid identifier\n", arg, 96);
		else
		{		
			// unset_export(arg);
			env_name = ft_strlcpy("", global.env[i], get_pos(global.env[i]));
			if (is_exist_var(arg, env_name) == 0)
				newenv[j++] = ft_strdup(global.env[i]);
			free(env_name);
			free(global.env[i++]);
		}
	}
	free(global.env);
	newenv[j] = NULL;
	global.env = newenv;
}
