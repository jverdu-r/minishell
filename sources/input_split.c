/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:34:22 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/06/07 14:34:42 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	quote_handler(t_lexer **lexer_list, char *input,  int *st_tk, int end_tk)
{
	int		j;

	j = *st_tk + 1;
	while (input[j] != input[*st_tk])
		j++;
	j++;
	lexer_addback(lexer_list, lexer_new(ft_substr(input, *st_tk, j - *st_tk), 0));
	end_tk += j;
	end_tk = end_tk - *st_tk;
	*st_tk = end_tk;
	return (end_tk);
}

int	token_handler(t_lexer **lexer_list, char *input, int i)
{
	if (input[i] == '|')
		lexer_addback(lexer_list, lexer_new(NULL, 1));
	if (input[i] == '<')
	{
		if (input[i + 1] == '<')
		{
			lexer_addback(lexer_list, lexer_new(NULL, 3));
			return (2);
		}
		else
			lexer_addback(lexer_list, lexer_new(NULL, 2));
	}
	if (input[i] == '>')
	{
		if (input[i + 1] == '>')
		{
			lexer_addback(lexer_list, lexer_new(NULL, 5));
			return (2);
		}
		else
			lexer_addback(lexer_list, lexer_new(NULL, 4));
	}
	return (1);
}

void show_lexer(t_lexer	*lexer_list)
{
	t_lexer	*tmp;

	tmp = lexer_list;
	while (tmp)
	{
		if (tmp->word)
			printf("\n%s\n", tmp->word);
		else
			printf("\n%d\n", tmp->token);
		tmp = tmp->next;
	}
/*	while (lexer_list)
	{
		if (lexer_list->word)
			free(lexer_list->word);
		lexer_list = lexer_list->next;
		tmp = lexer_list->prev;
		lexer_list->prev = NULL;
		tmp->next = NULL;
		free(tmp);
	}
	free(lexer_list);*/
}

void	input_filter(char *input)
{
	int		end_tk;
	int		st_tk;
	t_lexer	*lexer;

	end_tk = 0;
	st_tk = 0;
	lexer = NULL;
	while (input[end_tk])
	{
		if (input[end_tk] == '\"' || input[end_tk] == '\'')
			end_tk = quote_handler(&lexer, input, &st_tk, end_tk);
		if (input[end_tk] == '|' || input[end_tk] == '<' || input[end_tk] == '>')
		{
			if (st_tk != end_tk && (input[end_tk] != '|' || input[end_tk] != '<' ||
						input[end_tk] != '>'))
				lexer_addback(&lexer, lexer_new(ft_substr(input, st_tk, end_tk-st_tk), 0));
			end_tk += token_handler(&lexer,input,  end_tk);
			st_tk = end_tk;	
		}
		else
			end_tk++;
	}
	if (end_tk!=st_tk)
		lexer_addback(&lexer, lexer_new(ft_substr(input, st_tk, end_tk-st_tk), 0));
	show_lexer(lexer);
}
