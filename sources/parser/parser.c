/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 16:35:55 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/07/07 10:41:44 by jverdu-r         ###   ########.fr       */
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
	//t_lexer	*tmp;
	int		i;

	//tmp = list;
	i = 0;
	while (list)
	{
		if (list->token == 0)
			i++;
		list = list->next;
	}
	return (i);
}

char	**init_cmd(int count, t_lexer *list)
{
	char	**cmds;
	int		i;
	t_lexer	*tmp;

	cmds = ft_calloc(count + 1, sizeof(char *));
	if (cmds)
	{
		i = 0;
		tmp = list;
		while (tmp)
		{
			if (tmp->str)
				cmds[i] = ft_strdup(tmp->str);
			i++;
			tmp = tmp->next;
		}
		cmds[i] = 0;
	}
	return (cmds);
}

t_sp_cmds	*cmd_extract(t_p_toolbox *p_tools, t_sp_cmds *node)
{
	t_lexer		*lex_list;
	int			count;
	int			trig;

	lex_list = NULL;
	trig = 0;
	while (p_tools->lexer_list)
	{
		if (p_tools->lexer_list->token != PIPE)
		{
			lexer_addback(&lex_list, lexer_new(p_tools->lexer_list->str,
						p_tools->lexer_list->token));
		}
		if (p_tools->lexer_list->token == PIPE)
		{
			printf("\n--entering redirections--\n");
			handle_parse_redirections(lex_list, node);
			count = arg_count(lex_list);
			sp_cmds_addback(&node, sp_cmds_new(init_cmd(count, lex_list)));
			while (lex_list)
				lex_list = lex_list->next;
			trig = 0;
		}
		p_tools->lexer_list = p_tools->lexer_list->next;
	}
	printf("\n--entering redirections out while--\n");
	handle_parse_redirections(lex_list, node);
	count = arg_count(lex_list);
	sp_cmds_addback(&node, sp_cmds_new(init_cmd(count, lex_list)));
	lex_list_free(lex_list);
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
	node = cmd_extract(&p_tools, node);
	if (!node)
		return (error_msg("syntax error near unexpected token 'newline'\n"));
	sp_cmds_show(node); //for testing purposes
	return (0);
}
