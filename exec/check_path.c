/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoudin <mgoudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 10:52:17 by ffiliz            #+#    #+#             */
/*   Updated: 2022/06/21 16:35:39 by mgoudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	grep_path(char **env, t_exec *var)
{
	var->index_env = 0;
	if (env)
	{
		while (env[var->index_env])
		{
			if (ft_strncmp("PATH", env[var->index_env], 4) == 0)
				return (0);
			else
				var->index_env++;
		}
		return (-1);
	}
	return (-1);
}

int	ft_check_path(char **cmd, char **env, t_exec *var)
{
	int	access_return;

	access_return = 1;
	var->index_path = 0;
	while (env[var->index_path] && access_return != 0)
	{
		var->slash_join = ft_charjoin_lst(env[var->index_path], '/');
		var->path = ft_gnljoin(var->slash_join, *cmd);
		access_return = access(var->path, F_OK | X_OK);
		free(var->path);
		if (access_return != 0)
			var->index_path++;
	}
	return (access_return);
}

int	ft_check_cmd(char **cmd)
{
	if (cmd[0][0] == '/')
	{
		if (access(cmd[0], X_OK) == 0)
			return (1);
	}
	return (0);
}
