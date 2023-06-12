/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:06:01 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/06/12 10:53:59 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_lexer *lst_last(t_list *lst)
{
	t_lexer	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while (tmp->next != NULL)
		tmp = tmp = tmp->next;
	return (tmp);
}

void	lst_lexer_delone(t_lexer **lst, void (*del)(void *))
{
	if (lst != NULL)
	{
		del(lst->word);
		del(lst.token);
		del(lst.index);
		free(lst);
	}
}

void	lst_lex_addback(t_lexer **lst, t_lexer *new)
{
	t_lexer	*tmp;

	if (lst)
	{
		if (*lst == NULL)
		{
			*lst = new;
			new.index = 0;
		}
		else
		{
			tmp = lst_last_lexer(*(lst));
			tmp->next = new;
			new.index = tmp.index + 1;
		}
	}
}
