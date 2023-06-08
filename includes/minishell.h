/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:07:55 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/06/08 15:34:08 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h> //pending signals implementation
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

typedef struct	s_cmds
{
	char			**cmd;
	//	builtins site for  include builtins
	int				redirs;
	char			*file_name;
	t_lexer			*redirections;
	struct s_cmds	*next;
	struct s_cmds	*prev;
}	t_cmds;

// Signal functions
void	signals_workout(void);

// Parser functions
int		parser_length(t_cmds *list);
t_cmds	*parser_new(t_lexer *lexer);
t_cmds	*parser_last(t_cmds *lst);
void	parser_add(t_cmds **head, t_cmds *new);
void	parser_addback(t_cmds **head, t_cmds *new);
void	parser_delone(t_cmds **lst);

// Lexer functions
int		l_length(t_lexer *list);
t_lexer	*l_new(char *word, t_token token);
t_lexer	*l_last(t_lexer *lst);
void	l_add(t_lexer **head, t_lexer *new);
void	l_addback(t_lexer **head, t_lexer *new);
void	l_delone(t_lexer **lst);
void	show_lexer(t_lexer *lexer_list);

// Other functions
void	input_filter(char *input);

// functions of libft located in sources/test_functions.c
// must be removed when not necesary
int		ft_strcmp(const char *s1, const char *s2);
char	**ft_split(const char *s, char c);
char	*ft_substr(const char	*s, unsigned int start, size_t len);

#endif
