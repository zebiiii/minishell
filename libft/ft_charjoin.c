/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoudin <mgoudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 11:56:12 by mgoudin           #+#    #+#             */
/*   Updated: 2022/06/02 13:56:19 by mgoudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdlib.h>

char	*ft_charjoin(char *s1, char const c)
{
	char	*str;
	int		i;
	int		j;

	str = malloc(ft_strlen(s1) + 2);
	if (!str)
		return (0);
	i = 0;
	j = 0;
	str[i++] = c;
	while (s1[j])
	{
		str[i] = s1[j];
		j++;
		i++;
	}
	str[i] = 0;
	if (j)
		free(s1);
	return (str);
}
