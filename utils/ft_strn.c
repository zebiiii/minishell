/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoudin <mgoudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:41:20 by mgoudin           #+#    #+#             */
/*   Updated: 2022/06/17 15:03:51 by mgoudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strn(char const *str, int lenght)
{
	char	*value;
	int		i;

	value = ft_calloc(lenght + 1, 1);
	if (!value)
		return (0);
	i = 0;
	while (i <= lenght)
	{
		value[i] = str[i];
		i++;
	}
	value[i] = '\0';
	return (value);
}
