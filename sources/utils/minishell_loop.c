/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 12:14:37 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/07/24 09:27:46 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	tools_reload(t_toolbox *tools)
{
	lexer_free(tools->lexer_list);
	free(tools->args);
	tools->args = NULL;
	tools->sp_cmds = NULL;
	tools->lexer_list = NULL;
}

int	tools_load(t_toolbox *tools)
{
	tools->sp_cmds = NULL;
	tools->lexer_list = NULL;
	return (1);
}

int	exit_code(void)
{
	rl_clear_history();
	printf("\nEXIT\n");
	exit(0);
}

int	minishell_loop(t_toolbox *tools)
{
	char	*input;

	while (1)
	{
		signals_workout();
		tools->args = readline("minishell>");
		input = ft_strtrim(tools->args, " ");
		free(tools->args);
		tools->args = input;
		if (!tools->args)
			return (exit_code());
		else if (ft_strcmp(tools->args, "") == 0)
			free(tools->args);
		else
		{
			add_history(tools->args);
			if (!handle_quotes(tools->args))
			{
				token_reader(tools);
				parser(tools);
			}
			tools_reload(tools);
		}
	}
	return (0);
}
