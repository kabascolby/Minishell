/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_str.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 12:17:48 by lkaba             #+#    #+#             */
/*   Updated: 2019/12/25 16:49:11 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DYNAMIC_STR_H
# define DYNAMIC_STR_H
# include "libft.h"
# define DYNAMIC_STR_CAPACITY 512

typedef struct s_dstr	t_dstr;
struct			s_dstr {
	char		*buff;
	uint32_t	capacity;
	uint32_t	total;
	uint32_t	(*dstr_total)(t_dstr *);
	void		(*dstr_add)(t_dstr *, char);
	void		(*dstr_set)(t_dstr *, uint32_t, char);
	char		(*dstr_get)(t_dstr *, uint32_t);
	void		(*dstr_delete)(t_dstr *, uint32_t);

};

void			dstr_init(t_dstr *dstr);
uint32_t		dstr_total(t_dstr *dstr);
void			dstr_add(t_dstr *dstr, char c);
void			dstr_set(t_dstr *dstr, uint32_t index, char c);
char			dstr_get(t_dstr *dstr, uint32_t index);
void			dstr_delete(t_dstr *dstr, uint32_t index);
void			dstr_free(t_dstr *dstr);
void			dstr_join_str(t_dstr *dstr, char *str, uint32_t index);
void			dstr_remove(t_dstr *dstr, uint32_t index, uint32_t size);
#endif
