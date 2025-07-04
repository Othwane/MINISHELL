/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:33:04 by aasselma          #+#    #+#             */
/*   Updated: 2023/07/18 18:30:38 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_brakets(char *str)
{
	char	type;
	int		i;
	int		v;

	v = 0;
	i = 0;
	type = 'x';
	while (str[i])
	{
		if (str[i] == 34 && type == 'x')
			type = str[i];
		else if (str[i] == 39 && type == 'x')
			type = str[i];
		if (str[i] == type && type != 'x')
			v++;
		i++;
	}
	if ((v % 2) != 0)
		return (1);
	return (0);
}
