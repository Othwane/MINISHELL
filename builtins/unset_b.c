/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 23:13:37 by omajdoub          #+#    #+#             */
/*   Updated: 2023/08/19 23:33:34 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	newlen(char **varname)
{
	char	*env_name;
	int i;
	int j;
	int len;

	j = 0;
	len = env_len(global.env);
	while (varname[j])
	{
		i = 1;
		while (global.env[i])
		{
			env_name = ft_strlcpy("", global.env[i], get_pos(global.env[i]));
			if (ft_strcmp(varname[j], env_name) == 0)
				len--;
			free(env_name);
			i++;
		}
		j++;
	}
	return (len);
}

int	is_exist_var(char **varname, char *env_name)
{
	int i;
	int j;

	j = 0;
	while (varname[j])
	{
		i = 1;
		while (global.env[i])
		{
			if (ft_strcmp(varname[j], env_name) == 0)
				return (1);
			i++;
		}
		j++;
	}
	return (0);
}

void    unsetenv_b(char **args)
{
	char	**newenv;
	char	*env_name;
	int		i;
	int		j;

	i = 0;
	j = 0;
	newenv = malloc((newlen(args) + 1) * sizeof(char*));
	while (global.env[i])
	{
		env_name = ft_strlcpy("", global.env[i], get_pos(global.env[i]));
		if (is_exist_var(args, env_name) == 0)
			newenv[j++] = ft_strdup(global.env[i]);
		if (env_name)
			free(env_name);
		free(global.env[i++]);
	}
	free(global.env);
	newenv[j] = NULL;
	global.env = newenv;
}
