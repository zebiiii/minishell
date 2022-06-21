/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kangourou.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoudin <mgoudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 13:36:25 by mgoudin           #+#    #+#             */
/*   Updated: 2022/06/21 00:31:30 by ffiliz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec(char **cmd, char **env, t_exec *var, t_data *data)
{
	ft_chech_builtin(cmd, env, data);
	var->path = NULL;
	var->index_env = 0;
	if (grep_path(env, var) == -1)
		ft_quit_with_msg(NULL, "Error\nPATH\n", 1, var);
	var->env_path = ft_split(env[var->index_env], ':');
	if (ft_check_path(cmd, var->env_path, var) == 0)
	{
		var->slash_join = ft_charjoin_lst(var->env_path[var->index_path],
				'/');
		var->path = ft_gnljoin(var->slash_join, cmd[0]);
		ft_freesplit(var->env_path);
		if (execve(var->path, cmd, env) == -1)
			ft_quit_with_msg(NULL, "Error\nNo prog to execute\n", 126, var);
	}
	else
		ft_quit_with_msg(cmd[0], ": command not found\n", 127, var);
}

void	exec_case(char **cmd, char **env, t_exec *var, t_data *data)
{
	ft_chech_builtin_case(cmd, env, var, data);
	if (execve(cmd[0], cmd, env) == -1)
		ft_quit_with_msg(NULL, "Error\nNo prog to execute\n", 126, var);
	else
		ft_quit_with_msg(cmd[0], ": command not found\n", 127, var);
}

int	kangourou(char **cmd, char **env, t_redirect *tab, t_data *data)
{
	int		pid;
	int		cas;
	int		indic;
	t_exec	var;

	indic = 0;
	cas = 0;
	if (ft_check_cmd(cmd, env, &var) == 1)
		cas++;
	if (parce_builtin(cmd, env, data) == 1
		|| parce_builtin_2(cmd, env, data) == 1)
		indic++;
	if (grep_path(env, &var) != -1 || indic != 0)
	{
		pid = fork();
		if (pid == -1)
			ft_quit_with_msg(NULL, "Error\nFork\n", 2, &var);
		if (pid == 0)
		{
			ft_dup(tab, &var);
			if (cas == 1)
				exec_case(cmd, env, &var, data);
			else
				exec(cmd, env, &var, data);
		}
		else
		{
			g_global.qlf = 1;
			ft_close(tab);
		}
	}
	else
		ft_msg(cmd[0], ": No such file or directory\n", 127, &var);
	return (pid);
}
