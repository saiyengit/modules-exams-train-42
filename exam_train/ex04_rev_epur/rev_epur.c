#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int	spacetab(char c)
{
	if (c == ' ' || c == '\t')
		return 1;
	return 0;
}

int	ft_debutword(char *str, int i)
{
	if ((i == 0 && spacetab(str[i]) == 0)
		|| (i > 0 && spacetab(str[i]) == 0 && spacetab(str[i - 1]) == 1))
		return 1;
	return 0;
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		ft_putchar(str[i]);
		i++;
	}
}

char	*ft_cpystr(char *dest, char *src)
{
	int	i;
	int	i2;

	i = 0;
	i2 = 0;
	while (spacetab(src[i]) == 1)
		i++;
	if (src[i] == '\0')
	{	dest[0] = '\0';
		return dest;
	}
	dest[i2++] = src[i++];
	while (src[i])
	{
		if (spacetab(src[i]) == 0 && spacetab(src[i - 1]) == 0)
			dest[i2++] = src[i++];
		else if (spacetab(src[i]) == 0 && spacetab(src[i - 1]) == 1)
		{
			dest[i2++] = ' ';
			dest[i2++] = src[i++];
		}
		else if (spacetab(src[i]) == 1)
			i++;
	}
	dest[i2] = '\0';
	return dest;
}

char	*rev1all(char *newdest, char *clean_epur)
{
	int	i;
	int	i2;

	i = 0;
	i2 = 0;
	while (clean_epur[i])
		i++;
	i--;
	while (i >= 0)
	{
		newdest[i2++] = clean_epur[i--];
	}
	newdest[i2] = '\0';
	return newdest;
}

char	*rev_epur(char *bad_reversed)
{
	int	i;
	int	m;
	int	n;
	char	temp;

	i = 0;
	while (bad_reversed[i])
	{
		if (ft_debutword(bad_reversed, i) == 1)
		{
			n = i;
			while (bad_reversed[i] && spacetab(bad_reversed[i]) == 0)
			{
				i++;
			}
			i--;
			m = i;
			while (m > n)
			{
				temp = bad_reversed[m];
				bad_reversed[m] = bad_reversed[n];
				bad_reversed[n] = temp;
				m--;
				n++;
			}
		}
		i++;
	}
	return bad_reversed;
}

int	main(int argc, char **argv)
{
	char dest[10000];
	char ndest[10000];
	if (argc != 2)
	{
		ft_putchar('\n');
		return (0);
	}
	ft_cpystr(dest,argv[1]);
	rev1all(ndest,dest);
	rev_epur(ndest);
	ft_putstr(ndest);
	ft_putchar('\n');
	return 0;
}
