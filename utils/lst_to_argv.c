/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_to_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoudin <mgoudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 12:28:23 by mgoudin           #+#    #+#             */
/*   Updated: 2022/06/15 19:35:30 by mgoudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

typedef struct s_argv
{
	char *res;
	int type;
	int i;
}			    t_argv;

int count_arg(t_list **head)
{
    t_list *lst;
    int     i;
    int     type;

    i = 0;
    lst = *head;
    while (lst)
	{
        type = (int)((t_cmd *)lst->content)->type;
        if (type == 3)
            break;
        if (type != 8 && type != 9 && type != 10 && type != 11)
            i++;
		lst = lst->next;
	}
    return (i);
}

void    ft_initdata_argv(t_argv *data)
{
    data->res = 0;
    data->type = 0;
    data->i = 0;
}

t_list *ft_initargv(t_argv *data, t_list *lst)
{
    data->res = (char *)((t_cmd *)lst->content)->content;
    ((t_cmd *)lst->content)->type = delete;
    
    lst = lst->next;
    if (lst)
        data->type = (int)((t_cmd *)lst->content)->type;
    return (lst);
}

int end_argv(t_list *lst)
{
    if ((int)((t_cmd *)lst->content)->type == pipe_)
    {
        ((t_cmd *)lst->content)->type = delete;
        return (1);
    }
    return (0);
}

t_list *ft_iterargv(t_list *lst, t_argv *data)
{
    while(lst && (data->type == 8 || data->type == 9 || data->type == 10))
    {
        data->res = ft_strjoin(data->res, (char *)((t_cmd *)lst->content)->content);
        ((t_cmd *)lst->content)->type = delete;
        lst = lst->next;
        if (lst)
            data->type = (int)((t_cmd *)lst->content)->type;
    }
    return (lst);
}

char    **lst_to_argv(t_list **head)
{
    char **argv;
    t_argv *data;
    t_list *lst;

    lst = *head;
    argv = calloc(count_arg(head) + 1, sizeof(char *));
    data = ft_calloc(1, sizeof(t_argv*));
    ft_initdata_argv(data);
    while(lst)
    {
        if ((int)((t_cmd *)lst->content)->type == delete)
        {
            lst = lst->next;
            continue;
        }
        if (end_argv(lst))
            break;
        lst = ft_initargv(data, lst);
        lst = ft_iterargv(lst, data);
        argv[data->i++] = data->res;
    }
    argv[data->i] = 0;
    return (argv);
}