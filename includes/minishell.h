/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:07:55 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/05/25 13:34:31 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef enum	s_token
{
	PIPE = 1,
	LESS,
	LESS_LESS,
	GREAT,
	GREAT_GREAT,
}	t_token;

typedef struct	s_lexer
{
	char			*word;
	t_token			token;
	int				index;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

int		lexer_length(t_pile *list);
t_lexer	*lexer_new(char *word, t_token token);
t_lexer	*lexer_last(t_lexer *lst);
void	lexer_add(t_lexer **head, t_list *new);
void	lexer_addback(t_lexer **head, t_list *new);
void	lexer_delone(t_lexer **lst);
void	get_cmds(const char **input);

//functions of libft located in sources/test_functions.c
//must be removed when not necesary
int		ft_strcmp(const char *s1, const char *s2);
char	**ft_split(char const *str, char c);

#endif
