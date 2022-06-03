/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoudin <mgoudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 17:56:09 by mgoudin           #+#    #+#             */
/*   Updated: 2022/06/03 16:35:40 by mgoudin          ###   ########.fr       */
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
        printf("%s\n",argv[i]);
        i++;
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
    t_list  *symbol;
    t_list  **head_symbol;
    
    head = &lst;
    head_symbol = &symbol;
    signal(SIGINT, sig_handler);
    //signal(SIGQUIT, sig_handler);
    while(42)
    {
        ft_lstclear(head, &del);
        res = readline("minishell> ");
        if (res == NULL)
            exit(EXIT_SUCCESS);
        add_history(res);
        res = create_space(res);
        ft_split_list(res, ' ', head);
        handle_symbol(head, head_symbol); //TODO handle env with space
        set_env(head);
        print_argv(lst_to_argv(head));
        //print_lst(*head);
    }
    return (0);
}

// LEXER (parsing) -> execution -> pipe/redirection

//test/test/ls -a argument