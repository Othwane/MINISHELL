/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_b.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 23:13:12 by omajdoub          #+#    #+#             */
/*   Updated: 2023/08/23 04:05:35 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pwd_b(void)
{
	int		i;
	char	cwd[1024];

	i = 0;
	if (getcwd(cwd, 1024))
	{
		while (cwd[i])
		{
			write(1, &cwd[i], 1);
			i++;
		}
		write(1, "\n", 1);
		return (0);
	}
	else
	{
		write(2, "chdir: error retrieving current directory\n", 42);
		return (1);
	}
}
