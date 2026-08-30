#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int	is_spacetab(char c)
{
	if (c == '\t' || c == ' ')
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc != 2)
	{
		ft_putchar('\n');
		return (0);
	}
	while (is_spacetab(argv[1][i]) == 1)
	{
		i++;
	}
	if (argv[1][i] == '\0')
	{
		ft_putchar('\n');
		return (0);
	}
	while (is_spacetab(argv[1][i]) == 0 && argv[1][i] != '\0')
	{
		ft_putchar(argv[1][i]);
		i++;
	}
	ft_putchar('\n');
	return (0);
}
