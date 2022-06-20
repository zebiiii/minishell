/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoudin <mgoudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 17:56:34 by mgoudin           #+#    #+#             */
/*   Updated: 2022/06/17 21:29:53 by mgoudin          ###   ########.fr       */
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
# include <termios.h>

# define CMD 1
# define CMDENV 2
# define EXE 3

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

typedef struct s_redirect
{
	int	in;
	int	out;
	int st_pfd_in;
	int st_pfd_out;
	int lst_pfd_in;
	int lst_pfd_out;
	char *str;
}					t_redirect;

typedef struct	s_exec
{
	int		index_env;
	int		index_path;
	char	**env_path;
	char	*path;
	char	*slash_join;
}	t_exec;


typedef struct s_data
{
	struct s_exec		*exec;
	struct s_redirect	*redir;
	t_list		*env_lst;		//a free
	t_list		*export_lst;	//a free
	t_list		**head_env;
	t_list		**head_export;
	int		size;
	int		lst_size;
	int		i;
	int		j;
	int		k;
	char	**array;
}	t_data;

typedef struct s_matt
{
	int	i;
	int	j;
}				t_matt;

typedef struct s_cmd
{
	void			*content;
	enum s_type		type;
}					t_cmd;

typedef struct s_g
{
	int qlf;
	int exit_status;
	int	heredoc;
	int	listener;
	int	in_heredoc;
	int	indicateur;
}					t_g;

t_g		g_global;

typedef struct  s_symbol
{
	int		i;
	int		j;
}               t_symbol;
typedef struct s_split
{
	int		i;
	int		j;
	int		k;
	int		next_quote;
}				t_split;
typedef struct s_heredoc
{
	int		listener;
	char	*heredoc;
	char	*line;
	int		fd;
}				t_heredoc;
typedef struct s_redirectin
{
	int	fd;
	char *arg;
	char *tmp;
	int type;
}					t_redirectin;
typedef struct s_argv
{
	char	*res;
	int		type;
	int		i;
}				t_argv;


int     ft_pwd();
int    ft_echo(int argc, char **argv);
int		ft_check_option(char **argv);
int    ft_cd(char **argv);
char	**ft_split(char const *s, char c);


int		ft_exit_case(char **status);
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
t_redirect    *handle_symbol(t_list **head, int len);
char	*get_next_line(int fd);
char	*ft_gnljoin(char *s1, char *s2);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *s, size_t n);
int		kangourou(char **cmd, char **env, t_redirect *tab, t_data *data);
int		cd(char **argv);
int		echo(int argc, char **argv);
int		get_size(t_list **head);
char    *replace_len(char *str, char *word, int len);
char	*ft_itoa(int n);
int    ft_doubleredirect_in(t_list *lst);
int    ft_doubleredirect_out(t_list *lst);
int ft_pipe(t_list *lst, t_redirect tab[], int j, int size);
int    ft_redirect_in(t_list *lst);
int    ft_redirect_out(t_list *lst);
char    *replace_env_link(char *str);
char	*ft_strn(char const *str, int lenght);
enum s_type	get_type(char *str);
int	handle_quote(t_split *data, char const *str, int type, t_list **a);
int	ft_next_quote(t_split *data, char const *str, int type);
t_cmd	*create_content(char *str, int quote, int suite);
void	ft_initdata(t_heredoc *data);
int	write_heredoc(char *heredoc, int fd);
void	init_stdin_stdout(t_redirect *tab, int len);
void	ft_init_env(t_symbol *data);
char	*get_env_and_status(char *word);
void	ft_initdata_argv(t_argv *data);
int	is_space(char *str);
void    ft_freesplit(char **str);
void	*ft_memset(void *b, int c, size_t len);
void    ft_quit_with_msg(char *s1, char *s2, int exit_status, t_exec *var);
void    ft_msg(char *s1, char *s2, int exit_status, t_exec *var);
char	*ft_charjoin_lst(char *s1, char c);
void	ft_dup(t_redirect *tab, t_exec *var);
int    grep_path(char **env, t_exec *var);
int ft_check_path(char **cmd, char **env, t_exec *var);
void	ft_putstr_2(char **arg, char *msg);
int	parce_builtin(char **cmd, char **env, t_data *data);
int	parce_builtin_2(char **cmd, char **env, t_data *data);
void	manage_builtin_part_1(char **cmd, char **env, t_data *data);
void	manage_builtin_part_2(char **cmd, char **env, t_data *data);
int	ft_chech_builtin(char **cmd, char **env, t_data *data);
int	ft_chech_builtin_case(char **cmd, char **env, t_exec *var, t_data *data);
void    exec(char **cmd, char **env, t_exec *var, t_data *data);
void    exec_case(char **cmd, char **env, t_exec *var, t_data *data);
int ft_check_cmd(char **cmd, char **env, t_exec *var);
void	ft_close(t_redirect *tab);








void	ft_init_space(t_matt *data);
int	count_char(char *str);
void	count_symbol(t_matt *data, char *str);
int free_symbol(int fd, void *el);
char	*ft_gnljoin2(char *s1, char *s2);
long long	ft_atoi_exit_case(char *str);
void	ft_putchar_fd(char c, int fd);
size_t	ft_strlen2d(char **s);
char	*ft_strjoin_quote(char *s1, char *s2);
char	*ft_gnljoin_2(char *s1, char *s2);
char	*ft_strjoin_f(char *s1, char *s2);
void del_2(void*el);
void del_3(void*el);
int	bt_before_fork(char **cmd, t_data *data, t_list *lst, int size);
void    ft_create_env(char **env, t_list **first, t_data *data);
void    ft_create_export(char **env, t_list **first, t_data *data);
void ft_check_status(int *status);
int ft_unset(char **argv, t_data *data);
int    ft_check_unset(char *argv, t_data *data);
int    ft_del_equal(char *argv, t_data *data, t_list *lst);
int    ft_del_env(char *argv, t_data *data, t_list *lst);
int ft_check_option_unset(char *argv);
int    ft_exit_export(char *str, char *argv);
int ft_check_first_char(char *argv);
int ft_check_equal(char *tmp);
int ft_check_content(char *tmp, t_list *lst, t_data *data);
int	ft_strcmp(const char *s1, const char *s2);
int    ft_add_to_export(char *argv, t_list *lst, t_data *data);
char	*ft_strdup(char *s1);
char	*ft_substr(char *s, unsigned int start, size_t len);
int ft_len_equal(char *s);
int ft_fusion_equal(char *tmp, t_list *lst, char *str);
int ft_fusion(char *argv, t_list *lst, t_data *data);
int ft_check_str(char *argv, t_list *lst, t_data *data);
int ft_check_argument(char *argv, t_list *lst, t_data *data);
int ft_print_export(t_list *lst);
int export_first_step(char *argv, t_list *lst);
int    ft_export(char **argv, t_list *lst, t_data *data);
void    ft_exit_char(void);
void    ft_exit_arg(void);
int ft_check_exit(char *arg);
int	ft_env(t_list *lst);




#endif