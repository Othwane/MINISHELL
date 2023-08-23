/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omajdoub <omajdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 12:04:37 by aasselma          #+#    #+#             */
/*   Updated: 2023/08/23 05:42:49 by omajdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	nonexpandherdoc(int fd, char *filename)
{
	char	*input;
	char	*newinput;
	int		i;

	i = 0;
	signal(SIGINT, SIG_DFL);
	while (1)
	{
		input = readline(">");
		if (!input || ft_strcmp(input, filename) == 0)
			break ;
		newinput = ft_strjoin(input, "\n");
		write(fd, newinput, ft_strlen(newinput));
		free(newinput);
	}
}

char	*expand_input(char *input, char **env)
{
	t_env	*emt;
	int		res;
	int		len;

	while (1)
	{
		emt = NULL;
		res = ft_searchfor_var(input, &emt);
		if (emt)
		{
			len = ft_strlen(emt->value);
			if (emt->value[0] != '$')
				emt->value = get_value(env, emt->value);
			input = s_and_r(input, emt->value, emt->s_p, len);
			free(emt->value);
			free(emt);
		}
		if (res == -1)
			break ;
	}
	return (input);
}

void	expand_herdoc(int fd, char *filename, char **env)
{
	char	*input;
	char	*newinput;
	int		i;

	i = 0;
	signal(SIGINT, SIG_DFL);
	while (1)
	{
		input = readline(">");
		if (!input || ft_strcmp(input, filename) == 0)
			break ;
		input = expand_input(input, env);
		newinput = ft_strjoin(input, "\n");
		write(fd, newinput, ft_strlen(newinput));
		free(newinput);
	}
}

void	ft_herdoc(int fd, t_command *cmd, char **env)
{
	t_files	*file;

	file = cmd->files;
	if (file->quote == 0)
		expand_herdoc(fd, file->filename, env);
	else
		nonexpandherdoc(fd, file->filename);
}
