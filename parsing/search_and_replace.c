/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_and_replace.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 10:17:40 by aasselma          #+#    #+#             */
/*   Updated: 2023/07/20 18:48:24 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_tokenlen(char *str)
{
	int	i;
	int	len;
	int q;

	q = 0;
	i = 0;
	len = 0;
	while(str[i])
	{
		if (str[i] == '$' && q == 0)
		{
			i++;
			q++;
			while (check_ifvalid(str[i]))
				i++;
		}
		else
		{
			i++;
			len++;
		}
	}
	return (len);
}

char    *search_and_replace(char *src, char *value)
{
	char    *token;
	int     i;
	int     j;
	int		k;
	int     len;
	
	i = 0;
	j = 0;
	k = 0;
	len = count_tokenlen(src) + ft_strlen(value);
	token = malloc(sizeof(char) * (len + 1));
	while(i < len)
	{
		if ((src[j] == '$' && src[j + 1] != ' ') && k == 0)
		{
			j++;
			while(check_ifvalid(src[j]))
				j++;
			if (value)
			{
				while(value[k])
				{
					token[i++] = value[k++];

				}
			}
		}
		token[i++] = src[j++];
	}
	free(src);
	return (token);
}