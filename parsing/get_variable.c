/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 17:21:22 by aasselma          #+#    #+#             */
/*   Updated: 2023/08/23 04:41:58 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valid(char c, int sign)
{
	if ((c >= '0' && c <= '9') || c == '_')
		return (1);
	if (c >= 65 && c <= 90)
		return (1);
	if (c >= 97 && c <= 122)
		return (1);
	else if (sign == 0 && (c == '?' || c == '$'))
		return (1);
	return (0);
}

char	*copy_name(char *var, int sign)
{
	char	*var_name;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (sign == 1)
	{
		var_name = malloc(2 * sizeof(char));
		var_name[0] = var[0];
		var_name[1] = '\0';
	}
	else
	{
		var_name = malloc((ft_strlen(var) + 1) * sizeof(char));
		while (is_valid(var[i], 1) == 1)
			var_name[j++] = var[i++];
		var_name[j] = '\0';
	}
	return (var_name);
}

char	*get_varname(char *var)
{
	int		i;
	int		j;
	char	*varname;

	i = 0;
	j = 0;
	varname = NULL;
	while (var[i])
	{
		if (var[i] == '$' && next_isvalid(var[i + 1]))
		{
			if ((var[++i] == '?' || var[i] == '$') || (var[i] >= '0'
					&& var[i] <= '9'))
				varname = copy_name(&var[i], 1);
			else if (!((var[i] >= 97 && var[i] <= 122) || (var[i] >= 65
						&& var[i] <= 90)))
				varname = copy_name(&var[i], 1);
			else
				varname = copy_name(&var[i], 0);
			break ;
		}
		i++;
	}
	return (varname);
}

void	get_var_pos(char *s, char *v, int *start_pos, int *end_pos)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (v == NULL)
		return ;
	while (s[i++])
	{
		if (s[i] == v[j])
		{
			*start_pos = i;
			while (v[j] != '\0')
				if (v[j++] != s[i++])
					break ;
			if (j == ft_strlen(v))
			{
				*end_pos = i;
				break ;
			}
			else
				j = 0;
		}
	}
}

int	ft_searchfor_var(char *s, t_env **env)
{
	int		quotes;
	int		index;
	int		start_pos;
	int		end_pos;
	char	*var;

	index = 0;
	start_pos = 0;
	end_pos = 0;
	while (1)
	{
		quotes = check_quote(&s[index]);
		if (quotes == -1)
			return (-1);
		else if (quotes == 34 || quotes == 0)
		{
			var = get_varname(&s[index]);
			if (var != NULL)
			{
				get_var_pos(s, var, &start_pos, &end_pos);
				add_var(env, var, start_pos, end_pos);
				free(var);
			}
			else
			{
				index++;
				free(var);
			}
			break ;
		}
		else
			index = get_next_var(&s[index]);
	}
	return (0);
}

char	*get_value(char **env, char *var)
{
	char	*var2;
	int		i;
	int		len;

	i = 0;
	var2 = NULL;
	while (env[i])
	{
		len = special_strlen(env[i]);
		var2 = ft_strlcpy(var2, env[i], (len - 1));
		if (ft_strcmp(var2, var) == 0)
		{
			free(var2);
			var2 = ft_strlcpy(var2, env[i] + len, ft_strlen(env[i]));
			break ;
		}
		else
		{
			free(var2);
			var2 = NULL;
		}
		i++;
	}
	free(var);
	return (var2);
}

void	get_envirement(t_command *cmd, char **env)
{
	t_env	*emt;
	int		res;
	int		i;
	int		len;

	i = 0;
	res = 0;
	while (cmd->arguments[i])
	{
		emt = NULL;
		if (cmd->arguments[i][0])
			cmd->arguments[i] = remove_dollarsign(cmd->arguments[i]);
		res = ft_searchfor_var(cmd->arguments[i], &emt);
		if (emt)
		{
			len = ft_strlen(emt->value);
			if (emt->value[0] == '?')
			{
				free(emt->value);
				emt->value = ft_itoa(*global.exit_s);
			}
			else
				emt->value = get_value(env, emt->value);
			cmd->arguments[i] = s_and_r(cmd->arguments[i], emt->value, emt->s_p,
				len);
			free(emt->value);
			free(emt);
		}
		if (res == -1)
			i++;
	}
}
