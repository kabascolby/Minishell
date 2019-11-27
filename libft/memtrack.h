/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memtrack.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 11:21:38 by lkaba             #+#    #+#             */
/*   Updated: 2019/11/25 10:27:01 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMTRACK_H
# define MEMTRACK_H
# include "libft.h"
# define MEMSIZE 42

typedef struct s_memtrack	t_memtrack;

struct						s_memtrack
{
	void		**membuff;
	uint64_t	size;
	uint64_t	count;
	void		*(*track)(t_memtrack **, void *);
	void		(*destroy)(t_memtrack *);
};
/*
**Memory tracker initialization set the functions pointers
**"track" and "destroy" respectivily to ft_mtnew and
**ft_destroy
*/
t_memtrack					*memtracker_init(uint64_t size);
/*
**Track a pointer to a dynamic allocked pointer in purpose to
**all the pointer at once and not be worried of leaks;
*/
void						*ft_mtnew(t_memtrack **mt, void *ptr);
void						ft_mtdestroy(t_memtrack *mt);

#endif
