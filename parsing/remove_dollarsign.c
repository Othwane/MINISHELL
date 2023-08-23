/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_dollarsign.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:53:56 by aasselma          #+#    #+#             */
/*   Updated: 2023/08/22 03:56:11 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*remove_incase(char *arg, char c)
{
	char	*newarg;
	int		i;
	int		j;
	int		v;

	i = 0;
	j = 0;
	v = 0;
	newarg = malloc((ft_strlen(arg) + 1) * 1);
	while (arg[i])
	{
		if (arg[i + 1] == c || arg[i] == c)
		{
			v++;
			if (arg[i] == '$' && v == 1)
				i++;
		}
		if (v == 2)
			v = 0;
		newarg[j++] = arg[i];
		i++;
	}
	newarg[j] = '\0';
	free(arg);
	return (newarg);
}

char	*remove_dollarsign(char *arg)
{
	char *new;

	new = remove_incase(arg, 34);
	new = remove_incase(new, 39);
	return (new);
}