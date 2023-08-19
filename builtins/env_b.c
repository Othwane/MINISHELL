/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_b.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 23:13:29 by omajdoub          #+#    #+#             */
/*   Updated: 2023/08/19 11:33:15 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_b(char *str)
{
	int i;

	i = 0;
	while (global.env[i])
		printf("%s%s\n", str, global.env[i++]);
	global.exit_s = EXIT_SUCCESS;
}