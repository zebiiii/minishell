/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainutils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoudin <mgoudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 15:45:17 by mgoudin           #+#    #+#             */
/*   Updated: 2022/06/21 16:01:33 by mgoudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
