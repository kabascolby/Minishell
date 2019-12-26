/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index_tables.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 10:53:47 by lkaba             #+#    #+#             */
/*   Updated: 2019/12/25 20:54:08 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	index_table_init(char *table)
{
	char *tab;

	tab = (char[UINT8_MAX])
	{
		['$'] = 1,
		['#'] = 2,
		[';'] = 6,
		[34] = 3,
		[39] = 3,
		[92] = 4,
		[' '] = 5,
		['\t'] = 5,
		['\f'] = 5,
		['\n'] = 5,
		['\r'] = 5,
		['~'] = 7
	};
	table = ft_memcpy(table, tab, UINT8_MAX);
}

void	index_table_dquote_init(char *table)
{
	table[39] = 0;
	table[';'] = 0;
	table['~'] = 0;
	table[' '] = 0;
	table['#'] = 0;
	table['\t'] = 0;
	table['\f'] = 0;
	table['\n'] = 0;
	table['\r'] = 0;
}

void	index_table_quote_init(char *table)
{
	table[34] = 0;
	table[92] = 0;
	table['$'] = 0;
	table['#'] = 0;
	table[';'] = 0;
	table['~'] = 0;
	table[' '] = 0;
	table['\t'] = 0;
	table['\f'] = 0;
	table['\n'] = 0;
	table['\r'] = 0;
}
