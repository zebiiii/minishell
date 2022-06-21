/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_close.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffiliz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 10:52:29 by ffiliz            #+#    #+#             */
/*   Updated: 2022/06/21 10:52:32 by ffiliz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_dup(t_redirect *tab, t_exec *var)
{
	if (tab->lst_pfd_in != 0 && tab->lst_pfd_out != 0)
		close(tab->lst_pfd_out);
	if (tab->in == -1)
		ft_quit_with_msg(NULL, "Error fd", 2, var);
	if (dup2(tab->in, STDIN_FILENO) == -1)
		ft_quit_with_msg(NULL, "", 2, var);
	if (dup2(tab->out, STDOUT_FILENO) == -1)
		ft_quit_with_msg(NULL, "", 2, var);
}

void	ft_close(t_redirect *tab)
{
	if (tab->lst_pfd_in != 0)
		close(tab->lst_pfd_in);
	if (tab->st_pfd_in != 0)
		close(tab->st_pfd_in);
	if (tab->in)
		close(tab->in);
	if (tab->out != 1)
		close(tab->out);
}
