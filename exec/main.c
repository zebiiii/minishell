/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoudin <mgoudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 17:56:09 by mgoudin           #+#    #+#             */
/*   Updated: 2022/06/13 19:29:27 by mgoudin          ###   ########.fr       */
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

void	tty_hide_ctrl(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void    print_argv(char **argv)
{
	int i;

	i = 0;
	while(argv[i])
	{
		printf("%s ",argv[i]);
		i++;
	}
	printf("\n");
}

void del(void*el)
{
	t_cmd *cmd = (t_cmd *)el;
	free(cmd->content);
	free(el);
}

void del_2(void*el)
{
	//t_cmd *cmd = (t_cmd *)el;
	//if (cmd->content)
		//free(cmd->content);
	if (el)
		free(el);
}

void del_3(void*el)
{
	//t_cmd *cmd = (t_cmd *)el;
	//if (cmd->content)
		//free(cmd->content);
	return ;
}

void    sig_handler(int signo)
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

void    ft_create_export(char **env, t_list **first, t_data *data)
{
    int i;
	t_list *list;

    i = 0;
    *first = NULL;
    while (env[i])
        ft_lstadd_back(first, ft_lstnew(env[i++]));
	i = 0;
	list = *first;
	while (list)
	{
        list->content = ft_strjoin("declare -x ", (char *)list->content);
		list = list->next;
		i++;
	}
}

void    ft_create_env(char **env, t_list **first, t_data *data)
{
    int i;

    i = 0;
    *first = NULL;
    while (env[i])
    	ft_lstadd_back(first, ft_lstnew(env[i++]));
	data->lst_size = i;
}

int    ft_wait(int *pid)
{
    int status;
    int w;

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

int is_empty(t_list *lst)
{
	int type;

	while (lst)
	{
		type = (int)((t_cmd *)lst->content)->type;
		if (type != delete && type != pipe_)
			return (0);
		lst = lst->next;
	}
	return (1);
}

int	bt_before_fork(char **cmd, t_data *data, t_list *lst, int size)
{
	int i;
	int e;

	i = 0;
	e = 0;
	if (size == 1 && ft_strncmp(cmd[0], "exit", 4) == 0 
		&& ft_strlen(cmd[0]) == 4)
	{
		ft_putstr_fd("exit\n", 2);
		ft_exit_case(cmd + 1);
	}
	else if (size == 1 && (ft_strlen(cmd[0]) == 6) && 
		(ft_strncmp("export", cmd[0], 6) == 0))
	{	
		e = ft_export(cmd + 1, data->export_lst, data);
		g_global.exit_status = e;
		g_global.indicateur++;
	}
	else if (size == 1 && (ft_strlen(cmd[0]) == 3) && 
		(ft_strncmp("env", cmd[0], 3) == 0))
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
	else if (size == 1 && (ft_strlen(cmd[0]) == 5) && 
		(ft_strncmp("unset", cmd[0], 5) == 0))
	{	
		e = ft_unset(cmd + 1, data);
		g_global.exit_status = e;
		g_global.indicateur++;
	}
	return (0);
}

void ft_check_status(int *status)
{
	if (*status == 65280)
		*status = 255;
    else if (*status > 255)
        *status = *status % 255;
	if (g_global.indicateur == 0)
    	g_global.exit_status = *status;
}

int main(int argc, char **argv, char **env)
{
	t_list	*lst;
	t_list	**head;
	t_data	data;
	t_redirect	*tab;
	int		i;
	int 	pid;
	int 	status;
	char    *res;
	char 	**cmd;
	
	head = &lst;
	data.head_env = &data.env_lst;
	data.head_export = &data.export_lst; 
	status = 0;
	g_global.exit_status = 0;
	ft_create_env(env, &data.env_lst, &data);
	ft_create_export(env, &data.export_lst, &data);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	//tty_hide_ctrl();
	//while(42)
	//{
		i = 0;
		g_global.indicateur = 0;
		if (g_global.indicateur == 0)
			ft_lstclear(head, &del); 
		g_global.qlf = 0;
		g_global.heredoc = 0;
		g_global.in_heredoc = 0;
		//res = readline("minishell> ");
		//if (res == NULL)
			//exit(1);
		/*if (ft_strlen(res) < 1)
			continue;*/
		//add_history(res);
		res = create_space("unset LESS");
		ft_split_list(res, ' ', head);
		data.size = get_size(head);
		tab = handle_symbol(head, data.size);
		//if (!tab)
		//	continue;
		set_env(head);
		while (i < data.size)
		{
			cmd = lst_to_argv(head);
			bt_before_fork(cmd, &data, data.export_lst, data.size);
			//if (!cmd[0])
			//	close(tab[i].lst_pfd_in);
			//if (cmd[0] != 0 && g_global.indicateur == 0)
			//	pid = kangourou(cmd, env, &tab[i], &data);
			i++;
		}
		/*unlink(".heredoc");
        status = ft_wait(&pid);
		ft_check_status(&status);
		ft_freesplit(cmd);*/
		//ft_lstclear(data.head_export, &del_2);
		//ft_lstclear(head, &del);
		//ft_lstclear(data.head_env, &del_3);
		
		system("leaks minishell | grep leaked");
	//}
	return (0);
}
//segfault ft_lstclear 2ieme apl
//gerer a partir du egale
//gerer la fusion