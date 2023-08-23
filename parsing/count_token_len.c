/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_token_len.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 11:21:20 by aasselma          #+#    #+#             */
/*   Updated: 2023/08/23 04:59:29 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count__brkts(char *str, char c)
{
	int	i;
	int	v;

	v = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			v++;
		if (v == 2 && ((str[i + 1] == ' ' || str[i + 1] == '\t')
				|| (str[i + 1] == '>') || (str[i + 1] == '<')
				|| (str[i + 1] == '|')))
			return (++i);
		i++;
	}
	return (i);
}

int	check_dependins(char *str)
{
	if ((str[0] == '>' && str[1] != '>') || (str[0] == '<' && str[1] != '<'))
		return (1);
	if ((str[0] == '>' && str[1] == '>'))
		return (2);
	else if (str[0] == '<' && str[1] == '<')
		return (2);
	else if (str[0] == '|')
		return (1);
	return (0);
}

int	ft_count_other_cases(char *str)
{
	int	i;
	int	v;

	i = 0;
	v = check_dependins(str);
	if (v != 0)
		return (v);
	while (str[i])
	{
		if (str[i] == 34)
			v++;
		if ((((str[i + 1] == ' ' || str[i + 1] == '\t') || (str[i + 1] == '>')
					|| (str[i + 1] == '<') || (str[i + 1] == '|')) && v == 0))
			return (++i);
		else if (v == 2 && ((str[i + 1] == ' ' || str[i + 1] == '\t')
				|| (str[i + 1] == '>') || (str[i] == '<')
				|| (str[i + 1] == '|')))
			return (++i);
		i++;
	}
	return (i);
}

int	string_count(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 34)
			return (count__brkts(str, 34));
		else if (str[i] == 39)
			return (count__brkts(str, 39));
		else
			return (ft_count_other_cases(str));
		i++;
	}
	return (0);
}
