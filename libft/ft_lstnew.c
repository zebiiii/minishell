/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoudin <mgoudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 16:21:13 by mgoudin           #+#    #+#             */
/*   Updated: 2022/06/19 17:52:30 by mgoudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../minishell.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*lst;

	lst = ft_calloc(1, sizeof(t_list *));
	if (!lst)
		return (0);
	lst->content = content;
	lst->next = 0;
	return (lst);
}
