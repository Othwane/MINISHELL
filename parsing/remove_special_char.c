/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_special_char.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 20:46:39 by aasselma          #+#    #+#             */
/*   Updated: 2023/08/18 12:05:38 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valid(char c)
{
	if ((c >= 65 && c <= 90))
		return (1);
	else if ((c >= 97 && c <= 122))
		return (1);
	else if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	else if (c == '_' || c == '?' || c == 35 || c == 39)
		return (1);
	return (0);
}

char	*remove_special_char(char *str)
{
	char	*new_s;
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	new_s = malloc((ft_strlen(str) + 1) * 1);
	while(i < (ft_strlen(str)))
	{
		new_s[j++] = str[i++];
		if (str[i] == '$' && is_valid(str[i + 1]) == 0)
			i += 2;
	}
	new_s[j] = '\0';
	printf("new_s %s\n", new_s);
	exit(0);
	return (new_s);
}