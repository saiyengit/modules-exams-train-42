#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int	main(int argc, char **argv)
{
	int	i;
	int	i2;
	int	id;
	int	trouve;

	i = 0;
	if (argc != 3)
	{
		ft_putchar('\n');
		return (0);
	}
	while (argv[1][i])
	{
		trouve = 0;
		i2 = 0;
		while (argv[2][i2])
		{
			if (argv[1][i] == argv[2][i2])
			{
				id = i - 1;
				while (id < i && trouve == 0)
				{
					if (argv[1][id] == argv[1][i])
						trouve = 1;
					id++;
				}
				id = i2 - 1;
				while (id < i2 && trouve == 0)
				{
					if (argv[2][id] == argv[2][i2])
						trouve = 1;
					id++;
				}
				if (trouve == 0)
					ft_putchar(argv[1][i]);
			}
			i2++;
		}
		i++;
	}
	ft_putchar('\n');
	return (0);
}
