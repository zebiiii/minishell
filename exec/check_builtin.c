/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffiliz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 10:51:59 by ffiliz            #+#    #+#             */
/*   Updated: 2022/06/21 10:52:12 by ffiliz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_chech_builtin(char **cmd, char **env, t_data *data)
{
	manage_builtin_part_1(cmd, env, data);
	manage_builtin_part_2(cmd, env, data);
	return (0);
}

int	ft_chech_builtin_case(char **cmd, char **env, t_exec *var, t_data *data)
{
	if ((ft_strlen(cmd[0]) == 9)
		&& (ft_strncmp("/bin/echo", cmd[0], 9) == 0))
		ft_echo(ft_strlen2d(cmd), cmd + 1);
	else if ((ft_strlen(cmd[0]) == 11)
		&& (ft_strncmp("/usr/bin/cd", cmd[0], 11) == 0))
		ft_cd(cmd);
	else if ((ft_strlen(cmd[0]) == 8)
		&& (ft_strncmp("/bin/pwd", cmd[0], 8) == 0))
		ft_pwd();
	else if ((ft_strlen(cmd[0]) == 12)
		&& (ft_strncmp("/usr/bin/env", cmd[0], 12) == 0))
		ft_env(data->env_lst);
	return (0);
}
