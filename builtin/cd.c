/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffiliz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:03:10 by ffiliz            #+#    #+#             */
/*   Updated: 2022/06/20 15:03:58 by ffiliz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	bt_cd(char **cmd, int e, t_data *data)
{
	char	**pwd;
	char	**old;

	e = ft_cd(cmd + 1, data);
	if (e == 0)
	{
		pwd = ft_calloc(1, 1);
		old = ft_calloc(1, 1);
		pwd[0] = ft_strjoin_f("PWD=", getcwd(NULL, 0));
		old[0] = ft_strjoin_f("OLD", ft_get_pwd(data));
		pwd[1] = NULL;
		old[1] = NULL;
		ft_export(pwd, data->export_lst, data);
		ft_export(old, data->export_lst, data);
		ft_freesplit(pwd);
		ft_freesplit(old);
	}
	g_global.exit_status = e;
	g_global.indicateur++;
}

int	ft_exit_cd(char *str, char *argv)
{
	ft_putstr_fd("cd: ", 2);
	if (argv)
	{
		if (argv[0])
		{
			ft_putstr_fd(argv, 2);
			ft_putchar_fd(':', 2);
		}
	}
	ft_putstr_fd(str, 2);
	return (-1);
}

char	*ft_get_home(t_data *data)
{
	t_list	*first;

	first = data->env_lst;
	if (first)
	{
		while (first)
		{
			if (strncmp("HOME=", first->content, 5) == 0)
				return (&(first->content)[5]);
			first = first->next;
		}
		ft_exit_cd("HOME not set\n", "");
		return (NULL);
	}
	ft_exit_cd("HOME not set\n", "");
	return (NULL);
}

char	*ft_get_pwd(t_data *data)
{
	t_list	*first;

	first = data->env_lst;
	if (first)
	{
		while (first)
		{
			if (strncmp("PWD=", first->content, 4) == 0)
				return (first->content);
			first = first->next;
		}
	}
	return (NULL);
}

int	ft_cd(char **argv, t_data *data)
{
	char	*s;
	int		i;

	i = 0;
	s = getcwd(NULL, 0);
	if (!argv[0])
	{
		s = ft_get_home(data);
		if (!s)
			return (1);
		else
		{
			if (chdir(s) == -1)
				return (ft_error_cd(argv));
		}
	}
	else
	{
		if (chdir(argv[0]) == -1)
			return (ft_error_cd(argv));
	}
	return (0);
}
