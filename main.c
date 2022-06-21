/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoudin <mgoudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 17:56:09 by mgoudin           #+#    #+#             */
/*   Updated: 2022/06/21 15:32:47 by mgoudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_lst(t_list *lst)
{
	while (lst)
	{
		printf("%s\n", (char *)((t_cmd *)lst->content)->content);
		printf("type: %d\n", (int)((t_cmd *)lst->content)->type);
		lst = lst->next;
	}
}

void	print_lst2(t_list *lst)
{
	while (lst)
	{
		printf("%s\n", (char *)lst->content);
		lst = lst->next;
	}
}

void	tty_hide_ctrl(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	print_argv(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		printf("%s ", argv[i]);
		i++;
	}
	printf("\n");
}

void	del(void*el)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)el;
	free(cmd->content);
	free(el);
}

void	del_2(void*el)
{
	if (el)
		free(el);
}

void	del_3(void*el)
{
	return ;
}

void	sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		if (g_global.in_heredoc)
		{
			g_global.heredoc = 1;
			close(g_global.listener);
		}
		if (g_global.in_heredoc == 0 && g_global.qlf == 0)
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
}

void	ft_create_export(t_list **first, t_data *data)
{
	int		i;
	t_list	*list;

	i = 0;
	*first = NULL;
	while (data->export_dup[i])
		ft_lstadd_back(first, ft_lstnew(data->env_dup[i++]));
	i = 0;
	list = *first;
	while (list)
	{
		list->content = ft_strjoin_f("declare -x ", (char *)list->content);
		list = list->next;
		i++;
	}
}

void	ft_create_env(t_list **first, t_data *data)
{
	int	i;

	i = 0;
	*first = NULL;
	while (data->env_dup[i])
		ft_lstadd_back(first, ft_lstnew(data->env_dup[i++]));
	data->lst_size = i;
}

int	ft_wait(int *pid)
{
	int	status;
	int	w;

	w = 0;
	status = 0;
	w = waitpid(*pid, &status, 0);
	if (WIFSIGNALED(status))
		g_global.exit_status = 128 + WTERMSIG(status);
	else if (WIFCONTINUED(status))
		g_global.exit_status = 128 + WIFEXITED(status);
	else if (WIFSTOPPED(status))
		g_global.exit_status = 128 + WSTOPSIG(status);
	while (wait(NULL) > 0)
		break ;
	return (status);
}

int	is_empty(t_list *lst)
{
	int	type;

	while (lst)
	{
		type = (int)((t_cmd *)lst->content)->type;
		if (type != delete && type != pipe_)
			return (0);
		lst = lst->next;
	}
	return (1);
}

void	bt_exit(char **cmd)
{
	ft_putstr_fd("exit\n", 2);
	ft_exit_case(cmd + 1);
}

void bt_export(char **cmd, t_data *data, int e)
{
	e = ft_export(cmd + 1, data->export_lst, data);
	g_global.exit_status = e;
	g_global.indicateur++;
}

void bt_env(char **cmd, t_data *data, int e)
{
	if (cmd[1])
	{
		ft_putstr_fd("Error\nNo arg or option for env.\n", 2);
		g_global.exit_status = 127;
		g_global.indicateur++;
	}
	else
	{
		e = ft_env(data->env_lst);
		g_global.exit_status = e;
		g_global.indicateur++;
	}
}

void	bt_unset(char **cmd, t_data *data, int e)
{
	e = ft_unset(cmd + 1, data);
	g_global.exit_status = e;
	g_global.indicateur++;
}

int	bt_before_fork(char **cmd, t_data *data, t_list *lst, int size)
{
	int	i;
	int	e;

	i = 0;
	e = 0;
    if (cmd[0] == 0)
        return 0;
	if (size == 1 && ft_strncmp(cmd[0], "exit", 4) == 0
		&& ft_strlen(cmd[0]) == 4)
		bt_exit(cmd);
	else if (size == 1 && (ft_strlen(cmd[0]) == 6)
		&& (ft_strncmp("export", cmd[0], 6) == 0))
		bt_export(cmd, data, e);
	else if (size == 1 && (ft_strlen(cmd[0]) == 3)
		&& (ft_strncmp("env", cmd[0], 3) == 0))
		bt_env(cmd, data, e);
	else if (size == 1 && (ft_strlen(cmd[0]) == 5)
		&& (ft_strncmp("unset", cmd[0], 5) == 0))
		bt_unset(cmd, data, e);
	return (0);
}

void	ft_check_status(int *status)
{
	if (*status == 65280)
		*status = 255;
	else if (*status > 255)
		*status = *status % 255;
	if (g_global.indicateur == 0)
		g_global.exit_status = *status;
}

void	ft_dup_env(char **env, t_data *data)
{
	data->env_dup = ft_strdup2d(env);
	data->export_dup = ft_strdup2d(env);
}

void	init_env(char **env, t_data *data)
{
	ft_dup_env(env, data);
	ft_create_env(data->head_env, data);
	ft_create_export(data->head_export, data);
}

void set_signals(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}

char *ft_readline(t_data data)
{
	char *res;

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

void	ft_initglobal(void)
{
	g_global.indicateur = 0;
	g_global.qlf = 0;
	g_global.heredoc = 0;
	g_global.in_heredoc = 0;
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
		bt_before_fork(cmd, &data, data.export_lst, data.size);
		if (!cmd[0] && tab[i].lst_pfd_in)
			close(tab[i].lst_pfd_in);
		if (cmd[0] != 0 && g_global.indicateur == 0)
			pid = kangourou(cmd, env, &tab[i], &data);
		 i++;
	}
	return (pid);
}

void    ft_execute(t_list **head, t_data data, char **env)
{
    t_redirect  *tab;
    char        *res;
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
	return (0);
}