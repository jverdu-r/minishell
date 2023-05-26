/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:45:56 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/05/26 13:07:26 by jverdu-r         ###   ########.fr       */
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

t_lexer	*lexer_new(char *word, t_token token)
{
	t_lexer	*new;

	new = malloc(sizeof(t_lexer));
	if (!new)
		return (NULL);
	new->word = word;
	new->token = token;
	new->index = 0;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_lexer *lexer_last(t_lexer *lst)
{
	t_lexer	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

void	lexer_delone(t_lexer **lst)
{
	if (lst && *lst)
	{
		if (lexer_length(*lst) > 1)
		{
			lst[0] = lst[0]->next;
			free(lst[0]->prev);
			lst[0]->prev = NULL;
		}
		else
		{
			free(lst[0]);
			lst[0] = NULL;
		}
	}
}

void	lexer_add(t_lexer **head, t_lexer *new)
{
	t_lexer	*tmp;

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

void	lexer_addback(t_lexer **head, t_lexer *new)
{
	t_lexer	*tmp;

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
