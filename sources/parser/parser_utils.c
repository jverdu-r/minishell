/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 08:11:35 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/07/04 09:59:20 by jverdu-r         ###   ########.fr       */
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

void	handle_parse_redirections(t_lexer *list, t_sp_cmds *node)
{
	t_lexer	*redir;

	redir = NULL;
	printf("\n-- redir list --\n");
	lexer_show(list);
	/*while (list->token != 0 && list)
	{
		if (list->token > 0)
			break;
		list = list->next;
	}
	while (list)
	{
		if (list->token > 0)
			lexer_addback(&redir, lexer_new(NULL, list->token));
		else
		{
			if (ft_strnstr(list->str, ".", ft_strlen(list->str)))
				node->hd_file_name = ft_strdup(list->str);
			lexer_addback(&redir, lexer_new(list->str, 0));
		}
		list = list->next;
	}*/
	node->redirection = redir;
}

