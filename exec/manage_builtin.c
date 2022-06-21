/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffiliz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 10:52:49 by ffiliz            #+#    #+#             */
/*   Updated: 2022/06/21 10:59:15 by ffiliz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	manage_builtin_part_1(char **cmd, char **env, t_data *data)
{
	int	e;

	e = 0;
	if ((ft_strlen(cmd[0]) == 4)
		&& (ft_strncmp("echo", cmd[0], 4) == 0))
		ft_echo(ft_strlen2d(cmd), cmd + 1);
	else if ((ft_strlen(cmd[0]) == 2)
		&& (ft_strncmp("cd", cmd[0], 2) == 0))
		ft_cd(cmd);
	else if ((ft_strlen(cmd[0]) == 3)
		&& (ft_strncmp("pwd", cmd[0], 3) == 0))
		ft_pwd();
	else if ((ft_strlen(cmd[0]) == 3)
		&& (ft_strncmp("env", cmd[0], 3) == 0))
	{
		if (cmd[1])
		{
			ft_putstr_fd("Error\nNo arg or option for env.\n", 2);
			exit(127);
		}
		else
		{
			if (ft_env(data->env_lst) == 0)
				exit(EXIT_SUCCESS);
		}
	}
}

void	manage_builtin_part_2(char **cmd, char **env, t_data *data)
{
	int	e;

	e = 0;
	if ((ft_strlen(cmd[0]) == 4) && (ft_strncmp("exit", cmd[0], 4) == 0))
		ft_exit_case(cmd + 1);
	else if ((ft_strlen(cmd[0]) == 6) && (ft_strncmp("export", cmd[0], 7) == 0))
	{
		e = ft_export(cmd + 1, data->export_lst, data);
		if (e == -1)
			exit(EXIT_FAILURE);
		else if (e == 2)
			exit(2);
		else
			exit(EXIT_SUCCESS);
	}
	else if ((ft_strlen(cmd[0]) == 5) && (ft_strncmp("unset", cmd[0], 5) == 0))
	{
		e = ft_unset(cmd + 1, data);
		if (e == 0)
			exit(EXIT_SUCCESS);
	}
}
