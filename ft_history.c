/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 04:25:32 by lkaba             #+#    #+#             */
/*   Updated: 2019/12/24 20:06:12 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool		get_history(t_shell *s)
{
	uint32_t	fd;
	char		*line;

	if (access("history.txt", F_OK | W_OK) == -1)
		return (false);
	fd = open("history.txt", O_RDONLY, 0644);
	while (get_next_line(fd, &line) > 0)
		pushdll(line, &s->history);
	close(fd);
	return (true);
}

t_bool		set_history(char *data)
{
	uint32_t	fd;

	fd = 0;
	fd = open("history.txt", O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (!fd)
		return (false);
	ft_putendl_fd(data, fd);
	close(fd);
	return (true);
}
