/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 08:11:35 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/07/07 09:52:02 by jverdu-r         ###   ########.fr       */
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

void	handle_parse_redirections(t_lexer *list, t_sp_cmds *node)
{
	t_lexer	*redir;

	redir = NULL;
	(void)node;
	while (list->token != 0 && list)
		list = list->next;
	while (list)
	{
		if (list->token > 0)
		{
			printf("\n--list->token: %d--\n", list->token);
			lexer_addback(&redir, lexer_new(NULL, list->token));
		}
		else
		{
			printf("\n--list->str: %s--\n", list->str);
			if (file_checker(list->str, '.') == 1)
			{
				printf("\n--asingning hd_file_name--\n");
				//node->hd_file_name = list->str;
				//printf("\n--node->hd_file_name: %s--\n", node->hd_file_name);
			}
			lexer_addback(&redir, lexer_new(list->str, 0));
		}
		list = list->next;
	}
	printf("\n-- redir list --\n");
	lexer_show(redir);
	//printf("\n--node->hd_file_name: %s--\n", node->hd_file_name);
	//node->redirection = redir;
	//lexer_show(node->redirection);
}

