/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoudin <mgoudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 17:56:09 by mgoudin           #+#    #+#             */
/*   Updated: 2022/06/06 17:16:34 by mgoudin          ###   ########.fr       */
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

void    sig_handler(int signum)
{
    if (signum == SIGINT)
    {
        printf("\n");
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}

int main(int argc, char **argv, char **env)
{
    char    *res;
    t_list	*lst;
	t_list	**head;
    t_list  *symbol;
    t_list  **head_symbol;
    int     size;
    int     i;
    t_redirect *tab;
    
    head = &lst;
    head_symbol = &symbol;
    signal(SIGINT, sig_handler);
    //signal(SIGQUIT, sig_handler);
    i = 0;
    while(42)
    {
        ft_lstclear(head, &del);
        res = readline("minishell> ");
        if (res == NULL)
            exit(EXIT_SUCCESS);
        add_history(res);
        res = create_space(res);
        ft_split_list(res, ' ', head);
        size = get_size(head);
        tab = handle_symbol(head, head_symbol, size); //TODO handle env with space
        set_env(head);
        while (i < size)
        {
            kangourou(lst_to_argv(head), env, tab[i]);
            i++;
        }
        unlink(".heredoc");
    }
    return (0);
}

// LEXER (parsing) -> execution -> pipe/redirection

//test/test/ls -a argument