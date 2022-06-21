# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgoudin <mgoudin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/29 17:58:58 by mgoudin           #+#    #+#              #
#    Updated: 2022/06/21 15:30:11 by mgoudin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

SRCS	= 	main.c \
			builtin/pwd.c \
			builtin/exit.c \
			builtin/cd.c \
			builtin/echo.c \
			builtin/export.c \
			builtin/export_part2.c \
			builtin/export_part3.c \
			builtin/exit.c \
			builtin/unset.c \
			builtin/unset_part2.c \
			builtin/env.c \
			utils/error.c \
			utils/ft_atoi.c \
			utils/ft_putstr_fd.c \
			utils/ft_strlen.c \
			utils/create_space.c \
			utils/quote.c \
			utils/set_env.c \
			utils/lst_to_argv.c \
			utils/handle_symbol.c \
			utils/symbols/doubleredirect_in.c \
			utils/symbols/doubleredirect_out.c \
			utils/symbols/pipe.c \
			utils/symbols/redirect_in.c \
			utils/symbols/redirect_out.c \
			utils/symbols/free_symbols.c \
			utils/gnl.c \
			utils/get_size.c \
			utils/ft_strn.c \
			utils/misc.c \
			utils/env_misc.c \
			utils/misc_symbol.c \
			utils/handle_quote/handle_quote.c \
			utils/init/init.c \
			utils/ft_putchar_fd.c \
			utils/ft_strlen2d.c \
			utils/ft_strdup2d.c \
			utils/ft_getenv.c \
			utils/ft_freesplit.c \
			exec/kangourou.c \
			exec/check_builtin.c \
			exec/check_path.c \
			exec/dup_close.c \
			exec/ft_msg.c \
			exec/manage_builtin.c \
			exec/parce_builtin.c \
			libft/ft_bzero.c \
			libft/ft_calloc.c \
			libft/ft_charjoin.c \
			libft/ft_lstadd_back.c \
			libft/ft_lstadd_front.c \
			libft/ft_lstclear.c \
			libft/ft_lstdelone.c \
			libft/ft_lstiter.c \
			libft/ft_lstlast.c \
			libft/ft_lstmap.c \
			libft/ft_lstnew.c \
			libft/ft_lstsize.c \
			libft/ft_split_list.c \
			libft/ft_memset.c \
			libft/ft_split.c \
			libft/ft_strjoin.c \
			libft/ft_strncmp.c \
			libft/ft_gnljoin.c \
			libft/ft_itoa.c \
			libft/ft_strcmp.c \
			libft/ft_strdup.c \
			libft/ft_substr.c

OBJS	= ${SRCS:.c=.o}

HEADER	= minishell.h

LIBS	=	-L/Users/mgoudin/.brew/opt/readline/lib -lreadline
HEADERS	=	-I$(HEADER) -I/Users/mgoudin/.brew/opt/readline/include

CC		= gcc
RM		= rm -f

CFLAGS = -Wall -Wextra -Werror -g

%.o: %.c 
	$(CC) -c -o $@ $< $(HEADERS) -g

all: $(NAME)

$(NAME):	$(OBJS)
	$(CC) -o $@ $^ $(LIBS)

clean:
	${RM} ${OBJS}

fclean:	clean
	${RM} ${NAME}

re: fclean all

.PHONY:	all clean fclean re