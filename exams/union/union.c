#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int	est_doublon(int limite, char c, char *str)
{
	int	id;

	id = 0;
	while (id <= limite)
	{
		if (c == str[id])
			return (1);
	}
	return (0);
}

void	gererstr1(char *str1)
{
	int	i;

	i = 0
	while (str1[i])
	{
		if (est_doublon(i, str1[i], str) == 1)
		{
			ft_putchar()			
		}
	}
}

void	gererstr2(char *str1, char *str2)

int	main(int argc, char **argv)
{

}
