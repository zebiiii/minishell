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

long long	ft_atoi_exit_case(char *str)
{
	unsigned int	i;
	int				sign;
	long long				res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] && ((str[i] == 32) || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		if (res > res * 10 + str[i] - '0')
			ft_exit_char();
		res = res * 10 + str[i++] - '0';
	}
	return (res * sign);
}


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
