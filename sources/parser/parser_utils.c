/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 08:11:35 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/07/24 10:40:49 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*void	lex_list_free(t_lexer *list)
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
}*/

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

/*t_sp_cmds	*handle_parse_redirections(t_lexer *list)
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

t_lexer	*redirection_handler(t_lexer *list, t_sp_cmds **node,
		t_sp_cmds *aux_node)
{
	if (list->token > 0 && list->token != PIPE)
		aux_node->hd_file_name = ft_strdup(list->next->str);
	aux_node->redirection = get_redir(list);
	sp_cmds_addback(node, aux_node);
	while (list && list->token != PIPE)
		list = list->next;
	return (list);
}

t_sp_cmds	*pipe_handler(t_lexer *list)
{
	t_sp_cmds	*pipe_node;

	pipe_node = ft_calloc(1, sizeof(t_sp_cmds));
	pipe_node->cmd = get_cmd(list);
	list = list->next;
	while (list && list->next->token != 0)
		list = list->next;
	printf("\n entrando en get_redir del pipe_node\n");
	pipe_node->redirection = get_redir(list);
	return (pipe_node);
}*/
