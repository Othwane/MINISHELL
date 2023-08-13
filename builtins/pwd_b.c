/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_b.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omajdoub <omajdoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 23:13:12 by omajdoub          #+#    #+#             */
/*   Updated: 2023/08/13 02:23:18 by omajdoub         ###   ########.fr       */
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
