/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoudin <mgoudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 15:45:41 by mgoudin           #+#    #+#             */
/*   Updated: 2022/06/20 19:32:36 by mgoudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_var(char *str, int len)
{
	char	*res;
	int		i;

	res = ft_calloc(len + 1, sizeof(char));
	i = 0;
	while (i < len)
	{
		res[i] = str[i];
		i++;
	}
	res[i] = 0;
	return (res);
}

char	**explode(char *str)
{
	char	**res;
	int		i;

	res = ft_calloc(2, sizeof(char *));
	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			res[0] = get_var(str, i);
			res[1] = &str[++i];
		}
		i++;
	}
	return (res);
}

void	ft_freeline(char **line)
{
	free(line[0]);
	free(line);
}

char	*ft_getenv(char *str, t_list *env)
{
	char	**line;
	char	*tmp;

	while (env)
	{
		line = explode((char *)env->content);
		if (line[0])
		{
			if (ft_strncmp(line[0], str, ft_strlen(str)) == 0)
			{
				if (line[1])
				{
					free(line[0]);
					return (line[1]);
				}
			}
		}
		env = env->next;
	}
	ft_freeline(line);
	return (0);
}
