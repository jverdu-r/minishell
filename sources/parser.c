/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:27:39 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/05/26 13:11:57 by jverdu-r         ###   ########.fr       */
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
void	get_cmds(char **input)
{
	int		i;
	int		tk;
	t_lexer	*lexer;
	t_lexer	*tmp;

	lexer = NULL;
	i = 0;
	tk = 0;
	while (input[i])
	{
		tk =token_parser(input[i]);
		if (tk != 0)
			lexer_addback(&lexer, lexer_new(NULL, tk));
		else
			lexer_addback(&lexer, lexer_new(input[i], 0));
		tk = 0;
		i++;
	}
	while (lexer->prev)
		lexer = lexer->prev;
	tmp = lexer;
	while (tmp->next)
	{
		if (tmp->word)
			printf("%s\n", tmp->word);
		else
			printf("%d\n", tmp->token);
		tmp = tmp->next;
	}
	while (lexer->next)
	{
		tmp = lexer->next;
		lexer_delone(&lexer);
		lexer = tmp;
	}
//	else
//		printf("ERROR could not reserve lexer's memory");
	free(input);
}
