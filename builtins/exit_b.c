/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 23:13:32 by omajdoub          #+#    #+#             */
/*   Updated: 2023/08/22 08:02:09 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_num(char *str)
{
	int	i;
	
	i = 0;
	while(str[i])
	{
		if (i == 0 && (str[i] == '-' || str[i] == '+'))
			i++;
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

int	count_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);	
}

void	exit_b(t_command *command, char x)
{
	if (count_args(&command->arguments[1]) == 1 || count_args(&command->arguments[1]) == 0)
	{
		if (command->arguments[1])
		{
			if (is_num(command->arguments[1]))
				x = (char) atoi(command->arguments[1]);
			else
			{
				write(2, "minishell: exit: ", 17);
				write(2, command->arguments[1], ft_strlen(command->arguments[1]));
				write(2, ": numeric argument required\n", 28);
				free_command(command);
				exit(255);
			}
		}
		else
			x = 0;
		free_command(command);
		exit(x);
	}
	else
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		*global.exit_s = x;	
	}
}
