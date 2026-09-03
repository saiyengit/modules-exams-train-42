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
	int i = 0;
	int i2 = 0
	
	while (spacetab(src[i]) == 1)
	i++;

	while (src[i])
	{
		if (spacetab(src[i]) == 0)
			dest[i2++] = src[i];
		else
		{
			while (spacetab(src[i]) == 1)
				i++;
			if (src[i] != '\0')
			{
				dest[i2++] = ' ';
				dest[i2++] = ' ';
				dest[i2++] = ' ';
			}
			i--;
		}
		i++;
	}
	dest[i2] = '\0';
	return dest;
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
