/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffiliz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 23:26:22 by ffiliz            #+#    #+#             */
/*   Updated: 2022/06/20 23:31:45 by ffiliz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_del_env(char *argv, t_data *data, t_list *lst)
{
	data->indic = 0;
	data->current = lst;
	data->before = data->current;
	if (!lst)
		return (0);
	while (data->current)
	{
		if (ft_strncmp(data->current->content, argv, ft_len_equal(argv)) == 0)
		{
			data->tmp = ft_substr(data->current->content, 0,
					ft_len_equal(data->current->content));
			if (ft_strcmp(argv, data->tmp) == 0)
			{
				if (data->indic == 0)
					data->before = data->current->next;
				else
					data->before->next = data->current->next;
				free_triple(data->current->content, data->tmp, data->current);
				return (1);
			}
			free(data->tmp);
		}
		become(data);
	}
	return (0);
}

int	analyse_str(char c)
{
	if ((!(c >= 65 && c <= 90))
		&& (!(c >= 97 && c <= 122)))
	{
		if ((c >= 48 && c <= 57) || (c == '_'))
			return (1);
		else
			return (-1);
	}
	return (1);
}

int	ft_check_eq(char *argv, t_data *data)
{
	int		i;
	int		indic;
	char	*tmp;

	tmp = NULL;
	indic = 0;
	i = -1;
	while (argv[++i])
	{
		if (analyse_str(argv[i]) == 1)
			continue ;
		else
			return (ft_exit_unset(": not a valid identifier\n", argv));
	}
	tmp = ft_strjoin_f("declare -x ", argv);
	if (ft_del_env(tmp, data, data->export_lst) == 1)
	{
		free(tmp);
		tmp = ft_strdup(argv);
		ft_del_env(tmp, data, data->env_lst);
		free(tmp);
		return (1);
	}
	return (0);
}

int	ft_check_unset(char *argv, t_data *data)
{
	int	i;

	i = ft_check_first_char(argv);
	if (i == 1)
		i = ft_check_eq(argv, data);
	return (i);
}

int	ft_unset(char **argv, t_data *data)
{
	int	i;
	int	e;
	int	esc;

	i = 0;
	e = ft_check_option_unset(argv[0]);
	if (e == 1)
		return (e);
	if (e == 0)
	{
		while (argv[i])
		{
			e = ft_check_unset(argv[i], data);
			if (e == -1)
				esc = e;
			i++;
		}
	}
	if (esc == -1)
		return (1);
	return (0);
}
