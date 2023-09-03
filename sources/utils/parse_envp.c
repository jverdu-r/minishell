/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daparici <daparici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 12:33:17 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/06/22 20:21:58 by daparici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pwd_search(t_toolbox *tools)
{
	int	i;

	i = 0;
	while (tools->env[i])
	{
		if (!ft_strncmp(tools->env[i], "PWD=", 4))
			tools->pwd = ft_substr(tools->env[i],
					4, ft_strlen(tools->env[i]) - 4);
		if (!ft_strncmp(tools->env[i], "OLDPWD=", 7))
			tools->old_pwd = ft_substr(tools->env[i],
					7, ft_strlen(tools->env[i]) - 7);
		i++;
	}
	return (i);
}

/*char	**st_envp(t_toolbox *tools, char **envp)
{
	int		i;
	int		k;
	char	*index;
	char	**sort_env;

	i = 0;
	while (envp[i])
		i++;
	index = ft_calloc(sizeof(int), i);
	sort_env = ft_calloc(sizeof(char *), i + 1);
	
}*/
t_env	*env_lstlast(t_env *lst)
{
	t_env	*temp;

	if (!lst)
		return (NULL);
	temp = lst;
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}

void	env_lstadd_back_m(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (lst)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			tmp = env_lstlast(*(lst));
			tmp->next = new;
		}
	}
}

t_env	*env_lstnew_m(char *content)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	new->var = ft_strdup(content);
	if (!new->var)
	{
		free_arr(new->var);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}

void	ft_lstlast_p_2(t_env *lst)
{
	while (lst)
	{
		printf("%s\n", lst->var);
		lst = lst->next;
	}
}

void	envp_dup(char	**envp, t_toolbox *tools)
{
	int		i;
	t_env	*new;
	t_env	*start;

	start = tools->env;
	i = 0;
	while (envp[i])
	{
		new = ft_lstnew_m(envp[i]);
		ft_lstadd_back(&tools->env, new);
		i++;
	}
	tools->env = start;
	ft_lstlast_p_2(tools->env);
	//tools->sort_env = st_envp(tools, envp);
}
