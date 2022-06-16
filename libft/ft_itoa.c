/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoudin <mgoudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 19:20:07 by mgoudin           #+#    #+#             */
/*   Updated: 2022/06/16 16:01:06 by mgoudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_len(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_intmin_handler( void )
{
	char	*intmin;
	char	*result;
	int		i;

	result = malloc(11);
	if (!result)
		return (0);
	intmin = ft_itoa(-214748364);
	i = 0;
	while (i < 10)
	{
		result[i] = intmin[i];
		i++;
	}
	free(intmin);
	result[10] = 56;
	result[11] = 0;
	return (result);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;

	if (n == -2147483648)
		return (ft_intmin_handler());
	i = ft_len(n);
	str = malloc(i + 1);
	if (!str)
		return (0);
	str[i--] = '\0';
	if (n == 0)
		str[0] = 48;
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
	}
	while (n > 0)
	{
		str[i--] = n % 10 + 48;
		n /= 10;
	}
	return (str);
}
