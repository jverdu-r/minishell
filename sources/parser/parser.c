/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 16:35:55 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/07/12 11:19:17 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_p_toolbox	init_p_tools(t_toolbox *tools)
{
	t_p_toolbox	p_tools;

	p_tools.lexer_list = tools->lexer_list;
	p_tools.redirections = NULL;
	p_tools.num_redirections = 0;
	p_tools.tools = tools;
	return (p_tools);
}

char	**cmd_get(t_lexer *list)
{
	char	**cmd;
	int		i;
	int		j;
	t_lexer	*aux;

	i = 0;
	aux = list;
	while (aux)
	{
		i++;
		aux = aux->next;
	}
	cmd = ft_calloc(i + 1, sizeof(char *));
	if (!cmd)
		return (NULL);
	j = 0;
	while (j < i)
	{
		if (list->str)
		{
			cmd[j] = ft_strdup(list->str);
			j++;
		}
		list = list->next;
	}
	cmd[j] = NULL;
	printf("\nexit cmd_get\n");
	return (cmd);
}

t_lexer	*get_redir(t_lexer *list)
{
	t_lexer *aux;

	printf("\nentering get_redir\n");
	aux = NULL;
	while (list->token == 0)
		list = list->next;
	if (list != NULL)
	{
		while (list != NULL)
		{
			if (list->token)
				lexer_addback(&aux, lexer_new(NULL, list->token));
			if (list->str)
				lexer_addback(&aux, lexer_new(ft_strdup(list->str), 0));
			list = list->next;
		}
	}
	printf("\nexit get_redir\n");
	return (aux);
}

t_sp_cmds	*cmd_extract(t_lexer *list, t_sp_cmds *node)
{
	t_lexer	*aux;
	t_sp_cmds *aux_node;

	printf("\nentering cmd_extract\n");
	aux = NULL;
	aux_node = ft_calloc(1, sizeof(t_sp_cmds));
	if (!aux_node)
		return (NULL);
	while (list)
	{
		if (list->token == 0)
		{
			lexer_addback(&aux, lexer_new(ft_strdup(list->str), 0));
		}
		if (list->token > 0 && list->token != PIPE)
		{
			aux_node->cmd = cmd_get(aux);
			if (file_checker(list->next->str, '.'))
				aux_node->hd_file_name = ft_strdup(list->next->str);
			aux_node->redirection = get_redir(list);
			sp_cmds_addback(&node, aux_node);
		}
		list = list->next;
	}
	printf("\nexit cmd_extract\n");
	return (node);
}

int	parser(t_toolbox *tools)
{
	t_sp_cmds	*node;
	t_p_toolbox	p_tools;

	if (tools->lexer_list->token == PIPE)
		return (error_token(tools->lexer_list->token));
	node = NULL;
	p_tools = init_p_tools(tools);
	node = cmd_extract(p_tools.lexer_list, node);
	if (!node)
		return (error_msg("syntax error near unexpected token 'newline'\n"));
	/*printf("\nnode->redirection:\n");
	lexer_show(node->redirection);
	printf("\nnode->hd_filename: %s\n", node->hd_file_name);*/
	sp_cmds_show(node); //for testing purposes
	return (0);
}
