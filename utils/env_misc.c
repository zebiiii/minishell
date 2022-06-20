/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_misc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoudin <mgoudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 19:35:20 by mgoudin           #+#    #+#             */
/*   Updated: 2022/06/20 19:38:05 by mgoudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_and_status(char *word, t_data data)
{
	char	*tmp;

	if (!ft_strncmp(word, "?", ft_strlen(word)))
		tmp = ft_itoa(g_global.exit_status);
	else
		tmp = ft_getenv(word, *(data.head_env));
	return (tmp);
}

void	ft_init_env2(t_env *data)
{
	data->i = 0;
	data->j = 0;
	data->k = 0;
}

void	increment(t_env *data)
{
	data->k++;
	data->i++;
}

void	increment_var(t_env *data, int len)
{
	data->k += data->j;
	data->i += len;
}
