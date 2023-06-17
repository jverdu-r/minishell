/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sp_cmds_utils_one.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 13:31:45 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/06/17 13:52:22 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_sp_cmds	*sp_cmds_new(char	**cmd)
{
	t_sp_cmds	*new;

	new = malloc(sizeof(t_sp_cmds));
	if (!new)
		return (NULL);
	new->cmd = cmd;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_sp_cmds	*sp_cmds_last(t_sp_cmds *list)
{
	t_sp_cmds	tmp;

	if (!list)
		return (NULL);
	tmp = list;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	sp_cmds_delone(t_sp_cmds **list)
{
	if (list && *list)
	{
		if (sp_cmds_length(*list) > 1)
		{
			list[0] = list[0]->next;
			free(list[0]->prev);
			list[0]->prev = NULL;
		}
		else
		{
			free(list[0]);
			lst[0] = NULL;
		}
	}
}

void	sp_cmds_add(t_sp_cmds **head, t_sp_cmds *new)
{
	t_sp_cmds	*tmp;
	
	tmp = *head;
	if (*head == NULL)
		*head = new;
	else
	{
		new->next = tmp;
		tmp->prev = new;
		tmp = new;
		*head = tmp;
	}
}

void	sp_cmds_addback(t_sp_cmds **head, t_sp_cmds *new)
{
	t_sp_cmds	*tmp;

	tmp = *head;
	if (*head == NULL)
		*head = new;
	else
	{
		while (tmp)
		{
			if (!tmp->next)
			{
				tmp->next = new;
				new->prev = tmp;
				tmp = new;
			}
			tmp = tmp->next;
		}
	}
}
