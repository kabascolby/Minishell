/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doubly_link.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 08:24:03 by lkaba             #+#    #+#             */
/*   Updated: 2018/06/25 11:50:10 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOUBLY_LINK_H
# define DOUBLY_LINK_H

typedef struct	s_dllnode
{
	void				*data;
	struct s_dllnode	*next;
	struct s_dllnode	*prev;
}				t_dllnode;
#endif
