/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffiliz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:04:47 by ffiliz            #+#    #+#             */
/*   Updated: 2022/06/20 16:10:04 by ffiliz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exit_export(char *str, char *argv)
{
	ft_putstr_fd("export: ", 2);
	ft_putchar_fd('`', 2);
	ft_putstr_fd(argv, 2);
	ft_putchar_fd('\'', 2);
	ft_putstr_fd(str, 2);
	return (-1);
}

int	ft_check_first_char(char *argv)
{
	int	i;

	i = 0;
	if ((!(argv[0] >= 65 && argv[0] <= 90))
		&& (!(argv[0] >= 97 && argv[0] <= 122)))
	{
		if (argv[0] == '_')
			i++;
		if (i == 0)
			i = ft_exit_export(": not a valid identifier\n", argv);
	}
	if (i == 0)
		i++;
	return (i);
}

int	ft_check_equal(char *tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		if (tmp[i] == '=')
			return (1);
		i++;
	}
	return (0);
}
