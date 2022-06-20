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

char	*ft_strjoin_quote(char *s1, char *s2)
{
	char	*pt;
	size_t	i;
	size_t	j;
	int		indic;

	if (!s1 || !s2)
		return (NULL);
	indic = 0;
	i = -1;
	j = -1;
	pt = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 3, sizeof (char *));
	if (pt == NULL)
		return (NULL);
	while (s1[++i])
		pt[i] = s1[i];
	while (s2[++j])
	{
		if (s2[j] == '=' && indic == 0)
		{
			pt[i++ + j] = '=';
			pt[i + j] = '"';
			indic++;
			continue ;
		}
		pt[i + j] = s2[j];
	}
	if (!(s2[j]))
		pt[i++ + j] = '"';
	pt[i + j] = '\0';
	return (pt);
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
