/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:43:37 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/06/09 12:46:19 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	token_parser(char	*input)
{
	if (ft_strcmp(input, "|") == 0)
		return (1);
	else if (ft_strcmp(input, "<") == 0)
		return (2);
	else if (ft_strcmp(input, "<<") == 0)
		return (3);
	else if (ft_strcmp(input, ">") == 0)
		return (4);
	else if (ft_strcmp(input, ">>") == 0)
		return (5);
	else
		return (0);
}

void	show_split(char **split)
{
	int	x;

	x = 0;
	while (split[x])
	{
		printf("%s ", split[x]);
		x++;
	}
	printf("\n");
}
void	get_cmds(t_lexer *lex)
{
	t_cmds	*cmds;

	cmds = NULL;
	while (lex)
	{
		if (lex->word)
		{
			parser_addback(&cmds, parser_new(ft_split(lex->word, ' '), 0));
		}
		else if (lex->token)
			parser_addback(&cmds, parser_new(NULL, lex->token));
		lex = lex->next;
	}
	l_free(lex);
	show_parser(cmds);
}
