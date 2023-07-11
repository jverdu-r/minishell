/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 08:11:35 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/07/11 09:36:16 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	lex_list_free(t_lexer *list)
{
	if (list)
	{
		while (list->prev)
			list = list->prev;
		while (list->next)
		{
			list = list->next;
			free(list->prev);
		}
		free(list);
	}
}

int	file_checker(char	*str, char c)
{
	int	i;

	if (str)
	{
		i = 0;
		while (str[i])
		{
			if (str[i] == c)
				return (1);
			i++;
		}
	}
	return (0);
}

t_sp_cmds	*handle_parse_redirections(t_lexer *list)
{
	t_lexer		*redir;
	t_sp_cmds	*node;

	redir = NULL;
	node = ft_calloc(1, sizeof(t_sp_cmds));
	if (!node)
		return (NULL);
	while (list->prev)
		list = list->prev;
	while (list->token != 0 && list)
		list = list->next;
	while (list)
	{
		if (list->token > 0)
			lexer_addback(&redir, lexer_new(NULL, list->token));
		else
		{
			if (file_checker(list->str, '.') == 1)
				node->hd_file_name = list->str;
			lexer_addback(&redir, lexer_new(list->str, 0));
		}
		list = list->next;
	}
	node->redirection = redir;
	return (node);
}

