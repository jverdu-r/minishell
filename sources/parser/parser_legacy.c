/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 16:35:55 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/07/24 10:06:00 by jverdu-r         ###   ########.fr       */
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

char	**get_cmd(t_lexer *list)
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
	return (cmd);
}

t_lexer	*get_redir(t_lexer *list)
{
	t_lexer *aux;

	if (!list)
		return (NULL);
	lexer_show(list);
	aux = NULL;
	while (list->token == 0)
		list = list->next;
	if (list != NULL)
	{
		while (list != NULL)
		{
			if (list->token == PIPE)
				return (aux);
			if (list->token)
				lexer_addback(&aux, lexer_new(NULL, list->token));
			if (list->str)
				lexer_addback(&aux, lexer_new(ft_strdup(list->str), 0));
			list = list->next;
		}
	}
	return (aux);
}

t_sp_cmds	*cmd_extract(t_lexer *list, t_sp_cmds *node)
{
	t_lexer		*aux;
	t_sp_cmds	*aux_node;
	char		**cmd;

	aux = NULL;
	aux_node = ft_calloc(1, sizeof(t_sp_cmds));
	if (!aux_node)
		return (NULL);
	while (list)
	{

	}
	while (list && list->token == 0)
	{
		if (list->token == 0)
			lexer_addback(&aux, lexer_new(ft_strdup(list->str), 0));
		list = list->next;
	}
	aux_node->cmd = get_cmd(aux);
	if (list)
	{
		if (list->token > 0 && list->token != PIPE)
			list = redirection_handler(list, &node, aux_node);
		//printf("\nshowing the rest of the list\n");
		//lexer_show(list);
		if (list && list->token  == PIPE)
			sp_cmds_addback(&node, pipe_handler(list));
	}
	else
		sp_cmds_addback(&node, aux_node);
	printf("\nnode added\n");
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
	printf("\nnode list created\n");
	if (!node)
		return (error_msg("syntax error near unexpected token 'newline'\n"));
	sp_cmds_show(node); //for testing purposes
	return (0);
}
