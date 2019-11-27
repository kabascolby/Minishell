/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listenner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 01:18:17 by lkaba             #+#    #+#             */
/*   Updated: 2019/11/25 12:27:19 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	nothing(int num)
{
	UNUSED(num);
	write(1, "nothing\n", 8);
}

static char	*auto_complete_handler(void)
{
	ft_putstr("everything gonna be alright");
	return (NULL);
}

static void	create_process(t_shell *s)
{
	static char *path;

	s->proc->id = getpid();
	path = ft_join_args("/", _PATH_BSHELL, *s->proc->tokens, NULL);
	if (-1 == (s->proc->status =
	execve(path, s->proc->tokens, get_table(s->ht))))
		ft_errexit(*s->proc->tokens, "invalide commmad", NULL, 0);
		// ft_putendl("invalide commmad");
	FREE(path);
	exit(0);
}

void	*arrow_keys_handler(int str_size, ssize_t (*read_fptr)(int fd,
void *s, size_t len))
{
	char		c;
	static	int	pos;

	read_fptr(STDIN_FILENO, &c, 1);
	read_fptr(STDIN_FILENO, &c, 1);
	if (str_size > 0)
	{
		c == 'D' && pos >= 0 && str_size >= pos ?
		write(1, "\033[D", 4) && ++pos : 0;
		c == 'C' && pos > 0 ? write(1, "\033[C", 4) && --pos : 0;
		// ft_debug_output("/dev/ttys002", ft_itoa(pos), ft_putendl_fd);
	}
	return (NULL);
}

static t_bool	is_quote_balanced(char *s)
{
	uint16_t		num_quotes;
	static uint16_t	i;

	num_quotes = 0;
	i = -1;
	if (!s)
		return (true);
	while (s[++i])
		if (s[i] == '\"')
		{
			if (i && s[i - 1] == '\\')
				continue ;
			num_quotes++;
		}
	return (EVEN(num_quotes));
}

static int16_t	read_stdin(t_shell *s)
{
	ssize_t	i;
	char	c;

	i = -1;
	s->line = s->mt->track(&s->mt, ft_strnew(1024));
	while ((read(STDIN_FILENO, &c, 1)) > 0)
	{
		if (c == 27 && arrow_keys_handler(i, read))
			continue;
		if (c == '\n')
		{
			if (i >= 0 && !is_quote_balanced(s->line))
			{
				write(1, "\ndquote> ", 9);
				s->line[++i] = '\n';
				continue;
			}
			if (i >= 0 && s->line[i] == '\\' && write(1, "\n> ", 2))
			{
				s->line[i--] = '\0';
				continue;
			}
			break ;
		}
		else if (i >= 0 && s->old_t_attr.c_cc[VERASE] == c)
		{
			write(STDOUT_FILENO, "\b \b", 3);
			s->line[i--] = '\0';
		}
		else if (c == '\t')
			auto_complete_handler();
		else if (ft_isprint(c) && write(1, &c, 1))
			s->line[++i] = c;
		// printf("i = %zd | c = %c val = %d\n", i, c, c == 0x7f);
	}
	return true;
}

void	stdin_listenner(t_shell *s)
{
	t_command	proc;
	int8_t		idx;
	int			p;

	ft_bzero((t_command *)&proc, sizeof(t_command));
	s->proc = &proc;
	PROMPT;
	if(read_stdin(s))
	{
		printf("\nline----------->%s|\n", s->line);
		proc.tokens = split_line(s);
		idx = get_index(s, proc.tokens[0], TOKENS);
		if (idx >= 0 && idx < s->fptr_len)
			g_fptr[idx](s, proc.tokens + 1);
		else if (0 == (p = fork()) && proc.tokens[0])
			create_process(s);

		wait(&p);
		s->parent_id = getpid();
		stdin_listenner(s);
	}
}

// TODO
//check if the charactere has balanced quotes
//if yes point to the specific filter
//
// ft_printf("_____child_____________%d___%d\n", getpid(), p);
// ft_printf("________________parent________%d___%d\n", getpid(), p);
