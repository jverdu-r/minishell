# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/24 15:20:41 by jverdu-r          #+#    #+#              #
#    Updated: 2023/06/17 10:53:34 by jverdu-r         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

CC		=	gcc

INCLUDE	=	includes -I $(READ)/include

CFLAGS	=	-Wall -Werror -Wextra -g3 -I$(INCLUDE)

RM		=	rm -f

SRCS	=	sources/main.c \
			sources/signals.c \
			sources/test_functions.c

OBJS	=	$(SRCS:%.c=%.o)

READ	=   /System/Volumes/Data/Users/jverdu-r/.brew/Cellar/readline/8.2.1

all:		$(NAME)

$(NAME):	$(OBJS)
			@$(CC) $(CFLAGS) $(OBJS)  -lreadline -L $(READ)/lib -o $(NAME)
			@echo "Linked into excutable \033[0;32mminishell\033[0m."


.c.o:		
			@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)
			@echo "Compiling... $<."

clean:		
			@$(RM) $(OBJS)
			@echo "Removed object files."

fclean:		clean
			@$(RM) $(NAME)
			@echo "Removed excutable file."

re:			fclean all

.PHONY:		all clean fclean re
