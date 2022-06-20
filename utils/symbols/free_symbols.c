/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_symbols.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoudin <mgoudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 13:07:25 by mgoudin           #+#    #+#             */
/*   Updated: 2022/06/20 20:25:44 by mgoudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	free_symbol(int fd, void *el)
{
	int	tmp;

	tmp = fd;
	free(el);
	return (tmp);
}

int	free_symbol_heredoc(int fd, t_heredoc *el)
{
	int	tmp;

	tmp = fd;
	free(el->line);
	free(el->heredoc);
	free(el);
	return (tmp);
}

int	handle_exit_heredoc(t_heredoc *data)
{
	free(data->heredoc);
	return (free_symbol(ft_quitcase(data), data));
}

int	end_heredoc(t_heredoc *data)
{
	data->fd = write_heredoc(data->heredoc, data->fd);
	free(data->heredoc);
	g_global.in_heredoc = 0;
	return (free_symbol(data->fd, data));
}
