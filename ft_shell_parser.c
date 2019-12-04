/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 19:45:25 by lkaba             #+#    #+#             */
/*   Updated: 2019/12/03 10:15:34 by lkaba            ###   ########.fr       */
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

char	*token_handler(t_shell *s, char *line, const char *filter, char **save)
{
	char *ret;
	// char *temp;
	(void)s; //remove it later
	int t;

	t = ft_strcspn(line, filter);

	if (line[t] == ' ')
	{
		ret = ft_strtok_r(line, " ", save);
		return (ret);
	}
	else if (line[t] == (char)34)
	{
		// ft_printf("%d\n", t);
		ret = ft_strtok_r(line, "\"", save);
		return (ret);
	}

	return (ft_strtok_r(line, filter, save));
}

/*
**Using coumpound literral to create a char array and
**retuning a value to a pointer
*/


void split_line(t_shell *s, t_vector *v)
{
	char *ptr;

	s->filters = (char[]){FILTERS};
	while ((ptr = token_handler(s, s->dstr->buff, s->filters, &s->dstr->buff)))
		v->vector_add(v, ptr);
}


/* char	**split_line(t_shell *s)
{
	char		**tokens;
	char		**tmp;
	uint16_t	bufsize;
	uint16_t	i;
	s->filters = (char[]){FILTERS};
	bufsize = TOK_BUFSIZE;
	tokens = MALLOC(bufsize * sizeof(char *));
	i = -1;
	while ((tokens[++i] = token_handler(s, s->dstr->buff, s->filters, &s->dstr->buff)) != 0)
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
} */



// int get_token(char *s, const char *filter, char **save_ptr)
// {
// 	if(s == NULL)
// 		s = *save_ptr;
// 	if(*s == '\0')
// 	{
// 		*save_ptr = s;
// 		return (NULL);
// 	}
// 	return ft_strspn(line, filter);
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
