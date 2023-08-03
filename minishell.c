/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omajdoub <omajdoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 13:10:57 by aasselma          #+#    #+#             */
/*   Updated: 2023/08/03 04:18:10 by omajdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

t_files	*check_firts_token(t_tokens **token)
{
	t_tokens	*node;
	t_files		*file;

	node = *token;
	file = NULL;
	while(node)
	{
		if (is_redirections(node->content))
		{
			add_files(&file, node->next->content, node->content);
			if (node->next->next)
				node = node->next->next;
		}
		else
		{
			*token = node;
			return (file);
		}
	}
	return (NULL);
}

void	parsing(t_tokens *token, t_command **cmd)
{
	t_command	*command;

	command = *cmd;
	command->files = NULL;
	command->args = NULL;
	command->infile = 0;
	command->outfile = 1;
	command->cmd_path = NULL;
	command->files = check_firts_token(&token);
	add_command(&command, token->content);
	token = token->next;
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
		command->next->cmd_num = command->cmd_num;
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
	while((i - 1) != len)
	{
		cmd->arguments[i++] = ft_strdup(argument->args);
		free(argument->args);
		free(argument);
		argument = argument->next;
	}
	cmd->arguments[i] = NULL;
	if (cmd->next != NULL)
		convert_linkedlist(cmd->next, cmd->next->args);
}

int main(int ac, char **av, char **env)
{
	t_tokens	*node_head;
	t_command	*command;
	char		*input;

	while (1)
	{
		node_head = NULL;
		command = malloc(sizeof(t_command));
		command->cmd_num = 0;
		input = readline("\033[31m~minishell$> \033[0m");
		if (ft_strlen(input) != 0)
		{
			add_history(input);
			super_split(&node_head ,input);
			// print_list(node_head);
			// printf("<<<<--------->>>>>\n");
			// get_envirement(node_head, env);
			remove_quotes(node_head);
			if (check_syntax_error(node_head) == 1 || check_brakets(input) == 1)
				printf("minishell~: syntax error near unexpected token\n");
			else
			{
				parsing(node_head, &command);
				convert_linkedlist(command, command->args);
				_exec(command, env);
			}
			if (command->cmd_num > 0)
				free_command(command);
			else
				free(command);
			// print_list(node_head);
			free_tokens(node_head);
		}
		free(input);
	}
}
