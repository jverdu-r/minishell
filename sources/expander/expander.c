/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 08:40:43 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/08/17 10:01:48 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*close_quote(char *str)
{
	char	input;
	char	*aux;
	char	*temp;

	if (!str)
		return (NULL);
	input = readline(">");
	while (input[ft_strlen(input) - 1] != str[0])
	{
		aux = readline(">");
		temp = input;
		input = ft_strjoin(temp, aux);
		free(temp);
		free(aux);
	}
	temp = str;
	str = ft_strjoin(temp, input);
	free(temp);
	free(input);
	return(str);
}

int	check_quotes(char *str)
{
	int	i;

	if (!str)
		return (0);
	if (str[0] == '\"' || str[0] == '\'')
	{
		i = 1;
		while (str[i])
		{
			if (str[i] == str[0])
			return (1);
			i++;
		}
		if (str[i] == '\0')
			return (2);
	}
	else
		return (0);
}

char	*extract_var(char **vars, char *str)
{
	if (!str)
		return (NULL);
	if (str[0] != '$')
		return (str);
}

char	*expander(t_toolbox *tools, char *str)
{
	int		quote_ck;
	char	*var;

	quote_ck = 0;
	if (str[0] == '\'' || str[0] == '\"')
	{
		quote_ck = check_quotes(str);
		if (quote_ck == 2)
		{
			var = close_quote(str);
		}
		else
			var = str;
		return (extract_var(tools->env,
					ft_substr(var, var[1], ft_strlen(var) - 2)));
	}
	else if (str[0] == '$')
		return (extract_var(tools->env, str));
}
/*
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
}*/
