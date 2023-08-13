/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omajdoub <omajdoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 17:21:22 by aasselma          #+#    #+#             */
/*   Updated: 2023/08/12 20:23:19 by omajdoub         ###   ########.fr       */
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

int	ft_search(char *s, t_env **env)
{
	int		i;
	int		start;
	char	quotes;
	char	dollar_sign;
	int		in;

	i = 0;
	quotes = 0;
	dollar_sign = 0;
	in = 0;
	while (s[i] != '\0')
	{
		if ((s[i] == 34 || s[i] == 39) && quotes == 0)
			quotes = s[i];
		if (s[i] == 39)
			in++;
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
				|| (dollar_sign == '$' && quotes == 39 && in == 2))
			{
				in = 0;
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

void	get_envirement(t_tokens *token, char **env)
{
	t_env	*emt;
	int		res;

	(void)env;
	while (token)
	{
		emt = NULL;
		res = ft_search(token->content, &emt);
		if (emt)
		{
			if (emt->value[0] != '$')
				emt->value = get_value(env, emt->value);
			token->content = search_and_replace(token->content, emt->value, emt->index);
			free(emt->value);
			free(emt);
		}
		if (res == -1)
			token = token->next;
	}
}
