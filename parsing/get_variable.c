/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 17:21:22 by aasselma          #+#    #+#             */
/*   Updated: 2023/07/20 18:39:47 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_var(char *str, int f, int l, t_env **env)
{
	t_env	*emt;
	char	*var;
	int		len;
	int		i;

	l++;
	len = (l - f);
	i = 0;
	var = malloc((len + 1) * sizeof(char));
	while(f != l)
	{
		var[i] = str[f];
		f++;
		i++;
	}
	var[i] = '\0';
	add_var(env, var, ft_strlen(var));
	free(var);
}

void	ft_search(char *s, t_env **env)
{
	int		i;
	int		start;	
	char	quotes;
	char	dollar_sign;

	i = 0;
	quotes = 0;
	dollar_sign = 0;
	while (s[i] != '\0')
	{
		if ((s[i] == 34 || s[i] == 39) && quotes == 0)
			quotes = s[i];
		else if (s[i] == '$')
		{
			dollar_sign = '$';
			start = (++i);
			while (check_ifvalid(s[i + 1]))
				i++;
			if ((quotes == 34 && dollar_sign == '$') || (dollar_sign == '$' && quotes == 0))
				get_var(s, start, i, env);
		}
		i++;
	}
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
	t_env *emt;

	emt = NULL;
	while (token)
	{
		ft_search(token->content, &emt);
		while(emt)
		{
			printf("rrrv \n%c\n", emt->value[0]);
			// if (emt->value[0] != '$')
			// 	emt->value = get_value(env, emt->value);
			exit(0);
			token->content = search_and_replace(token->content, emt->value);
			free(emt->value);
			free(emt);
			emt = emt->next;
		}
		token = token->next;
	}
	// exit(0);
}