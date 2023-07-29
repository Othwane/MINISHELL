/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reomve_qoutes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 01:44:04 by aasselma          #+#    #+#             */
/*   Updated: 2023/07/26 17:17:41 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char    find_quote(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			return (str[i]);
		i++;
	}
	return (0);
}

int newstr_len(char *str, char q)
{
	int i;
	int len;

	i = 0;
	len = 0;
	while(str[i])
	{
		if (str[i] != q)
		   len++;
		i++; 
	}
	return (len);
}

char* remove_outer_quotes(char* str)
{
	char    *new_str;
	char    quote;
	int     i;
	int     j;
	int     len;
	
	i = 0;
	j = 0;
	quote = find_quote(str);
	len = newstr_len(str, quote);
	new_str = malloc((len + 1) * sizeof(char));
	while(str[i])
	{
		if (str[i] != quote)
			new_str[j++] = str[i];
		i++;
	}
	free(str);
	new_str[j] = '\0';
	return (new_str);
}

void    remove_quotes(t_tokens *token)
{
	while (token)
	{
		token->content = remove_outer_quotes(token->content);
		token = token->next;
	}
}
