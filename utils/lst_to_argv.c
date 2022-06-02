/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_to_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoudin <mgoudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 12:28:23 by mgoudin           #+#    #+#             */
/*   Updated: 2022/06/02 15:33:46 by mgoudin          ###   ########.fr       */
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
    argv = malloc(sizeof(char *) * count_arg(head));
    while(lst)
    {
        res = (char *)((t_cmd *)lst->content)->content;
        lst = lst->next;
        if (lst)
            type = (int)((t_cmd *)lst->content)->type;
        while(lst && (type == 8 || type == 9 || type == 10))
        {
            res = ft_strjoin(res, (char *)((t_cmd *)lst->content)->content);
            lst = lst->next;
            if (lst)
                type = (int)((t_cmd *)lst->content)->type;
        }
        argv[i++] = res;
    }
    return (argv);
}