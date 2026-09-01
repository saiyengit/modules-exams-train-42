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

	i2 = 0;
	if (argc != 3)
	{
		ft_putchar('\n');
		return (0);
	}
	while (argv[2][i2])
	{
		if (argv[1][0] == argv[2][i2])
			ft_putchar(argv[1][0]);
		i2++;
	}
	i = 1;
	while (argv[1][i])
	{
		i2 = 0;
		while (argv[2][i2])
		{
			if (argv[1][i] == argv[2][i2])
			{
				id = 0;
				while (id < i && trouve == 0)
				{
					if (argv[1][id] == argv[1][i])
						trouve == 1;
					id++;
				}
				if (trouve == 1)
					ft_putchar(argv[1][i]);
			}
			i2++;
		}
		i++;
	}
	ft_putchar('\n');
	return (0);
}
