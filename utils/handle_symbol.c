/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_symbol.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoudin <mgoudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 12:05:30 by mgoudin           #+#    #+#             */
/*   Updated: 2022/06/15 19:18:08 by mgoudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

typedef struct  s_data
{
	int		i;
	int		j;
}               t_data;

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

int   handle_error(t_data *data, char *tmp, char *str)
{
    if (tmp == 0)
    {
        str = replace_len(str, "", data->j);
        data->i++;
        return (1);
    }
    if (is_space(tmp))
        print_error("ambiguous redirect\n");
    return (0);
}

void    ft_init_env(t_data *data)
{   
    data->i = 0;
    data->j = 0;
}

char    *replace_env_link(char *str)
{
    t_data  *data;
    char *tmp;
    char *word;

    data = ft_calloc(1, sizeof(t_data*));
    ft_init_env(data);
    while(str[data->i])
    {
        if (str[data->i] == '$')
        {
            data->j = 1;
            while(str[data->i + data->j] && str[data->i + data->j] != ' ' && str[data->i + data->j] != '$')
                data->j++;
            word = ft_strn(&str[data->i + 1], data->j - 2);
            if (!ft_strncmp(word, "?", ft_strlen(word)))
                tmp = ft_itoa(g_global.exit_status);
            else
                tmp = getenv(word);
            if(handle_error(data, tmp, str))
                continue;
            str = replace_len(str, tmp, data->j);
            data->i += ft_strlen(tmp) - 1;
        }
        data->i++;
    }
    return (str);
}

void    init_stdin_stdout(t_redirect *tab, int len)
{
    int i;

    i = 0;
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
}

int    handle_type_redirect(t_list *lst, t_redirect *tab, int type, int j)
{
    if (type == redirect_right)
    {
        tab[j].out = ft_redirect_out(lst); 
        if (tab[j].out == 0)
            return (0);
    }
    if (type == redirect_left)
    {
        tab[j].in = ft_redirect_in(lst); 
        if (tab[j].in == 0)
            return (0);
    }
    if (type == double_redirect_right)
    {
        tab[j].out = ft_doubleredirect_out(lst); 
        if (tab[j].out == 0)
            return (0);
    }
    if (type == double_redirect_left)
    {
        tab[j].in = ft_doubleredirect_in(lst);
        if (tab[j].in == -1)
            return (0);
    }
    return (1);
}

int handle_type_pipe(t_list *lst, t_redirect *tab, int j, int len)
{
    if (!(lst->next))
    {
        print_error("Nothing after last pipe\n");
        g_global.exit_status = 2;
        return (0);
    }
    if ((int)((t_cmd *)lst->next->content)->type == pipe_)
    {
        print_error("Two followed pipe\n");
        g_global.exit_status = 2;
        return (0);
    }
    if (!ft_pipe(lst, tab, j, len))
        return (0);
    return (1);
}

t_redirect  *handle_symbol(t_list **head, int len)
{
    t_list *lst;
    t_redirect *tab;
    int type;
    int j;
    
    lst = *head;
    tab = ft_calloc(len, sizeof(t_redirect));
    init_stdin_stdout(tab, len);
    j = 0;
    while(lst)
    {
        type = (int)((t_cmd *)lst->content)->type;
        if (type == pipe_)
        {
            if (!handle_type_pipe(lst, tab, j, len))
                return (NULL);
            j++;
        }
        if (!handle_type_redirect(lst, tab, type, j))
            return (NULL);
        lst = lst->next;
    }
    return (tab);
}
