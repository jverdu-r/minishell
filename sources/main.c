/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daparici <daparici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 10:28:15 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/06/22 20:26:24 by daparici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	leaks(void)
{
	system("leaks minishell");
}

int	main(int argc, char **argv, char **envp)
{
	t_toolbox	tools;

	atexit(leaks);
	if (argc != 1 || argv[1])
	{
		printf("Minishell must be executed wihtout arguments");
		exit(0);
	}
	//tools.env = (t_env *)malloc(sizeof(t_env));
	envp_dup(envp, &tools);
	tools_load(&tools);
	pwd_search(&tools);
	//minishell_loop(&tools);
	return (0);
}
