#include <stdlib.h>

int	ft_strlen(char *s)
{
	int i = 0;
	while (s[i])
		i++;
	return i;
}

char	**ft_chunks(char *str, int n)
{
	char	**cpy;
	int	s;
	int	z;
	int	i;
	int	ic;

	if (str == NULL || n <= 0)
		return NULL;
	s = ft_strlen(str);
	z = s / n;
	if (s % n != 0)
		z++;
	cpy = malloc(sizeof(char *) * (z + 1));
	if (cpy == NULL)
		return NULL;
	i = 0;
	ic = 0;
	while (str[i])
	{
		cpy[ic]	= donc cpy ic c la str pas le caractere, et il va prendre le malloc de chaque str, apres ca deviebndra cpy[ic][ic25
		]
	}
}
