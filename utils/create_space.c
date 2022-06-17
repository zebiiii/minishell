/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_space.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoudin <mgoudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 17:05:57 by mgoudin           #+#    #+#             */
/*   Updated: 2022/06/17 11:41:34 by mgoudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	count_symbol(t_data *data, char *str)
{
	if (str[data->i - 1] == '|')
		data->j++;
	if (str[data->i] == '<' && str[data->i - 1] != '<')
		data->j++;
	if (str[data->i] == '>' && str[data->i - 1] != '>')
		data->j++;
	if (str[data->i] != '<' && str[data->i - 1] == '<')
		data->j++;
	if (str[data->i] != '>' && str[data->i - 1] == '>')
		data->j++;
}

void	add_symbol(t_data *data, char *str, char *res)
{
	if (str[data->i - 1] == '|')
		res[data->i + data->j++] = ' ';
	if (str[data->i] == '<' && str[data->i - 1] != '<')
		res[data->i + data->j++] = ' ';
	if (str[data->i] == '>' && str[data->i - 1] != '>')
		res[data->i + data->j++] = ' ';
	if (str[data->i] != '<' && str[data->i - 1] == '<')
		res[data->i + data->j++] = ' ';
	if (str[data->i] != '>' && str[data->i - 1] == '>')
		res[data->i + data->j++] = ' ';
}

int	handle_stopcpy(t_data *data, char *str)
{
	int	stopcpy;

	stopcpy = 0;
	if (str[data->i] == '\"')
		stopcpy = (is_quote_close(&str[data->i], '\"') + 1);
	if (str[data->i] == '\'')
		stopcpy = (is_quote_close(&str[data->i], '\'') + 1);
	return (stopcpy);
}

char	*create_space(char *str)
{
	char	*res;
	int		stop_cpy;
	t_data	*data;

	res = ft_calloc(count_char(str) + 1, 1);
	data = ft_calloc(1, sizeof(t_data *));
	ft_init_space(data);
	stop_cpy = 0;
	while (str[data->i])
	{
		stop_cpy = handle_stopcpy(data, str);
		if (stop_cpy < 1)
		{
			if (str[data->i] == '|')
				res[data->i + data->j++] = ' ';
			if (data->i > 0)
				add_symbol(data, str, res);
		}
		else
			stop_cpy--;
		res[data->i + data->j] = str[data->i];
		data->i++;
	}
	res[data->i + data->j] = 0;
	return (res);
}
