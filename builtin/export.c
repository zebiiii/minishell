#include "../minishell.h"

int    ft_exit_export(char *str, char *argv)
{
    ft_putstr_fd("export: ", 2);
    ft_putchar_fd('`', 2);
    ft_putstr_fd(argv, 2);
    ft_putchar_fd('\'', 2);
    ft_putstr_fd(str, 2);
    return (-1);
}

int ft_check_first_char(char *argv)
{
    int i;

    i = 0;
    if ((!(argv[0] >= 65 && argv[0] <= 90)) 
            && (!(argv[0] >= 97 && argv[0] <= 122)))
    {
        if (argv[0] == '_')
            i++;
        if (i == 0)
            i = ft_exit_export(": not a valid identifier\n", argv);
    }
    if (i == 0)
        i++;
    return (i);
}

int ft_check_equal(char *tmp)
{
    int i;

    i = 0;
    while (tmp[i])
    {
        if (tmp[i] == '=')
            return (1);
        i++;
    }
    return (0);
}

int ft_check_content(char *tmp, t_list *lst, t_data *data)
{
    t_list *first;
    int len;
    int len2;

    len = ft_strlen(tmp);
    first = lst;
    if (lst)
    {
	    while (first)
	    {
            if (ft_strncmp(first->content, tmp, len) == 0)
            {
                len2 = ft_strlen(first->content);
                if (((char *)first->content)[len] == '=')
                    return (1);
                if (len2 == len)
                    return(1);
            }
            first = first->next;
    	}
    }
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;
	unsigned char	cmp_1;
	unsigned char	cmp_2;

	i = 0;
	cmp_1 = (unsigned char)s1[i];
	cmp_2 = (unsigned char)s2[i];
	while ((cmp_1 && cmp_2))
	{
		cmp_1 = (unsigned char)s1[i];
		cmp_2 = (unsigned char)s2[i];
		if (cmp_1 != cmp_2)
			return (cmp_1 - cmp_2);
		i++;
	}
	return (cmp_1 - cmp_2);
}


int    ft_add_to_export(char *argv, t_list *lst, t_data *data)
{
    char *tmp;

    tmp = ft_strjoin_f("declare -x ", argv);
    if (!tmp)
        return (-1);
    if (ft_check_content(tmp, lst, data) != 1)
        ft_lstadd_back(data->head_export, ft_lstnew((char *)tmp));
    else
    {
        if (tmp)
            free(tmp);
    }
    ft_lstsize(lst);
    return (0);
}

char	*ft_strdup(char *s1)
{
	size_t	i;
	char	*pt;

	i = 0;
	pt = malloc(sizeof (char) * ft_strlen(s1) + 1);
	if (!pt)
		return (NULL);
	while (s1[i])
	{
		pt[i] = s1[i];
		i++;
	}
	pt[i] = '\0';
	return (pt);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	i = 0;
	if (!s || len <= 0 || start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s))
		return (ft_strdup((char *)s + start));
	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = s[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}

int ft_len_equal(char *s)
{
    int i;

    i = 0;
    while(s[i] && s[i] != '=')
        i++;
    return (i);
}

int ft_fusion_equal(char *tmp, t_list *lst, char *str)
{
    t_list *first;
    char *tmp2;

    first = lst;
    if (lst)
    {
	    while (first)
	    {
            if (ft_strncmp(first->content, tmp, ft_len_equal(tmp)) == 0)
            {
                tmp2 = ft_substr(first->content, 0, ft_len_equal(first->content));
                if (ft_strcmp(tmp, tmp2) == 0)
                {
                    if (first->content)
                        free(first->content);
                    first->content = str;
                    free(tmp2);
                    return(1);
                }
            }
            first = first->next;
    	}
    }
	return (0);
}

int ft_fusion(char *argv, t_list *lst, t_data *data)
{
    char *tmp;
    char *tmp2;
    char *argv_copie;

    tmp = ft_strjoin_quote("declare -x ", argv);
    if (!tmp)
        return(-1);
    tmp2 = ft_substr(tmp, 0, ft_len_equal(tmp));
    if (ft_fusion_equal(tmp2, lst, tmp) != 1)
    {
        argv_copie = ft_strdup(argv);
        if (tmp2)
            free(tmp2);
        ft_lstadd_back(data->head_export, ft_lstnew((char *)tmp));
        if (data->head_env)
            ft_lstadd_back(data->head_env, ft_lstnew(argv_copie));
    }
    else
    {
        if (tmp2)
            free(tmp2);
        tmp2 = ft_substr(argv, 0, ft_len_equal(argv));
        argv_copie = ft_strdup(argv);
        if (ft_fusion_equal(tmp2, data->env_lst, argv_copie) == 0)
            ft_lstadd_back(data->head_env, ft_lstnew(argv_copie));
        if (tmp2)
            free(tmp2);
    }
    ft_lstsize(lst);
    ft_lstsize(data->env_lst);
    return(0);
}

int ft_check_str(char *argv, t_list *lst, t_data *data)
{
    int i;
    int indic;

    indic = 0;
    i = -1;
    while (argv[++i])
    {
        if ((!(argv[i] >= 65 && argv[i] <= 90)) 
            && (!(argv[i] >= 97 && argv[i] <= 122)))
        {
            if ((argv[i] >= 48 && argv[i] <= 57) || (argv[i] == '_'))
                continue;
            else if (argv[i] == '=' && indic == 0)
            {
                if (ft_fusion(argv, lst, data) == 0)
                    return(1);
            }
            else
                return(ft_exit_export(": not a valid identifier\n", argv));
        }
    }
    if (ft_check_equal(argv) == 0)
        return(ft_add_to_export(argv, lst, data));
    return (0);
}

int ft_check_argument(char *argv, t_list *lst, t_data *data)
{
    int i;

    i = 0;
    i = ft_check_first_char(argv);
    if (i == 1)
        i = ft_check_str(argv, lst, data);
    return (i);
}

int ft_print_export(t_list *lst)
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

int export_first_step(char *argv, t_list *lst)
{
    int i;

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

int    ft_export(char **argv, t_list *lst, t_data *data)
{
    int i;
    int e;
    int esc;

    i = 0;
    e = 0;
    esc = 0;
    e = export_first_step(argv[0], lst);
    if (e == 2 || e == 1)
        return (e);
    if (e == 0)
    {
        while (argv[i])
        {
            e = ft_check_argument(argv[i], lst, data);
            if (e == -1)
                esc = e;
            i++;
        }
    }
    if (esc == -1)
        return (1);
    return (0);
}