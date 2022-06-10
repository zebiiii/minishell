/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoudin <mgoudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 18:57:59 by mgoudin           #+#    #+#             */
/*   Updated: 2022/06/09 17:45:49 by mgoudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "../minishell.h"

int ft_strlen(char *str)
{
    int i;
    
    i = 0;
    if (str[0] == '\0')
    {
        //print_error("strlen error\n");
        return (0);
    }
    while (str[i])
        i++;
    return (i);
}
