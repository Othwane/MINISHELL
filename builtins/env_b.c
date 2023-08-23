/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_b.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 23:13:29 by omajdoub          #+#    #+#             */
/*   Updated: 2023/08/23 06:50:24 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_b(char **export)
{
	int	i;

	i = 0;
	if (export == NULL)
	{
		while (g_global.env[i])
			printf("%s\n", g_global.env[i++]);
	}
	else
	{
		while (g_global.export[i])
			printf("declare -x %s\n", g_global.export[i++]);
	}
	*g_global.exit_s = EXIT_SUCCESS;
}
