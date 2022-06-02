/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoudin <mgoudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 16:45:54 by mgoudin           #+#    #+#             */
/*   Updated: 2022/06/02 12:27:39 by mgoudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char    *replace_len(char *str, char *word, int len)
{
    char    *res;
    int     i;
    int     j;
    int     k;
    int     length; 

    i = 0;
    k = 0;
    j = 0;
    length = ft_strlen(word) + ft_strlen(str);
    res = malloc(length - len + 1);
    while(str[i])
    {
        if (str[i] == '$' && !j)
        {   
            if (word)
                while(word[j])
                {
                    res[k + j] = word[j];
                    j++;
                }
            k += j;
            i += len;
        }
        res[k] = str[i];
        i++;
        k++;
    }
    res[k] = 0;
    free(str);
    return (res);
}

void    replace_env(t_cmd *e)
{
    int i;
    int j;
    char *tmp;

    i = 0;
    j = 0;
    while(((char *)e->content)[i])
    {
        if (((char *)e->content)[i] == '$')
        {
            j = 1;
            while(((char *)e->content)[i + j] && ((char *)e->content)[i + j] != ' ' && ((char *)e->content)[i + j] != '$')
                j++;
            tmp = getenv(ft_strn(&((char *)e->content)[i + 1], j - 2));
            if (tmp == NULL)
            {
                e->content = replace_len(((char *)e->content), "", j);
                i++;
                continue;
            }
            e->content = replace_len(((char *)e->content), tmp, j);
            i += ft_strlen(tmp) - 1;
        }
        i++;
    }
}

void    set_env(t_list **a)
{
    t_list *lst;

    lst = *a;
    while (lst)
	{
        if ((int)((t_cmd *)lst->content)->type != 1)
            replace_env((t_cmd *)lst->content);
		lst = lst->next;
	}
}