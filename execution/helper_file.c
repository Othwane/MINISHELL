/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omajdoub <omajdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 05:30:00 by omajdoub          #+#    #+#             */
/*   Updated: 2023/08/23 05:40:35 by omajdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_herdoc_file(t_files *file)
{
	while (file)
	{
		if (file->red_type == HERDOC)
			unlink(file->filename);
		file = file->next;
	}
}

void	prep_pipe(t_command *command)
{
	if (command->infile != 0)
	{
		dup2(command->infile, 0);
		close(command->infile);
	}
	if (command->outfile != 1)
	{
		dup2(command->outfile, 1);
		close(command->outfile);
	}
}

void	check_permis(t_command *command)
{
	if (access(command->arguments[0], F_OK))
	{
		write(2, "minishell : No such file or directory\n", 39);
		*global.exit_s = 127;
	}
	else if (access(command->arguments[0], X_OK))
	{
		write(2, "minishell : Permission denied\n", 30);
		*global.exit_s = 126;
	}
}

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
