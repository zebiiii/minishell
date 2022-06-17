/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnljoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoudin <mgoudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 16:04:41 by mgoudin           #+#    #+#             */
/*   Updated: 2022/06/17 21:30:48 by mgoudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_gnljoin(char *s1, char *s2)
{
	char	*pt;
	size_t	i;
	size_t	j;

	if (!s1)
		s1 = ft_calloc(1, 1);
	i = 0;
	j = 0;
	pt = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof (char *));
	if (pt == NULL)
		return (NULL);
	while (s1[i])
	{
		pt[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		pt[i + j] = s2[j];
		j++;
	}
	pt[i + j] = '\0';
	free(s1); //PROBLEMATIC
	return (pt);
}

