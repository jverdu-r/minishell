/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sp_cmds_utils_two.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 13:52:34 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/06/27 10:11:18 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	sp_cmds_length(t_sp_cmds *list)
{
	int			i;
	t_sp_cmds	*aux;

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

void	sp_cmds_free(t_sp_cmds *list)
{
	int	i;

	i = 0;
	if (list)
	{
		while (list->next)
		{
			if (list->cmd)
				free_arr(list->cmd);
			list = list->next;
			free(list->prev);
		}
		if (!list->next)
		{
			if (list->cmd)
				free_arr(list->cmd);

		}
		free(list->cmd);
		free(list);
	}
}

void	sp_cmds_show(t_sp_cmds *list) //only for testing
{
	t_sp_cmds	*tmp;
	int			i;
	int			a;

	tmp = list;
	printf("\n");
	a = 0;
	while (tmp)
	{
		if (tmp->cmd)
		{
			a++;
			printf("\n node %d:\n", a);
			i = 0;
			while (tmp->cmd[i])
			{
				printf("%s\n", tmp->cmd[i]);
				i++;
			}
		}
		tmp = tmp->next;
	}
	sp_cmds_free(list);
}
