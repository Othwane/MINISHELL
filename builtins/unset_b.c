/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 23:13:37 by omajdoub          #+#    #+#             */
/*   Updated: 2023/08/23 06:52:59 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	newlen(char *varname)
{
	char	*env_name;
	int		i;
	int		len;

	i = 0;
	len = env_len(g_global.env);
	while (g_global.env[i])
	{
		env_name = ft_strlcpy("", g_global.env[i], get_pos(g_global.env[i]));
		if (ft_strcmp(varname, env_name) == 0)
			len--;
		free(env_name);
		i++;
	}
	return (len);
}

int	new_exportlen(char *varname)
{
	char	*env_name;
	int		i;
	int		len;

	i = 0;
	len = env_len(g_global.export);
	while (g_global.export[i])
	{
		env_name = ft_strlcpy("", g_global.export[i], \
			get_pos(g_global.export[i]));
		if (ft_strcmp(varname, env_name) == 0)
			len--;
		free(env_name);
		i++;
	}
	return (len);
}

int	is_exist_var(char *varname, char *env_name)
{
	int	i;

	i = 0;
	while (g_global.env[i])
	{
		if (ft_strcmp(varname, env_name) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	unset_export(char *arg)
{
	char	**new_exp;
	char	*env_name;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_exp = malloc((new_exportlen(arg) + 1) * sizeof(char *));
	while (g_global.export[i])
	{
		env_name = ft_strlcpy("", g_global.export[i],
				get_pos(g_global.export[i]));
		if (ft_strcmp(arg, env_name) != 0)
			new_exp[j++] = ft_strdup(g_global.export[i]);
		free(env_name);
		free(g_global.export[i++]);
	}
	free(g_global.export);
	new_exp[j] = NULL;
	g_global.export = new_exp;
}

void	unsetenv_b(char *arg)
{
	char	**newenv;
	char	*env_name;
	int		i;
	int		j;

	i = 0;
	j = 0;
	newenv = malloc((newlen(arg) + 1) * sizeof(char *));
	while (g_global.env[i])
	{
		unset_export(arg);
		env_name = ft_strlcpy("", g_global.env[i], get_pos(g_global.env[i]));
		if (is_exist_var(arg, env_name) == 0)
			newenv[j++] = ft_strdup(g_global.env[i]);
		free(env_name);
		free(g_global.env[i++]);
	}
	free(g_global.env);
	newenv[j] = NULL;
	g_global.env = newenv;
}
