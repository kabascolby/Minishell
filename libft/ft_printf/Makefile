# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/27 18:43:13 by lkaba             #+#    #+#              #
#    Updated: 2018/07/05 19:44:11 by lkaba            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
FLAGS = -Wall -Wextra -Werror
FILES = $(wildcard *.c)
OFILES = $(patsubst %.c, %.o, $(FILES))
LIBFT = libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OFILES)
	@ar rc $(NAME) $(OFILES) $(wildcard ../*.o)
	@ranlib $(NAME)

$(LIBFT): force
	@make -C ../

%.o: %.c ft_printf.h
	@echo compiling $<
	@gcc $(FLAGS) -I ../ -c $<

force:
	@true

clean:
	@/bin/rm -f $(OFILES)
	@make clean -C ../

fclean: clean
	@/bin/rm -f $(NAME)
	@make fclean -C ../

re: fclean all
