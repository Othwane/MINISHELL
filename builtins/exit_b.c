/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omajdoub <omajdoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 23:13:32 by omajdoub          #+#    #+#             */
/*   Updated: 2023/08/13 15:46:46 by omajdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// exit should accept arguments, which is the exit status you
// want to exit with. if no arguments are specified, it exists with
// the last command's exit status
int exit_b() {
	exit(0);
}
