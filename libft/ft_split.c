/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffiliz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 11:06:48 by ffiliz            #+#    #+#             */
/*   Updated: 2022/06/21 11:07:00 by ffiliz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_sep(char s, char c)
{
	if (s == c)
		return (1);
	else
		return (0);
}

static size_t	word(char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	w;

	w = 0;
	i = 0;
	j = 0;
	while (s[i] && s[j])
	{
		i = j;
		while (is_sep(s[i], c) && s[i])
			i++;
		j = i;
		while ((!(is_sep(s[j], c))) && s[j])
			j++;
		if (j > i)
			w++;
	}
	return (w);
}

static int	alloc_char(size_t len, size_t index, char **tab)
{
	tab[index] = malloc(sizeof(char) * len + 1);
	if (!tab[index])
		return (0);
	return (1);
}

static char	**walloc(char const *s, char c)
{
	char	**tab;
	size_t	i;
	size_t	j;
	size_t	w;

	w = 0;
	i = 0;
	j = 0;
	tab = malloc(sizeof(char *) * word(s, c) + 1);
	if (!tab)
		return (NULL);
	while (s[i] && s[j])
	{
		i = j;
		while (is_sep(s[i], c) && s[i])
			i++;
		j = i;
		while ((!(is_sep(s[j], c))) && s[j])
			j++;
		if (j > i)
			if (!(alloc_char(j - i, w, tab)))
				return (NULL);
		w++;
	}
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	size_t	w;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	w = 0;
	tab = walloc(s, c);
	if (!tab)
		return (NULL);
	while (j < word(s, c))
	{
		w = 0;
		while (is_sep(s[i], c) && s[i])
			i++;
		while ((!(is_sep(s[i], c))) && s[i])
			tab[j][w++] = s[i++];
		tab[j][w] = 0;
		j++;
	}
	tab[j] = 0;
	return (tab);
}
