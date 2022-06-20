/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoudin <mgoudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 16:45:54 by mgoudin           #+#    #+#             */
/*   Updated: 2022/06/20 19:38:21 by mgoudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*replace_len(char *str, char *word, int len)
{
	char	*res;
	t_env	*data;
	int		length;

	data = ft_calloc(1, sizeof(t_env *));
	ft_init_env2(data);
	length = ft_strlen(word) + ft_strlen(str);
	res = ft_calloc(length - len + 1, 1);
	while (str[data->i])
	{
		if (str[data->i] == '$' && !(data->j))
		{
			while (word[data->j])
			{
				res[data->k + data->j] = word[data->j];
				data->j++;
			}
			increment_var(data, len);
		}
		res[data->k] = str[data->i];
		increment(data);
	}
	res[data->k] = 0;
	free(data);
	return (res);
}

int	check_env(t_cmd *e, char *tmp, int j)
{
	if (tmp == NULL)
	{
		e->content = replace_len(((char *)e->content), "", j);
		return (1);
	}
	return (0);
}

void	replace_env(t_cmd *e, t_data data)
{
	int		i;
	int		j;
	char	*tmp;
	char	*word;

	i = 0;
	j = 0;
	while (((char *)e->content)[i])
	{
		if (((char *)e->content)[i] == '$')
		{
			j = 1;
			tmp = ((char *)e->content);
			while (tmp[i + j] && tmp[i + j] != ' ' && tmp[i + j] != '$')
				j++;
			word = ft_strn(&((char *)e->content)[i + 1], j - 2);
			tmp = get_env_and_status(word, data);
			if (check_env(e, tmp, j))
				continue ;
			e->content = replace_len(((char *)e->content), tmp, j);
			i += ft_strlen(tmp) - 1;
		}
		i++;
	}
}

void	set_env(t_list **a, t_data data)
{
	t_list	*lst;
	int		type;

	lst = *a;
	while (lst)
	{
		type = (int)((t_cmd *)lst->content)->type;
		if (type != 1 && type != delete)
			replace_env((t_cmd *)lst->content, data);
		lst = lst->next;
	}
}
