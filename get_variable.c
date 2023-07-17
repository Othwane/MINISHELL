/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 17:21:22 by aasselma          #+#    #+#             */
/*   Updated: 2023/07/17 22:08:42 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var(char	*str, int f, int l)
{
	char	*var;
	int		len;
	int		i;

	l++;
	len = (l - f);
	i = 0;
	var = malloc((len + 1) * sizeof(char));
	while(f != l)
	{
		var[i] = str[f];
		f++;
		i++;
	}
	var[i] = '\0';
	return (var);
}

int	check_ifvalid(char c)
{
	if ((c >= 65 && c <= 90))
		return (1);
	else if ((c >= 97 && c <= 122))
		return (1);
	else if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
	return (0);
}

char	*ft_search(char *s)
{
	int		i;
	int		start;	
	char	quotes;
	char	dollar_sign;

	i = 0;
	quotes = 0;
	dollar_sign = 0;
	while (s[i] != '\0')
	{
		if ((s[i] == 34 || s[i] == 39) && quotes == 0)
			quotes = s[i];
		else if (s[i] == '$')
		{
			dollar_sign = '$';
			start = (i + 1);
			while (check_ifvalid(s[i + 1]))
				i++;
			break ;
		}
		i++;
	}
	if (quotes == 34 && dollar_sign == '$')
		return (get_var(s, start, i));
	return (NULL);
}

void	replace_value(char *token, char *var)
{
	int	i;
	int	j;

	while(token[i])
	{
		if (token[i] == '$')
		{
			while(check_ifvalid(token[i + 1]))
				token[i++] = var[j++];
			
		}
	}
}

void	get_envirement(t_tokens *token)
{
	char *variable;
	
	while (token)
	{
		printf("%s\n", token->content);
		variable = ft_search(token->content);
		if (variable != NULL)
		{
			printf("variable = [%s]\n", variable);
			variable = getenv(variable);
			printf("value	 = [%s]\n", variable);
			// replace_value(token->content, variable);
			exit(0);
		}
		else
		{
			printf("not found \n");
			exit(0);
		}
		token = token->next;
	}
	printf("%s\n", variable);
}