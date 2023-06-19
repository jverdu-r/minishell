/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 12:58:17 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/06/19 18:07:21 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error_msg(char *msg)
{
	printf("ERROR: %s", msg);
}

int	handle_quotes(char *input)
{
	int	qt;
	int	i;

	qt = -1;
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			qt = i;
			i++;
			while (input[i] != input[qt] && input[i])
				i++;
			if (input[i] == input[qt])
				qt = -1;
		}
		i++;
	}
	if (qt != -1)
	{
		error_msg("unclosed quotation mark\n");
		return (1);
	}
	return (0);
}

void	free_arr(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
}
