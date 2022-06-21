/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoudin <mgoudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 18:38:30 by mgoudin           #+#    #+#             */
/*   Updated: 2022/06/16 18:58:19 by mgoudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_error(char *str)
{
	ft_putstr_fd(str, 2);
	strerror(0);
	return (0);
}

int	ft_error_cd(char **argv)
{
	ft_exit_cd(" No such file or directory\n", argv[0]);
	return (1);
}
