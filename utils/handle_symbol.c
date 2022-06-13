/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_symbol.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoudin <mgoudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 12:05:30 by mgoudin           #+#    #+#             */
/*   Updated: 2022/06/13 18:24:53 by mgoudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	write_heredoc(char *heredoc, int fd)
{
	ft_putstr_fd(heredoc, fd);
	close(fd);
	fd = open(".heredoc", O_RDWR, 0644);
    return (fd);
}

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

int	ft_heredoc(char *limiter)
{
	char	*line;
    int     fd;
    char    *heredoc;
    int     listener;

    g_global.in_heredoc = 1;
    fd = open(".heredoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (fd < 0)
    {
        print_error("Error\nFile Descriptor\n");
        g_global.exit_status = 1;
        return (-1);
    }
    heredoc = NULL;
    ft_putstr_fd("> ", 1);
    listener = dup(0);
    g_global.listener = listener;
    line = get_next_line(listener);
    if (line == NULL || g_global.heredoc)
    {
        rl_redisplay();
        fd = write_heredoc("", fd);
        return (fd);
    }
	if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		return (fd);
	while (line && ft_strncmp(line, limiter, ft_strlen(limiter)) != 0)
	{
		if (!(ft_strncmp(line, limiter, ft_strlen(limiter)) == 0))
			heredoc = ft_gnljoin(heredoc, line);
        ft_putstr_fd("> ", 1);
		line = get_next_line(listener);
        if (line == NULL || g_global.heredoc)
        {
            rl_redisplay();
            fd = write_heredoc("", fd);
            return (fd);
        }
	}
    fd = write_heredoc(heredoc, fd);
    g_global.in_heredoc = 0;
    return (fd);
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
            {
                print_error("ambiguous redirect\n");
                g_global.exit_status = 1;
                return (0);
            }
            str = replace_len(str, tmp, j);
            i += ft_strlen(tmp) - 1;
        }
        i++;
    }
    return (str);
}

int    ft_redirect_out(t_list *lst)
{
    int fd;
    char *arg;
    char *tmp;
    int type;

    ((t_cmd *)lst->content)->type = delete;
    lst = lst->next;
    if (!lst)
        return (0);
    arg = replace_env_link((char *)((t_cmd *)lst->content)->content);
    if (!arg)
        return (0);
    ((t_cmd *)lst->content)->type = delete;
    lst = lst->next;
    if (lst)
        type = (int)((t_cmd *)lst->content)->type;
    else
        type = 0;
    while(lst && (type == 8 || type == 9 || type == 10))
    {
        tmp = replace_env_link((char *)((t_cmd *)lst->content)->content);
        if (!tmp)
            return (0);
        arg = ft_strjoin(arg, tmp);
        ((t_cmd *)lst->content)->type = delete;
        lst = lst->next;
        if (lst)
            type = (int)((t_cmd *)lst->content)->type;
    }
    fd = open(arg, O_DIRECTORY | O_WRONLY, 0644);
    if (fd > 0)
    {
        print_error(ft_strjoin(arg, " is a directory\n"));
        g_global.exit_status = 1;
        return (0);
    }
    fd = open(arg, O_WRONLY | O_CREAT, 0644);
    if (fd == -1)
    {
        print_error(ft_strjoin(arg, ": No such file or directory\n"));
        g_global.exit_status = 1;
        return (0);
    }
    return (fd);
}

int    ft_redirect_in(t_list *lst)
{
    int fd;
    char *arg;
    char *tmp;
    int type;

    ((t_cmd *)lst->content)->type = delete;
    lst = lst->next;
    if (!lst)
        return (0);
    arg = replace_env_link((char *)((t_cmd *)lst->content)->content);
    if (!arg)
        return (0);
    ((t_cmd *)lst->content)->type = delete;
    lst = lst->next;
    if (lst)
        type = (int)((t_cmd *)lst->content)->type;
    else
        type = 0;
    while(lst && (type == 8 || type == 9 || type == 10))
    {
        tmp = replace_env_link((char *)((t_cmd *)lst->content)->content);
        if (!tmp)
            return (0);
        arg = ft_strjoin(arg, tmp);
        ((t_cmd *)lst->content)->type = delete;
        lst = lst->next;
        if (lst)
            type = (int)((t_cmd *)lst->content)->type;
    }
    fd = open(arg, O_DIRECTORY | O_RDONLY, 0644);
    if (fd == -1)
        fd = open(arg, O_RDONLY, 0644);
    if (fd == -1)    
    {
        print_error(ft_strjoin(arg, ": No such file or directory\n"));
        g_global.exit_status = 1;
        return (0);
    }
    return (fd);
}

int    ft_doubleredirect_out(t_list *lst)
{
    int fd;
    char *arg;
    char *tmp;
    int type;

    ((t_cmd *)lst->content)->type = delete;
    lst = lst->next;
    if (!lst)
        return (0);
    arg = replace_env_link((char *)((t_cmd *)lst->content)->content);
    if (!arg)
        return (0);
    ((t_cmd *)lst->content)->type = delete;
    lst = lst->next;
    if (lst)
        type = (int)((t_cmd *)lst->content)->type;
    else
        type = 0;
    while(lst && (type == 8 || type == 9 || type == 10))
    {
        tmp = replace_env_link((char *)((t_cmd *)lst->content)->content);
        if (!tmp)
            return (0);
        arg = ft_strjoin(arg, tmp);
        ((t_cmd *)lst->content)->type = delete;
        lst = lst->next;
        if (lst)
            type = (int)((t_cmd *)lst->content)->type;
    }
    fd = open(arg, O_DIRECTORY | O_WRONLY, 0644);
    if (fd > 0)
    {
        print_error(ft_strjoin(arg, " is a directory\n"));
        g_global.exit_status = 1;
        return (0);
    }
    fd = open(arg, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1)
    {
        print_error(ft_strjoin(arg, ": No such file or directory\n"));
        g_global.exit_status = 1;
        return (0);
    }
    return (fd);
}

int    ft_doubleredirect_in(t_list *lst)
{
    int fd;
    char *arg;

    ((t_cmd *)lst->content)->type = delete;
    lst = lst->next;
    if (!lst)
        return (0);
    arg = (char *)((t_cmd *)lst->content)->content;
    if (!arg)
        return (0);
    ((t_cmd *)lst->content)->type = delete;
    fd = ft_heredoc(arg);
    if (!fd)
        return (0);
    return (fd);
}

int ft_pipe(t_list *lst, t_redirect tab[], int j, int size)
{
    int  pfd[2];

    if (pipe(pfd) == -1)
    {
        print_error("pipe failed\n");
        g_global.exit_status = 1;
        return (0);
    }
    tab[j].out = pfd[1];
    tab[j].lst_pfd_in = pfd[1];
    tab[j].lst_pfd_out = pfd[0];
    if (j + 1 < size)
    {
        tab[j + 1].in = pfd[0];
        tab[j + 1].st_pfd_in = pfd[1];
        tab[j + 1].st_pfd_out = pfd[0];
    }
    return (1);
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
