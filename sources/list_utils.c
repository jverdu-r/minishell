/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:06:25 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/06/09 12:15:09 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	l_length(t_lexer *list)
{
	int		i;
	t_lexer	*aux;

	if (!list)
		return (0);
	aux = list;
	i = 0;
	while (aux)
	{
		aux = aux->next;
		i++;
	}
	return (i);
}

void	l_free(t_lexer *lexer)
{
	if (lexer)
	{
		while (lexer->next)
		{
			if (lexer->word)
				free(lexer->word);
			lexer =  lexer->next;
			free(lexer->prev);
		}
		if (!lexer->next)
		{
			if (lexer->word)
				free(lexer->word);
			free(lexer);
		}
	}
}

void show_lexer(t_lexer	*lexer_list)
{
	t_lexer	*tmp;

	tmp = lexer_list;
	while (tmp)
	{
		if (tmp->word)
			printf("\n%s\n", tmp->word);
		else if (tmp->token > 0)
			printf("\n%d\n", tmp->token);
		tmp = tmp->next;
	}
	l_free(lexer_list);
}


int	parser_length(t_cmds *list)
{
	int		i;
	t_cmds	*aux;

	if (!list)
		return (0);
	aux = list;
	i = 0;
	while (aux)
	{
		aux = aux->next;
		i++;
	}
	return (i);
}

void	p_free(t_cmds *cmds)
{
	int x;

	if (cmds)
	{
		while (cmds->next)
		{
			if (cmds->cmd)
			{
				x = 0;
				while (cmds->cmd[x])
				{
					free(cmds->cmd[x]);
					x++;
				}
				free(cmds->cmd);
			}
			cmds =  cmds->next;
			free(cmds->prev);
		}
		if (!cmds->next)
		{
			if (cmds->cmd)
			{
				x = 0;
				while (cmds->cmd[x])
				{
					free(cmds->cmd[x]);
					x++;
				}
			}
			free(cmds);
		}
	}
}


void show_parser(t_cmds	*cmds)
{
	t_cmds	*tmp;
	int		x;

	tmp = cmds;
	printf("\n");
	while (tmp)
	{
		if (tmp->cmd)
		{
			x = 0;
			while (tmp->cmd[x])
			{
				printf("%s ", tmp->cmd[x]);
				x++;
			}
		}
		else if (tmp->redirs > 0)
			printf("%d ", tmp->redirs);
		tmp = tmp->next;
	}
	printf("\n");
	p_free(cmds);
}
