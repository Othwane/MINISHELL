/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:54:03 by aasselma          #+#    #+#             */
/*   Updated: 2023/08/14 11:45:46 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (i);
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_substr(char const *s, int start, int len)
{
	char	*str2;
	int		i;
	char	*strmmry;

	if (!s)
		return (0);
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	str2 = (char *)&s[start];
	i = 0;
	strmmry = malloc((len + 1));
	if (!strmmry)
		return (NULL);
	while (i < len && start < ft_strlen(s))
	{
		strmmry[i] = (char)str2[i];
		i++;
	}
	strmmry[i] = '\0';
	return (strmmry);
}

char	*ft_strdup(const char *s1)
{
	int		s1_len;
	int		i;
	char	*dup;

	i = 0;
	if (s1 == NULL || ft_strlen(s1) == 0)
		return (NULL);
	s1_len = ft_strlen(s1);
	dup = (char *)malloc(sizeof(char) * (s1_len + 1));
	if (!dup)
		return (NULL);
	while (s1[i])
	{
		dup[i] = (char)s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;
	size_t	x;
	int		total;

	x = 0;
	i = 0;
	total = 0;
	if (!s1 || !s2)
		return (1);
	while ((s1[x] || s2[x]))
	{
		if (s1[i] != s2[x])
		{
			total = ((unsigned char)s1[i] - (unsigned char)s2[x]);
			return (total);
		}
		i++;
		x++;
	}
	return (0);
}

char	*ft_strlcpy(char *dst, const char *src, int len)
{
	int	i;
	int	j;

	j = 0;
	i = ft_strlen(src);
	dst = malloc((len + 1) * sizeof(char));
	while (j != len && src[j] != '\0')
	{
		dst[j] = src[j];
		j++;
	}
	dst[j] = '\0';
	return (dst);
}
