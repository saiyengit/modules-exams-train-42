#include <stdlib.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char    *ft_strdup(char *src)
{
	char	*cpy;
	int	i;
	
	i = 0;
	cpy = malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (cpy == 0)
		return (NULL);
	while (src[i])
	{
		cpy[i] = src[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}
