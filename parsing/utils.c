/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omajdoub <omajdoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 23:52:04 by aasselma          #+#    #+#             */
/*   Updated: 2023/07/22 05:07:11 by omajdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_ifvalid(char c)
{
	if ((c >= 65 && c <= 90))
		return (1);
	else if ((c >= 97 && c <= 122))
		return (1);
	else if (c >= '0' && c <= '9')
		return (1);
	else if (c == '_')
		return (1);
	else
		return (0);
	return (0);
}

int	is_redirections(char *token)
{
	if (ft_strcmp(token, ">") == 0 || ft_strcmp(token, ">>") == 0
		|| ft_strcmp(token, "<") == 0 || ft_strcmp(token, "<<") == 0)
		return (1);
	return (0);
}

char	*get_variable(char *env, int end)
{
	int		i;
	char	*var;

	i = 0;
	var = malloc((end + 1) * sizeof(char));
	while(i != end)
	{
		var[i] = env[i];
		i++;
	}
	var[i] = '\0';
	return (var);
}

int	special_strlen(char	*env)
{
	int	i;

	i = 0;
	while(env[i - 1] != '=')
		i++;
	return (i);
}

int calc_arr_len(char** arr)
{
	int sz = 0;
	if (!arr)
		return sz;
	while (arr[sz])
		sz++;
	return sz;
}

void free_arr(char** arr)
{
	int i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}


char** realloc_arr(char** arr, int new_sz)
{
	int arr_sz = calc_arr_len(arr);
	int i = 0;
	char** new_arr = malloc(sizeof(char*) * (arr_sz + new_sz + 1));
	while (arr[i])
	{
		new_arr[i] = ft_strdup(arr[i]);
		i++;
	}
	new_arr[i] = NULL;
	free_arr(arr);
	return new_arr;
}
