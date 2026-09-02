#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int	ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return i;
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

int	main(int argc, char **argv)
{
        int     i;
        int     i2;
        int     total;
        int     trouve;

        if (argc != 3)
        {
                ft_putchar('\n');
 		return (0);
        }
	i = 0;
	total = 0;
	i2 = i;
	while (argv[1][i])
	{
		trouve = 0;
		while (argv[2][i2] != '\0' && trouve == 0)
		{
			if (argv[1][i] == argv[2][i2])
			{
				trouve = 1;
				total++;
			}
			i2++;
		}
		i++;
	}
	if (ft_strlen(argv[1]) == total)
		putstr(argv[1]);
	ft_putchar('\n');
	return (0);
}
