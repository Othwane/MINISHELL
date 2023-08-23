/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_b.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omajdoub <omajdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 23:13:29 by omajdoub          #+#    #+#             */
/*   Updated: 2023/08/23 05:45:04 by omajdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_b(char **export)
{
	int	i;

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
