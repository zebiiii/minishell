/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_symbol.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoudin <mgoudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 12:05:30 by mgoudin           #+#    #+#             */
/*   Updated: 2022/06/14 15:48:02 by mgoudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_space(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == ' ')
            return (1);
        i++;
    }
    return (0);
}

char    *replace_env_link(char *str)
{
    int i;
    int j;
    char *tmp;
    char *word;

    i = 0;
    j = 0;
    while(str[i])
    {
        if (str[i] == '$')
        {
            j = 1;
            while(str[i + j] && str[i + j] != ' ' && str[i + j] != '$')
                j++;
            word = ft_strn(&str[i + 1], j - 2);
            if (!ft_strncmp(word, "?", ft_strlen(word)))
                tmp = ft_itoa(g_global.exit_status);
            else
                tmp = getenv(word);
            if (tmp == 0)
            {
                str = replace_len(str, "", j);
                i++;
                continue;
            }
            if (is_space(tmp))
                print_error("ambiguous redirect\n");
            str = replace_len(str, tmp, j);
            i += ft_strlen(tmp) - 1;
        }
        i++;
    }
    return (str);
}

t_redirect  *handle_symbol(t_list **head, int len)
{
    t_list *lst;
    int type;
    int i;
    int j;
    t_redirect *tab;
    
    lst = *head;
    i = 0;
    j = 0;
    tab = calloc(len, sizeof(t_redirect));
    while(i < len)
    {
        tab[i].out = 1;
        tab[i].in = 0;
        tab[i].st_pfd_in = 0;
        tab[i].st_pfd_out = 0;
        tab[i].lst_pfd_in = 0;
        tab[i].lst_pfd_out = 0;
        i++;
    }
    while(lst)
    {
        type = (int)((t_cmd *)lst->content)->type;
        if (type == pipe_)
        {
            if (!(lst->next))
            {
                print_error("Nothing after last pipe\n");
                g_global.exit_status = 2;
                return (NULL);
            }
            if ((int)((t_cmd *)lst->next->content)->type == pipe_)
            {
                print_error("Two followed pipe\n");
                g_global.exit_status = 2;
                return (NULL);
            }
            if (!ft_pipe(lst, tab, j, len))
                return (NULL);
            j++;
        }
        if (type == redirect_right)
        {
            tab[j].out = ft_redirect_out(lst); 
            if (tab[j].out == 0)
                return (NULL);
        }
        if (type == redirect_left)
        {
            tab[j].in = ft_redirect_in(lst); 
            if (tab[j].in == 0)
                return (NULL);
        }
        if (type == double_redirect_right)
        {
            tab[j].out = ft_doubleredirect_out(lst); 
            if (tab[j].out == 0)
                return (NULL);
        }
        if (type == double_redirect_left)
        {
            tab[j].in = ft_doubleredirect_in(lst);
            if (tab[j].in == -1)
                return (NULL);
        }
        lst = lst->next;
    }
    return (tab);
}
