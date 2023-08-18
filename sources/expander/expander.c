/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 08:40:43 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/08/18 09:15:43 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*char	*close_quote(char *str)
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
}*///codigo reutilizable para echo built-in

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

int	var_search(char **gvars, char *var)
{
	int	pos;

	pos = 0;
	while (gvars[pos])
	{
		if (ft_strnstr(gvars[pos], var, ft_strlen(var)))
			return (pos);
		pos++;
	}
	return (-1);
}

char	*extract_var(char **vars, char *str, int quote)
{
	int		part;
	int		var_pos;
	char	*var;
	char	**s_var;

	part = 0;
	if (quote == 1)
	{
		if (str[0] == '\"')
			part = 1;
		var = ft_substr(str, 2, ft_strlen(str) - 3);
	}
	else
		var = ft_substr(str, 1, ft_strlen(str) - 1);
	var_pos = var_search(vars, var);
	if (var_pos >= 0)
	{
		s_var = ft_split(vars[var_pos], '=');
		return (s_var[part]);
	}
	else
		return (NULL);
}

char	*expander(t_toolbox *tools, char *str)
{
	char	*var;

	var = NULL;
	if (str[0] == '\'' || str[0] == '\"')
	{
		if (check_quotes(str) == 1 && str[1] == '$')
			var = extract(tools->env, str, 1);
		else
		{
			error_msg("Global var sintax error");
			return (NULL)
		}
	}
	else if (str[0] == '$')
		var = extract_var(tools->env, str, 0);
	return (var);
}
