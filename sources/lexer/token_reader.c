/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_reader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:46:24 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/06/19 19:51:10 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_white_space(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' ||
			c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

check_token(char tk)
{
	if (tk == '|' || '<' || '>')
		return (tk);
	return (NULL);
}

int	token_reader(t_toolbox *tools)
{
	int	tk;
	int	i;

	i = 0;
	while (tools->args[i])
	{
		if (is_white_space(tools->args[i]))
				i++;
		if (check_token(tools->args[i]))
			j = handle_token(tools->args, i, &tools->lexer_list);
		i++;
	}
	return (1);
}
