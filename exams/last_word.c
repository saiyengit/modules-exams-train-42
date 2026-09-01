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

int	debutword(char *str, int i)
{
	if ((i == 0 && spacetab(str[i]) == 0) 
			|| (i > 0 && spacetab(str[i - 1]) == 1))
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
	while (spacetab(argv[1][i]) == 1)
		i++;
	while (argv[1][i] != '\0' && spacetab(argv[1]) == 0)
	{
	}
