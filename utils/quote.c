/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoudin <mgoudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:18:29 by mgoudin           #+#    #+#             */
/*   Updated: 2022/06/14 19:05:48 by mgoudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//return index of the closed quote. 0 if not.
//first char of str have to be the first quote.

int	is_quote_close(const char *str, char quote)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] == quote)
			return (i);
		i++;
	}
	return (0);
}
