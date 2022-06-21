/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoudin <mgoudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 10:59:20 by ffiliz            #+#    #+#             */
/*   Updated: 2022/06/21 16:42:58 by mgoudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parce_builtin(char **cmd)
{
	if ((ft_strlen(cmd[0]) == 4)
		&& (ft_strncmp("echo", cmd[0], 4) == 0))
		return (1);
	else if ((ft_strlen(cmd[0]) == 2)
		&& (ft_strncmp("cd", cmd[0], 2) == 0))
		return (1);
	else if ((ft_strlen(cmd[0]) == 3)
		&& (ft_strncmp("pwd", cmd[0], 3) == 0))
		return (1);
	else if ((ft_strlen(cmd[0]) == 5)
		&& (ft_strncmp("unset", cmd[0], 5) == 0))
		return (1);
	else if ((ft_strlen(cmd[0]) == 6)
		&& (ft_strncmp("export", cmd[0], 6) == 0))
		return (1);
	else if ((ft_strlen(cmd[0]) == 4)
		&& (ft_strncmp("exit", cmd[0], 4) == 0))
		return (1);
	else
		return (0);
}

int	parce_builtin_2(char **cmd)
{
	if ((ft_strlen(cmd[0]) == 9)
		&& (ft_strncmp("/bin/echo", cmd[0], 9) == 0))
		return (1);
	else if ((ft_strlen(cmd[0]) == 11)
		&& (ft_strncmp("/usr/bin/cd", cmd[0], 11) == 0))
		return (1);
	else if ((ft_strlen(cmd[0]) == 8)
		&& (ft_strncmp("/bin/pwd", cmd[0], 8) == 0))
		return (1);
	else
		return (0);
}
