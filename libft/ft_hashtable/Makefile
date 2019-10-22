# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/17 23:35:12 by lkaba             #+#    #+#              #
#    Updated: 2019/10/18 15:57:40 by lkaba            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libfthashtable.a
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

%.o: %.c hashtable.h
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
