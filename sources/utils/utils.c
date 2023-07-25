/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 12:58:17 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/07/25 11:03:03 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		return (error_msg("unclosed quotation mark\n"));
	}
	return (0);
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	check_input_end(char c)
{
	if (c == '<' || c == '>')
		return (0);
	return (1);
}

int	check_input(t_toolbox *tools)
{
	char	*aux;
	char	*aux_input;
	char	*input;

	input = readline("minishell>");
	while (input[ft_strlen(input) - 1] == '|')
	{
		aux = readline(">");
		aux_input = ft_strjoin(input, aux);
		free(aux);
		free(input);
		input = aux_input;
	}
	if (!check_input_end(input[ft_strlen(input) - 1]))
	{
		free(input);
		return (error_msg("sintax parse error\n"));
	}
	tools->args = input;
	input = ft_strtrim(tools->args, " ");
	free(tools->args);
	tools->args = input;
	return (0);
}
