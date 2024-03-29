/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoudin <mgoudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 15:25:12 by mgoudin           #+#    #+#             */
/*   Updated: 2022/06/20 19:59:40 by mgoudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_list	*ft_init(t_redirectin *data, t_list *lst, t_data env)
{
	((t_cmd *)lst->content)->type = delete;
	lst = lst->next;
	if (!lst)
		return (0);
	data->arg = replace_env_link((char *)((t_cmd *)lst->content)->content, env);
	if (!(data->arg))
		return (0);
	((t_cmd *)lst->content)->type = delete;
	lst = lst->next;
	if (lst)
		data->type = (int)((t_cmd *)lst->content)->type;
	else
		data->type = 0;
	return (lst);
}

void	ft_open(t_redirectin *data)
{
	if (!(data->arg))
		return ;
	data->fd = open(data->arg, O_DIRECTORY | O_RDONLY, 0644);
	if (data->fd == -1)
		data->fd = open(data->arg, O_RDONLY, 0644);
	if (data->fd == -1)
	{
		print_error(data->arg);
		print_error(": No such file or directory\n");
		g_global.exit_status = 1;
	}
}

int	ft_redirect_in(t_list *lst, t_data env)
{
	t_redirectin	*data;

	data = ft_calloc(1, sizeof(t_redirectin *));
	lst = ft_init(data, lst, env);
	if (!lst)
	{
		ft_open(data);
		return (free_symbol(data->fd, data));
	}
	while (lst && (data->type == 8 || data->type == 9 || data->type == 10))
	{
		data->tmp = replace_env_link(
				(char *)((t_cmd *)lst->content)->content, env);
		if (!(data->tmp))
			return (free_symbol(0, data));
		data->arg = ft_strjoin(data->arg, data->tmp);
		((t_cmd *)lst->content)->type = delete;
		lst = lst->next;
		if (lst)
			data->type = (int)((t_cmd *)lst->content)->type;
	}
	ft_open(data);
	return (free_symbol(data->fd, data));
}

// int    ft_redirect_in(t_list *lst)
// {
//     int fd;
//     char *arg;
//     char *tmp;
//     int type;

//     ((t_cmd *)lst->content)->type = delete;
//     lst = lst->next;
//     if (!lst)
//         return (0);
//     arg = replace_env_link((char *)((t_cmd *)lst->content)->content);
//     if (!arg)
//         return (0);
//     ((t_cmd *)lst->content)->type = delete;
//     lst = lst->next;
//     if (lst)
//         type = (int)((t_cmd *)lst->content)->type;
//     else
//         type = 0;
//     while(lst && (type == 8 || type == 9 || type == 10))
//     {
//         tmp = replace_env_link((char *)((t_cmd *)lst->content)->content);
//         if (!tmp)
//             return (0);
//         arg = ft_strjoin(arg, tmp);
//         ((t_cmd *)lst->content)->type = delete;
//         lst = lst->next;
//         if (lst)
//             type = (int)((t_cmd *)lst->content)->type;
//     }
//     fd = open(arg, O_DIRECTORY | O_RDONLY, 0644);
//     if (fd == -1)
//         fd = open(arg, O_RDONLY, 0644);
//     if (fd == -1)    
//     {
//         print_error(ft_strjoin(arg, ": No such file or directory\n"));
//         g_global.exit_status = 1;
//         return (fd);
//     }
//     return (fd);
// }
