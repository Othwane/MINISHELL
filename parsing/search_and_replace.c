/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_and_replace.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 10:17:40 by aasselma          #+#    #+#             */
/*   Updated: 2023/08/23 05:44:27 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*s_and_r(char *src, char *value, int index, int l)
{
	char	*token;
	char	*last_p;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = (ft_strlen(src) + ft_strlen(value)) - l;
	last_p = ft_strdup(&src[index + (l + 1)]);
	token = malloc((len + 1) * sizeof(char));
	while (i != len)
	{
		if (i == index)
		{
			token[i] = '\0';
			token = ft_strjoin(token, value);
			token = ft_strjoin(token, last_p);
			break ;
		}
		if (i < len)
			token[i++] = src[j++];
	}
	free(last_p);
	return (token);
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
