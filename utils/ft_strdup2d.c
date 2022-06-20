/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup2d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffiliz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 00:20:06 by ffiliz            #+#    #+#             */
/*   Updated: 2022/06/21 00:20:42 by ffiliz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_strdup2d(char **s1)
{
	int		i;
	char	**s2;

	i = -1;
	s2 = NULL;
	s2 = malloc(sizeof(char *) * ft_strlen2d(s1) + 1);
	if (!s2)
		return (NULL);
	while (s1[++i])
		s2[i] = ft_strdup(s1[i]);
	s2[i] = NULL;
	return (s2);
}
