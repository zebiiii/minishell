/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kangourou.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoudin <mgoudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 13:36:25 by mgoudin           #+#    #+#             */
/*   Updated: 2022/06/07 16:49:27 by mgoudin          ###   ########.fr       */
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

void    ft_quit_with_msg(char *str, int i, t_exec *var)
{
	if (i == CMDENV)
		i = 0;
	if (i == EXE)
		i = 0;
	ft_putstr_fd(str, 2);
	exit(EXIT_FAILURE);
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
	if (dup2(tab->in, STDIN_FILENO) == -1)
		ft_quit_with_msg("", 0, var);
	if (dup2(tab->out, STDOUT_FILENO) == -1)
		ft_quit_with_msg("", 0, var);
}

int    grep_path(char **env, t_exec *var)
{
    while (env[var->index_env])
    {
        if (ft_strncmp("PATH", env[var->index_env], 4) == 0)
            return (0);
        else
            var->index_env++;
    }
	ft_putstr_fd(env[var->index_env], 2);
    return (-1);
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

void    exec(char **cmd, char **env, t_exec *var, t_redirect *tab)
{
	var->path = NULL;
    var->index_env = 0;
    if (grep_path(env, var) == -1)
        ft_quit_with_msg("Error\nPATH\n", EXE, var);
    var->env_path = ft_split(env[var->index_env], ':');
	if (ft_check_path(cmd, var->env_path, var) == 0)
	{
		var->slash_join = ft_charjoin_lst(var->env_path[var->index_path],
				'/');
		var->path = ft_gnljoin(var->slash_join, cmd[0]);
		ft_freesplit(var->env_path);
		if (execve(var->path, cmd, env) == -1)
            ft_quit_with_msg("Error\nNo prog to execute\n", EXE, var);
	}
	else
		ft_quit_with_msg("Error\nCommand not found\n", CMDENV, var);
}

void    exec_case(char **cmd, char **env, t_exec *var)
{
		if (execve(cmd[0], cmd, env) == -1)
            ft_quit_with_msg("Error\nNo prog to execute\n", EXE, var);
		else
			ft_quit_with_msg("Error\nCommand not found\n", CMDENV, var);
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

int kangourou(char **cmd, char **env, t_redirect *tab)
{
    int pid;
    int cas;
	t_exec var;

	cas = 0;
    if (ft_check_cmd(cmd, env, &var) == 1)
		cas++;
    pid = fork();
    if (pid == -1)
		ft_quit_with_msg("Error\nFork\n", CMDENV, &var);
    if (pid == 0)
    {
        ft_dup(tab, &var);
        if (cas == 1)
			exec_case(cmd, env, &var);
		else
			exec(cmd, env, &var, tab);
    }
    else
    {
		g_global.qlf = 1;
		ft_close(tab);
	}
	return (pid);
}