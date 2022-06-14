/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doubleredirect_in.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoudin <mgoudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 15:26:27 by mgoudin           #+#    #+#             */
/*   Updated: 2022/06/14 21:17:24 by mgoudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

typedef struct s_heredoc
{
	int	listener;
	char *heredoc;
	char *line;
	int fd;
}					t_heredoc;

int	write_heredoc(char *heredoc, int fd)
{
	ft_putstr_fd(heredoc, fd);
	close(fd);
	fd = open(".heredoc", O_RDWR, 0644);
    return (fd);
}

void ft_initdata(t_heredoc *data)
{
    g_global.in_heredoc = 1;
    data->line = NULL;
    data->heredoc = NULL;
    data->listener = dup(0);
    g_global.listener = data->listener;
    data->fd = -1;
}

int ft_firstcall(t_heredoc *data, char *limiter)
{
    data->line = get_next_line(data->listener);
    if (data->line == NULL || g_global.heredoc)
    {
        rl_redisplay();
        if (g_global.heredoc)
        {
            data->fd = -1;
            g_global.exit_status = 1;
        }
        else
            data->fd = write_heredoc("", data->fd);
        return (1);
    }
	if (ft_strncmp(data->line, limiter, ft_strlen(limiter)) == 0)
		return (1);
    return (0);
}

void    ft_openheredoc(t_heredoc *data)
{
    data->fd = open(".heredoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (data->fd < 0)
    {
        print_error("Error\nFile Descriptor\n");
        g_global.exit_status = 1;
    }
}

int    ft_quitcase(t_heredoc *data)
{
    rl_redisplay();
    if (g_global.heredoc)
    {
        g_global.exit_status = 1;
        return (-1);
    }
    return (write_heredoc("", data->fd));
}

int	ft_heredoc(char *limiter)
{
    t_heredoc *data;

    data = ft_calloc(1, sizeof(t_heredoc*));
    ft_initdata(data);
    ft_openheredoc(data);
    if (data->fd < 0)
        return (data->fd);
    ft_putstr_fd("> ", 1);
    if(ft_firstcall(data, limiter) == 1)
        return (data->fd);
	while (data->line && ft_strncmp(data->line, limiter, ft_strlen(limiter)) != 0)
	{
		if (!(ft_strncmp(data->line, limiter, ft_strlen(limiter)) == 0))
			data->heredoc = ft_gnljoin(data->heredoc, data->line);
        ft_putstr_fd("> ", 1);
		data->line = get_next_line(data->listener);
        if (data->line == NULL || g_global.heredoc)
            return (ft_quitcase(data));
	}
    data->fd = write_heredoc(data->heredoc, data->fd);
    g_global.in_heredoc = 0;
    return (data->fd);
}

// int	ft_heredoc(char *limiter)
// {
// 	char	*line;
//     int     fd;
//     char    *heredoc;
//     int     listener;

//     g_global.in_heredoc = 1;
//     fd = open(".heredoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
//     if (fd < 0)
//     {
//         print_error("Error\nFile Descriptor\n");
//         g_global.exit_status = 1;
//         return (fd);
//     }
//     heredoc = NULL;
//     ft_putstr_fd("> ", 1);
//     listener = dup(0);
//     g_global.listener = listener;
//     line = get_next_line(listener);
//     if (line == NULL || g_global.heredoc)
//     {
//         rl_redisplay();
//         if (g_global.heredoc)
//         {
//             fd = -1;
//             g_global.exit_status = 1;
//         }
//         else
//             fd = write_heredoc("", fd);
//         return (fd);
//     }
// 	if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
// 		return (fd);
// 	while (line && ft_strncmp(line, limiter, ft_strlen(limiter)) != 0)
// 	{
// 		if (!(ft_strncmp(line, limiter, ft_strlen(limiter)) == 0))
// 			heredoc = ft_gnljoin(heredoc, line);
//         ft_putstr_fd("> ", 1);
// 		line = get_next_line(listener);
//         if (line == NULL || g_global.heredoc)
//         {
//             rl_redisplay();
//             if (g_global.heredoc)
//             {
//                 fd = -1;
//                 g_global.exit_status = 1;
//             }
//             else
//                 fd = write_heredoc("", fd);
//             return (fd);
//         }
// 	}
//     fd = write_heredoc(heredoc, fd);
//     g_global.in_heredoc = 0;
//     return (fd);
// }


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
        return (-1);
    return (fd);
}