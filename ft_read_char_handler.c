/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_char_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 13:18:04 by lkaba             #+#    #+#             */
/*   Updated: 2019/12/08 17:20:33 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_debug_output(char *dev, char *res,
void (*fptr)(const char *arg, int num))
{
	static int fd;

	if (!fd && (fd = open(dev, 1)) == -1)
	{
		ft_putendl("error opennig fd");
		return ;
	}
	fptr(res, fd);
}

void	fn_other_key(t_shell *s, char c, wptr wrchar)
{
	if (ft_isprint(c) && wrchar(1, &c, 1))
		dstr_add(s->dstr, c);
}

void	fn_tab(t_shell *s, char c, wptr wrchar)
{
	UNUSED(s, c, wrchar);
	ft_putstr("handle auto completion");
}

void	fn_new_line(t_shell *s, char c, wptr wrchar)
{

	if (s->isquote)
	{
		s->isquote == 34 ? wrchar(1, "\ndquote> ", 9) :
		wrchar(1, "\nquote> ", 8);
		dstr_add(s->dstr, c);
	}
	else
		s->is_readding = false;
}

void	fn_delete(t_shell *s, char c, wptr wrchar)
{
	uint32_t	num;

	(void)c;
	if ((num = dstr_total(s->dstr)) && wrchar(STDOUT_FILENO, "\b \b", 3))
	{
		ft_debug_output("/dev/ttys001", ft_itoa(s->isquote), ft_putendl_fd);
		if (s->isquote == dstr_get(s->dstr, num - 1) && !((num > 1) &&
		dstr_get(s->dstr, num - 2) == 92))
			s->isquote = '\0';
		dstr_delete(s->dstr, num - 1);
		ft_debug_output("/dev/ttys001", s->dstr->buff, ft_putendl_fd);
	}
}

void	fn_with_esc(t_shell *s, char c, wptr wrchar)
{
	static	int	pos;
	int32_t		str_size;

	read(STDIN_FILENO, &c, 1);
	read(STDIN_FILENO, &c, 1);
	if ((str_size = dstr_total(s->dstr)) > 0)
	{
		c == 'D' && pos >= 0 && str_size > pos ?
		wrchar(1, "\033[D", 4) && ++pos : 0;
		c == 'C' && pos > 0 ? write(1, "\033[C", 4) && --pos : 0;
	}
}

void	fn_quote(t_shell *s, char c, wptr wrchar)
{
	uint32_t	num;

	dstr_add(s->dstr, c);
	wrchar(1, &c, 1);
	num = dstr_total(s->dstr);
	if (num > 1 && (dstr_get(s->dstr, num - 2) == 92))
		return ;
	if (s->isquote == c || s->isquote == '\0')
		s->isquote = !s->isquote ? c : 0;
}
