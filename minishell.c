/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 13:10:57 by aasselma          #+#    #+#             */
/*   Updated: 2023/08/23 08:04:47 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	convert_linkedlist(t_command *cmd, t_args *argument)
{
	t_args	*args;
	int		len;
	int		i;

	len = 0;
	i = 0;
	args = cmd->args;
	while (args)
	{
		len++;
		args = args->next;
	}
	cmd->arguments = malloc((len + 2) * sizeof(char *));
	cmd->arguments[i++] = ft_strdup(cmd->command);
	cmd->arguments[len + 1] = NULL;
	while (argument)
	{
		cmd->arguments[i++] = ft_strdup(argument->args);
		args = argument;
		argument = argument->next;
		free(args->args);
		free(args);
	}
	if (cmd->next != NULL)
		convert_linkedlist(cmd->next, cmd->next->args);
}

int	ft_inputlen(char *input)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (input[0] == 0)
		return (0);
	while (input[i])
	{
		if (input[i] >= 33 && input[i] <= 126)
			len++;
		i++;
	}
	return (len);
}

void	ft_ft(char *input)
{
	t_tokens	*node_head;
	t_command	*command;

	node_head = NULL;
	command = malloc(sizeof(t_command));
	intialize_command(&command);
	super_split(&node_head, input);
	if (check_syntax_error(node_head) == 1 || check_brakets(input) == 1)
	{
		write(2, "minishell: syntax error\n", 25);
		*g_global.exit_s = 258;
		free(command);
	}
	else
	{
		parsing(node_head, &command);
		convert_linkedlist(command, command->args);
		get_envirement(command, g_global.env);
		remove_quotes(command);
		_exec(command, g_global.env, 0);
		free_command(command);
	}
	free_resources(node_head);
}

int	ft_system(char **env)
{
	char		*input;

	init_global(env);
	while (1)
	{
		set_signal();
		input = readline("~minishell$> ");
		add_history(input);
		if (!input)
			return (0);
		else if (ft_inputlen(input) != 0)
			ft_ft(input);
		free(input);
	}
	free_env();
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	ft_system(env);
}
