/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 16:35:55 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/06/27 10:54:42 by jverdu-r         ###   ########.fr       */
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

char	**init_cmd(t_p_toolbox *p_tools) //reescribir para adaptar a cmd_extract
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
	cmds[i] = 0;
	return (cmds);
}

t_sp_cmds	*cmd_extract(t_toolbox *tools)
{
	t_sp_cmds	*node;
	int			a;
	int			b;
	int			count;

	a = 0;
	b = 0;
	node = NULL;
	while (tools->lexer_list[b])
	{
		if (tools->lexer_list[b]->token == PIPE)
		{
			count = arg_count(tools->lexer_list[a]);
			init_cmd(node, a, b, count);
			a = b + 1;
		}
		b++;
	}
	//hacer que recoorra con dos indices para que el arg count 
	//y el init_cmd rrecorran de 'a' a 'b'
	return (node)
}

int	parser(t_toolbox *tools)
{
	t_sp_cmds	*node;
	t_p_toolbox	p_tools;

	if (tools->lexer_list->token == PIPE)
		return (error_token(tools->lexer_list->token));
	p_tools = init_p_tools(tools);
	node = cmd_extract(tools);
	sp_cmds_addback(&node, sp_cmds_new(init_cmd(&p_tools)));
	if (!node)
		return (error_msg("syntax error near unexpected token 'newline'"));
	sp_cmds_show(node); //for testing purposes
	return (0);
}
