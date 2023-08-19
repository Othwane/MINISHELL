/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_and_replace.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 10:17:40 by aasselma          #+#    #+#             */
/*   Updated: 2023/08/18 08:54:43 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*s_and_r(char *src, char *value, int index, int l)
{
	char    *token;
	char    *last_p;
	int     len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = (ft_strlen(src) + ft_strlen(value)) - l;
	last_p = ft_strdup(&src[index + (l + 1)]);
	token = malloc((len + 1) * sizeof(char));
	while(i != len)
	{
		if (i == index)
		{
			token[i] = '\0';
			token = ft_strjoin(token, value);
			token = ft_strjoin(token, last_p);
			break ;
		}
		if (i < len)
			token[i++] = src[j++];
	}
	free(src);
	free(last_p);
	return (token);
}
