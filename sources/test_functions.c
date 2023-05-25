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

int	ft_strlen(const char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_wordcount(char const *str, char c)
{
	int	res;
	int	trig;

	res = 0;
	trig = 0;
	if (!str)
		return (0);
	while (*str)
	{
		if (*str != c && trig == 0)
		{
			trig = 1;
			res++;
		}
		else if (*str == c)
			trig = 0;
		str++;
	}
	return (res);
}

char	*ft_word(char const *str, int st, int end)
{
	char	*ptr;
	int		i;
	
	i = 0;
	ptr = malloc(sizeof(char) * (end - st + 1));
	if (!ptr)
		return (0);
	while (st < end)
	{
		ptr[i] = str[i];
		i++;
		st++;
	}
	ptr[i] = 0;
	return (ptr);
}

char	**ft_split(char const *str, char c)
{
	int		index;
	size_t	a;
	int		i;
	char	**split;

	split = malloc(sizeof(char *) * (ft_wordcount(s, c) + 1));
	if (!split)
		return (0);
	index = -1;
	a = 0;
	i = 0;
	while (a <= ft_strlen(str))
	{
		if (str[a] != c && index < 0)
			index = a;
		else if ((str[a] == c || a == ft_strlen(str)) && index >= 0)
		{
			split[i++] = ft_word(str, index, a);
			index = -1;
		}
		a++;
	}
	split[i] = 0;
	return (split);
}
