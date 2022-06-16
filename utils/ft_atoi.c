/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoudin <mgoudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 18:55:37 by mgoudin           #+#    #+#             */
/*   Updated: 2022/06/16 18:58:36 by mgoudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_atoi(char *str)
{
	int	i;
	int	nb;

	nb = 0;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] >= 48 && str[i] <= 57)
		{
			nb *= 10;
			nb += (str[i] - 48);
		}
		else
			print_error("");
		i++;
	}
	if (i < 2 && str[0] == '-')
		print_error("");
	if (str[0] == '-')
		return (-nb);
	else
		return (nb);
}

int	ft_atoi_secure(char *str)
{
	int	i;
	int	neg;
	int	nb;

	neg = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg++;
		i++;
	}
	nb = ft_atoi(str);
	if ((nb > 0 || ft_strlen(str) > 11) && neg % 2)
		print_error("");
	if ((nb < 0 || ft_strlen(str) > 10) && !(neg % 2))
		print_error("");
	return (nb);
}
