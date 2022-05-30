/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoudin <mgoudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 17:56:09 by mgoudin           #+#    #+#             */
/*   Updated: 2022/05/30 16:33:33 by mgoudin          ###   ########.fr       */
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
    
    head = &lst;
    signal(SIGINT, sig_handler);
    signal(SIGQUIT, sig_handler);
    while(42)
    {
        ft_lstclear(head, &del);
        res = readline("minishell> ");
        if (res == NULL)
        {
            ft_exit("1");
        }
        add_history(res);
        res = create_space(res);
        ft_split_list(res, ' ', head);
        set_env(head);
        print_lst(*head);
    }
    return (0);
}

// LEXER (parsing) -> execution -> pipe/redirection

//TODO: handle "" and ''