/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoudin <mgoudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 13:56:25 by mgoudin           #+#    #+#             */
/*   Updated: 2022/06/17 20:43:41 by mgoudin          ###   ########.fr       */
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
	while(s1[++i])
		pt[i] = s1[i];
	while(s2[++j])
	{
		if (s2[j] == '=' && indic == 0)
		{
			pt[i++ + j] = '=';
			pt[i + j] = '"';
			indic++;
			continue;
		}
		pt[i + j] = s2[j];
	}
	if(!(s2[j]))
		pt[i++ + j] = '"';
	pt[i + j] = '\0';
	return (pt);
}

char	*ft_strjoin_f(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	str = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, 1);
	if (!str)
		return (0);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = 0;
	return (str);
}



char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	str = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, 1);
	if (!str)
		return (0);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	free(s1);
	j = 0;
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = 0;
	return (str);
}
