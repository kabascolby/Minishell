/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_char_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 13:18:04 by lkaba             #+#    #+#             */
/*   Updated: 2019/12/03 11:16:08 by lkaba            ###   ########.fr       */
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
	UNUSED(c);
	if (s->is_dquote)
		wrchar(1, "\ndquote> ", 9);
	else if (s->is_quote)
		wrchar(1, "\nquote> ", 8);
	else
		s->is_readding = false;
}

void	fn_delete(t_shell *s, char c, wptr wrchar)
{
	uint32_t	num;

	UNUSED(c);
	if ((num = dstr_total(s->dstr)) && wrchar(STDOUT_FILENO, "\b \b", 3))
	{
		if (s->is_dquote && !((num > 1) && CE_(dstr_get(s->dstr, num - 1), 92)))
			s->is_dquote = s->is_dquote ^ 1;
		if (s->is_quote && !((num > 1) && CE_(dstr_get(s->dstr, num - 1), 92)))
			s->is_quote = s->is_quote ^ 1;
		dstr_delete(s->dstr, num - 1);
		ft_debug_output("/dev/ttys000", s->dstr->buff, ft_putendl_fd);
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

void	fn_dquote(t_shell *s, char c, wptr wrchar)
{
	uint32_t	num;

	ft_debug_output("/dev/ttys000", ft_itoa(s->is_quote), ft_putendl_fd);
	if (!s->is_quote && !((num = dstr_total(s->dstr) > 1)
	&& CE_(dstr_get(s->dstr, num - 1), 92)))
	{
		ft_debug_output("/dev/ttys000", s->dstr->buff, ft_putendl_fd);
		s->is_dquote = s->is_dquote ^ 1;
	}
	wrchar(1, &c, 1);
	dstr_add(s->dstr, c);
}

void	fn_quote(t_shell *s, char c, wptr wrchar)
{
	uint32_t	num;

	ft_debug_output("/dev/ttys000", ft_itoa(s->is_dquote), ft_putendl_fd);
	if (!s->is_dquote && !((num = dstr_total(s->dstr) > 1)
	&& CE_(dstr_get(s->dstr, num - 1), 92)))
	{
		ft_debug_output("/dev/ttys000", s->dstr->buff, ft_putendl_fd);
		s->is_quote = s->is_quote ^ 1;
	}
	wrchar(1, &c, 1);
	dstr_add(s->dstr, c);
}
