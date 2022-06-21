/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoudin <mgoudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 17:56:09 by mgoudin           #+#    #+#             */
/*   Updated: 2022/06/21 16:29:28 by mgoudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_readline(t_data data)
{
	char	*res;

	res = readline("minishell> ");
	if (res == NULL)
	{
		unlink(".heredoc");
		ft_lstclear(data.head_export, &del_2);
		ft_lstclear(data.head_env, &del_3);
		exit(1);
	}
	return (res);
}

int	ft_send_to_exec(t_list	**head, t_data data, t_redirect *tab, char **env)
{
	char	**cmd;
	int		i;
	int		pid;

	i = 0;
	pid = 0;
	while (i < data.size)
	{
		cmd = lst_to_argv(head);
		bt_before_fork(cmd, &data, data.size);
		if (!cmd[0] && tab[i].lst_pfd_in)
			close(tab[i].lst_pfd_in);
		if (cmd[0] != 0 && g_global.indicateur == 0)
			pid = kangourou(cmd, env, &tab[i], &data);
		i++;
	}
	return (pid);
}

void	ft_execute(t_list **head, t_data data, char **env)
{
	t_redirect	*tab;
	char		*res;
	int			pid;
	int			status;

	res = ft_readline(data);
	if (ft_strlen(res) < 1)
		return ;
	add_history(res);
	res = create_space(res);
	ft_split_list(res, ' ', head);
	data.size = get_size(head);
	tab = handle_symbol(head, data.size, data);
	if (!tab)
		return ;
	set_env(head, data);
	pid = ft_send_to_exec(head, data, tab, env);
	unlink(".heredoc");
	status = ft_wait(&pid);
	ft_check_status(&status);
	return ;
}

int	main(int argc, char **argv, char **env)
{
	t_list		*lst;
	t_list		**head;
	t_data		data;

	head = &lst;
	data.head_env = &data.env_lst;
	data.head_export = &data.export_lst;
	g_global.exit_status = 0;
	init_env(env, &data);
	set_signals();
	while (42)
	{
		ft_lstclear(head, &del);
		ft_initglobal();
		ft_execute(head, data, env);
	}
	(void)argc;
	(void)argv;
	return (0);
}
