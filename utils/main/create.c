/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoudin <mgoudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 15:42:03 by mgoudin           #+#    #+#             */
/*   Updated: 2022/06/21 15:46:55 by mgoudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_create_export(t_list **first, t_data *data)
{
	int		i;
	t_list	*list;

	i = 0;
	*first = NULL;
	while (data->export_dup[i])
		ft_lstadd_back(first, ft_lstnew(data->env_dup[i++]));
	i = 0;
	list = *first;
	while (list)
	{
		list->content = ft_strjoin_f("declare -x ", (char *)list->content);
		list = list->next;
		i++;
	}
}

void	ft_create_env(t_list **first, t_data *data)
{
	int	i;

	i = 0;
	*first = NULL;
	while (data->env_dup[i])
		ft_lstadd_back(first, ft_lstnew(data->env_dup[i++]));
	data->lst_size = i;
}

void	ft_initglobal(void)
{
	g_global.indicateur = 0;
	g_global.qlf = 0;
	g_global.heredoc = 0;
	g_global.in_heredoc = 0;
}

void	init_env(char **env, t_data *data)
{
	ft_dup_env(env, data);
	ft_create_env(data->head_env, data);
	ft_create_export(data->head_export, data);
}
