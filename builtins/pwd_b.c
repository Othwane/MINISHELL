/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_b.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 23:13:12 by omajdoub          #+#    #+#             */
/*   Updated: 2023/08/23 08:14:25 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pwd_b(void)
{
	int		i;
	char	*cwd;

	i = 0;
	cwd = malloc(PATH_MAX * sizeof(char));
	if (getcwd(cwd, PATH_MAX))
	{
		while (cwd[i])
		{
			write(1, &cwd[i], 1);
			i++;
		}
		write(1, "\n", 1);
		free(cwd);
		return (0);
	}
	else
	{
		free(cwd);
		write(2, "chdir: error retrieving current directory\n", 42);
		return (1);
	}
}
