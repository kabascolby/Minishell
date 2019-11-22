/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 19:45:25 by lkaba             #+#    #+#             */
/*   Updated: 2019/11/21 11:07:52 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**Parsing the environement array to copy in my hashtable all the variables.
**Calling ft_strtok twice to split each line by equal sign
*/

void	parse_env(t_shell *s, char **env)
{
	char	*key;
	char	*value;
	t_entry	*shell_path;

	while (*++env)
	{
		key = ft_strdup(ft_strtok_r(*env, "=", env));
		value = ft_strdup(ft_strtok_r(*env, "=", env));
		s->ht->insert(&s->ht, key, value);
	}

	if (s->ht && (shell_path = s->ht->get_entry(s->ht, "SHELL")))
		s->ht->update(&s->ht, shell_path->key, "./minishell");
}

char	*token_handler(char *s, const char *filter, char **save)
{
	char *ret;
	int t;

	t = ft_strcspn(s, filter);

	if (s[t] == ' ')
	{
		ret = ft_strtok_r(s, " ", save);
		if (*ret == '#')
		{
			*save = NULL;
			return (NULL);
		}
		return (ret);
	}
	else if (s[t] == (char)34)
	{
		ret = ft_strtok_r(s, "\"", save);
		if (*ret == '#')
		{
			*save = NULL;
			return (NULL);
		}
		return (ret);
	}
	else if (s[t] == '$')
	{
		if(s[t + 1] == '$')
			ft_printf("%d", getpid());
	}
	else if (s[t] == (char)35)
	{
		*save = NULL;
		s[t] = '\0';
		return (NULL);
	}
	return ft_strtok_r(s, filter, save);
}

char	**split_line(char *line)
{
	char		**tokens;
	char		**tmp;
	uint16_t	bufsize;
	uint16_t	i;
	char filters[] = {FILTERS};

	bufsize = TOK_BUFSIZE;
	tokens = MALLOC(bufsize * sizeof(char *));
	i = -1;
	while ((tokens[++i] = token_handler(line, filters, &line)) != NULL)
	{
		if (i + 1 >= bufsize)
		{
			tmp = MALLOC((bufsize + TOK_BUFSIZE) * sizeof(char *));
			ft_memcpy((char **)tmp, (char **)tokens, bufsize * sizeof(char *));
			bufsize += TOK_BUFSIZE;
			FREE(tokens);
			tokens = tmp;
			tmp = NULL;
		}
	}
	tokens[i] = NULL;
	return (tokens);
}



// int get_token(char *s, const char *filter, char **save_ptr)
// {
// 	if(s == NULL)
// 		s = *save_ptr;
// 	if(*s == '\0')
// 	{
// 		*save_ptr = s;
// 		return (NULL);
// 	}
// 	return ft_strspn(s, filter);
// }

// t_command	*command_handler(char *buff, t_command **h)
// {
// 	t_command *new_command;
// 	t_command *tmp;
// 	if (!buff || !*buff)
// 		return (h);
// 	new_command = MALLOC(sizeof(t_command));
// 	*h = new_command;
// 	while()

// }

// char *tokenizer()

// else
// 	{
// 		tmp = *h;
// 		while(tmp && tmp->next)
// 			tmp = tmp->next;
// 		tmp->next = new_command;
// 	}

//todo write a malloc pointer tracker will mae your life easier
