/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoudin <mgoudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 15:35:39 by mgoudin           #+#    #+#             */
/*   Updated: 2022/06/21 16:28:54 by mgoudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	bt_exit(char **cmd)
{
	ft_putstr_fd("exit\n", 2);
	ft_exit_case(cmd + 1);
}

void	bt_export(char **cmd, t_data *data, int e)
{
	e = ft_export(cmd + 1, data->export_lst, data);
	g_global.exit_status = e;
	g_global.indicateur++;
}

void	bt_env(char **cmd, t_data *data, int e)
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

int	bt_before_fork(char **cmd, t_data *data, int size)
{
	int	i;
	int	e;

	i = 0;
	e = 0;
	if (cmd[0] == 0)
		return (0);
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
	else if (size == 1 && (ft_strlen(cmd[0]) == 2)
		&& (ft_strncmp("cd", cmd[0], 2) == 0))
		bt_cd(cmd, e, data);
	return (0);
}
