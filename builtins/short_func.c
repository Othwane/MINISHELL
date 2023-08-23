/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   short_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 06:58:23 by aasselma          #+#    #+#             */
/*   Updated: 2023/08/23 07:00:28 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_pos(char *var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		if (var[i] == '=')
			return (i);
		i++;
	}
	return (i);
}

int	env_len(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}
