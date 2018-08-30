/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 08:33:00 by lkaba             #+#    #+#             */
/*   Updated: 2018/05/05 18:20:17 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_remalloc(char **save, int len)
{
	char	*tmp;

	tmp = *save;
	if (!(*save = ft_strnew(len)))
		return (0);
	ft_strcpy(*save, tmp);
	(*save)[len] = '\0';
	free(tmp);
	return (1);
}

int	fill_line(int j, char **save, char **line)
{
	int i;
	int k;

	k = 0;
	i = 0;
	if (j != 0 || ft_strlen((*save)) != 0)
	{
		while (((*save)[i] != '\0') && ((*save)[i] != '\n'))
			i++;
		if ((*save)[i] == '\0' || (*save)[i] == '\n')
		{
			*line = ft_strnew(i);
			ft_strncpy(*line, *save, i);
			(*line)[i] = '\0';
		}
		else if ((*save)[i] == '\0' && j == 0)
			return (1);
		if ((*save)[i++])
			while ((*save)[i])
				(*save)[k++] = (*save)[i++];
		(*save)[k] = '\0';
		return (2);
	}
	return (1);
}

int	get_next_line(int fd, char **line)
{
	int			l;
	int			len;
	static char	*save[5000];
	char		buf[BUFF_SIZE + 1];

	if (fd < 0 || read(fd, buf, 0) < 0 || !line)
		return (-1);
	len = ft_strlen(save[fd]);
	while ((l = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[l] = '\0';
		len += BUFF_SIZE;
		if (!(ft_remalloc(&save[fd], len)))
			return (-1);
		ft_strncat(save[fd], buf, BUFF_SIZE);
		if (ft_memchr(buf, '\n', BUFF_SIZE))
			break ;
	}
	if ((fill_line(l, &save[fd], line)) == 2)
		return (1);
	ft_strdel(&save[fd]);
	return (0);
}
