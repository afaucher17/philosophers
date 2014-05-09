# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/12/27 14:53:18 by tdieumeg          #+#    #+#              #
#    Updated: 2014/05/09 19:45:02 by tdieumeg         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo

CC		= gcc

DEPS	= ft_script.h 

SRCS	= philo.c \
		  philo_fun.c \
		  philolunch.c \
		  ncurses.c \
		  ncurses_fun.c

CFLAGS	= -Wall -Wextra -Werror -g

HEADERS	= -I includes -I libft

LIB		= -L libft -lft -lncurses

OBJ		= $(patsubst %.c,src/%.o, $(SRCS))

all: $(NAME)

%.o: %.c
	$(CC) $(HEADERS) $(CFLAGS) -o $@ -c $< 

libft:
	@$(MAKE) $(HEADERS) -C libft/

$(NAME): $(OBJ)
	@$(MAKE) -C libft/
	$(CC) $(CFLAGS) $(LIB) -o $(NAME) $^

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

lib.fclean:
	make -C libft fclean

re: fclean all

.PHONY: clean fclean re libft
