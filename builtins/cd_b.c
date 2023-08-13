/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_b.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omajdoub <omajdoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 23:13:15 by omajdoub          #+#    #+#             */
/*   Updated: 2023/08/13 17:30:13 by omajdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int cd_b(char** argv) {
	if (!argv)
		return 1;
	if (!argv[1]) {
		chdir(getenv("HOME"));
	}
	else {
		if (chdir(argv[1]) == -1) {
			// should print in stderr
			printf("minishell: cd: %s: No such file or directory\n", argv[1]);
			return 1;
		}
	}
	return 0;
}
