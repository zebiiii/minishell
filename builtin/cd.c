/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffiliz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:03:10 by ffiliz            #+#    #+#             */
/*   Updated: 2022/06/20 15:03:58 by ffiliz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cd(char **argv)
{
	char	*s;

	s = getcwd(NULL, 0);
	printf("%s\n", s);
	if (!argv[0])
	{
		if (chdir(argv[0]) == -1)
		{
			ft_putstr_fd("no such file or directory", 2);
			exit(EXIT_FAILURE);
		}
	}
	s = getcwd(NULL, 0);
	printf("%s\n", s);
	return (0);
}
