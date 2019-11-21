# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/07 05:25:18 by lkaba             #+#    #+#              #
#    Updated: 2019/11/20 14:20:43 by lkaba            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
FLAGS = -Wall -Wextra -Werror -Wno-pointer-arith -g -fsanitize=address
FILES = $(wildcard *.c)
OFILES = $(patsubst %.c, %.o, $(FILES))
PLIBFT = ./libft/ft_printf/libftprintf.a
HASHTABLE = ./libft/ft_hashtable/libfthashtable.a

all: $(NAME)


$(NAME): $(PLIBFT) $(HASHTABLE) $(OFILES)
	@gcc $(FLAGS) $^ -o $@

$(PLIBFT):
	@make -C libft/ft_printf

$(HASHTABLE):
	@make -C libft/ft_hashtable

%.o: %.c minishell.h
	gcc $(FLAGS) -c $<

debug: $(PLIBFT) $(HASHTABLE) $(OFILES)
	@gcc -g $(FLAGS) $^ -o $@

clean:
	@/bin/rm -f $(FILES:.c=.o)
	@make clean -C libft/ft_printf
	@make clean -C libft/ft_hashtable

fclean: clean
	@/bin/rm -f $(NAME)
	@make fclean -C libft/ft_printf
	@make fclean -C libft/ft_hashtable

re: fclean all
