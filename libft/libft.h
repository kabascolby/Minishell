/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 13:33:59 by lkaba             #+#    #+#             */
/*   Updated: 2019/12/25 16:50:32 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <string.h>
# include <stdarg.h>
# include <stdint.h>
# include <stdlib.h>
# include "get_next_line.h"
# include "ft_printf/ft_printf.h"
# include "ft_hashtable/hashtable.h"
# include "doubly_link.h"
# include "ft_deque.h"
# include "memtrack.h"
# include "vector.h"
# include "dynamic_str.h"
# include <errno.h>
# define ERROR_ALLOC_MESSAGE "Insufficient memory"
# define MALLOC ft_get_malloc
# define FREE ft_mem_reset
# define CE ft_charscmp

typedef enum	e_bool
{
	false,
	true
}				t_bool;

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

typedef struct	s_node
{
	void			*data;
	struct s_node	*next;
}				t_node;

typedef struct	s_queue
{
	t_node		*front;
	t_node		*rear;
}				t_queue;

typedef struct	s_dynamic_array
{
	void	*tab;
	size_t	length;
	size_t	capacity;
	size_t	item_size;
}				t_dynamic_array;

int				ft_toupper(int c);
int				ft_tolower(int c);
int				ft_isdigit(int c);
int				ft_isalpha(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
/*
**Take a char pointer and dereferrence that pointer
**to a Lowercase
*/
void			ft_tolower2(char *c);
void			*ft_memset(void *b, int c, size_t len);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s1);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strncpy(char *dst, const char *src, size_t n);
char			*ft_strcat(char *s1, const char *s2);
char			*ft_strncat(char *s1, const char *s2, size_t n);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strstr(const char *s1, const char *s2);
char			*ft_strnstr(const char *s1, const char *s2, size_t n);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strmerge(char *s1, char *s2);
int				ft_atoi(const char *str);
void			*ft_memalloc(size_t size);
void			ft_memdel(void **ap);
char			*ft_strnew(size_t size);
void			ft_strdel(char **as);
void			ft_strclr(char *s);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strequ(char const *s1, char const *s2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s);
char			**ft_strsplit(char const *s, char c);
int				ft_splitdel(char ***split);
char			*ft_itoa(int n);
void			ft_putchar(char c);
void			ft_putstr(char const *s);
void			ft_putendl(char const *s);
void			ft_putnbr(int n);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char const *s, int fd);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr_fd(int n, int fd);
t_list			*ft_lstnew(void const *content, size_t content_size);
void			ft_lstdelone(t_list **alst, void(*del)(void *, size_t));
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstdelfn(void *obj, size_t size);
void			ft_lstadd(t_list **alst, t_list *new);
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void			ft_lstrev(t_list **alst);
size_t			ft_lstcount(t_list *lst);
t_list			*ft_lstat(t_list *lst, size_t val);
void			ft_lstremove(t_list **alst, void *content);
int				ft_min(int a, int b);
int				ft_max(int a, int b);
int				ft_abs(int i);
int				ft_iswhitespace(char c);
int				ft_countwords(char *str, char c);
int				ft_debug(char *s);
void			ft_print_words_tables(char **tab);
int				get_next_line(int fd, char **line);
int				ft_strcchr(char *str, char c);
t_queue			*init(void);
void			enqueue(t_queue *q, void *n);
void			*dequeue(t_queue *q);
void			*peek(t_queue *q);
int				is_empty(t_queue *q);
t_dllnode		*create_dllnode(void *data);
void			pushdll(void *data, t_dllnode **head);
void			insertddl(size_t pos, void *data, t_dllnode **head);
void			reverseddl(t_dllnode *head);
t_dynamic_array	ft_init_dynamic_array(size_t length, size_t data_t_size);
int				ft_free_darray(void *ptr);
uint8_t			ft_darray_grow(t_dynamic_array *da);
void			ft_add_to_darray(void *data, t_dynamic_array *da);
char			*ft_strupcase(char *str);
wchar_t			*ft_wstrdup(wchar_t *ws);
char			*ft_uitoabase(uintmax_t val, int base, int opt);
char			*ft_str_cat_free(char **s, int j, char *s2);
char			*ft_strtok_r(char *s, const char *filter, char **save_ptr);
size_t			ft_strspn(const char *str, const char *charset);
size_t			ft_strcspn(const char *str, const char *charset);
uint64_t		ft_numdigit(uint64_t num);
uint8_t			ft_isprime(uint32_t a);
uint64_t		ft_find_next_prime(uint64_t n);
void			*ft_get_malloc(size_t n);
/*
**Free a pointer and set it to NULL
*/
void			ft_mem_reset(void *p);
/*
**Open a terminal device or a file and write on it;
*/
int				ft_open_fd(char *device);
/*
** Take a separator char[0] with list of arguments terminated by NULL
** return a copy of joingned arguments
*/
char			*ft_join_args(char *sep, ...);
/*
**shift a string by triming a substring with the most accurate position
**if the substring is close to the front the trim will happen from the
**front else it will happen from the rear;
*/
char			*ft_shift_position(char *buf, uint32_t index, uint32_t size);
/*
** Display the appropriate error message and exit;
** prog: cmd name | errstr: str argument(s) | reason: why error
** return: 1;
*/
int				ft_errexit(const char *prog, char *errstr, const char *reason);

/*
**Use a variadic variables to compare the first char with the rest
**@params:number of arguments and argument list
**return: index of the match else 0
*/
int				ft_charscmp(int num, ...);
#endif
