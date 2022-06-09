/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoudin <mgoudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 17:21:19 by mgoudin           #+#    #+#             */
/*   Updated: 2022/06/08 19:09:48 by mgoudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../minishell.h"

struct s_data
{
	int		i;
	int		j;
	int		k;
	char	**array;
};

char	*ft_strn(char const *str, int lenght)
{
	char	*value;
	int		i;

	value = malloc(lenght + 1);
	if (!value)
		return (0);
	i = 0;
	while (i <= lenght)
	{
		value[i] = str[i];
		i++;
	}
	value[i] = '\0';
	return (value);
}

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

enum s_type get_type(char *str)
{
	enum s_type	type;
	int		len;

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

t_cmd *create_content(char *str, int quote, int suite)
{
	t_cmd *cmd;

	cmd = malloc(sizeof(t_cmd *));
	cmd->content = str;
	if (quote && !suite)
		cmd->type = quote;
	else if (suite)
		cmd->type = suite;
	else
		cmd->type = get_type(str);
	return (cmd);
}

int	handle_quote(struct s_data *data, char const *str, int type, t_list **a)
{
	int	suite;
	int	next_quote;

	suite = 0;
	if (type)
		next_quote = is_quote_close(&str[data->i + data->j], '\"');
	else 
		next_quote = is_quote_close(&str[data->i + data->j], '\'');
	if (next_quote)
	{
		if (data->j)
		{
			if (data->i > 0 && str[data->i - 1] != ' ')
				suite = 8;
			ft_lstadd_back(a, ft_lstnew(create_content(ft_strn(&str[data->i], data->j - 1), 0, suite)));
			data->i += data->j;
		}
		if (data->i > 0 && str[data->i - 1] != ' ')
			suite = 9 + type;
		ft_lstadd_back(a, ft_lstnew(create_content(ft_strn(&str[data->i + 1], next_quote - 2), 2, suite)));
		data->i += next_quote;
		data->j = 0;
		return (1);
	}
	else
		return (0);
}

void	ft_split_list(char const *str, char c, t_list **a)
{
	struct s_data	*data;
	int	next_quote;
	int	nfq;

	next_quote = 0;
	data = malloc(sizeof(*data));
	data->i = 0;
	while (str[data->i])
	{
		data->j = 0;
		while (str[data->i + data->j] && str[data->i + data->j] != c)
		{
			if (str[data->i + data->j] == '\"')
				if (handle_quote(data, str, 1, a))
					break;
			if (str[data->i + data->j] == '\'')
				if (handle_quote(data, str, 0, a))
					break;
			data->j++;
		}
		if (data->j)
		{
			if (data->i > 0 && str[data->i - 1] != ' ')
				ft_lstadd_back(a, ft_lstnew(create_content(ft_strn(&str[data->i], data->j - 1), 0, 8)));
			else
				ft_lstadd_back(a, ft_lstnew(create_content(ft_strn(&str[data->i], data->j - 1), 0, 0)));
			data->i += data->j;
		}
		else
			data->i++;
	}
	free(data);
}

