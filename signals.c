/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 01:20:36 by aasselma          #+#    #+#             */
/*   Updated: 2023/08/20 23:45:21 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

void signal_handler(int signum)
{
    (void)signum;
    printf("\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void    set_signal()
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}