/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_symbol.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoudin <mgoudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 12:05:30 by mgoudin           #+#    #+#             */
/*   Updated: 2022/06/03 16:53:44 by mgoudin          ###   ########.fr       */
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

int	ft_heredoc(char *limiter)
{
	char	*line;
    int     fd;
    char    *heredoc;

    fd = open(".heredoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (fd < 0)
        print_error("Error\nFile Descriptor\n");
    line = get_next_line(0);
	if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		return (fd);
	while (ft_strncmp(line, limiter, ft_strlen(limiter)) != 0)
	{
		if (!(ft_strncmp(line, limiter, ft_strlen(limiter)) == 0))
			heredoc = ft_gnljoin(heredoc, line);
		line = get_next_line(0);
	}
    fd = write_heredoc(heredoc, fd);
    return (fd);
}

int    ft_redirect_out(t_list *lst)
{
    int fd;
    char *arg;

    arg = (char *)((t_cmd *)lst->next->content)->content;
    fd = open(arg, O_DIRECTORY | O_WRONLY, 0644);
    if (fd > 0)
        print_error(ft_strjoin(arg, " is a directory\n"));
    fd = open(arg, O_WRONLY | O_CREAT, 0644);
    if (fd == -1)
        print_error(ft_strjoin(arg, " does not exist\n"));
    ((t_cmd *)lst->content)->type = delete;
    ((t_cmd *)lst->next->content)->type = delete;
    return (fd);
}

int    ft_redirect_in(t_list *lst)
{
    int fd;
    char *arg;

    arg = (char *)((t_cmd *)lst->next->content)->content;
    fd = open(arg, O_DIRECTORY | O_RDONLY | O_CREAT, 0644);
    if (fd == -1)
        print_error(ft_strjoin(arg, " does not exist\n"));
    ((t_cmd *)lst->content)->type = delete;
    ((t_cmd *)lst->next->content)->type = delete;
    return (fd);
}

int    ft_doubleredirect_out(t_list *lst)
{
    int fd;
    char *arg;

    arg = (char *)((t_cmd *)lst->next->content)->content;
    fd = open(arg, O_DIRECTORY | O_WRONLY, 0644);
    if (fd > 0)
        print_error(ft_strjoin(arg, " is a directory\n"));
    fd = open(arg, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1)
        print_error(ft_strjoin(arg, " does not exist\n"));
    ((t_cmd *)lst->content)->type = delete;
    ((t_cmd *)lst->next->content)->type = delete;
    return (fd);
}

int    ft_doubleredirect_in(t_list *lst)
{
    int fd;
    char *arg;

    arg = (char *)((t_cmd *)lst->next->content)->content;
    fd = ft_heredoc(arg);
    unlink(".heredoc");
    ((t_cmd *)lst->content)->type = delete;
    ((t_cmd *)lst->next->content)->type = delete;
    return (fd);
}

void    handle_symbol(t_list **head, t_list **head_symbol)
{
    t_list *lst;
    int type;
    int i;
    int j;
    t_redirect tab[1]; //get amount of cmd

    lst = *head;
    i = 0;
    j = 0;
    tab[0].out = 1;
    tab[0].in = 0;
    while(lst)
    {
        type = (int)((t_cmd *)lst->content)->type;
        //if (type == pipe_)
        if (type == redirect_right)
            tab[j].out = ft_redirect_out(lst); 
        if (type == redirect_left)
            tab[j].in = ft_redirect_in(lst); 
        if (type == double_redirect_right)
            tab[j].out = ft_doubleredirect_out(lst); 
        if (type == double_redirect_left)
            tab[j].in = ft_doubleredirect_in(lst);
        i++;
        lst = lst->next;
    }
    printf("fd: %d\n", tab[0].in);
    printf("fd: %d\n", tab[0].out);
}

//todo: handle no 2nd arg