/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omajdoub <omajdoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 05:35:46 by aasselma          #+#    #+#             */
/*   Updated: 2023/07/25 18:19:47 by omajdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_new(t_tokens **t_list, char *content)
{
	t_tokens	*newnode;
	t_tokens	*tmp;

	newnode = malloc(sizeof(t_tokens));
	newnode->content = ft_strdup(content);
	newnode->next = NULL;
	if (*t_list == NULL)
		*t_list = newnode;
	else
	{
		tmp = *t_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = newnode;
	}
}

void	super_split(t_tokens **my_list, char *str)
{
	char *token;
	int i;
	// int w;
	int s_len;
	int	len;

	i = 0;
	// w = 0;
	len = ft_strlen(str);
	while(i <= len)
	{
		if(str[i] >= 33 && str[i] <= 127)
		{
			s_len = string_count(str + i);
			token = ft_substr(str, i, s_len);
			i += s_len;
			add_new(my_list, token);
			free(token);
		}
		else
			i++;
	}
}
