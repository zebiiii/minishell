/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kangourou.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoudin <mgoudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 13:36:25 by mgoudin           #+#    #+#             */
/*   Updated: 2022/06/14 18:15:13 by mgoudin          ###   ########.fr       */
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

void    ft_freesplit(char **str)
{
        int     i;

        i = 0;
        if (!str)
                return ;
        while (str[i])
        {
			if (str[i])
                free(str[i]);
            i++;
        }
		if (str)
        	free(str);
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*dst;

	i = 0;
	dst = (unsigned char *) b;
	while (i < len)
	{
		dst[i] = (unsigned char) c;
		i++;
	}
	return (dst);
}

void    ft_quit_with_msg(char *s1, char *s2, int exit_status, t_exec *var)
{
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(s2, 2);
	exit(exit_status);
}

void    ft_msg(char *s1, char *s2, int exit_status, t_exec *var)
{
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(s2, 2);
	g_global.exit_status = 127;
}

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

void	ft_dup(t_redirect *tab, t_exec *var)
{
	if (tab->lst_pfd_in != 0 && tab->lst_pfd_out != 0)
		close(tab->lst_pfd_out);
	if (tab->in == -1)
		ft_quit_with_msg(NULL, "Error fd", 2, var);
	if (dup2(tab->in, STDIN_FILENO) == -1)
		ft_quit_with_msg(NULL, "", 2, var);
	if (dup2(tab->out, STDOUT_FILENO) == -1)
		ft_quit_with_msg(NULL, "", 2, var);
}

int    grep_path(char **env, t_exec *var)
{
	var->index_env = 0;
	if (env)
	{
		while (env[var->index_env])
		{
			if (ft_strncmp("PATH", env[var->index_env], 4) == 0)
				return (0);
			else
				var->index_env++;
		}
		return (-1);
	}
	return(-1);
}

int ft_check_path(char **cmd, char **env, t_exec *var)
{
    int access_return;

    access_return = 1;
    var->index_path = 0;
    while (env[var->index_path] && access_return != 0)
    {
        var->slash_join = ft_charjoin_lst(env[var->index_path], '/');
		var->path = ft_gnljoin(var->slash_join, *cmd);
		access_return = access(var->path, F_OK | X_OK);
		free(var->path);
		if (access_return != 0)
			var->index_path++;
	}
	return (access_return);
}

void	ft_putstr_2(char **arg, char *msg)
{
	int i = 0;
	while (arg[i])
	{
		ft_putstr_fd(msg, 2);
		ft_putstr_fd(arg[i++], 2);
		ft_putstr_fd("\n", 2);
	}
}

int	parce_builtin(char **cmd, char **env, t_data *data)
{
	if ((ft_strlen(cmd[0]) == 4) && 
		(ft_strncmp("echo", cmd[0], 4) == 0))
		return (1);
	else if ((ft_strlen(cmd[0]) == 2) &&
		(ft_strncmp("cd", cmd[0], 2) == 0))
		return (1);
	else if ((ft_strlen(cmd[0]) == 3) &&
		(ft_strncmp("pwd", cmd[0], 3) == 0))
		return (1);
	else if ((ft_strlen(cmd[0]) == 5) &&
		(ft_strncmp("unset", cmd[0], 5) == 0))
		return (1);
	else if ((ft_strlen(cmd[0]) == 6) &&
		(ft_strncmp("export", cmd[0], 6) == 0))
		return (1);
	else if ((ft_strlen(cmd[0]) == 4) &&
		(ft_strncmp("exit", cmd[0], 4) == 0))
		return (1);
	else
		return (0);
}

int	parce_builtin_2(char **cmd, char **env, t_data *data)
{
	if ((ft_strlen(cmd[0]) == 9) &&
		(ft_strncmp("/bin/echo", cmd[0], 9) == 0))
		return (1);
	else if ((ft_strlen(cmd[0]) == 11) && 
		(ft_strncmp("/usr/bin/cd", cmd[0], 11) == 0))
		return (1);
	else if ((ft_strlen(cmd[0]) == 8) && 
		(ft_strncmp("/bin/pwd", cmd[0], 8) == 0))
		return (1);
	else
		return (0);
}

void	manage_builtin_part_1(char **cmd, char **env, t_data *data)
{
	int e;

	e = 0;
	if ((ft_strlen(cmd[0]) == 4) && 
		(ft_strncmp("echo", cmd[0], 4) == 0))
		ft_echo(ft_strlen2d(cmd), cmd + 1);
	else if ((ft_strlen(cmd[0]) == 2) &&
		(ft_strncmp("cd", cmd[0], 2) == 0))
		ft_cd(cmd);
	else if ((ft_strlen(cmd[0]) == 3) &&
		(ft_strncmp("pwd", cmd[0], 3) == 0))
		ft_pwd();
	else if ((ft_strlen(cmd[0]) == 3) &&
		(ft_strncmp("env", cmd[0], 3) == 0))
	{
		if (cmd[1])
		{
			ft_putstr_fd("Error\nNo arg or option for env.\n", 2);
			exit(127);
		}
		else
		{
			if (ft_env(data->env_lst) == 0)
				exit(EXIT_SUCCESS);
		}
	}
}

void	manage_builtin_part_2(char **cmd, char **env, t_data *data)
{
	int e;

	e = 0;
	if ((ft_strlen(cmd[0]) == 4) && (ft_strncmp("exit", cmd[0], 4) == 0))
		ft_exit_case(cmd + 1);
	else if ((ft_strlen(cmd[0]) == 6) && (ft_strncmp("export", cmd[0], 7) == 0))
	{
		e = ft_export(cmd + 1, data->export_lst, data);
		if (e == -1)
			exit(EXIT_FAILURE);
		else if (e == 2)
			exit(2);
		else
			exit(EXIT_SUCCESS);
	}
	else if ((ft_strlen(cmd[0]) == 5) && (ft_strncmp("unset", cmd[0], 5) == 0))
	{
		e = ft_unset(cmd + 1, data);
		if (e == 0)
			exit(EXIT_SUCCESS);
	}
}

int	ft_chech_builtin(char **cmd, char **env, t_data *data)
{
	manage_builtin_part_1(cmd, env, data);
	manage_builtin_part_2(cmd, env, data);
	return (0);
}

int	ft_chech_builtin_case(char **cmd, char **env, t_exec *var, t_data *data)
{
	if ((ft_strlen(cmd[0]) == 9) && (ft_strncmp("/bin/echo", cmd[0], 9) == 0))
		ft_echo(ft_strlen2d(cmd), cmd + 1);
	else if ((ft_strlen(cmd[0]) == 11) && (ft_strncmp("/usr/bin/cd", cmd[0], 11) == 0))
		ft_cd(cmd);
	else if ((ft_strlen(cmd[0]) == 8) && (ft_strncmp("/bin/pwd", cmd[0], 8) == 0))
		ft_pwd();
	else if ((ft_strlen(cmd[0]) == 12) && (ft_strncmp("/usr/bin/env", cmd[0], 12) == 0))
		ft_env(data->env_lst);
	return (0);
}

void    exec(char **cmd, char **env, t_exec *var, t_data *data)
{
	ft_chech_builtin(cmd, env, data);
	var->path = NULL;
	var->index_env = 0;
	if (grep_path(env, var) == -1)
		ft_quit_with_msg(NULL, "Error\nPATH\n", 1, var);
	var->env_path = ft_split(env[var->index_env], ':');
	if (ft_check_path(cmd, var->env_path, var) == 0)
	{
		var->slash_join = ft_charjoin_lst(var->env_path[var->index_path],
				'/');
		var->path = ft_gnljoin(var->slash_join, cmd[0]);
		ft_freesplit(var->env_path);
		if (execve(var->path, cmd, env) == -1)
			ft_quit_with_msg(NULL, "Error\nNo prog to execute\n", 126, var);
	}
	else
		ft_quit_with_msg(cmd[0], ": command not found\n", 127, var);
}

void    exec_case(char **cmd, char **env, t_exec *var, t_data *data)
{
	ft_chech_builtin_case(cmd, env, var, data);
	if (execve(cmd[0], cmd, env) == -1)
		ft_quit_with_msg(NULL, "Error\nNo prog to execute\n", 126, var);
	else
		ft_quit_with_msg(cmd[0], ": command not found\n", 127, var);
}

int ft_check_cmd(char **cmd, char **env, t_exec *var)
{
	if (cmd[0][0] == '/')
	{
		if (access(cmd[0], X_OK) == 0)
			return (1);
	}
	return (0);
}

void	ft_close(t_redirect *tab)
{
	if (tab->lst_pfd_in != 0)
		close(tab->lst_pfd_in);
	if (tab->st_pfd_in != 0)
		close(tab->st_pfd_in);
	if (tab->in)
		close(tab->in);
	if (tab->out != 1)
		close(tab->out);
}

int kangourou(char **cmd, char **env, t_redirect *tab, t_data *data)
{
    int pid;
    int cas;
	int indic;
	t_exec var;

	indic = 0;
	cas = 0;
    if (ft_check_cmd(cmd, env, &var) == 1)
		cas++;
	if (parce_builtin(cmd, env, data) == 1 
		|| parce_builtin_2(cmd, env, data) == 1)
		indic++;
	if (grep_path(env, &var) != -1 || indic != 0)
	{
		pid = fork();
		if (pid == -1)
			ft_quit_with_msg(NULL, "Error\nFork\n", 2, &var);
		if (pid == 0)
		{
			ft_dup(tab, &var);
			if (cas == 1)
				exec_case(cmd, env, &var, data);
			else
				exec(cmd, env, &var, data);
		}
		else
		{
			g_global.qlf = 1;
			ft_close(tab);
		}
	}
	else
		ft_msg(cmd[0], ": No such file or directory\n", 127, &var);
	return(pid);
}