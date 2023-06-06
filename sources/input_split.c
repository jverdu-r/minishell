/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:34:22 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/06/06 19:00:56 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_white_space(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

int	quote_handler(t_lexer **lexer_list, char *input,  int i)
{
	int		j;

	j = i + 1;
	while (input[j] != input[i])
		j++;
	lexer_addback(lexer_list, lexer_new(ft_substr(input, i, j - i), 0));
	return (j);
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

	while (lexer_list)
	{
		if (lexer_list->word)
		{
			printf("\n%s\n", lexer_list->word);
			// free(lexer_list->word);
		}
		else
			printf("\n%d\n", lexer_list->token);
		lexer_list = lexer_list->next;
		// free(lexer_list->prev);
	}
	//free(lexer_list);
}

void	input_filter(char	*input)
{
	int		end_token;
	int		start_token;
	t_lexer	*lexer_list;

	end_token = 0;
	start_token = 0;
	lexer_list = NULL;
	while (input[end_token])
	{
		if (input[end_token] == '\"' || input[end_token] == '\'')
		{
			end_token += quote_handler(&lexer_list, input, start_token);;
			start_token = end_token;
		}
		if (input[end_token] == '|' || input[end_token] == '<' || input[end_token] == '>')
		{
			if (start_token != end_token)
				lexer_addback(&lexer_list, lexer_new(ft_substr(input, start_token, end_token-start_token), 0)); 
			end_token += token_handler(&lexer_list,input,  end_token);
			start_token = end_token;
		
		}
		else
			end_token++;
	}
	if (end_token!=start_token)
		lexer_addback(&lexer_list, lexer_new(ft_substr(input, start_token, end_token-start_token), 0));
	show_lexer(lexer_list);
}

