/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_token_len.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 11:21:20 by aasselma          #+#    #+#             */
/*   Updated: 2023/06/15 17:24:28 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

int	count__brkts(char *str, char c)
{
	int i;
	int	v;

	v = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			v++;
		if (v == 2 && ((str[i + 1] == ' ' || str[i + 1] == '\t')
			|| (str[i + 1] =='>' || str[i + 1] =='<') || (str[i + 1] == '|')))
		{
			i++;
			break ;
		}
		i++;
	}
	return (i);
}

int	ft_count_other_cases(char *str)
{
	int	i;
	int	v;

	i = 0;
	v = 0;
	while(str[i])
	{
		if (str[i] == 34)
			v++;
		if ((((str[i + 1] == ' ' || str[i + 1] == '\t')
			|| (str[i + 1] =='>'  || str[i] == '<') || (str[i + 1] == '|')) && v == 0))
		{
			i++;
			break ;
		}
		else if (v == 2 && ((str[i + 1] == ' ' || str[i + 1] == '\t')
			|| (str[i + 1] == '>' || str[i] == '<') || (str[i + 1] == '|')))
		{
			i++;
			break ;
		}
		i++;
	}
	return (i);
}

int string_count(char *str)
{
	int i;

	i = 0;
	while(str[i])
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
