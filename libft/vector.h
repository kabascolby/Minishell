/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 11:31:46 by lkaba             #+#    #+#             */
/*   Updated: 2019/12/25 16:44:23 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H
# include "libft.h"
# define VECTOR_INIT_CAPACITY 8

typedef struct s_vector	t_vector;
struct			s_vector {
	void	**items;
	int		capacity;
	int		total;
	int		(*vector_total)(t_vector *v);
	void	(*vector_add)(t_vector *v, void *item);
	void	(*vector_set)(t_vector *v, int index, void *item);
	void	*(*vector_get)(t_vector *v, int index);
	void	(*vector_delete)(t_vector *v, int index);
};

void			vector_init(t_vector *v);
int				vector_total(t_vector *v);
void			vector_add(t_vector *v, void *item);
void			vector_set(t_vector *v, int index, void *item);
void			*vector_get(t_vector *v, int index);
void			vector_delete(t_vector *v, int index);
void			vector_free(t_vector **v);
#endif
