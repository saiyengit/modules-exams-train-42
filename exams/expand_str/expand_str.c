#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int	spacetab(char c)
{
	if (c == ' ' && c == '\t')
		return (1);
	return 0;
}

char	*cpystr(char *dest, char *src)
{
	int	i;
	int	i2;

	i = 0;
	i2 = 0;
	while (spacetab(src[i]) == 1)
		i++;
	while (src[i])
	{
		if (spacetab(src[i]) == 0)
			dest[i2] = src[i];
		if (spacetab(src[i]) == 1)
		{	
			dest[i2] = ' ';
			i2++;
			dest[i2] = ' ';
			i2++;
			dest[i2] = ' ';
			i2++;
			while (spacetab(src[i]) == 1)
				i++;
		}
		if (spacetab(src[i - 1]) == 1)
			i--;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	main(int argc, char **argv)
{
	int	i;
	char    cpy[1000];
	
	i = 0;
	if (argc != 2)
	{
		ft_putchar('\n');
		return (0);
	}
