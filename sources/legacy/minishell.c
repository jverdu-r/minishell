/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:15:26 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/06/17 10:47:27 by jverdu-r         ###   ########.fr       */
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
		if (!input)
			return (exit_code());
		else if (ft_strcmp(input,  "") == 0)
			free(input);
		else
		{	
			add_history(input);
			get_cmds(input_filter(input));
			free (input);
		}
	}
	return (0);
}
