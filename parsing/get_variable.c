/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 17:21:22 by aasselma          #+#    #+#             */
/*   Updated: 2023/08/14 15:54:33 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_var(char *str, int f, int l, t_env **env)
{
	char	*var;
	int		len;
	int		i;
	int		start;

	l++;
	len = (l - f);
	i = 0;
	start = f;
	var = malloc((len + 1) * sizeof(char));
	while(f != l)
	{
		var[i] = str[f];
		f++;
		i++;
	}
	var[i] = '\0';
	add_var(env, var, ft_strlen(var), start);
	free(var);
}

int	ft_searchfor_var(char *s, t_env **env)
{
	int		i;
	int		start;	
	char	quotes;
	char	dollar_sign;
	int		s_in;

	i = 0;
	quotes = 0;
	dollar_sign = 0;
	s_in = 0;
	while (s[i] != '\0')
	{
		if ((s[i] == 34 || s[i] == 39) && quotes == 0)
			quotes = s[i];
		if (s[i] == 39)
			s_in++;
		if (s_in == 2)
		{
			s_in = 0;
			quotes = 0;
		}
		else if (s[i] == '$' && check_ifvalid(s[i + 1]))
		{
			dollar_sign = '$';
			start = (++i);
			while (check_ifvalid(s[i + 1]))
			{
				if (s[i] >= '0' && s[i] <= '9')
					break;
				i++;
			}
			if ((quotes == 34 && dollar_sign == '$') || (dollar_sign == '$' && quotes == 0)
				|| (dollar_sign == '$' && quotes == 39 && s_in == 2))
			{
				// printf("%d\n", s_in);
				// exit(0);
				s_in = 0;
				get_var(s, start, i, env);
				return (0);
			}
		}
		i++;
	}
	if (!(quotes == 34 && dollar_sign == '$') || !(dollar_sign == '$' && quotes == 0))
		return (-1);
	return (0);
}

char	*get_value(char **env, char *var)
{
	char	*var2;
	int		i;
	int		len;

	i = 0;
	while(env[i])
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
	return(var2);
}

void	get_envirement(t_command *cmd, char **env)
{
	t_env	*emt;
	int		res;
	int		i;

	i = 0;
	(void)env;
	while (cmd->arguments[i])
	{
		emt = NULL;
		res = ft_searchfor_var(cmd->arguments[i], &emt);
		if (emt)
		{
			if (emt->value[0] != '$')
				emt->value = get_value(env, emt->value);
			cmd->arguments[i] = s_and_r(cmd->arguments[i], emt->value, emt->index);
			free(emt->value);
			free(emt);
		}
		if (res == -1)
			i++;
	}
}
