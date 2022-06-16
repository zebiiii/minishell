/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoudin <mgoudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 16:45:54 by mgoudin           #+#    #+#             */
/*   Updated: 2022/06/16 19:50:14 by mgoudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

typedef struct s_env
{
	int	i;
	int	j;
	int	k;
}				t_env;

void	ft_init_env(t_env *data)
{
	data->i = 0;
	data->j = 0;
	data->k = 0;
}

char	*replace_len(char *str, char *word, int len)
{
	char	*res;
	t_env	*data;
	int		length;

	data = ft_calloc(1, sizeof(t_env *));
	ft_init_env(data);
	length = ft_strlen(word) + ft_strlen(str);
	res = calloc(length - len + 1, 1);
	while (str[data->i])
	{
		if (str[data->i] == '$' && !(data->j))
		{
			while (word && word[data->j])
				res[data->k + data->j] = word[data->j++];
			data->k += data->j;
			data->i += len;
		}
		res[data->k] = str[data->i++];
		data->k++;
	}
	res[data->k] = 0;
	free(str);
	return (res);
}

//if (word) -> while(word && word)

int	check_env(t_cmd *e, char *tmp, int j)
{
	if (tmp == NULL)
	{
		e->content = replace_len(((char *)e->content), "", j);
		return (1);
	}
	return (0);
}

void	replace_env(t_cmd *e)
{
	int		i;
	int		j;
	char	*tmp;
	char	*word;

	i = -1;
	j = 0;
	while (((char *)e->content)[++i])
	{
		if (((char *)e->content)[i] == '$')
		{
			j = 1;
			tmp = ((char *)e->content)[i + j];
			while (tmp && tmp != ' ' && tmp != '$')
				j++;
			word = ft_strn(&((char *)e->content)[i + 1], j - 2);
			tmp = get_env_and_status(word);
			if (check_env(e, tmp, j))
				continue ;
			e->content = replace_len(((char *)e->content), tmp, j);
			i += ft_strlen(tmp) - 1;
		}
	}
}

void	set_env(t_list **a)
{
	t_list	*lst;
	int		type;

	lst = *a;
	while (lst)
	{
		type = (int)((t_cmd *)lst->content)->type;
		if (type != 1 && type != delete)
			replace_env((t_cmd *)lst->content);
		lst = lst->next;
	}
}
