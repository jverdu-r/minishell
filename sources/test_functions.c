#include "../includes/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	a;
	int	res;

	a = 0;
	while (s1[a] != 0 && s2[a] != 0 && s1[a] == s2[a])
		a++;
	res = s1[a] - s2[a];
	return (res);
}
