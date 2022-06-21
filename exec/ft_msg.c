/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_msg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffiliz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 10:52:38 by ffiliz            #+#    #+#             */
/*   Updated: 2022/06/21 10:52:41 by ffiliz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_quit_with_msg(char *s1, char *s2, int exit_status, t_exec *var)
{
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(s2, 2);
	exit(exit_status);
}

void	ft_msg(char *s1, char *s2, int exit_status, t_exec *var)
{
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(s2, 2);
	g_global.exit_status = 127;
}
