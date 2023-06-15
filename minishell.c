/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 13:10:57 by aasselma          #+#    #+#             */
/*   Updated: 2023/06/15 12:58:58 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

void	print_list(t_content *my_list)
{
	t_content	*node_head;
	
	node_head = my_list;
	while(node_head)
	{
		printf("[%s]\n", node_head->content);
		node_head = node_head->next;
	}
}

int main()
{
	t_content	*node_head;
	char		*input;

	node_head = NULL;
	while (1)
	{
		input = readline("\033[31m~minishell$> \033[0m");
		check_brakets(input);
		super_split(&node_head ,input);
		print_list(node_head);
		while(node_head)
		{
			free(node_head->content);
			free(node_head);
			node_head = node_head->next;
		}
		free(input);
	}
	return 0;
}

// echo hello"   world  $this  'amien  ' hi "kill

// >>cc|cat|wc -l     ==>        |>>| |cc| ||| |cat| |wc| |-l|
// >> << > <   sp |
