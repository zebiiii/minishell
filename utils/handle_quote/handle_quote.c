/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoudin <mgoudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:43:29 by mgoudin           #+#    #+#             */
/*   Updated: 2022/06/16 18:57:23 by mgoudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_next_quote(t_split *data, char const *str, int type)
{
	int	next_quote;

	if (type)
		next_quote = is_quote_close(&str[data->i + data->j], '\"');
	else
		next_quote = is_quote_close(&str[data->i + data->j], '\'');
	return (next_quote);
}

int	handle_quote(t_split *data, char const *str, int type, t_list **a)
{
	int	suite;
	int	next_quote;

	suite = 0;
	next_quote = ft_next_quote(data, str, type);
	if (next_quote)
	{
		if (data->j)
		{
			if (data->i > 0 && str[data->i - 1] != ' ')
				suite = 8;
			ft_lstadd_back(a, ft_lstnew(create_content(
						ft_strn(&str[data->i], data->j - 1), 0, suite)));
			data->i += data->j;
		}
		if (data->i > 0 && str[data->i - 1] != ' ')
			suite = 9 + type;
		ft_lstadd_back(a, ft_lstnew(create_content(ft_strn(&str[data->i + 1],
						next_quote - 2), type + 1, suite)));
		data->i += next_quote;
		data->j = 0;
		return (1);
	}
	else
		return (0);
}
