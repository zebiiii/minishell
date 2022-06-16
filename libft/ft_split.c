/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoudin <mgoudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 17:21:19 by mgoudin           #+#    #+#             */
/*   Updated: 2022/06/16 15:43:27 by mgoudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../minishell.h"

int	ft_accuracy(char const *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (i && str[i] != c
			&& str[i - 1] == c)
			j++;
		if (str[i] != c && !i)
			j++;
		i++;
	}
	return (j);
}

t_cmd	*create_content(char *str, int quote, int suite)
{
	t_cmd	*cmd;

	cmd = calloc(1, sizeof(t_cmd *));
	cmd->content = str;
	if (quote && !suite)
		cmd->type = quote;
	else if (suite)
		cmd->type = suite;
	else
		cmd->type = get_type(str);
	return (cmd);
}

void	ft_add_content(t_split *data, char const *str, t_list **a)
{
	if (data->i > 0 && str[data->i - 1] != ' ')
		ft_lstadd_back(a, ft_lstnew(create_content(
					ft_strn(&str[data->i], data->j - 1), 0, 8)));
	else
		ft_lstadd_back(a, ft_lstnew(create_content(
					ft_strn(&str[data->i], data->j - 1), 0, 0)));
	data->i += data->j;
}

void	ft_split_list(char const *str, char c, t_list **a)
{
	t_split	*data;

	data = calloc(1, sizeof(*data));
	data->i = 0;
	while (str[data->i])
	{
		data->j = 0;
		while (str[data->i + data->j] && str[data->i + data->j] != c)
		{
			if (str[data->i + data->j] == '\"' && handle_quote(data, str, 1, a))
				break ;
			if (str[data->i + data->j] == '\'' && handle_quote(data, str, 0, a))
				break ;
			data->j++;
		}
		if (data->j)
			ft_add_content(data, str, a);
		else
			data->i++;
	}
	free(data);
}
