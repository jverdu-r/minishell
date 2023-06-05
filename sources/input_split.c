/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:34:22 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/06/05 16:42:05 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	show_list(t_lexer *lexer_list)
{
	//funcion de comprobacion
	t_lexer	*tmp;

	tmp = lexer_list;
	while (tmp)
	{
		if (tmp->word)
			printf("\n%s index: %d\n", tmp->word, tmp->index);
		else if (tmp->token > 0)
			printf("\ntoken: %d index: %d\n", tmp->token, tmp->index);
		else
			printf("lexer is empty");
		tmp = tmp->next;
	}
	while (lexer_list)
	{
		if (lexer_list->word)
			free(lexer_list->word);
		lexer_list = lexer_list->next;
		free(lexer_list->prev);
	}
	free(lexer_list);
}

int	is_white_space(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

int	quote_handler(t_lexer *lexer_list, char *input,  int i)
{
	int		j;

	j = i + 1;
	while (input[j] != input[i])
		j++;
	lexer_addback(&lexer_list, lexer_new(ft_substr(input, i, j), 0));
	return (j);
}

int	token_handler(t_lexer *lexer_list, char *input, int i)
{
	if (input[i] == 124)
		lexer_addback(&lexer_list, lexer_new(NULL, 1));
	if (input[i] == 60)
	{
		if (input[i + 1] == 60)
		{
			lexer_addback(&lexer_list, lexer_new(NULL, 3));
			return (2);
		}
		else
			lexer_addback(&lexer_list, lexer_new(NULL, 2));
	}
	if (input[i] == 62)
	{
		if (input[i + 1] == 62)
		{
			lexer_addback(&lexer_list, lexer_new(NULL, 5));
			return (2);
		}
		else
			lexer_addback(&lexer_list, lexer_new(NULL, 4));
	}
	return (1);
}

void	input_filter(char	*input)
{
	int		i;
	int		j;
	t_lexer	*lexer_list;

	i = 0;
	printf("\ndatos : %s", input);
	while (input[i])
	{
		j = i;
		if (input[i] == 34 || input[i] == 39)
			i += quote_handler(lexer_list,input,  i);
		else if (input[i] == 124 || input[i] == 60 || input[i] == 62)
			i += token_handler(lexer_list,input,  i);
		else
		{
			j = i;
			while (!is_white_space(input[i]) && input[i])
				i++;
		}
		if (j != i)
			lexer_addback(&lexer_list, lexer_new(ft_substr(input, j, i), 0));
		i++;
		printf("\n%d", i);
	}
	show_list(lexer_list);
}
