# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/24 15:20:41 by jverdu-r          #+#    #+#              #
#    Updated: 2023/06/17 12:01:59 by jverdu-r         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

LIBFT	=	includes/libft/

CC		=	gcc

LIBFT_A	=	$(addprefix $(LIBFT), libft.a)

INCLUDE	=	includes -I $(READ)/include

CFLAGS	=	-Wall -Werror -Wextra -g3 -I$(INCLUDE)

RM		=	rm -f

SRCS	=	sources/main.c \
			sources/signals.c \

OBJS	=	$(SRCS:%.c=%.o)

READ	=   /System/Volumes/Data/Users/jverdu-r/.brew/Cellar/readline/8.2.1

all:		$(NAME)

$(NAME):	$(OBJS) $(LIBFT_A)
			@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT) -lft  -lreadline -L $(READ)/lib -o $(NAME)
			@echo "Linked into excutable \033[0;32mminishell\033[0m."

$(LIBFT_A):	
			@$(MAKE) -s -C $(LIBFT)
			@echo "compiled $(LIBFT_A)."
.c.o:		
			@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)
			@echo "Compiling... $<."

localclean:		
			@$(RM) $(OBJS)
			@echo "Removed object files."

clean:		localclean
			@$(MAKE) clean -s -C $(LIBFT)
			@echo "Clean libft."

fclean:		localclean
			@$(MAKE) fclean -s -C $(LIBFT)
			@echo "Full clean libft."
			@$(RM) $(NAME)
			@echo "Removed excutable file."

re:			fclean all

.PHONY:		all clean fclean re
