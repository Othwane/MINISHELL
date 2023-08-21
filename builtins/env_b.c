/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_b.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 23:13:29 by omajdoub          #+#    #+#             */
/*   Updated: 2023/08/21 20:48:34 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_b(char **export)
{
	int i;

	i = 0;
	if (export == NULL)
	{
		while (global.env[i])
			printf("%s\n", global.env[i++]);
	}
	else
	{
		while (global.export[i])
			printf("declare -x %s\n", global.export[i++]);
	}
	*global.exit_s = EXIT_SUCCESS;
}