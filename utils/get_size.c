/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoudin <mgoudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:30:25 by mgoudin           #+#    #+#             */
/*   Updated: 2022/06/16 19:01:16 by mgoudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_size(t_list **head)
{
	t_list	*lst;
	int		type;
	int		i;

	lst = *head;
	i = 0;
	while (lst)
	{
		type = (int)((t_cmd *)lst->content)->type;
		if (type == pipe_)
			i++;
		lst = lst->next;
	}
	return (i + 1);
}
