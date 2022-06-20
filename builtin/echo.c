/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffiliz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:04:23 by ffiliz            #+#    #+#             */
/*   Updated: 2022/06/20 15:05:23 by ffiliz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_var_echo(t_echo *var)
{
	var->indic = 0;
	var->indic2 = 0;
	var->j = 0;
}

int	ft_check_option(char **argv, t_echo *var)
{
	int		i;

	i = -1;
	while (argv[++i])
	{
		init_var_echo(var);
		while (argv[i][var->j])
		{
			if (argv[i][var->j] == '-' && var->indic == 0)
			{
				var->j++;
				var->indic++;
			}
			if (argv[i][var->j] == 'n' && var->indic != 0)
				var->j++;
			else
			{
				var->indic2++;
				break ;
			}
		}
		if (var->indic2 == 1)
			break ;
	}
	return (i);
}

int	ft_echo(int argc, char **argv)
{
	int		i;
	t_echo	var;

	i = 0;
	var.len = argc - 1;
	var.with_option = 0;
	if (!argv[i])
	{
		write(1, "\n", 1);
		exit(EXIT_SUCCESS);
	}
	i = ft_check_option(argv, &var);
	if (i <= var.len && i != 0)
		var.with_option++;
	while (argv[i])
	{
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		if (!(argv[i + 1] == '\0'))
			write(1, " ", 1);
		i++;
	}
	if (var.with_option == 0)
		write(1, "\n", 1);
	exit(EXIT_SUCCESS);
}
