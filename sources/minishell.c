/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:15:26 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/06/08 15:27:50 by jverdu-r         ###   ########.fr       */
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
//	int		loop;

	atexit(leaks);
	(void)argc;
	(void)argv;
	rl_on_new_line();
//	loop = 1;
	while (1)
	{
		signals_do();
		input = readline("minishell>");
		add_history(input);
		if (input == NULL)
			return (exit_code());
	//	loop = ft_strcmp(input, "EXIT");
	/*	if (loop == 0)
		{
			clear_history();
			free(input);
		}*/
		else
		{
			
			input_filter(input);
			//get_cmds(ft_split(input, ' '));
			free (input);
		}
	}
	return (0);
}
