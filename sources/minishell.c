/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:15:26 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/05/24 15:33:19 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char	*input;
	int		loop;

	rl_on_new_line();
	loop = 1;
	while (loop != 0)
	{
		input = readline("minishel>");
		add_history(input);
		loop = ft_strcmp(input, "EXIT");
		if (loop == 0)
		{
			clear_history();
			free(input);
		}
		else
		{
			printf("%s\n", input);
			free (input);
		}
	}
	return (0);
}
