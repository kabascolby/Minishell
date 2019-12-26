/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 20:15:44 by lkaba             #+#    #+#             */
/*   Updated: 2019/12/26 09:46:49 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "ft_colors.h"
# include "../libft.h"
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <wchar.h>
# define NUMBERSET "0123456789abcdef0123456789ABCDEF"
# define UM p->f.types.um
# define IM p->f.types.im
# define PL p->f.length
# define STR p->f.str
# define UIB ft_uitoabase

typedef	union			u_value
{
	wchar_t				wc;
	char				c;
	char				*str;
	wchar_t				*ws;
	int64_t				im;
	uintmax_t			um;
	void				*p;
}						t_value;

typedef	struct			s_pfnode
{
	int					c;
	char				*s;
	struct s_pfnode		*next;
}						t_pfnode;

typedef struct			s_args
{
	u_int8_t			min;
	u_int8_t			plus;
	u_int8_t			space;
	u_int8_t			hash;
	u_int8_t			zero;
	u_int8_t			start;
	u_int8_t			prec;
	int					f_w;
	unsigned int		precis;
	unsigned int		l;
	char				type;
	char				*str;
	unsigned int		sign;
	int					len;
	int					pos;
	char				fw;
	t_value				types;
}						t_args;

typedef	struct			s_printf
{
	t_args				f;
	va_list				ap;
	t_pfnode			*head;
	char				*s3;
}						t_p;

enum					e_l
{
	H = 1,
	HH,
	L,
	LL,
	J,
	Z
};

void					ft_addnode(t_p *p, char *s1, size_t len);
int						ft_printf(char *s, ...);
int						ft_nodeprint(t_p *p);
void					ft_reverse_nodes(t_p *p);
char					*ft_parse1(char *s, t_p *p);
char					*ft_parse2(char *s, t_p *p);
char					*ft_parse3(char *s, t_p *p);
char					*ft_parse4(char *s, t_p *p);
void					ft_conversion(t_p *p);
void					format_conversion(t_p *p);
void					format_conversion2(t_p *p);
void					format_conversion3(t_p *p);
void					format_conversion4(t_p *p);
void					ft_precision(t_p *p);
void					ft_field_width(t_p *p);
void					ft_field_width2(t_p *p);
void					flags_space_sign(t_p *p);
void					flags_zero(t_p *p);
char					*ft_spf(char **s, int j, char *s2);
char					*ft_uitoabase(uintmax_t val, int base, int opt);
#endif
