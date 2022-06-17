/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_symbols.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoudin <mgoudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 13:07:25 by mgoudin           #+#    #+#             */
/*   Updated: 2022/06/17 19:22:21 by mgoudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	free_symbol(int fd, void *el)
{
	int	tmp;

	tmp = fd;
	free(el);
	return (tmp);
}
