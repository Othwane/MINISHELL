/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 17:21:22 by aasselma          #+#    #+#             */
/*   Updated: 2023/08/23 06:48:21 by aasselma         ###   ########.fr       */
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

void	add_var_to(char	*s, char *var, t_env **env)
{
	int		start_pos;
	int		end_pos;

	start_pos = 0;
	end_pos = 0;
	get_var_pos(s, var, &start_pos, &end_pos);
	add_var(env, var, start_pos, end_pos);
	free(var);
}

int	ft_searchfor_var(char *s, t_env **env, int index)
{
	int		quotes;
	char	*var;

	while (1)
	{
		quotes = check_quote(&s[index]);
		if (quotes == -1)
			return (-1);
		else if (quotes == 34 || quotes == 0)
		{
			var = get_varname(&s[index]);
			if (var != NULL)
				add_var_to(s, var, env);
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

char	*new_arg(t_env	*emt, char *arg, char **env)
{
	int		len;
	char	*new_arg;

	len = ft_strlen(emt->value);
	if (emt->value[0] == '?')
	{
		free(emt->value);
		emt->value = ft_itoa(*g_global.exit_s);
	}
	else
		emt->value = get_value(env, emt->value);
	new_arg = s_and_r(arg, emt->value, emt->s_p, len);
	free(arg);
	return (new_arg);
}

void	get_envirement(t_command *cmd, char **env)
{
	t_env	*emt;
	int		res;
	int		i;

	i = 0;
	res = 0;
	while (cmd->arguments[i])
	{
		emt = NULL;
		if (cmd->arguments[i][0])
			cmd->arguments[i] = remove_dollarsign(cmd->arguments[i]);
		res = ft_searchfor_var(cmd->arguments[i], &emt, 0);
		if (emt)
		{
			cmd->arguments[i] = new_arg(emt, cmd->arguments[i], env);
			free(emt->value);
			free(emt);
		}
		if (res == -1)
			i++;
	}
}
