/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_for_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 08:22:57 by aasselma          #+#    #+#             */
/*   Updated: 2023/08/21 13:49:56 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_checker(int *quote, int *d_sign, int *q_num)
{
	if ((*q_num) == 2 && (*d_sign) == 0)
	{
		(*q_num) = 0;
		(*quote) = 0;
	}
	if (((*d_sign) == '$' && (*q_num) == 2)
		|| ((*d_sign) == '$' && (*q_num) == 0))
		return (1);
	return (0);
}

int	next_isvalid(char c)
{
	if(c == '\0' || c == 34 || c == 39)
		return (0);
	else if ((c == 32 || (c <= 9 && c >= 13)))
		return (0);
	return (1);
}

int	check_quote(char *var)
{
	int		i;
	int		q_num;
	int	d_sign;
	int	quote;

	d_sign = 0;
	quote = 0;
	q_num = 0;
	i = 0;
	while (var[i])
	{
		if (var[i] == '$' && next_isvalid(var[i + 1]))
			d_sign = '$';
		if ((var[i] == 34 || var[i] == 39) && q_num != 2)
		{
			quote = var[i];
			q_num++;
		}
		if (ft_checker(&quote, &d_sign, &q_num))
			return (quote);	
		i++;
	}
	return (-1);
}

int	get_next_var(char *var)
{
	int	i;
	int	q_num;

	i = 0;
	q_num = 0;
	while (var[i])
	{
		if (var[i] == 39)
			q_num++;
		if (q_num == 2)
			return (++i);
		i++;
	}
	return (-1);
}
