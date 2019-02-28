# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/07 05:25:18 by lkaba             #+#    #+#              #
#    Updated: 2019/02/27 21:14:10 by lkaba            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
FLAGS = -Wall -Wextra -Werror #-g -fsanitize=address
FILES = $(wildcard *.c)
OFILES = $(patsubst %.c, %.o, $(FILES))
LIBFT = libft.a

all: $(NAME)


$(NAME): $(LIBFT) $(OFILES)
	@gcc $(FLAGS) $(OFILES) libft/$(LIBFT) -o $@

$(LIBFT):
	@make -C libft/ft_printf
	@mv libft/ft_printf/libftprintf.a libft/libft.a

%.o: %.c
	gcc $(FLAGS) -c $<

clean:
	@/bin/rm -f $(FILES:.c=.o)
	@make clean -C libft/ft_printf

fclean: clean
	@/bin/rm -f $(NAME)
	@make fclean -C libft/ft_printf

re: fclean all
