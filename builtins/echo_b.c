/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 23:13:40 by omajdoub          #+#    #+#             */
/*   Updated: 2023/08/22 04:19:47 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int func(char* argument)
{
    int i = 1;
    if (argument[0] != 45)
        return(0);
    if (argument[i])
    {
        while (argument[i] == 'n')
            i++;
        if(argument[i] == '\0')
            return(1);
        if (argument[i] != '\0')
            return(0);
    }
    return(0);
}

int        echo_b(char** args)
{
    int i = 1;
    int nl = 1;

    if (args[i] && (!ft_strcmp(args[i], "-n" ) || func(args[i])))
    {
        nl = 0;
        i++;
    }
    while (args[i])
    {
        printf("%s", args[i]);
        if (args[i + 1])
            printf(" ");
        i++;
    }
    if (nl)
        printf("\n");
    return (0);
}
