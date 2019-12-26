FILES = ft_countwords.c\
		ft_putstr.c\
		ft_strrchr.c\
		ft_strcmp.c\
		ft_strlcat.c\
		ft_memcpy.c\
		ft_lstat.c\
		ft_memmove.c\
		ft_min.c\
		ft_strsplit.c\
		ft_strncpy.c\
		ft_lstmap.c\
		ft_lstadd.c\
		ft_striter.c\
		ft_strstr.c\
		ft_isdigit.c\
		ft_putnbr.c\
		ft_lstremove.c\
		ft_iswhitespace.c\
		ft_memccpy.c\
		ft_max.c\
		ft_strdel.c\
		ft_memchr.c\
		ft_bzero.c\
		ft_isalnum.c\
		ft_putstr_fd.c\
		ft_lstiter.c\
		ft_lstrev.c\
		ft_toupper.c\
		ft_lstdelone.c\
		ft_strcpy.c\
		ft_strdup.c\
		ft_lstnew.c\
		ft_putnbr_fd.c\
		ft_striteri.c\
		ft_putendl_fd.c\
		ft_strmap.c\
		ft_memdel.c\
		ft_strnstr.c\
		ft_putchar.c\
		ft_isascii.c\
		ft_strlen.c\
		ft_strnew.c\
		ft_strsub.c\
		ft_putendl.c\
		ft_memalloc.c\
		ft_strncat.c\
		ft_strncmp.c\
		ft_itoa.c\
		ft_memcmp.c\
		ft_strequ.c\
		ft_strtrim.c\
		ft_putchar_fd.c\
		ft_memset.c\
		ft_isalpha.c\
		ft_strcat.c\
		ft_tolower.c\
		ft_strnequ.c\
		ft_strjoin.c\
		ft_atoi.c\
		ft_ilerp.c\
		ft_strclr.c\
		ft_lstcount.c\
		ft_isprint.c\
		ft_strmapi.c\
		ft_lstdel.c\
		ft_abs.c\
		ft_wstrdup.c\
		ft_strupcase.c\
		ft_uitoabase.c\
		ft_strchr.c\
		get_next_line.c\
		ft_print_words_tables.c\
		ft_strcchr.c\
		doubly_linked.c\
		ft_dynamic_array.c\
		ft_queue.c\
		ft_deque.c\
		ft_deque2.c\
		ft_str_cat_free.c\
		ft_numdigit.c\
		ft_strtok_r.c\
		ft_strspn.c\
		ft_strcspn.c\
		ft_isprime.c\
		ft_find_next_prime.c\
		ft_get_malloc.c\
		ft_join_args.c\
		ft_errexit.c\
		ft_vector_part1.c\
		ft_vector_part2.c\
		ft_dstr_part1.c\
		ft_dstr_part2.c\
		memtrack.c\
		ft_mem_reset.c\
		ft_remove_substring.c\
		ft_charscmp.c\
		ft_debug.c

OFILES = $(FILES:.c=.o)
NAME = libft.a

FLAGS = -Wall -Wextra -Werror -Wno-pointer-arith

$(NAME): $(OFILES)
	@ar rc $(NAME) $^
	@ranlib $(NAME)

%.o: %.c
#	echo Compiling $@...
	@gcc $(FLAGS) -c $< -o $@

all: $(NAME)

clean:
	@/bin/rm -f $(FILES:.c=.o)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
