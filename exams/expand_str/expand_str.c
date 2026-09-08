#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int	spacetab(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

void	putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
}

char	*cpystr(char *dest, char *src)
{
	int	i;
	int	i2;

	i = 0;
	i2 = 0;
	while (spacetab(src[i]) == 1)
		i++;
	if (src[i] == '\0')
	{
		dest[0] = '\0';
		return (dest);
	}
	dest[i2++] = src[i++];
	while (src[i] != '\0')
	{
		if (spacetab(src[i]) == 0 && spacetab(src[i - 1]) == 0)
			dest[i2++] = src[i++];
		if (spacetab(src[i]) == 0 && spacetab(src[i - 1]) == 1)
		{
			dest[i2++] = ' ';
			dest[i2++] = ' ';
			dest[i2++] = ' ';
			dest[i2++] = src[i++];
		}
		if (spacetab(src[i]) == 1)
			i++;
	}
	dest[i2] = '\0';
	return (dest);
}

int	main(int argc, char **argv)
{	
	char	cpy[100];

	if (argc != 2)
	{
		ft_putchar('\n');
		return (0);
	}
	cpystr(cpy, argv[1]);
	putstr(cpy);
	ft_putchar('\n');
	return (0);
}
