/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_terminal_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 14:01:12 by lkaba             #+#    #+#             */
/*   Updated: 2019/12/22 14:04:37 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**disable canonical mode (buffered i/o) and local echo
**set the new settings immediately
*/

void		set_unbeffered(void)
{
	t_termios new_term_attr;

	tcgetattr(1, &new_term_attr);
	new_term_attr.c_lflag &= (~ICANON & ~ECHO);
	new_term_attr.c_cc[VMIN] = 0;
	new_term_attr.c_cc[VTIME] = 1;
	tcsetattr(STDIN_FILENO, TCSANOW, &new_term_attr);
}

/*
**restore terminal to canonical mode
*/

void		restor_terminal(t_shell *s)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &s->old_t_attr);
}


void		display_prompt(t_shell *s)
{
	char abs_path[PATH_MAX];
	char *cwd;
	char *color;

	(void)s;
	getcwd(abs_path, PATH_MAX);
	cwd = ft_strrchr(abs_path, '/');
	cwd = cwd && cwd + 1 ? cwd + 1 : "";
	color = s->status == 0 ? LIGHT_GREEN : LIGHT_RED;
	ft_printf("%s%s%s", color, cwd, " $> "NO_COLOUR);
}
