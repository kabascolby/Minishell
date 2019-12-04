/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 11:31:46 by lkaba             #+#    #+#             */
/*   Updated: 2019/11/30 22:16:01 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H
# include "libft.h"
# define VECTOR_INIT_CAPACITY 8

/*
** To simplify the use of the vector data structure
** by removing some of the verbosity
*/

# define VECTOR_INIT(vec) t_vector vec; vector_init(&vec)
# define VECTOR_ADD(vec, item) vector_add(&vec, (void *) item)
# define VECTOR_SET(vec, id, item) vector_set(&vec, id, (void *) item)
# define VECTOR_GET(vec, type, id) (type) vector_get(&vec, id)
# define VECTOR_DELETE(vec, id) vector_delete(&vec, id)
# define VECTOR_TOTAL(vec) vector_total(&vec)
# define VECTOR_FREE(vec) vector_free(&vec)

typedef struct s_vector	t_vector;
struct			s_vector {
	void	**items;
	int		capacity;
	int		total;
	int	(*vector_total)(t_vector *v);
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
void			vector_free(t_vector *v);
#endif
