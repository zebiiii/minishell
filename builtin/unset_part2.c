/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffiliz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 23:26:22 by ffiliz            #+#    #+#             */
/*   Updated: 2022/06/20 23:31:45 by ffiliz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exit_unset(char *str, char *argv)
{
	ft_putstr_fd("unset: ", 2);
	ft_putchar_fd('`', 2);
	ft_putstr_fd(argv, 2);
	ft_putchar_fd('\'', 2);
	ft_putstr_fd(str, 2);
	return (-1);
}

int	ft_check_option_unset(char *argv)
{
	if (argv[0] == '-' && argv[1])
	{
		ft_putstr_fd("Error\nExport must not contain any options.\n", 2);
		return (1);
	}
	return (0);
}

void	free_triple(t_data *data)
{
	free(data->current->content);
	free(data->tmp);
	free(data->current);
}

void	become(t_data *data)
{
	data->before = data->current;
	data->current = data->current->next;
	data->i++;
}

int	ft_del_equal(char *argv, t_data *data, t_list *lst)
{
	int		i;
	t_list	*current;
	t_list	*before;
	char	*tmp;

	i = 0;
	current = lst;
	before = current;
	if (lst)
	{
		while (current)
		{
			if (ft_strncmp(current->content, argv, ft_len_equal(argv)) == 0)
			{
				tmp = ft_substr(current->content, 0,
						ft_len_equal(current->content));
				if (ft_strcmp(argv, tmp) == 0)
				{
					if (i == 0)
						before = current->next;
					else
						before->next = current->next;
					free(current->content);
					free(current);
					free(tmp);
					return (1);
				}
				free(tmp);
			}
			before = current;
			current = current->next;
			i++;
		}
	}
	return (0);
}
