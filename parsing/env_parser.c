/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 23:13:24 by omajdoub          #+#    #+#             */
/*   Updated: 2023/08/14 11:31:02 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env_e* create_env_node() {
	t_env_e* ret = malloc(sizeof(t_env_e));
	ret->key = NULL;
	ret->value = NULL;
	return ret;
}

t_env_e* parse_env(char** env) {
	if (!env || !*env)
		return NULL; // generate and return a dummy env
	int i = 0;
	t_env_e* ret = create_env_node();
	t_env_e* tmp = ret;
	while (env[i]) {
		char** spl_tmp = ft_split(env[i], '=');
		ret->key = spl_tmp[0];
		ret->value = spl_tmp[1];
		if (env[i + 1])
		{
			ret->next = create_env_node();
			ret = ret->next;
		}
		i++;
	}
	return tmp;
}

// char** join_env_lst(t_env_e* env_lst) {
// 	return NULL;
// }

void print_env_ll(t_env_e* lst) {
	while (lst) {
		printf("lst key: %s | lst val: %s\n", lst->key, lst->value);
		lst = lst->next;
	}
}
