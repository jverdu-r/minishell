/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 12:14:37 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/06/17 13:30:50 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	while (1)
	{
		signals_workout();
		tools->args = readline("minishell>");
		if (!tools->args)
			return (exit_code());
		else if (ft_strcmp(tools->args, "") == 0)
			free(tools->args);
		else
		{
			add_history(tools->args);
			printf("\n%s\n", tools->args);
			free(tools->args);
		}
	}
	return (0);
}
