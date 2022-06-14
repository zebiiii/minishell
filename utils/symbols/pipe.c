/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoudin <mgoudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 15:40:39 by mgoudin           #+#    #+#             */
/*   Updated: 2022/06/14 15:40:48 by mgoudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int ft_pipe(t_list *lst, t_redirect tab[], int j, int size)
{
    int  pfd[2];

    if (pipe(pfd) == -1)
    {
        print_error("pipe failed\n");
        g_global.exit_status = 1;
        return (0);
    }
    tab[j].out = pfd[1];
    tab[j].lst_pfd_in = pfd[1];
    tab[j].lst_pfd_out = pfd[0];
    if (j + 1 < size)
    {
        tab[j + 1].in = pfd[0];
        tab[j + 1].st_pfd_in = pfd[1];
        tab[j + 1].st_pfd_out = pfd[0];
    }
    return (1);
}