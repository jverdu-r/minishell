/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:34:22 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/06/08 10:41:20 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	quote_handler(t_lexer **lexer, char *input, int *st_tk, int end_tk)
{
	int		j;

	j = *st_tk + 1;
	while ((input[j] != input[*st_tk]) && input[j])
		j++;
	if (input[j] == 0)
		return (end_tk);
	j++;
	l_addback(lexer, l_new(ft_substr(input, *st_tk, j - *st_tk), 0));
	end_tk += j;
	end_tk = end_tk - *st_tk;
	*st_tk = end_tk;
	return (end_tk);
}

int	token_handler(t_lexer **lexer_list, char *input, int i)
{
	if (input[i] == '|')
		l_addback(lexer_list, l_new(NULL, 1));
	if (input[i] == '<')
	{
		if (input[i + 1] == '<')
		{
			l_addback(lexer_list, l_new(NULL, 3));
			return (2);
		}
		else
			l_addback(lexer_list, l_new(NULL, 2));
	}
	if (input[i] == '>')
	{
		if (input[i + 1] == '>')
		{
			l_addback(lexer_list, l_new(NULL, 5));
			return (2);
		}
		else
			l_addback(lexer_list, l_new(NULL, 4));
	}
	return (1);
}

void	input_filter(char *ipt)
{
	int		ed_tk;
	int		st_tk;
	t_lexer	*lex;

	ed_tk = 0;
	st_tk = 0;
	lex = NULL;
	while (ipt[ed_tk])
	{
		if (ipt[ed_tk] == '\"' || ipt[ed_tk] == '\'')
			ed_tk = quote_handler(&lex, ipt, &st_tk, ed_tk);
		if (ipt[ed_tk] == '|' || ipt[ed_tk] == '<' || ipt[ed_tk] == '>')
		{
			if (st_tk != ed_tk && (ipt[ed_tk] != '|' || ipt[ed_tk] != '<' \
				|| ipt[ed_tk] != '>'))
				l_addback(&lex, l_new(ft_substr(ipt, st_tk, ed_tk - st_tk), 0));
			ed_tk += token_handler(&lex, ipt, ed_tk);
			st_tk = ed_tk;
		}
		else
			ed_tk++;
	}
	if (ed_tk != st_tk)
		l_addback(&lex, l_new(ft_substr(ipt, st_tk, ed_tk - st_tk), 0));
	show_lexer(lex);
}
