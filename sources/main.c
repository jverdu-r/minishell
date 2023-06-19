/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daparici <daparici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 10:28:15 by jverdu-r          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/06/19 19:34:40 by jverdu-r         ###   ########.fr       */
=======
/*   Updated: 2023/06/19 19:28:44 by daparici         ###   ########.fr       */
>>>>>>> 36aa9fb6edf5fffe18dd470af13bdfadc06e7616
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
<<<<<<< HEAD
	tools.envp = envp_dup(envp)
=======
	tools.envp = envp_dup(envp, &tools);
>>>>>>> 36aa9fb6edf5fffe18dd470af13bdfadc06e7616
	tools_load(&tools);
	pwd_search(&tools);
	minishell_loop(&tools);
	return (0);
}
