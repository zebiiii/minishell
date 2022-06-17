/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoudin <mgoudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:42:03 by mgoudin           #+#    #+#             */
/*   Updated: 2022/06/17 14:25:18 by mgoudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

enum s_type	get_type(char *str)
{
	enum s_type	type;
	int			len;

	len = len;
	type = content;
	if (!ft_strncmp(str, "|", len))
		type = pipe_;
	if (!ft_strncmp(str, ">", len))
		type = redirect_right;
	if (!ft_strncmp(str, "<", len))
		type = redirect_left;
	if (!ft_strncmp(str, ">>", len))
		type = double_redirect_right;
	if (!ft_strncmp(str, "<<", len))
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

int count_char_return(t_data *data)
{
	int	tmp;

	tmp = data->j + data->i;
	free(data);
	return (tmp);
}

int	count_char(char *str)
{
	t_data	*data;
	int		stop_count;

	data = ft_calloc(1, sizeof(t_data *));
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

char	*get_env_and_status(char *word)
{
	char	*tmp;

	if (!ft_strncmp(word, "?", ft_strlen(word)))
		tmp = ft_itoa(g_global.exit_status);
	else
		tmp = getenv(word);
	return (tmp);
}
