/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omajdoub <omajdoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 13:10:57 by aasselma          #+#    #+#             */
/*   Updated: 2023/07/22 00:49:11 by omajdoub         ###   ########.fr       */
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

char** concat_argv(t_tokens* token)
{
	int argv_len = 0;
	t_tokens* tmp = token;
	int i = 0;
	while (tmp && !is_redirections(tmp->content) && ft_strcmp(tmp->content, "|"))
	{
		argv_len++;
		tmp = tmp->next;
	}
	char** ret = malloc(sizeof(char*) * argv_len + 1);
	while (token && !is_redirections(token->content) && ft_strcmp(token->content, "|"))
	{
		ret[i] = ft_strdup(token->content);
		i++;
		token = token->next;
	}
	ret[i] = NULL;
	return ret;
}

void	parcing(t_tokens *token, t_command **cmd)
{
	t_command	*command;

	command = *cmd;
	command->files = NULL;
	command->args = NULL;
	command->files = check_firts_token(&token);
	// add_command(&command, token->content);
	// token = token->next;
	while(token)
	{
		if (ft_strcmp(token->content, "|") == 0)
			break;
		else if (is_redirections(token->content))
		{
			add_files(&command->files, token->next->content, token->content);
			token = token->next;
		}
		else
		{
			command->argv = concat_argv(token);
			while (token && !is_redirections(token->content) && ft_strcmp(token->content, "|"))
				token = token->next;
		}
	}
	if (token)
	{
		command->next = malloc(sizeof(t_command));
		command->next->cmd_num = malloc(sizeof(t_cmd_nmbr));
		command->next->cmd_num->cmd_num = command->cmd_num->cmd_num;
		parcing(token->next, &command->next);
	}
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
		node_head = NULL;
		command = malloc(sizeof(t_command));
		command->cmd_num = malloc(sizeof(t_cmd_nmbr));
		command->cmd_num->cmd_num = 0;
		command->next = NULL;
		input = readline("\033[31m~minishell$> \033[0m");
		if (ft_strlen(input) != 0)
		{
			add_history(input);
			super_split(&node_head ,input);
			get_envirement(node_head, env);
			if (check_syntax_error(node_head) == 1 || check_brakets(input) == 1)
				printf("minishell~: syntax error near unexpected token\n");
			else
			{
				parcing(node_head, &command);
				// _exec(command);
			}
			if (command)
			{
				print_command(command);
				free_command(command);
			}
			else
				free(command);
			free_tokens(node_head);
		}
		free(input);
	}
}
