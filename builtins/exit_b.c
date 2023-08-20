/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 23:13:32 by omajdoub          #+#    #+#             */
/*   Updated: 2023/08/19 23:22:01 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// exit should accept arguments, which is the exit status you
// want to exit with. if no arguments are specified, it exists with
// the last command's exit status
int exit_b()
{
	exit(0);
}
