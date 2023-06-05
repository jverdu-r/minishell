/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:06:25 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/06/01 15:18:04 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	lexer_length(t_lexer *list)
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
