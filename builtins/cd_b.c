/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_b.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 23:13:15 by omajdoub          #+#    #+#             */
/*   Updated: 2023/08/23 06:49:25 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cd_b(char **argv)
{
	char	*path;

	if (!argv[1] || !ft_strcmp(argv[1], "~"))
	{
		path = get_value(g_global.env, ft_strdup("HOME"));
		if (!path)
		{
			write(2, "minishell: cd: HOME not set\n", 29);
			free(path);
			return (1);
		}
		chdir(path);
		free(path);
	}
	else
	{
		if (chdir(argv[1]) == -1)
		{
			write(2, "minishell: cd: ", 15);
			write(2, argv[1], ft_strlen(argv[1]));
			write(2, ": No such file or directory\n", 29);
			return (1);
		}
	}
	return (0);
}
