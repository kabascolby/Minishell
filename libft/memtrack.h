/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memtrack.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 11:21:38 by lkaba             #+#    #+#             */
/*   Updated: 2019/11/21 16:27:48 by lkaba            ###   ########.fr       */
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
	int64_t		count;
};

void						ft_mtadd(t_memtrack **h, uint64_t size);
void						ft_mtfree(void *ptr);
void						ft_mtdestroy(void);

#endif
