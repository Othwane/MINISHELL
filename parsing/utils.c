/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 23:52:04 by aasselma          #+#    #+#             */
/*   Updated: 2023/08/07 23:52:54 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_ifvalid(char c)
{
	if ((c >= 65 && c <= 90))
		return (1);
	else if ((c >= 97 && c <= 122))
		return (1);
	else if (c >= '0' && c <= '9')
		return (1);
	else if (c == '_')
		return (1);
	else
		return (0);
	return (0);
}

int	is_redirections(char *token)
{
	if (ft_strcmp(token, ">") == 0 || ft_strcmp(token, ">>") == 0
		|| ft_strcmp(token, "<") == 0 || ft_strcmp(token, "<<") == 0)
		return (1);
	return (0);
}

char	*get_variable(char *env, int end)
{
	int		i;
	char	*var;

	i = 0;
	var = malloc((end + 1) * sizeof(char));
	while (i != end)
	{
		var[i] = env[i];
		i++;
	}
	var[i] = '\0';
	return (var);
}

int	in_qoute(char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (token[i] == 34 || token[i] == 39)
			return (1);
		i++;
	}
	return (0);
}

int	special_strlen(char *env)
{
	int	i;

	i = 0;
	while (env[i] != '=')
		i++;
	return (++i);
}
