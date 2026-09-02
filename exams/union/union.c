#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int	est_doublon(int limite, char c, char *str)
{
	int	id;

	id = 0;
	while (id < limite)
	{
		if (c == str[id])
			return (1);
		id++;
	}
	return (0);
}

void	gererstr1(char *str1)
{
	int	i;

	i = 0
	while (str1[i])
	{
		if (est_doublon(i, str1[i], str) == 0)
			ft_putchar(str1[i]);
		i++;
	}
}

void	gererstr2(char *str1, char *str2)
{
	int	len1;
	int	i2;
	
	len1 = 0;
	i2 = 0;
	while (str1[len1])
		len1++;
	while (str2[i2])
	{
		if ((est_doublon(i2, str2[i2], str2) == 0) 
				&& (est_doublon(len1, str2[i2], str1) == 0))
			ft_putchar(str2[i2]);
		i2++;
	}
}

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		ft_putchar('\n');
		return (0);
	}
	gererstr1(argv[1]);
	gererstr2(argv[2]);
	ft_putchar('\n');
	return (0);

