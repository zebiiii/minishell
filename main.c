/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoudin <mgoudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 17:56:09 by mgoudin           #+#    #+#             */
/*   Updated: 2022/06/09 15:12:31 by mgoudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_lst(t_list *lst)
{
	while (lst)
	{
        printf("%s\n", (char *)((t_cmd *)lst->content)->content);
        printf("type: %d\n", (int)((t_cmd *)lst->content)->type);
		lst = lst->next;
	}
}

void    print_argv(char **argv)
{
    int i;

    i = 0;
    while(argv[i])
    {
        printf("%s ",argv[i]);
        i++;
    }
    printf("\n");
}

void del(void*el)
{
    t_cmd *cmd = (t_cmd *)el;
    free(cmd->content);
    free(el);
}

// void    sig_handler(int signum)
// {
//     if (signum == SIGINT)
//     {
//         printf("\n");
//         rl_on_new_line();
//         rl_replace_line("", 0);
//         rl_redisplay();
//     }
// }

void    sig_handler(int signo)
{
	if (signo == SIGINT)
    {
        printf("\n");
        if (g_global.qlf == 0)
        {
            rl_on_new_line();
            rl_replace_line("", 0);
            rl_redisplay();
        }
    }
}

int is_empty(t_list *lst)
{
    int type;

    while (lst)
	{
        type = (int)((t_cmd *)lst->content)->type;
        if (type != delete && type != pipe_)
            return (0);
		lst = lst->next;
	}
    return (1);
}

int main(int argc, char **argv, char **env)
{
    char    *res;
    t_list	*lst;
	t_list	**head;
    int     size;
    int     i;
    t_redirect *tab;
    int pid;
    int status;
    
    status = 0;
    head = &lst;
    signal(SIGINT, sig_handler);
    signal(SIGQUIT, SIG_IGN);
    while(42)
    {
        i = 0;
        ft_lstclear(head, &del);
        g_global.qlf = 0;
        res = readline("minishell> ");
        if (res == NULL)
            exit(1);
        if (ft_strlen(res) < 1)
            continue;
        add_history(res);
        res = create_space(res);
        ft_split_list(res, ' ', head);
        size = get_size(head);
        tab = handle_symbol(head, size);
        if (!tab)
            continue;
        set_env(head);
        if (is_empty(*head))
            continue;
        while (i < size)
        {
            pid = kangourou(lst_to_argv(head), env, &tab[i]);
            i++;
        }
        unlink(".heredoc");
        waitpid(pid, &status, 0);
        while (wait(NULL) > 0)
            ;
    }
    return (0);
}

// LEXER (parsing) -> execution -> pipe/redirection

//test/test/ls -a argument