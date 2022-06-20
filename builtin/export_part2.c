/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffiliz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:04:47 by ffiliz            #+#    #+#             */
/*   Updated: 2022/06/20 16:10:04 by ffiliz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_content(char *tmp, t_list *lst, t_data *data)
{
	t_list	*first;
	int		len;
	int		len2;

	len = ft_strlen(tmp);
	first = lst;
	if (lst)
	{
		while (first)
		{
			if (ft_strncmp(first->content, tmp, len) == 0)
			{
				len2 = ft_strlen(first->content);
				if (((char *)first->content)[len] == '=')
					return (1);
				if (len2 == len)
					return (1);
			}
			first = first->next;
		}
	}
	return (0);
}

int	ft_add_to_export(char *argv, t_list *lst, t_data *data)
{
	char	*tmp;

	tmp = ft_strjoin_f("declare -x ", argv);
	if (!tmp)
		return (-1);
	if (ft_check_content(tmp, lst, data) != 1)
		ft_lstadd_back(data->head_export, ft_lstnew((char *)tmp));
	else
	{
		if (tmp)
			free(tmp);
	}
	return (0);
}

int	ft_len_equal(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	return (i);
}

int	ft_fusion_equal(char *tmp, t_list *lst, char *str)
{
	t_list	*first;
	char	*tmp2;

	first = lst;
	tmp2 = NULL;
	if (lst)
	{
		while (first)
		{
			if (ft_strncmp(first->content, tmp, ft_len_equal(tmp)) == 0)
			{
				tmp2 = ft_substr(first->content,
						0, ft_len_equal(first->content));
				if (ft_strcmp(tmp, tmp2) == 0)
				{
					free(first->content);
					first->content = str;
					free(tmp2);
					return (1);
				}
			}
			first = first->next;
		}
	}
	return (0);
}

int	ft_fusion(char *argv, t_list *lst, t_data *data)
{
	char	*tmp;
	char	*tmp2;
	char	*argv_copie;

	tmp = ft_strjoin_quote("declare -x ", argv);
	tmp2 = ft_substr(tmp, 0, ft_len_equal(tmp));
	if (ft_fusion_equal(tmp2, lst, tmp) != 1)
	{
		argv_copie = ft_strdup(argv);
		free(tmp2);
		ft_lstadd_back(data->head_export, ft_lstnew(tmp));
		if (data->head_env)
			ft_lstadd_back(data->head_env, ft_lstnew(argv_copie));
	}
	else
	{
		free(tmp2);
		tmp2 = ft_substr(argv, 0, ft_len_equal(argv));
		argv_copie = ft_strdup(argv);
		if (ft_fusion_equal(tmp2, data->env_lst, argv_copie) == 0)
			ft_lstadd_back(data->head_env, ft_lstnew(argv_copie));
		free(tmp2);
	}
	return (0);
}
