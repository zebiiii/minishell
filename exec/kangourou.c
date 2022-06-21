/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kangourou.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoudin <mgoudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 13:36:25 by mgoudin           #+#    #+#             */
/*   Updated: 2022/06/21 15:31:25 by mgoudin          ###   ########.fr       */
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

void	init_kg(t_data *data)
{
	data->indic_kg = 0;
	data->cas_kg = 0;
}

void	ft_check_kg(char **cmd, char **env, t_data *data, t_exec *var)
{
	if (ft_check_cmd(cmd, env, var) == 1)
		data->cas_kg++;
	if (parce_builtin(cmd, env, data) == 1
		|| parce_builtin_2(cmd, env, data) == 1)
		data->indic_kg++;
}

int	kangourou(char **cmd, char **env, t_redirect *tab, t_data *data)
{
	int		pid;
	t_exec	var;

	init_kg(data);
	ft_check_kg(cmd, env, data, &var);
	if (grep_path(env, &var) != -1 || var.indic != 0)
	{
		pid = fork();
		if (pid == -1)
			ft_quit_with_msg(NULL, "Error\nFork\n", 2, &var);
		if (pid == 0)
		{
			ft_dup(tab, &var);
			if (data->cas_kg == 1)
				exec_case(cmd, env, &var, data);
			else
				exec(cmd, env, &var, data);
		}
		else
			ft_close(tab);
	}
	else
		ft_msg(cmd[0], ": No such file or directory\n", 127, &var);
	return (pid);
}
