/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 23:13:24 by omajdoub          #+#    #+#             */
/*   Updated: 2023/08/21 20:00:11 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**fill_env(char **env)
{
	char    **new_env;
	int i;

	i = 0;
	new_env = NULL;
	if (env)
	{
		while (env[i])
			i++;
		new_env = malloc((i + 1) * sizeof(char*));
		i = 0;
		while (env[i])
		{
			new_env[i] = ft_strdup(env[i]);		
			i++;
		}
	}
	new_env[i] = NULL;
	return (new_env);
}

char	**add_newenv(char **env, char *new)
{
	char    **new_env;
	int i;

	i = 0;
	new_env = NULL;
	if (env)
	{
		while (env[i])
			i++;
		new_env = malloc((i + 2) * sizeof(char*));
		i = 0;
		while (env[i])
		{
			new_env[i] = ft_strdup(env[i]);		
			i++;
		}
		new_env[i++] = ft_strdup(new);
	}
	new_env[i] = NULL;
	i = 0;
	while (env[i])
		free(env[i++]);
	free(env);
	return (new_env);
}

char    **add_newexp(char **env, char *new)
{
	char    **new_env;
	int i;

	i = 0;
	new_env = NULL;
	if (env)
	{
		while (env[i])
			i++;
		new_env = malloc((i + 2) * sizeof(char*));
		i = 0;
		while (env[i])
		{
			new_env[i] = ft_strdup(env[i]);		
			i++;
		}
		new_env[i++] = ft_strdup(new);
	}
	new_env[i] = NULL;
	i = 0;
	while (env[i])
		free(env[i++]);
	free(env);
	return (new_env);
}

