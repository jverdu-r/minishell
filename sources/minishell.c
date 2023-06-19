/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daparici <daparici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:15:26 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/06/08 16:49:04 by daparici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exit_code(void)
{
	rl_clear_history();
	printf("EXIT\n");
	exit(0);
}

void	leaks(void)
{
	system("leaks minishell");
}

int	main(int argc, char *argv[])
{
	char	*input;

	atexit(leaks);
	(void)argc;
	(void)argv;
	rl_on_new_line();
	while (1)
	{
		signals_workout();
		input = readline("minishell>");
		add_history(input);
		if (input == NULL)
			return (exit_code());
		else
		{
			input_filter(input);
			//get_cmds(ft_split(input, ' '));
			free (input);
		}
	}
	return (0);
}
