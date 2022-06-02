# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgoudin <mgoudin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/29 17:58:58 by mgoudin           #+#    #+#              #
#    Updated: 2022/06/02 13:31:13 by mgoudin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

SRCS	= 	main.c \
			builtin/pwd.c \
			builtin/exit.c \
			utils/error.c \
			utils/ft_atoi.c \
			utils/ft_putstr_fd.c \
			utils/ft_strlen.c \
			utils/create_space.c \
			utils/quote.c \
			utils/set_env.c \
			utils/lst_to_argv.c \
			libft/ft_lstadd_back.c \
			libft/ft_lstadd_front.c \
			libft/ft_lstclear.c \
			libft/ft_lstdelone.c \
			libft/ft_lstiter.c \
			libft/ft_lstlast.c \
			libft/ft_lstmap.c \
			libft/ft_lstnew.c \
			libft/ft_lstsize.c \
			libft/ft_split.c \
			libft/ft_strjoin.c \
			libft/ft_strncmp.c

OBJS	= ${SRCS:.c=.o}

HEADER	= minishell.h

LIBS	=	-L/Users/mgoudin/.brew/opt/readline/lib -lreadline
HEADERS	=	-I$(HEADER) -I/Users/mgoudin/.brew/opt/readline/include

CC		= gcc
RM		= rm -f

CFLAGS = -Wall -Wextra -Werror

%.o: %.c 
	$(CC) -c -o $@ $< $(HEADERS)

all: $(NAME)

$(NAME):	$(OBJS)
	$(CC) -o $@ $^ $(LIBS)

clean:
	${RM} ${OBJS}

fclean:	clean
	${RM} ${NAME}

re: fclean all

.PHONY:	all clean fclean re