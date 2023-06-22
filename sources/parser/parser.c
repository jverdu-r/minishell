/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 16:35:55 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/06/22 20:21:27 by jverdu-r         ###   ########.fr       */
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

int	arg_count(t_lexer *list)
{
	t_lexer	*tmp;
	int		i;

	tmp = list;
	i = 0;
	while (tmp && tmp->token != PIPE)
	{
		if (tmp->token == 0)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

char	**init_cmd(t_p_toolbox *p_tools)
{
	char	**cmds;
	int		cmd_size;
	int		i;
	t_lexer	*tmp;

	cmd_size = arg_count(p_tools->lexer_list);
	cmds = ft_calloc(cmd_size + 1, sizeof(char *));
	if (!cmds)
		return (NULL);
	tmp = p_tools->lexer_list;
	i = 0;
	while (tmp)
	{
		if (tmp->token == 0)
		{
			cmds[i] = ft_strdup(tmp->str);
			i++;
		}
		tmp = tmp->next;
	}
	return (cmds);
}

int	parser(t_toolbox *tools)
{
	t_sp_cmds	*node;
	t_p_toolbox	p_tools;

	if (tools->lexer_list->token == PIPE)
		return (error_token(tools->lexer_list->token));
	p_tools = init_p_tools(tools);
	sp_cmds_addback(&node, sp_cmds_new(init_cmd(&p_tools)));
	if (!node)
		return (error_msg("syntax error near unexpected token 'newline'"));
	//sp_cmds_show(node); //for testing purposes
	return (0);
}
