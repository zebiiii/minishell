/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaouil <itaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 19:13:05 by itaouil           #+#    #+#             */
/*   Updated: 2022/06/06 19:41:08 by itaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_env_entry(char *var, char *value)
{
	t_env	*new_entry;

	new_entry = malloc(sizeof(t_env));
	new_entry->variable = ft_strdup(var);
	if (value)
		new_entry->value = ft_strdup(value);
	else
		new_entry->value = NULL;
	return (new_entry);
}

void	ft_export(t_list **env, char *var, char *value)
{
	if (!var) // cas où on a fait export sans arguments derrière -> on fera un appel à cette fonction avec NULL à la place de var et value
		print_env_in_ascii_order(*env);
	else // car où on export avec arguments ; value peut être égale à NULL ce qui est géré dans l'autre fonction
	{
		ft_lstadd_back(env, ft_lstnew(new_env_entry(var, value)));
	}
}
