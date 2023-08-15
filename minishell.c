/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 13:10:57 by aasselma          #+#    #+#             */
/*   Updated: 2023/08/13 18:16:30 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

t_files	*check_firts_token(t_tokens **token)
{
	t_tokens	*node;
	t_files		*file;

	node = *token;
	file = NULL;
	if (is_redirections(node->content))
	{
		add_files(&file, node->next->content, node->content);
		if (node->next->next)
			*token = node->next->next;
		else
			*token = NULL;
		return (file);
	}
	return (NULL);
}

void	parsing(t_tokens *token, t_command **cmd)
{
	t_command	*command;

	command = *cmd;
	command->files = check_firts_token(&token);
	if (token)
	{
		if ((is_redirections(token->content) == 0) && (ft_strcmp(token->content, "|") != 0))
		{
			// command->cmd_num++;
			command->command = ft_strdup(token->content);
			token = token->next;
		}
	}
	while(token)
	{
		if (ft_strcmp(token->content, "|") == 0)
			break;
		else if (is_redirections(token->content))
		{
			add_files(&command->files, token->next->content, token->content);
			token = token->next;
		}
		else if (is_redirections(token->content) == 0
			|| ft_strcmp(token->content, "|") == 1)
			add_args(&command->args, token->content);
		token = token->next;
	}
	if (token)
	{
		command->next = malloc(sizeof(t_command));
		command->next->command = NULL;
		command->next->arguments = NULL;
		command->next->files = NULL;
		command->next->args = NULL;
		command->next->infile = 0;
		command->next->outfile = 1;
		command->next->cmd_path = NULL;
		// command->next->cmd_num = command->cmd_num;
		command->next->next = NULL;
		parsing(token->next, &command->next);
	}
}

void	convert_linkedlist(t_command *cmd, t_args *argument)
{
	t_args	*args;
	int		len;
	int		i;

	len = 0;
	i = 0;
	args = cmd->args;
	while(args)
	{
		len++;
		args = args->next;
	}
	cmd->arguments = malloc((len + 2) * sizeof(char*));
	cmd->arguments[i++] = ft_strdup(cmd->command);
	cmd->arguments[len + 1] = NULL;
	while(argument)
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

int main(int ac, char **av, char **env)
{
	t_tokens	*node_head;
	t_command	*command;
	char		*input;

	(void)ac;
	(void)av;
	while (1)
	{
		set_signal();
		input = readline("~minishell$> ");
		add_history(input);
		if (!input)
			return (0);
		else if (ft_inputlen(input) != 0)
		{
			node_head = NULL;
			command = malloc(sizeof(t_command));
			command->next = NULL;
			// command->cmd_num = 0;
			command->command = NULL;
			command->arguments = NULL;
			command->files = NULL;
			command->args = NULL;
			command->infile = 0;
			command->outfile = 1;
			command->cmd_path = NULL;
			super_split(&node_head ,input);
			if (check_syntax_error(node_head) == 1 || check_brakets(input) == 1)
			{
				printf("minishell~: syntax error near unexpected token\n");
				free(command);
			}
			else
			{
				parsing(node_head, &command);
				convert_linkedlist(command, command->args);
				get_envirement(command, env);
				remove_quotes(command);
				_exec(command, env);
				free_command(command);
			}
			free_tokens(node_head);
		}
		free(input);
	}
}
