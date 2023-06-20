/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:40:51 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/06/20 18:11:43 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

int	token_handler(char *args, int i, t_lexer *list)
{
	t_token tk;

	tk = check_token(args, i);
	if (tk == LESS_LESS || tk == GREAT_GREAT)
	{
		lexer_addback(&list, lexer_new(NULL, tk));
		return (2);
	}
	else if (tk == PIPE || tk == LESS || tk == GREAT)
	{
		lexer_addback(&list, lexer_new(NULL, tk));
		return (1);
	}
	return (0);
}


