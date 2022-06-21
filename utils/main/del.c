/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoudin <mgoudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 15:41:08 by mgoudin           #+#    #+#             */
/*   Updated: 2022/06/21 17:44:21 by mgoudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	del(void*el)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)el;
	free(cmd->content);
	free(el);
}

void	del_2(void*el)
{
	if (el)
		free(el);
}

void	del_3(void*el)
{
	(void)el;
	return ;
}
