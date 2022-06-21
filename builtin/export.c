/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoudin <mgoudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:04:47 by ffiliz            #+#    #+#             */
/*   Updated: 2022/06/21 15:57:42 by mgoudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_str(char *argv, t_list *lst, t_data *data)
{
	int	i;
	int	indic;

	indic = 0;
	i = -1;
	while (argv[++i])
	{
		if ((!(argv[i] >= 65 && argv[i] <= 90))
			&& (!(argv[i] >= 97 && argv[i] <= 122)))
		{
			if ((argv[i] >= 48 && argv[i] <= 57) || (argv[i] == '_'))
				continue ;
			else if (argv[i] == '=' && indic == 0)
			{
				if (ft_fusion(argv, lst, data) == 0)
					return (1);
			}
			else
				return (ft_exit_export(": not a valid identifier\n", argv));
		}
	}
	if (ft_check_equal(argv) == 0)
		return (ft_add_to_export(argv, lst, data));
	return (0);
}

int	ft_check_argument(char *argv, t_list *lst, t_data *data)
{
	int	i;

	i = 0;
	i = ft_check_first_char(argv);
	if (i == 1)
		i = ft_check_str(argv, lst, data);
	return (i);
}

int	ft_print_export(t_list *lst)
{
	t_list	*list;
	int		i;

	i = 0;
	list = lst;
	if (list)
	{
		while (list)
		{
			printf("%s\n", (char *)list->content);
			list = list->next;
			i++;
		}
	}
	return (1);
}

int	export_first_step(char *argv, t_list *lst)
{
	int	i;

	i = 0;
	if (!argv)
	{
		ft_print_export(lst);
		return (1);
	}
	else if (argv[0] == '-' && argv[1])
	{
		ft_putstr_fd("Error\nExport must not contain any options.\n", 2);
		return (2);
	}
	return (0);
}

int	ft_export(char **argv, t_list *lst, t_data *data)
{
	int	i;
	int	e;
	int	esc;

	i = -1;
	esc = 0;
	e = export_first_step(argv[0], lst);
	if (e == 2 || e == 1)
	{
		if (e == 1)
			e = 0;
		return (e);
	}
	if (e == 0)
	{
		while (argv[++i])
		{
			e = ft_check_argument(argv[i], lst, data);
			if (e == -1)
				esc = e;
		}
	}
	if (esc == -1)
		return (1);
	return (0);
}
