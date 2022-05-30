/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_space.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoudin <mgoudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 17:05:57 by mgoudin           #+#    #+#             */
/*   Updated: 2022/05/25 19:36:47 by mgoudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int count_char(char *str)
{
    int i;
    int j;
    int stop_count;

    i = 0;
    j = 0;
    stop_count = 0;
    while(str[i])
    {
        if (str[i] == '\"')
            stop_count = is_quote_close(&str[i], '\"') + 1;
        if (str[i] == '\'')
            stop_count = is_quote_close(&str[i], '\'') + 1;
        if (stop_count < 1)
        {
            if (str[i] == '|')
            j++;
            if (i > 0)
            {
                if (str[i - 1] == '|')
                    j++;
                if (str[i] == '<' && str[i - 1] != '<')
                    j++;
                if (str[i] == '>' && str[i - 1] != '>')
                    j++;
                if (str[i] != '<' && str[i - 1] == '<')
                    j++;
                if (str[i] != '>' && str[i - 1] == '>')
                    j++;
            }
        }
        else
            stop_count--;
        i++;
    }
    return (j + i);
}

char *create_space(char *str)
{
    char *res;
    int i;
    int j;
    int stop_cpy;

    res = malloc(count_char(str) + 1);
    i = 0;
    j = 0;
    stop_cpy = 0;
    while(str[i])
    {
        if (str[i] == '\"')
            stop_cpy = is_quote_close(&str[i], '\"') + 1;
        if (str[i] == '\'')
            stop_cpy = is_quote_close(&str[i], '\'') + 1;
        if (stop_cpy < 1)
        {
            if (str[i] == '|')
            res[i + j++] = ' ';
            if (i > 0)
            {
                if (str[i - 1] == '|')
                    res[i + j++] = ' ';
                if (str[i] == '<' && str[i - 1] != '<')
                    res[i + j++] = ' ';
                if (str[i] == '>' && str[i - 1] != '>')
                    res[i + j++] = ' ';
                if (str[i] != '<' && str[i - 1] == '<')
                    res[i + j++] = ' ';
                if (str[i] != '>' && str[i - 1] == '>')
                    res[i + j++] = ' ';
            }
        }
        else
            stop_cpy--;
        res[i + j] = str[i];
        i++;
    }
    res[i + j] = 0;
    return (res);
}