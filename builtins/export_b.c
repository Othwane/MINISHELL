/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_b.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 23:13:35 by omajdoub          #+#    #+#             */
/*   Updated: 2023/08/21 20:05:06 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_function(char *v_n, char *value, int index)
{
	char	*env_var;
	char	*env_val;
	int		len;
	int		p;

	p = get_pos(global.env[index]);
	len = ft_strlen(global.env[index]) - (p);
	env_var = ft_strlcpy("", global.env[index], p);
	env_val = ft_strlcpy("", &global.env[index][p], len);
	if (ft_strcmp(env_var, v_n) == 0)
	{
		if (ft_strcmp(env_val, value) != 0)
		{
			global.env[index] = ft_strjoin(ft_strdup(env_var), value);
			free(env_var);
			free(env_val);
			return (1);
		}
		else
			return (0);
	}
	free(env_var);
	free(env_val);
	return (3);
}

int	is_exist(char *var, int p)
{
	char	*varname;
	char	*value;
	int	i;
	int	res;

	i = 0;
	res = 0;
	varname = ft_strlcpy("", var, p);
	value = ft_strlcpy("", &var[p], ft_strlen(var) - (i));
	if (global.env[0] == NULL)
		return (3);
	while(global.env[i])
	{
		if (ft_function(varname, value, i) == 3)
			res = 3;
		else
			return (1);
		i++;
	}
	free(varname);
	return (res);
}
void	add_to_env(char *var)
{
	int		i;

	i = 0;
	while(var[i])
	{
		if (var[i] == '=')
		{
			if (is_exist(var, i) == 3)
				global.env = add_newenv(global.env, var);
		}
		i++;
	}
}

void	add_to_export(char *newvar)
{
	char	*varname;
	char	*value;
	int	i;
	int	p;

	i = 0;
	p = get_pos(newvar);
	if (p == ft_strlen(newvar))
	{
		if (check_ifexist(newvar) == 0)
			global.export = add_newenv(global.export, newvar);
	}
	else
	{
		varname = ft_strlcpy("", newvar, p);
		value = ft_strlcpy("", &newvar[p], ft_strlen(newvar) - (i));
		if (ft_var_checker(varname, value, i) == 3)
			global.export = add_newenv(global.export, newvar);
	}
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
			add_to_export(cmd->arguments[i]);
			add_to_env(cmd->arguments[i]);
			i++;
		}
	}
	if (cmd->arguments[1] == NULL)
		env_b(global.export);
}
