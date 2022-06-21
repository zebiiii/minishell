/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoudin <mgoudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 10:51:59 by ffiliz            #+#    #+#             */
/*   Updated: 2022/06/21 16:41:29 by mgoudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_chech_builtin(char **cmd, t_data *data)
{
	manage_builtin_part_1(cmd, data);
	manage_builtin_part_2(cmd, data);
	return (0);
}

int	ft_chech_builtin_case(char **cmd, t_data *data)
{
	if ((ft_strlen(cmd[0]) == 9)
		&& (ft_strncmp("/bin/echo", cmd[0], 9) == 0))
		ft_echo(ft_strlen2d(cmd), cmd + 1);
	else if ((ft_strlen(cmd[0]) == 11)
		&& (ft_strncmp("/usr/bin/cd", cmd[0], 11) == 0))
		ft_cd(cmd, data);
	else if ((ft_strlen(cmd[0]) == 8)
		&& (ft_strncmp("/bin/pwd", cmd[0], 8) == 0))
		ft_pwd();
	else if ((ft_strlen(cmd[0]) == 12)
		&& (ft_strncmp("/usr/bin/env", cmd[0], 12) == 0))
		ft_env(data->env_lst);
	return (0);
}
