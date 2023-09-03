/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 08:40:43 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/08/14 09:03:38 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*expander(t_toolbox *tools, char *str)
{
	int		i;
	int		j;
	char	*aux;

	j = 0;
	if ((str[0] == '\'' || str[0] == '\"') && str[1] == '$')
	{
		i = 1;
		while (str[i] && str[i] != str[0])
			i++;
		if (str[i] == '\0')
		{
			printf("\nerror unclosed quotes\n");
			return (NULL);
		}
		else
		{
			aux = malloc(sizeof(char) * (i - 2));
			if (!aux)
				return (NULL);
			i = 2;
			while (str[i] && str[i] != str[0])
			{
				aux[j] = str[i];
				i++;
				j++;
			}
			aux[j] = '\0';
		}
		return (aux);
	}
	return (NULL);
}
