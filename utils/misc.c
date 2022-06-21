/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoudin <mgoudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:42:03 by mgoudin           #+#    #+#             */
/*   Updated: 2022/06/21 17:43:11 by mgoudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

enum s_type	get_type(char *str)
{
	enum s_type	type;

	type = content;
	if (!ft_strncmp(str, "|", 1))
		type = pipe_;
	if (!ft_strncmp(str, ">", 1))
		type = redirect_right;
	if (!ft_strncmp(str, "<", 1))
		type = redirect_left;
	if (!ft_strncmp(str, ">>", 2))
		type = double_redirect_right;
	if (!ft_strncmp(str, "<<", 2))
		type = double_redirect_left;
	return (type);
}

int	write_heredoc(char *heredoc, int fd)
{
	ft_putstr_fd(heredoc, fd);
	close(fd);
	fd = open(".heredoc", O_RDWR, 0644);
	return (fd);
}

int	count_char_return(t_matt *data)
{
	int	tmp;

	tmp = data->j + data->i;
	free(data);
	return (tmp);
}

int	count_char(char *str)
{
	t_matt	*data;
	int		stop_count;

	data = ft_calloc(1, sizeof(t_matt *));
	ft_init_space(data);
	stop_count = 0;
	while (str[data->i])
	{
		if (str[data->i] == '\"')
			stop_count = is_quote_close(&str[data->i], '\"') + 1;
		if (str[data->i] == '\'')
			stop_count = is_quote_close(&str[data->i], '\'') + 1;
		if (stop_count < 1)
		{
			if (str[data->i] == '|')
				data->j++;
			if (data->i > 0)
				count_symbol(data, str);
		}
		else
			stop_count--;
		data->i++;
	}
	return (count_char_return(data));
}

int	is_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}
