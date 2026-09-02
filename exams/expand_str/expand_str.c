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

int	main(int argc, char **argv)
{
	int	i;
	
	i = 0;
	if (argc != 2)
	{
		ft_putchar('\n');
		return (0);
	}
	while (spacetab(argv[1][i]) == 1)
		i++;
	while (argv1[1][i])
	{
		if (spacetab(argv[1][i]) == 0)
			ft_putchar(argv[1][i]);
		else if (spacetab(argv[1][i]) == 1)	
		{
			ft_putchar(' ');
			ft_putchar(' ');
			ft_putchar(' ');
		}
		i++;
	}
	while (spacetab(argv[1][i]) == 1)
	{
		i--;
		ft_putchar()
	}
}
