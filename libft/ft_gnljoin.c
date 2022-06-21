/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnljoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoudin <mgoudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 16:04:41 by mgoudin           #+#    #+#             */
/*   Updated: 2022/06/20 19:27:42 by mgoudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_charjoin_lst(char *s1, char c)
{
	size_t	i;
	char	*pt;

	if (!s1)
		return (NULL);
	i = 0;
	pt = malloc(sizeof(char) * ft_strlen(s1) + 1 + 1);
	if (pt == NULL)
		return (NULL);
	while (s1[i])
	{
		pt[i] = s1[i];
		i++;
	}
	pt[i++] = c;
	pt[i] = '\0';
	return (pt);
}

void	init_var_join(t_join *join)
{
	join->indic = 0;
	join->i = -1;
	join->j = -1;
}

char	*ft_strjoin_quote(char *s1, char *s2)
{
	t_join	join;

	if (!s1 || !s2)
		return (NULL);
	init_var_join(&join);
	join.pt = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 3, sizeof (char *));
	if (join.pt == NULL)
		return (NULL);
	while (s1[++(join.i)])
		join.pt[join.i] = s1[join.i];
	while (s2[++(join.j)])
	{
		if (s2[join.j] == '=' && join.indic == 0)
		{
			join.pt[join.i++ + join.j] = '=';
			join.pt[join.i + join.j] = '"';
			join.indic++;
			continue ;
		}
		join.pt[join.i + join.j] = s2[join.j];
	}
	if (!(s2[join.j]))
		join.pt[join.i++ + join.j] = '"';
	join.pt[join.i + join.j] = '\0';
	return (join.pt);
}

char	*ft_gnljoin_2(char *s1, char *s2)
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
	if (s2)
		free(s2);
	return (pt);
}

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
	free(s1);
	return (pt);
}
