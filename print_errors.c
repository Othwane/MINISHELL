/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 20:01:56 by aasselma          #+#    #+#             */
/*   Updated: 2023/08/21 20:48:20 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_error(char  *error, char *str, char c)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (error[i])
	{
		write(2, &error[i], 1);
		if (error[i] == c && str != NULL)
		{
			while (str[j])
				write(2, &str[j++], 1);
		}
		i++;
	}
	*global.exit_s = EXIT_FAILURE;
}
