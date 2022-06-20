/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoudin <mgoudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:37:16 by mgoudin           #+#    #+#             */
/*   Updated: 2022/06/20 18:22:22 by mgoudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_initdata(t_heredoc *data)
{
	g_global.in_heredoc = 1;
	data->line = ft_calloc(1, 1);
	data->heredoc = ft_calloc(1, 1);
	data->listener = dup(0);
	g_global.listener = data->listener;
	data->fd = -1;
}

void	ft_init_env(t_symbol *data)
{
	data->i = 0;
	data->j = 0;
}

void	init_stdin_stdout(t_redirect *tab, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		tab[i].out = 1;
		tab[i].in = 0;
		tab[i].st_pfd_in = 0;
		tab[i].st_pfd_out = 0;
		tab[i].lst_pfd_in = 0;
		tab[i].lst_pfd_out = 0;
		i++;
	}
}

void	ft_init_space(t_matt *data)
{
	data->i = 0;
	data->j = 0;
}

void	ft_initdata_argv(t_argv *data)
{
	data->res = 0;
	data->type = 0;
	data->i = 0;
}
