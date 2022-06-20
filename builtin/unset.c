#include "../minishell.h"



int ft_check_option_unset(char *argv)
{
    if (argv[0] == '-' && argv[1])
    {
        ft_putstr_fd("Error\nExport must not contain any options.\n", 2);
        return (1);
    }
    return (0);
}

int    ft_del_env(char *argv, t_data *data, t_list *lst)
{
    int i;
    t_list *current;
    t_list *before;
    char    *tmp;

    i = 0;
    current = lst;
    before = current;
    if (lst)
    {
	    while (current)
	    {
            
            if (ft_strncmp(current->content, argv, ft_len_equal(argv)) == 0)
            {
                tmp = ft_substr(current->content, 0, ft_len_equal(current->content));
                if (ft_strcmp(argv, tmp) == 0)
                {
                    if (i == 0)
                        before = current->next;
                    else
                        before->next = current->next;
                    free(current);
                    free(tmp);
                    return(1);
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

int    ft_del_equal(char *argv, t_data *data, t_list *lst)
{
    int i;
    t_list *current;
    t_list *before;
    char    *tmp;

    i = 0;
    current = lst;
    before = current;
    if (lst)
    {
	    while (current)
	    {
            
            if (ft_strncmp(current->content, argv, ft_len_equal(argv)) == 0)
            {
                tmp = ft_substr(current->content, 0, ft_len_equal(current->content));
                if (ft_strcmp(argv, tmp) == 0)
                {
                    if (i == 0)
                        before = current->next;
                    else
                        before->next = current->next;
                    free(current->content);
                    free(current);
                    free(tmp);
                    return(1);
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

int ft_check_eq(char *argv, t_data *data)
{
    int i;
    int indic;
    char *tmp;

    tmp = NULL;
    indic = 0;
    i = -1;
    while (argv[++i])
    {
        if ((!(argv[i] >= 65 && argv[i] <= 90)) 
            && (!(argv[i] >= 97 && argv[i] <= 122)))
        {
            if ((argv[i] >= 48 && argv[i] <= 57) || (argv[i] == '_'))
                continue;
            else
                return(ft_exit_export(": not a valid identifier\n", argv));
        }
    }
    tmp = ft_strjoin_f("declare -x ", argv);
    if (ft_del_equal(tmp, data, data->export_lst) == 1)
    {
        free(tmp);
        tmp = ft_strdup(argv);
        ft_del_env(tmp, data, data->env_lst);
        free(tmp);
        return(1);
    }
    return (0);
}

int    ft_check_unset(char *argv, t_data *data)
{
    int i;

    i = ft_check_first_char(argv);
    if (i == 1)
        i = ft_check_eq(argv, data);
    return (i);
}

int ft_unset(char **argv, t_data *data)
{
    int i;
    int e;
    int esc;

    i = 0;
    e = ft_check_option_unset(argv[0]);
    if (e == 1)
        return (e);
    if (e == 0)
    {
        while (argv[i])
        {
            e = ft_check_unset(argv[i], data);
            if (e == -1)
                esc = e;
            i++;
        }
    }
    if (esc == -1)
        return (1);
    return (0);
}