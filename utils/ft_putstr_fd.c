/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoudin <mgoudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 18:36:12 by mgoudin           #+#    #+#             */
/*   Updated: 2022/06/16 18:59:06 by mgoudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_putstr_2(char **arg, char *msg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		ft_putstr_fd(msg, 2);
		ft_putstr_fd(arg[i++], 2);
		ft_putstr_fd("\n", 2);
	}
}

int	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (write(fd, &str[i], 1) == -1)
			exit(EXIT_FAILURE);
		i++;
	}
	return (0);
}
