/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 15:56:25 by aasselma          #+#    #+#             */
/*   Updated: 2023/08/17 19:12:59 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	while (s[i] && s[i] != (char)c)
		i++;
	if (s[i] == (char)c)
		return ((char *)s + i);
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*new_s;

	i = 0;
	j = 0;
	new_s = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!new_s)
		return (NULL);
	if (s1)
	{
		while (s1[j])
			new_s[i++] = s1[j++];
	}
	if (s2)
	{
		while (*s2)
			new_s[i++] = *s2++;
	}
	new_s[i] = '\0';
	free(s1);
	return (new_s);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return ((char)s1[i] - (char)s2[i]);
		i++;
	}
	return (0);
}

static	int	count_words(const char *s, char c)
{
	int	i;
	int	wd;

	i = 0;
	wd = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		wd++;
		while (s[i] && s[i] != c)
			i++;
		while (s[i] && s[i] == c)
			i++;
	}
	return (wd);
}

int	wordlen(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

char	**ft_mini_split(char **str, const char *s, char c, int words)
{
	int	i;
	int	j;
	int	l;

	i = 0;
	while (i < words)
	{
		while (*s && *s == c)
			s++;
		str[i] = (char *)malloc(sizeof(char) * (wordlen(s, c) + 1));
		j = 0;
		l = wordlen(s, c);
		while (j < l)
		{
			str[i][j++] = *s;
			s++;
		}
		str[i][j] = '\0';
		i++;
	}
	str[i] = NULL;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		words;

	words = count_words(s, c);
	str = (char **)malloc((words + 1) * (sizeof(char *)));
	if (!str)
		return (NULL);
	str = ft_mini_split(str, s, c, words);
	return (str);
}
