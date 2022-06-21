/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_symbol.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoudin <mgoudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 19:45:41 by mgoudin           #+#    #+#             */
/*   Updated: 2022/06/21 16:26:41 by mgoudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_redirect	*handle_symbol_error(t_redirect *tab, int j)
{
	ft_closetab(tab, j);
	free(tab);
	return (NULL);
}

void	ft_closetab(t_redirect *tab, int j)
{
	int	i;

	i = 0;
	while (i <= j)
	{
		if (tab[i].out != 1)
			close(tab[i].out);
		if (tab[i].in != 0)
			close(tab[i].in);
		if (tab[i].st_pfd_in && tab[i].st_pfd_out)
		{
			close(tab[i].st_pfd_in);
			close(tab[i].st_pfd_out);
		}
		if (tab[i].lst_pfd_in && tab[i].lst_pfd_out)
		{
			close(tab[i].lst_pfd_in);
			close(tab[i].lst_pfd_out);
		}
		i++;
	}
}

int	handle_error(t_symbol *data, char *tmp, char *str)
{
	if (tmp == 0)
	{
		str = replace_len(str, "", data->j);
		data->i++;
		return (1);
	}
	if (is_space(tmp))
		print_error("ambiguous redirect\n");
	return (0);
}

char	*free_error(t_symbol *data)
{
	free(data);
	return (0);
}
