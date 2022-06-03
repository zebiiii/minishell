/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoudin <mgoudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 17:56:34 by mgoudin           #+#    #+#             */
/*   Updated: 2022/06/03 16:23:11 by mgoudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h> 

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;
typedef enum s_type {
    content,
	simple_quote,
	quote,
	pipe_,
	redirect_right,
	redirect_left,
	double_redirect_right,
	double_redirect_left,
	suite,
	simple_quote_suite,
	quote_suite,
	delete,
}					t_type;
typedef struct s_cmd
{
	void			*content;
	enum s_type		type;
}					t_cmd;
typedef struct s_redirect
{
	int	in;
	int	out;
}					t_redirect;
int     ft_pwd();
int		ft_exit(char *status);
int     ft_putstr_fd(char *str, int fd);
int     ft_atoi_secure(char *str);
int     print_error(char *str);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **head, t_list *new);
void	ft_lstadd_front(t_list **head, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
void	ft_split_list(char const *str, char c, t_list **a);
int     ft_strlen(char *str);
char	*create_space(char *str);
int		ft_strncmp(const char *s1, const char *s2, unsigned int n);
int		is_quote_close(const char *str, char quote);
char	*ft_strn(char const *str, int lenght);
void    set_env(t_list **a);
char    **lst_to_argv(t_list **head);
char	*ft_strjoin(char *s1, char *s2);
void    handle_symbol(t_list **head, t_list **head_symbol);
char	*get_next_line(int fd);
char	*ft_gnljoin(char *s1, char *s2);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *s, size_t n);

#endif