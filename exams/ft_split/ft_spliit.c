#include <stdlib.h>

int	issep(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (1);
	return (0);
}

int	debut_word(char *str, int i)
{
	if ((i == 0 && issep(str[i]) == 0)
		|| (i > 0 && issep(str[i]) == 0
			&& issep(str[i - 1]) == 1))
		return (1);
	return (0);
}

int	count_words(char *str)
{
	int	i;
	int	total;

	i = 0;
	total = 0;
	while (str[i])
	{
		if (debut_word(str, i) == 1)
			total++;
		i++;
	}
	return (total);
}

int	wordlen(int start, char *str)
{
	int	len;

	len = 0;
	while (str[start] && issep(str[start]) == 0)
	{
		start++;
		len++;
	}
	return (len);
}

char	*extract_word(char *str, int start)
{
	char	*cpy;
	int		ic;

	ic = 0;
	cpy = malloc(sizeof(char) * (wordlen(start, str) + 1));
	if (cpy == 0)
		return (NULL);
	while (str[start] && issep(str[start]) == 0)
		cpy[ic++] = str[start++];
	cpy[ic] = '\0';
	return (cpy);
}

char	**split(char *str)
{
	char	**res;
	int		i;
	int		ir;
	int		i2;

	i = 0;
	ir = 0;
	res = malloc(sizeof(char *) * (count_words(str) + 1));
	if (res == 0)
		return (NULL);
	while (str[i])
	{
		if (debut_word(str, i) == 1)
		{
			res[ir] = extract_word(str, i);
			if (res[ir] == NULL)
			{
				i2 = 0;
				while (i2 < ir)
				{
					free(res[i2]);
					i2++;
				}
				free(res);
				return (NULL);
			}
			ir++;
		}
		i++;
	}
	res[ir] = NULL;
	return (res);
}
