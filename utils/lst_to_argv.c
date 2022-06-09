/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_to_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoudin <mgoudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 12:28:23 by mgoudin           #+#    #+#             */
/*   Updated: 2022/06/09 15:04:34 by mgoudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
        if (type != 8 && type != 10 && type != 11)
            i++;
		lst = lst->next;
	}
    return (i);
}

char    **lst_to_argv(t_list **head)
{
    char **argv;
    t_list *lst;
    char *res;
    int type;
    int i;

    i = 0;
    lst = *head;
    argv = malloc(sizeof(char *) * count_arg(head) + 1);
    while(lst)
    {
        res = (char *)((t_cmd *)lst->content)->content;
        if ((int)((t_cmd *)lst->content)->type == delete)
        {
            lst = lst->next;
            continue;
        }
        if ((int)((t_cmd *)lst->content)->type == pipe_)
        {
            ((t_cmd *)lst->content)->type = delete;
            break;
        }
        ((t_cmd *)lst->content)->type = delete;
        lst = lst->next;
        if (lst)
            type = (int)((t_cmd *)lst->content)->type;
        while(lst && (type == 8 || type == 9 || type == 10))
        {
            res = ft_strjoin(res, (char *)((t_cmd *)lst->content)->content);
            ((t_cmd *)lst->content)->type = delete;
            lst = lst->next;
            if (lst)
                type = (int)((t_cmd *)lst->content)->type;
        }
        argv[i++] = res;
    }
    argv[i] = 0;
    return (argv);
}