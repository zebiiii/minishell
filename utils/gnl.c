/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoudin <mgoudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:29:36 by mgoudin           #+#    #+#             */
/*   Updated: 2022/06/16 19:01:31 by mgoudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	lenbeforen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	return (i);
}

void	ft_stockcpy(char *dst, const char *src)
{
	size_t	i;

	i = 0;
	while ((char)src[i])
	{
		dst[i] = (char)src[i];
		i++;
	}
	dst[i] = '\0';
}

char	*extraction(char *stock)
{
	int		k;
	int		j;
	char	*res;

	if (stock[0] == '\0')
		return (NULL);
	k = lenbeforen(stock);
	res = calloc(k + 1, sizeof(char *));
	j = 0;
	while (j < k)
	{
		res[j] = stock[j];
		j++;
	}
	res[j] = '\0';
	ft_stockcpy(stock, &stock[k]);
	return (res);
}

int	occurence_is_n(const char *s1, char c)
{
	unsigned int	i;

	i = 0;
	if (!s1)
		return (0);
	while (s1[i])
	{
		if (s1[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*get_next_line(int fd)
{
	int			r;
	char		buf[2];
	static char	*stock;
	char		*line;

	if (fd < 0 || fd > 256)
		return (NULL);
	r = 1;
	while (r > 0 && !(occurence_is_n(stock, '\n')))
	{
		r = read(fd, buf, 1);
		if ((r == -1) || (r == 0 && stock && stock[0] == '\0'))
		{
			//free(stock);
			return (NULL);
		}
		buf[r] = '\0';
		stock = ft_gnljoin(stock, buf);
	}
	line = extraction(stock);
	return (line);
}
