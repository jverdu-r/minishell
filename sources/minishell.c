/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:15:26 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/06/07 13:06:12 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char *argv[])
{
	char	*input;
	int		loop;

	(void)argc;
	(void)argv;
	rl_on_new_line();
	loop = 1;
	while (loop != 0)
	{

		input = readline("minishell>");
		add_history(input);
		loop = ft_strcmp(input, "EXIT");
		if (loop == 0)
		{
			clear_history();
			free(input);
		}
		else
		{
			
			input_filter(input);
			//get_cmds(ft_split(input, ' '));
			free (input);
		}
	}
	return (0);
}
