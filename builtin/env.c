#include "../minishell.h"

int	ft_env(t_list *lst)
{
	t_list	*list;

	list = lst;
	while (list)
	{
		printf("%s\n", list->content);
		list = list->next;
	}
	return (0);
}