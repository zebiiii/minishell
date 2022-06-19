/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoudin <mgoudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 17:57:49 by mgoudin           #+#    #+#             */
/*   Updated: 2022/04/29 19:07:20 by mgoudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_check_exit(char *arg)
{
    int i;

    i = 0;
    if (!arg)
        return (0);
    while(arg[i])
    {
        if (!(arg[i] >= 48 && arg[i] <= 57))
        {
            if (arg[i] == '-')
            {
                i++;
                continue;
            }
            else
                return (1);
        }
        i++;
    }
    return (0);
}

void    ft_exit_char(void)
{
    ft_putstr_fd("exit: numeric argument required\n", 2);
    exit(255);
}

void    ft_exit_arg(void)
{
    ft_putstr_fd("exit: too many arguments\n", 2);
    exit(EXIT_FAILURE);
}

int ft_exit_case(char **status)
{
    long long exit_value;

    exit_value = 0;
    if (status[0] && ft_check_exit(status[0]) == 0)
    {
        if (ft_strlen2d(status) <= 1)
        {
            if (status[0])
            {
                exit_value = ft_atoi_exit_case(*status);
                exit(exit_value % 256);
            }
            else
                exit(0);
        }
        else
            ft_exit_arg();
    }
    else if (status[0])
        ft_exit_char();
    else
        exit(EXIT_SUCCESS);
    return(0);
}