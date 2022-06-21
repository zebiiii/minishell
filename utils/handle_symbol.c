/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_symbol.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoudin <mgoudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 12:05:30 by mgoudin           #+#    #+#             */
/*   Updated: 2022/06/21 16:26:53 by mgoudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*replace_env_link(char *str, t_data env)
{
	t_symbol	*data;
	char		*tmp;
	char		*word;

	data = ft_calloc(1, sizeof(t_symbol *));
	ft_init_env(data);
	while (str[data->i])
	{
		if (str[data->i] == '$')
		{
			data->j = 1;
			while (str[data->i + data->j] && str[data->i + data->j] != ' '
				&& str[data->i + data->j] != '$')
				data->j++;
			word = ft_strn(&str[data->i + 1], data->j - 2);
			tmp = get_env_and_status(word, env);
			if (handle_error(data, tmp, str))
				return (free_error(data));
			str = replace_len(str, tmp, data->j);
			data->i += ft_strlen(tmp) - 1;
		}
		data->i++;
	}
	free(data);
	return (str);
}

int	handle_heredoc(t_list *lst, t_redirect *tab, int j)
{
	int	type;

	type = (int)((t_cmd *)lst->content)->type;
	if (type == double_redirect_left)
	{
		tab[j].in = ft_doubleredirect_in(lst);
		if (tab[j].in == -1)
			return (0);
	}
	return (1);
}

int	handle_type_redirect(t_list *lst, t_redirect *tab, int j, t_data env)
{
	int	type;

	type = (int)((t_cmd *)lst->content)->type;
	if (type == redirect_right)
	{
		tab[j].out = ft_redirect_out(lst, env);
		if (tab[j].out == 0)
			return (0);
	}
	if (type == redirect_left)
	{
		tab[j].in = ft_redirect_in(lst, env);
		if (tab[j].in == 0)
			return (0);
	}
	if (type == double_redirect_right)
	{
		tab[j].out = ft_doubleredirect_out(lst, env);
		if (tab[j].out == 0)
			return (0);
	}
	return (handle_heredoc(lst, tab, j));
}

int	handle_type_pipe(t_list *lst, t_redirect *tab, int j, int len)
{
	if (!(lst->next))
	{
		print_error("Nothing after last pipe\n");
		g_global.exit_status = 2;
		return (0);
	}
	if ((int)((t_cmd *)lst->next->content)->type == pipe_)
	{
		print_error("Two followed pipe\n");
		g_global.exit_status = 2;
		return (0);
	}
	if (!ft_pipe(tab, j, len))
		return (0);
	return (1);
}

t_redirect	*handle_symbol(t_list **head, int len, t_data env)
{
	t_list		*lst;
	t_redirect	*tab;
	int			type;
	int			j;

	lst = *head;
	tab = ft_calloc(len, sizeof(t_redirect));
	init_stdin_stdout(tab, len);
	j = 0;
	while (lst)
	{
		type = (int)((t_cmd *)lst->content)->type;
		if (type == pipe_)
		{
			if (!handle_type_pipe(lst, tab, j, len))
				return (handle_symbol_error(tab, j));
			j++;
		}
		if (!handle_type_redirect(lst, tab, j, env))
			return (handle_symbol_error(tab, j));
		lst = lst->next;
	}
	return (tab);
}
