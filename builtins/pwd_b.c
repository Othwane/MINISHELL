/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_b.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 23:13:12 by omajdoub          #+#    #+#             */
/*   Updated: 2023/08/21 15:52:56 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pwd_b(void)
{
	int i;
	char	cwd[1024];

	i = 0;
	if (getcwd(cwd, 1024))
	{
		while (cwd[i])
		{
			write(1,&cwd[i],1);
			i++;
		}
		write(1,"\n",1);
		return (0);
	}
	else
	{
		perror("chdir: error retrieving current directory");
		return (1);
	}
}
